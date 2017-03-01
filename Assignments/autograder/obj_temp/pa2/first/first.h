#ifndef _first_h
#define _first_h

typedef struct node{
  int alpha;
  char *word;
  int wordCt;
  int prefixCt;
  struct node* children[26];
} node;

void readDict(FILE *dict_file);
void readFile(FILE *file);
node* makeNode();
void addDicWord(char* word);
void matchStr(char* str);
void printResult();
void traverse(FILE *output, node* ptr);
void dealloc(node* ptr);



#endif
