#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char ** argv){
	if(argc>2 || argc<2){
		printf("error\n");
		return 0;
	}
	
	FILE* file = fopen(argv[1],"r");
	if(file==0){
		printf("\n");
		fclose(file);
		return 0;
	}else{
			int m,n,i,j;
			fscanf(file, "%d %d", &m, &n);

			int first[m][n], second [m][n], total[m][n];
			
			for(i=0;i<m;i++){
				for(j=0;j<n;j++){
					fscanf(file, "%d", &first[i][j]);
				}
			}

			for(i=0;i<m;i++){
				for(j=0;j<n;j++){
					fscanf(file, "%d", &second[i][j]);
				}
			}

			for(i=0;i<m;i++){
				for(j=0;j<n;j++){
					total[i][j] = first[i][j] + second[i][j];
					printf("%d\t", total[i][j]);	
				}
				printf("\n");
			}

	}

	fclose(file);
	return 0;
}
