#ifndef _ASSEMBLY_GEN_H_
#define _ASSEMBLY_GEN_H_

#define INF 1000000000

#include "codeGenDef.h"

typedef struct node
{
	char str[100];
	struct node* next;
}node;

void writeConstant(FILE* fp);
void readDirective(int option, triple t,FILE* fp);
void writeDirective(int option, triple t,FILE* fp);
void assignDirectiveZero(char* a,char* b ,FILE* fp);
void assignDirectiveOne(char* a,int b ,FILE* fp);
void arithDirective(char* op , int option , char* ans , char* val1,char* val2 ,FILE* fp);
void compareDirective(int option,char* op,int jump_label,char* val1,char* val2,FILE* fp);
void labelDirective(int label_index,FILE* fp);
void jumpDirective(int label_index,FILE* fp);
void generateAssemblyCode(triple* currTriple,int len);
void combineCode();
void insert(char* temp);
int searchEntry(char* temp);



#endif