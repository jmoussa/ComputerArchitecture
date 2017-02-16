#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char ** argv){
	int i, length;
	char* data;

	for(i = 1; i < argc; i++){
		data = argv[i];
		length = strlen(data);
		printf("%c", argv[i][length-1]);
					  
	}
	printf("\n");
	return 0;
}
