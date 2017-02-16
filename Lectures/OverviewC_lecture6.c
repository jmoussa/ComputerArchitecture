//LECTURE 6 C Programming Conclusion
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

//LL Node
struct node{
	char ch;
	int num;
	struct node* next;
};
typedef struct node Node;



int main(int argc, char ** argv){
	
	//COMMAND LINE INPUTS-----------------------------------------------------------------------------------------
	if(argc < 2){ //check how many arguments are given <program> <file>
		printf("No file name given\n");
		exit(0);
	}
	char* filename = argv[1]; //filename points to file
	FILE* fp = fopen(filename, "r"); //open filename file in 'read' mode
	
	//PARSING FILES-----------------------------------------------------------------------------------------------
	char ch;
	int num;
	while(fscanf(fp, "%c : %d\n", &ch, &num) != EOF){ //read character and integer and store values
		printf("%c : %d", ch, num);
	}		
	fclose(fp);
	
	//MEMORY ALLOCATION and LINKED LISTS--------------------------------------------------------------------------
	Node* start = NULL; //beginning of the LL
	Node* temp; //create a pointer to node called temp
	temp = (Node*)malloc(sizeof(Node)); //allocated memory/space for temp
	//Fill in Values
	temp->ch = ch;
	temp->num = num;
	temp->next = NULL;
	
	//Adding element at the beginning
	temp->next = start;
	start = temp; //reassign head of list
	
	//DEBUGGING---------------------------------------------------------------------------------------------------
	/*	
		 gcc -g -Wall -Werror	-fsanitize=address <file.c> -o <file>
		 gdb ./<file>
	
	Set a break point (stop when this break point is reached)
		break main
		break <file.c>:<line #>
	-Run Program
		run <argument>
	-Go to next Statement
		n    
	-Print variables
		print <argument>
	-Exit
		quit
	*/

	//POINTERS & STRINGS & CHARS----------------------------------------------------------------------------------
	//Strings must be terminated by '\0'
	



	return 0;
}
