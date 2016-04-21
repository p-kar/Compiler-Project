#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lexer.h"
//#include <parserDef.h>

#define INTSPACE 2
#define REALSPACE 4

typedef struct entry
{
	TERMINAL   type;   // example TK_INT etc the table remains the same as the one used earlier
	tokenInfo token;
	char recordType[100];
	struct entry* next;
	int offset;
	// storing the exact value can be a number can be something else
}entry;

typedef struct IdTable
{
	entry *entryArray[997] ;
}IdTable;

typedef struct funcIdTable
{
	IdTable table;
	char funcName[100];
	entry* inputParameterList;
	entry *outputParameterList;
	struct funcIdTable* next;
	int input_num;
	int output_num;
	int identifier;
}funcIdTable;

typedef struct funcTable
{
	funcIdTable *funcTableArray[997];

}funcTable;
typedef struct recordEntry
{
	entry* arr;
	char name[100];
	struct recordEntry* next;
	int identifier;

}recordEntry;

typedef struct recordTable
{
	recordEntry* arr[7];
	int next_identifer;
}recordTable;

typedef struct GlobalTable
{
	entry *entryArray[997] ;
	funcTable finalFuncTable;

}GlobalTable;



int computeHashVal(char* ch);
bool insertGlobalId(GlobalTable* table ,tokenInfo temp,TERMINAL type);
entry* findGlobalId(GlobalTable *table,char* name);
funcIdTable* insertFuncIdTable(GlobalTable* table , char* funcName);
funcIdTable* findFuncIdTable(funcTable *curr, char* curr_name);
bool insertLocalId(GlobalTable* global_table,funcIdTable* function_table,tokenInfo temp,TERMINAL type);
entry* findLocalId(funcIdTable* table,char* name);
void insertInputParameter(GlobalTable* g,funcIdTable* temp,tokenInfo tk,TERMINAL type);
void insertOutputParameter(GlobalTable* g, funcIdTable* temp,tokenInfo tk,TERMINAL type);
bool insertLocalId(GlobalTable* global_table,funcIdTable* function_table,tokenInfo temp,TERMINAL type);
entry* findLocalId(funcIdTable* table,char* name);



void insertRecord(char* name,recordTable* curr);
void insertRecordEntry(char* name,recordTable* curr,tokenInfo tk , TERMINAL type);
recordEntry* findRecordEntry(char* name,recordTable* curr);
recordEntry* getRecordEntry(int identifier,recordTable *table);

bool insertGlobalRecord(GlobalTable* table,tokenInfo temp,TERMINAL type, char* recordtype , recordTable* record_table);
bool insertLocalRecord(GlobalTable *t,funcIdTable *table , tokenInfo temp,TERMINAL type,char* recordtype , recordTable* record_table);

recordTable* initializeRecordTable();
GlobalTable* initalizeGlobalTable();
funcIdTable* initalizeLocalTable();
void displaySymbolTable(GlobalTable* t);
void insertInputParameterRecord(GlobalTable *g,funcIdTable* temp,tokenInfo tk,char* name,recordTable *currRecordTable);
void insertOutputParameterRecord(GlobalTable *g,funcIdTable* temp,tokenInfo tk,char* name,recordTable *currRecordTable);

#endif
