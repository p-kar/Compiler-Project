#ifndef CODE_GEN_DEF_H
#define CODE_GEN_DEF_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct triple
{
	char op[100];
	int val1,val2;
	int mylabel;
	int jumplabel;

}triple;

void displayTriple();
void addTriple(char* op,int val1,int val2);
void addTriple2(char* op,int val1,int val2,int mylabel,int jumplabel);

#endif