#ifndef _first_h
#define _first_h

typedef struct node{
  int alpha;
  char *word;
  int wordCt;
  int prefCt;
  struct node* children[26];
} node;

void readDic(FILE *file);
void readFile(FILE *file);
node* makeNode();
void addDicWord(char* word);
void matchString(char* string);
void result();
void traverse(FILE *output, node* ptr);
void dealloc(node* ptr);



#endif
