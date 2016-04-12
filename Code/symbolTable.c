/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: symbolTable.c
* @Date:      2016-03-29 10:44:42
*/

#include "symbolTable.h"

int computeHashVal(char* ch)
{
	int k=0;
	int i=0;
	for(i=0;i< sizeof(ch)/sizeof(char);i++)
	{
		k+= (int)ch[i];
	}
	return k%997;
}

void insertId(IdTable* table , entry* new_entry)
{
	int k=computeHashVal(new_entry->name);
	entry* temp = table->entryArray[k];
	if(temp==NULL)
	{
		table->entryArray[k]=new_entry;
	}
	else
	{
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next = new_entry ;
	}
}


entry* findId(IdTable* table,char* name)
{
	int  k = computeHashVal(name);
	entry* temp = table->entryArray[k];
	while(temp!=NULL)
	{
		if( strcmp(temp->name , name)==0   )
			return temp;
		temp = temp->next;
	}
	return NULL;
}

void insertFuncIdTable(funcTable *curr , funcIdTable *curr_funcidtable)
{
	int k = computeHashVal(curr_funcidtable->funcName);
	if(curr->funcTableArray[k]==NULL )
	{
		curr->funcTableArray[k] = curr_funcidtable ;
	}
	else
	{
		funcIdTable *temp = curr->funcTableArray[k];
		while(temp->next!=NULL)
		{
			temp = temp->next;
		}
		temp->next = curr_funcidtable;
	}
}

funcIdTable* findfunctionIdTable(funcTable *curr, char* curr_name)
{
	int k = computeHashVal(curr_name);
	funcIdTable* temp = curr->funcTableArray[k];
	while(temp!=NULL)
	{
		if(strcmp( temp->funcName,curr_name)==0)
		{
			return temp;
		}
	}
	return NULL;
}


void deleteFuncIdTable(funcTable *curr , char* curr_name)
{
	int  k = computeHashVal(curr_name);
	if(curr->funcTableArray[k]!=NULL)
	{
		if( strcpy( curr->funcTableArray[k]->funcName,curr_name )==0 )
		{
			curr->funcTableArray[k] = curr->funcTableArray[k]->next;
		}
		else
		{
			funcIdTable* temp = curr->funcTableArray[k];
			while(temp->next!=NULL)
			{
				if( strcpy(temp->next->funcName , curr_name)==0  )
				{
					temp->next = temp->next->next;
					return ;
				}
			}
		}
	}
}