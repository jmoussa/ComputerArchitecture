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
	Node* prev;
	if(front==NULL){
		front = (Node*)malloc(sizeof(Node));
		front->data=new_data;
		front->next=NULL;
	}else if(front->data > new_data){
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->data = new_data;
		newNode->next = front;
		return newNode;
	}else{
		Node* temp=front;
		while(temp!=NULL){
			if(temp->data == new_data){ //duplicates
				return front;
			}else if(temp->data > new_data){
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->data = new_data;
				newNode->next = prev->next;
				prev->next = newNode;
				return front;
			}
			prev = temp;
			temp = temp->next;
		}
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->data = new_data;
		newNode->next=NULL;
		prev->next = newNode;

		return front;
		
	}
	return front;
}


Node* deleteNode(Node* front, int key){
	Node* temp = front;
	Node* prev = front;
	if(front == NULL){
		return front;
	}
	if(front->data == key){
		return front->next;
	}
	while(temp != NULL){
		if(temp->data == key){
			prev->next = temp->next;
			return front;
		}
		prev=temp;
		temp=temp->next;
	}
	return front;
}

//main method
int main(int argc, char ** argv){
	if(argc!=2){
		printf("error\n");
		return 0;
	}

	Node* front=NULL;
	
	FILE *file = fopen( argv[1], "r" );
	char decision;
	int value;

	if ( file == 0 ){
        printf( "\n" );
		return 0;
    }
	while(fscanf(file, "%c %d\n", &decision, &value)==2){
			
		if(decision=='i'){
			front = insertNode(front, value);
		}else if(decision == 'd'){
			front = deleteNode(front, value);
		}else{
			return 0;
		}
	}
	if(!feof(file)){
		printf("error");
		return 0;
	}
	while(front != NULL){
		printf("%d\t", front->data);
		front = front->next;
	}
    
	fclose(file);
	free(front);
	return 0;
}
