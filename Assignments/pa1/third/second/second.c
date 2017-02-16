//Linked List Sorting
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
struct Node{
	int data;
	struct Node * next;
};

typedef struct Node Node;


Node* insertNode(Node* front, int new_data){
	Node* new_node= (Node*)malloc(sizeof(Node));
	Node* ptr = front;
	Node* prev = front;
	new_node->data = new_data;
	//front has not been initialized by file and is therefore unassigned
	if(front == NULL){
		new_node->next=NULL;
		front = new_node;
		return front;
	}	

	if(front->next==NULL){
		if(front->data>new_data){
			new_node->next = front;
			front = new_node;
			return front;
		}
		if(front->data<new_data){
			new_node->next = NULL;
			front->next = new_node;
			return front;
		}
	}

	//Move up front ptr until it's greater than the new node
	while(ptr->data < new_data){
		prev = ptr;
		ptr = ptr->next;
	}
	//When front ptr is greater than new node, point new node.next to ptr
	if(ptr->data > new_data || new_data > prev->data){
		new_node->next = ptr;
		prev->next=new_node;
	}
	return front;	
}


void deleteNode(Node* front, int key){
	Node* temp = front;
	Node* prev = front;
	if(temp != NULL && temp->data == key){
		front = temp->next;
		free(temp);
		return;
	}

	while(temp != NULL && temp->data != key){
		prev = temp;
		temp = temp->next;
	}
	if(temp==NULL){
		return;
	}
	prev->next=temp->next;
	free(temp);
	return;
}

void printLL(Node* front){
	Node* ptr = front;
	while(ptr->next != NULL){
		printf("%d ", ptr->data);
		ptr = ptr->next;
	}
	if(ptr != NULL){
		printf("%d\n ", ptr->data);
	}
}
//main method
int main(int argc, char ** argv){
	if(argc<2 || argc>2){
		printf("error\n");
		return 0;
	}

	Node* front=NULL;
	
	Node* ptr =(Node*)malloc(sizeof(Node));
	ptr=front;
	

	FILE *file = fopen( argv[1], "r" );
	if ( file == 0 ){
        printf( "\n" );
    }else {
		while(!feof(file)){
			char decision[1];
			int value;
			fscanf(file, "%c %d\n", decision, &value);
			
			if(strncmp(decision, "i", 1)==0){
				ptr = insertNode(ptr, value);
			}else if(strncmp(decision, "d", 1)==0){
				deleteNode(ptr, value);
			}else{
				continue;
			}
		
		}
    }
	printLL(ptr);
	fclose( file );
	return 0;
}
