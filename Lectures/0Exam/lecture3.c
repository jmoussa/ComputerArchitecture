#include <stdio.h>
#include <stdlib.h>


//FUNCTION PROTOTYPE/SIGNATURE----------------------------------------------------------------------------------
void swap(int *, int *);

//SWAPS FUNCTION------------------------------------------------------------------------------------------------
void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main(int argc, char * argv[]){
	
	//POINTERS--------------------------------------------------------------------------------------------------
	int a,b;
	a=5;
	b=42;
	
	//initialized pointer
	//int *p = NULL;
	//p points to address in memory where a is
	//p = &a;

	a=5;
	b=42;
	swap(&a,&b);
	printf("A = %d , B = %d\n", a,b);
	
	//TAKING INPUT----------------------------------------------------------------------------------------------
	printf("Enter number for variable A and B\n");
	
	//Take a number input and assign it to an address of a variable in memory
	scanf("%d %d", &a, &b);
	swap(&a,&b);
	printf("A = %d , B = %d\n", a,b);
	
	//ARRAYS----------------------------------------------------------------------------------------------------
	int arr[100];
	//arr[0] is a pointer always bound to said location (in this case index 0)
	arr[0]=42;

	
	return 0;
}
