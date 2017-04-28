#include <stdio.h>
#include "cache.h"
#include "runSim.h"
#include "validate.h"

int main(int argc, char**argv){
    Cache currentSim;
    if(argc == 5){
        int valid;
        validate = validate(argv[1],argv[2],argv[3],&currentSim);
        if(validate){
            if(currentSim.setSize > 1){
                printf("ERROR");
                return -1;
            }
            simulate(&currentSim,argv[4]);
            return 0;
        }
    }
    printf("ERROR: invalid arguments");
    return -1;
    
}
