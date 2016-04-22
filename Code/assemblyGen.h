/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: typeChecker.h
* @Date:      2016-03-29 10:44:42
*/

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
void generateAssemblyCode(triple* currTriple,int len,const char* asmFile);
void combineCode(const char* asmFile);
void insert(char* temp);
int searchEntry(char* temp);



#endif