#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

typedef struct node{
	int value, height;
	struct node* left;
	struct node* right;
} Node;

void insert(Node* root, int key){
	if(root==NULL){
		root = (Node*)malloc(sizeof(Node));
		root->value = key;
		root->height = 1;
		printf("inserted 1\n");
		return;
	}
	if (root->value == key){
        printf("duplicate\n");
        return;
    }
    
    Node* temp = root;
    Node* before = root;
    int h = 1;
    
    while (temp != NULL){
        if (temp->value == key){
            printf("duplicate %d\n", temp->height);
            return;
        }else if (temp->value > key){
            before = temp;
            temp = temp->left;
            h++;
        }else{
            before = temp;
            temp = temp->right;
            h++;
        }
    }
    
    
    Node* newNode =(Node*) malloc(sizeof(Node));
    newNode->value = key;
    newNode->height = h;
    if (before->value > key){
        before->left = newNode;
    } else {
        before->right = newNode;
    }
    printf("inserted %d\n", h);
    return;		
}

void search(Node* root, int key){
	if(root==NULL){
		printf("absent\n");
		return;
	}
	if (root->value == key){
        printf("present 1\n");
        return;
    }
    Node* temp = root;
    while (temp != NULL){
        if (temp->value == key){
            printf("present %d\n", temp->height);
            return;
        }else if (temp->value > key){
            temp = temp->left;
        }else{
            temp = temp->right;
        }
    }
    printf("absent\n");
    return;
}

void rebalance(Node* root, int height){
	if(root == NULL){
		return;
	}  
	if (root->right != NULL){
		    rebalance(root->right, height+1);
	}
	if (root->left != NULL){
		    rebalance(root->left, height+1);
	}
	root->height = height;
	return;
}


Node* del(Node* root, int height){
	Node *left;
    Node *right = root->right;
 	Node *before = root;
    
  	if (root->right == NULL){
    	if(root->left == NULL){
      		root = NULL;
      		printf("success\n");
      		return root;
    	}
    	root = root->left;
    	rebalance(root, height);
    	printf("success\n");
    	return root;
  
  	}else{
    	if(right-> left != NULL){
     		while(right->left != NULL){
				before = right;
				right = right->left; 
     	 	}
      		before->left = NULL;
    	}
    	if(before != root){
      		if(right->right != NULL){
				left = right->right;
				before->left = left;
      		}
      		right->right = root->right;
    	}

    	if(root->left != NULL){
      		right->left = root->left;
    	}else{
      		right->left = NULL;
    	}

    	root = right;
    	rebalance(root, height);
    	printf("success\n");
    	return root;
  	}

}

Node* findMe(Node* root, int key){
	Node* temp = root;
	Node* before = NULL;

	while(temp!=NULL){
		if(temp->value == key){
			temp = del(temp, temp->height);
			if(before!=NULL){
				if(temp->value < before->value){
					before->left = temp;
				}else{
					before->right = temp;
				}
			}else{
				return temp;
			}
			break;
		}else if(temp->value > key){
			before = temp;
			temp = temp->left;
		}else{
			before = temp;
			temp = temp->left;
		}
	}
	if(temp==NULL){
		printf("fail\n");
	}
	return root;
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

	while(decision!='i'){
		printf("absent\n");
		fscanf(file, "%c %d\n", &decision, &num);
	}
	Node* root = (Node*)malloc(sizeof(Node));
	root->value = num;
	root->height = 1;
	printf("inserted 1\n");

	while(fscanf(file,"%c %d\n", &decision, &num)==2){
		if(decision=='i'){
			insert(root,num);
		}else if(decision=='s'){
			search(root,num);
		}else if(decision=='d'){
			root=findMe(root,num);
		}else{
			printf("error\n");
		}
	}

	return 0;
}
