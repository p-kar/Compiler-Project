/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: symbolTable.h
* @Date:      2016-03-29 10:44:42
*/

#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include "parserDef.h"

typedef struct entry
{
	int   type;   // example TK_INT etc. the table remains the same as the one used earlier
	char name[100];   // the name of the variable example  a, #abc etc.
	char val[100];
	struct entry* next;
	// storing the exact value can be a number can be something else
}entry;

typedef struct IdTable
{
	entry *entryArray[997] ;

}IdTable;

int computeHashVal();
void insertId(IdTable* table , entry* new_entry);
entry* findId(IdTable *idTable,char* name);

// may need other but do not need the now

typedef struct funcIdTable
{
	IdTable table;
	char funcName[100];
	struct funcIdTable* next;

}funcIdTable;

// insert input and output parameters
typedef struct funcTable
{
	funcIdTable *funcTableArray[997];
}funcTable;

void insertFuncIdTable(funcTable *curr , funcIdTable *curr_funcidtable);
funcIdTable* findFuncIdTable(funcTable *curr, char* curr_functionname);
void deleteFuncIdTable(funcTable* curr , char* curr_funcName);

#endif
