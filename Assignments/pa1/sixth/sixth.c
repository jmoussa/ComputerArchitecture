#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char ** argv){
	int i;
	if(argc == 1){
		printf("error\n");
		return 0;
	}
	for(i=1;i<argc; i++){
		printf("%c",argv[i][0]);
	}
	printf("\n");

	return 0;
}
