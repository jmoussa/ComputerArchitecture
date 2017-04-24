#include <stdlib.h>
#include <stdio.h>
#include "cache.h"
#include <math.h>

void print();

typedef struct{
    int tag;
    int min;
    int max;
    int valid;
    int dirty;
} Line;

typedef struct{
    Line* baseLine;
    int size;
} Set;

FILE* trace;
int reads, writes, hits, misses;

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
    //100

}


