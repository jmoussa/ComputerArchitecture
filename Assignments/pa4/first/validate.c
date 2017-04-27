#include <stdio.h>
#include <string.h>
#include "cache.h"

int validArgs(char* cache, char* associativity, char* block, Cache* currentSim){
    int cacheSize = 0;
    int setSize = 0;
    int blockSize = 0;
    int sets = 0;

    cacheSize = validCache(cache);
    if(!cacheSize){
        return 0;
    }
    currentSim->cacheSize = cacheSize;

    setSize = validAss(associativity);
    if(!setSize){
        return 0;
    }
    currentSim->setSize = setSize;

    blockSize = validBlock(block);
    if(!blockSize){
        return 0;
    }
    currentSim->blockSize = blockSize;

    sets = cacheSize/(setSize*blockSize);
    if(sets==0){
        return 0;
    }
    currentSim->sets = sets;

    return 1;
}

int validCache(char* cache){
    int cacheSize;
    int numScan = sscanf(cache,"%d",&cacheSize);
    if(numScan == 0){
        return 0;
    }
    if(isPow2(cacheSize)){
        return cacheSize;
    }
    return 0;
}

int validAss(char* ass){
    int setSize;
    if(strcmp(ass, "-direct")==0){
        setSize = 1;
    }else if(strncmp(ass, "-assoc:",7)==0){
        setSize = strtol(ass,ass+7,10);
        if(!isPow2(setSize)){
            setSize = 0;
        }
    }
    return setSize;
}

int validBlock(char* block){
    int blockSize;
    int numScan = sscanf(block, "%d",&blockSize);
    if(numScan==0){
        return 0;
    }
    if(isPow2(blockSize)){
        return blockSize;
    }
    return 0;
}

int isPow2(int x){
    int i;
    for(i=0;i<31;i++){
        if(x == 1<<i){
            return 1;
        }
    }
    return 0;
}
