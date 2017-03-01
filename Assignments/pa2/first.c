#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "first.h"

node* head;
int mlc = 1;

int main(int argc, char ** argv){
  FILE *file;
  char buffer[600];

  if(argc < 2 || !(file = fopen(argv[1],"r"))){
    printf("ERROR, Invalid Input \n");
    return 0;
  }
  while(fgets(buffer,sizeof(buffer),file)){
    FILE *dictionary;
    FILE *data;

    char* dicfunction=strtok(buffer," ");
    char* datafunction=strtok(NULL, " \n");

    head = NULL;
    dictionary = fopen(dicfunction, "r");
    if(!data){
      printf("ERROR, No Data File\n");
      return 0;
    }
    readFile(data);
    fclose(data);

    result();
    dealloc(head);
    mlc +=1;

  }
  fclose(file);
  return 0;
}


//Helper Functions
void readDic(FILE *file){
  char w;
  size_t cin = 0;
  char buffer[600];
  for(;;){
    if((w=fgetc(file))==EOF || !isalpha(w)){
      if(cin > 0){
        buffer[cin] = '\0';
        addDicWord(buffer);
        cin = 0;
      }
      if(w==EOF){
        break;
      }
    }else{
      buffer[cin++]=tolower(w);
    }
  }
}

void readFile(FILE *file){
	char w;
	size_t cin = 0;
	char buffer[600];

	for (;;) {
		if ((w = fgetc(file)) == EOF || !isalpha(w) ) {
			if (cin > 0) {
				buffer[cin] = '\0';
				matchStr(buffer);
				cin = 0;
			}
			if (w == EOF) break;
		}
		else {
			buffer[cin++] = tolower(w);
		}	
	}
}

node* makeNode(){
  node* newNode = (node*)malloc(sizeof(node));
  int i;

  newNode->alpha = -1;
  newNode->word = NULL;
  newNode->wordCt = 0;
  newNode->prefixCt = 0;

  for(i=0;i<26;i++){
    newNode->children[i] = 0;

  }
  return newNode;
}

void addDicWord(char* word){
  int i;
  node* ptr;
  int wordLen = strlen(word);
  
  if(!head){
    head = makeNode();
  }
  ptr = head;
  for(i=0;i<wordLen;i++){
    int x = tolower(word[i]) - 'a';

    if(!ptr->children[x]){
      ptr->children[x] = makeNode();
      ptr->children[x]->isalpha = x;
    }
    ptr = ptr->children[x];
  }
  ptr->word = (char*)malloc(sizeof(char)*(wordLen+1));
  for(i=0;i<wordLen;i++){
    ptr->word[x] = word[x];
  }
}

void matchString(char* string){
  int i;
  node* ptr;
  int stringLen = strlen(string);

  if(!head){
    return;
  }
  ptr=head;
  for(i=0;i<stringLen;i++){
    int x = tolower(string[i]) - 'a';
    if(!(ptr = ptr->children[x])){
      return;
    }
    if(ptr < stringLen -1){
      ptr->prefixCt+=1;
    }
    ptr->wordCt+=1;
  }
}

void result(){
  FILE *file;
  char filename[64];

  sprintf(filename, "out%d.txt", mlc);
  file = fopen(filename,"w");
  if(!file){
    printf("ERROR, NO FILE\n ");
    return;
  }
  traverse(file,head);
  fclose(file);
}

void traverse(FILE *output, node* ptr){
  int i;
  if(!ptr){
    return;
  }
  if(ptr->word){
    fprintf(output,"%s %d %d\n",ptr->word,ptr->wordCt,ptr->prefixCt);
  }
  for(i=0; i<26; i++){
    traverse(file, ptr->children[i]);
  }
}

void dealloc(node* ptr){
  int i;
  if(!ptr){
    return;
  }
  for(i=0;i<26;i++){
    dealloc(ptr->children[x]);
  }
  if(ptr->word){
    free(ptr->word);

  }
  free(ptr);
}
