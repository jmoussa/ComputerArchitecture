#include <stdlib.h>
#include <stdio.h>
#include "cache.h"
#include <math.h>

typedef struct{
    int tag;
    int min;
    int max;
    int valid;
} Line;

typedef struct{
    Line* baseLine;
    int size;
} Set;

void printStatus();

FILE* trace;
int aReads, aWrites, aHits, aMisses;
int bReads,bWrites , bHits, bMisses;

int simulate(Cache * cache, char* traceFile){
    char line[50];
    char eip[20];
    char mode;
    int address;

    Set *currentSet;
    Set *baseSet;

    Line *currentLine;

    int setSize = cache->setSize;
    int numSets = cache->sets;
    int blockSize = cache->blockSize;
    
    int tag;
    int set;
    int blockOffset;

    int setBits;
    int blockBits;

    int blockSection;
    int setSection;
    int tagSection;

    blockSection = blockSize - 1;
    blockBits = log2(blockSize);
    setBits = log2(numSets);
    setSection = (numSets - 1)<<blockBits;
    tagSection = -1^setSection^blockSection;

    trace = fopen(traceFile, "r");
    if(!trace){
        printf("ERROR: Couldn't open tracefile");
        return 0;
    }
    baseSet = (Set*)malloc(numSets*sizeof(Set));
    int i;
    for(i=0;i<numSets;i++){
        currentSet = baseSet+i;
        currentSet->baseLine = (Line*)malloc(setSize*sizeof(Line));
    }
    currentSet = baseSet;

    while(fgets(line,50,trace)!=NULL){
        sscanf(line, "%s %c %x",eip, &mode,&address);
        //Type A
        blockOffset = address&blockSection;
        set = (address&setSection) >> blockBits;
        tag = ((address&tagSection)>>blockBits)>>setBits;

        currentSet = baseSet + set;
        for(i=0;i<setSize;i++){
            currentLine = currentSet->baseLine + i;

            if(currentLine->tag == tag){
                aHits++;
                if(mode=='W'){
                    aWrites++;
                }else{
                    aReads++;
                }
            }else{
                aMisses++;

                currentLine->tag = tag;
                currentLine->min = blockOffset-blockOffset%blockSize;
                currentLine->max = currentLine->min+blockSize;
                currentLine->valid = 1;
                if(mode=='W'){
                    aReads++;
                    aWrites++;
                }
            }
        }

        //Type B
        blockOffset = address&blockSection; 
        set = ((address&tagSection)>>blockBits)>>setBits;
        tag = (address&setSection) >> blockBits;
        currentSet = baseSet + set;
        for(i=0;i<setSize;i++){
            currentLine = currentSet->baseLine + i;

            if(currentLine->tag == tag){
                bHits++;
                if(mode=='W'){
                    bWrites++;
                }else{
                    bReads++;
                }
            }else{
                bMisses++;

                currentLine->tag = tag;
                currentLine->min = blockOffset-blockOffset%blockSize;
                currentLine->max = currentLine->min+blockSize;
                currentLine->valid = 1;
                if(mode=='W'){
                    bReads++;
                    bWrites++;
                }
            }
        }
    }

    for(i=0;i<numSets;i++){
        currentSet = baseSet+i;
        free(currentSet->baseLine);
    }
    free(baseSet);
    fclose(trace);
    printStatus();
    return 0;
}

void printStatus(){
    printf("Cache A\n");
    printf("Memory reads : %d\n",aReads);
    printf("Memory writes : %d\n",aWrites);
    printf("Cache hits : %d\n",aHits);
    printf("Cache misses : %d\n",aMisses);
    
    printf("Cache B\n");
    printf("Memory reads : %d\n",bReads);
    printf("Memory writes : %d\n",bWrites);
    printf("Cache hits : %d\n",bHits);
    printf("Cache misses : %d\n",bMisses);   
    return;
}


