//IS PRIME
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char**argv){
	if(argc < 2){
		printf("error\n");
		return 0;
	}	

	int num=atoi(argv[1]);

	if(num<=0){
		printf("error\n");
		return 0;
	}
	
	int i;
	for(i=2; i<num/2;i++){
		if(num%i==0){
			printf("no\n");
			return 0;
		}
	}
	printf("yes\n");
	return 0;
}
