/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: typeChecker.h
* @Date:      2016-03-29 10:44:42
*/

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

typedef struct tuple
{
    int len;
    int *arr;
}tuple;

void displayTriple();
int addTriple(char* op,int val1,int val2);
void addTriple2(char* op,int val1,int val2,int mylabel,int jumplabel);

#endif