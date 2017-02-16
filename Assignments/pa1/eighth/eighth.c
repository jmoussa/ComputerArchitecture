#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct node{
	int data, height;
	struct node* left;
	struct node* right;
} Node;

void search(Node* root, int key){
	if(root->data == key){
		printf("present 1\n");
		return;
	}
	Node* temp = root;
	while(temp!=NULL){
		if(temp->data == key){
			printf("present %d\n", temp->height);
		}else if(temp->data > key){
			temp = temp->left;
		}else{
			temp = temp->right;
		}
	}
	printf("absent\n");
	return;
}

void insert(Node* root, int key){
	if(root->data == key){
		printf("duplicate\n");
		return;
	}

	Node* temp = root;
	Node* before = root;
	int h = 1;

	while(temp!=NULL){
		if(temp->data==key){
			printf("duplicate %d\n", temp->height);
			return;
		}else if(temp->data > key){
			before = temp;
			temp = temp->left;
			h++;
		}else{
			before = temp;
			temp = temp->right;
			h++;
		}
	}
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = key;
	newNode->height=h;
	if(before->data > key){
		before->left = newNode;
	}else{
		before->right = newNode;
	}
	printf("inserted %d\n", h);
	return;
}


int main(int argc, char ** argv){
	char decision;
	int num;

	if(argc!=2){
		printf("error\n");
		return 0;
	}

	FILE* file = fopen(argv[1],"r");
	fscanf(file, "%c %d\n", &decision, &num);
	
	while(decision != 'i'){
		printf("absent\n");
		fscanf(file, "%c %d\n",&decision,&num);
	}
	Node* root = (Node*)malloc(sizeof(Node));
	root->data = num;
	root->height = 1;
	printf("inserted 1\n");

	while(fscanf(file, "%c %d\n", &decision, &num)==2){
		if(decision =='i'){
			insert(root, num);
		}else if(decision == 's'){
			search(root, num);
		}else{
			printf("error\n");
			continue;
		}
	}
		
	return 0;
}
