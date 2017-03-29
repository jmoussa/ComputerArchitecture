//LECTURE 4 Malloc and Strings
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char ** argv){
	//initialize array
/*	
	int ar[3]={1,2,3};
	
	int result=0;
	int num=0;
	printf("Enter number\n");
	scanf("%d",&num); //store value in the address of num
	if(num<3 && num>=0){
		result = ar[num];
	}
	printf("%d\n",result);
	

//DYNAMICALLY ALLOCATING AN ARRAY-------------------------------------------------------------------------------
	int *arr = NULL;
	int num;
	printf("Number of elements\n");
	scanf("%d",&num);
	
	//creates space in the heap for an integer array of size <num>
	arr = (int*)malloc(num*sizeof(int));
	for(int i=0; i<num; i++){
		arr[i]=i; //SAME AS *(arr+i)=i;
	}

	free(arr);
*/
//STRINGS-------------------------------------------------------------------------------------------------------
// char s[6]={'c','s','2','1','1','\0'}; OR char[6]="CS211"
//COMMAND LINE PARAMETERS---------------------------------------------------------------------------------------
	
	if(argc<2){
		printf("error\n");
	}
	//ASKEY to INTEGER
	int num = atoi(argv[1]);
	printf("argument number: %d\n",num);
	return 0;
}
