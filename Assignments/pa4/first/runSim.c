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

void printCache();

FILE* trace;
int aReads, aWrites, aHits, aMisses;
int bReads=0;
int bWrites=0;
int bHits=0;
int bMisses=0;

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
    int index;
    int blockOffset;

    int indexBits;
    int blockBits;

    int blockSection;
    int indexSection;
    int tagSection;

    blockSection = blockSize - 1;
    blockBits = log2(blockSize);
    indexBits = log2(numSets);
    indexSection = (numSets - 1)<<blockBits;
    tagSection = -1^indexSection^blockSection;

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
        sscanf(line, "%s %c %x", eip, &mode,&address);
        
        //Type A
        blockOffset = address&blockSection;
        index = (address&indexSection) >> blockBits;
        tag = ((address&tagSection)>>blockBits)>>indexBits;

        currentSet = baseSet + index;
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
        index = ((address&indexSection)>>blockBits)>>(address-blockBits-indexBits);
        tag = (address&tagSection) >> blockBits;
        
        currentSet = baseSet + index;
        
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
    printCache();
    return 0;
}

void printCache(){
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
