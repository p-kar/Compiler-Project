#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lexer.h"
//#include <parserDef.h>


typedef struct entry
{
	TERMINAL   type;   // example TK_INT etc the table remains the same as the one used earlier
	tokenInfo token;
	char recordType[100];
	struct entry* next;
	// storing the exact value can be a number can be something else
}entry;


typedef struct IdTable
{
	entry *entryArray[997] ;
}IdTable;


int computeHashVal(char* ch);

//entry* findId(IdTable *idTable,char* name);

// may need other but do not need the now

typedef struct funcIdTable
{
	IdTable table;
	char funcName[100];
	entry* inputParameterList;
	entry *outputParameterList;
	struct funcIdTable* next;

}funcIdTable;


typedef struct funcTable
{
	funcIdTable *funcTableArray[997];

}funcTable;




//void deleteFuncIdTable(funcTable* curr , char* curr_funcName);



typedef struct recordEntry
{
	entry* arr;
	char name[100];
	struct recordEntry* next ;
	int identifier;

}recordEntry;

typedef struct recordTable
{
	recordEntry* arr[7];
	int next_identifer;
}recordTable;

//void insertRecord(recordTable* curr,char* name,int type[],char* attr[],char* value[]);
//recordEntry* findRecordTable(recordTable* curr,char* name);


typedef struct GlobalTable
{
	entry *entryArray[997] ;
	funcTable finalFuncTable;
}GlobalTable;

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


bool insertGlobalRecord(GlobalTable* table,tokenInfo temp,TERMINAL type, char* recordtype , recordTable* record_table);
bool insertLocalRecord(GlobalTable *t,funcIdTable *table , tokenInfo temp,TERMINAL type,char* recordtype , recordTable* record_table);

recordTable* initializeRecordTable();
GlobalTable* initalizeGlobalTable();
funcIdTable* initalizeLocalTable();
void displaySymbolTable(GlobalTable* t);

#endif
