#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

typedef struct node {
	int data;
	struct node* next;
} Node;

int check(Node* front, int key){
	if(front==NULL){
		return 0;
	}
	Node* temp = front;
	while(temp!=NULL){
		if(temp->data == key){
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}



Node* insertToHash(Node* front, int data) {
	if(front==NULL){
		front = (Node*)malloc(sizeof(Node));
		front->data = data;
		front->next = NULL;
		printf("inserted\n");
		return front;	
	}else{
		if(check(front,data)==1){
			printf("duplicate\n");
			return front;
		}
		Node* newNode;
		Node* temp = front;
		while(temp->next != NULL){
			temp=temp->next;
		}
		newNode = (Node*)malloc(sizeof(Node));
		newNode->data = data;
		temp->next = newNode;
		newNode->next = NULL;
		printf("inserted\n");
		return front;
	}

}


int main(int argc, char ** argv){
	Node* start = NULL;
	Node *hashtable[10000];

	if(argc!=2){
		printf("error\n");
		return 0;
	}
	
	FILE* file = fopen(argv[1],"r");
	char decision;
	int value, i;
	if(file==0){
		printf("\n");
		return 0;
	}
	for(i=0;i<10000;i++){
		hashtable[i]=NULL;
	}

	while(fscanf(file, "%c %d\n", &decision, &value)==2){
		int key;
		if(value>=0){
			key = (value%10000);
		}else{
			key = -(value%10000);
		}

		if(decision == 'i'){
			if(hashtable[key]==NULL){
				hashtable[key] = insertToHash(start, value);
			}else{
				Node* temp = hashtable[key];
				hashtable[key] = insertToHash(temp, value);
			}
		}else if(decision == 's'){
			if(hashtable[key]==NULL){
				printf("absent\n");
			}else{
				Node* temp = hashtable[key];
				if(check(temp, value)==0){
					printf("absent\n");
				}else{
					printf("present\n");
				}
			}
		}else{
			printf("error\n");
		}
	
	}
	fclose(file);	
	return 0;
}
