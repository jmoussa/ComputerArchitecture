#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char** argv){
	if (argc != 2){
		printf("error\n");
		return 0;
	}

	FILE *file = fopen(argv[1], "r");

	if(file == 0){
		printf("error\n");
		return 0;
	}

	int r1,c1,r2,c2;	
	fscanf(file, "%d %d", &r1, &c1);
	int m1[100][100];
	int m2[100][100];
	int result[100][100];
	int i, j, k, value = 0;

	for(i = 0; i < r1; i++){
		for(j = 0; j < c1; j++){
			fscanf(file, "%d", &m1[i][j]);
		}
		fscanf(file, "\n");
	}

	fscanf(file, "%d %d", &r2, &c2);
	for(i = 0; i < r2; i++){
		for(j = 0; j < c2; j++){
			fscanf(file, "%d", &m2[i][j]);
		}
		fscanf(file, "\n");
	}

	for(i = 0; i < r1; i++){
		for(j = 0; j < c2; j++){
			for(k = 0; k < r2; k++){
				value = value + m1[i][k] * m2[k][j];
			}
			result[i][j] = value;
			value = 0;
		}
	}

	for(i = 0; i < r1; i++){
		for(j = 0; j < c2; j++){
			printf ("%d\t", result[i][j]);
		}
		printf("\n");
	}

	return 0;
}
