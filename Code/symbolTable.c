
#include "symbolTable.h"

int func_num=0;

void displaySymbolTable(GlobalTable* t)
{
	printf("GLOBAL SCOPE\n");
	printf("--------------------\n");
	int i;
	for(i=0;i<997;i++)
	{
		if(t->entryArray[i]!=NULL)
		{
			entry* temp = t->entryArray[i];
			while(temp != NULL)
			{
				printf("%s\t\t%s\n", temp->token.lexeme, getTerminalStr(temp->type));
				temp = temp->next;
			}
		}
	}
	funcTable *temp2 = &(t->finalFuncTable);

	for(i=0;i<997;i++)
	{
		funcIdTable *temp3 = temp2->funcTableArray[i];
		while(temp3!=NULL)
		{
			printf("LOCAL SCOPE %s\n",temp3->funcName );
			printf("--------------------\n");
			int j=0;
			for(j=0;j<997;j++)
			{
				entry* temp4 = temp3->table.entryArray[j];
				while(temp4!=NULL)
				{
					//entry* temp4 = temp3->table.entryArray[i];
					printf("%s\t\t%s\n",temp4->token.lexeme , getTerminalStr(temp4->type));
					temp4=temp4->next;
				}
			}
			temp3=temp3->next;
		}
	}
}

int computeHashVal(char* ch)
{
	int k=0;
	int i=0;
	//printf("%d\n",sizeof(ch)/sizeof(char));
	for(i=0;i< sizeof(ch)/sizeof(char);i++)
	{   if(ch[i]!='\0')
			k+= (int)ch[i];
		else
			break;
		//printf("%d\n",k);
	}
	//printf("\n");
	return k%997;
}


bool checkFunctiondeclaration(funcTable table,char* name)
{
	//printf("%s\n",name);
	int i;
	for(i=0;i<997;i++)
	{
		if(table.funcTableArray[i]!=NULL)
		{
			funcIdTable *index = table.funcTableArray[i];
			while(index!=NULL)
			{
				if(strcmp(index->funcName,name)==0)
					return 1;
				index = index->next;
			}
		}
	}
	return 0;
}

bool checkLocalDeclaration(funcTable temp,char* ch)
{

	int i;
	for(i=0;i<997;i++)
	{
		funcIdTable* temp2 = temp.funcTableArray[i];
		if(temp2!=NULL)
		{
			int j;
			IdTable temp3 = temp2->table;
			for(j=0;j<997;j++)
			{
				if(temp3.entryArray[j]!=NULL)
				{
					entry* temp4 = temp3.entryArray[j];
					while(temp4!=NULL)
					{
						if(strcmp(temp4->token.lexeme,ch)==0)
						{
							return 1;
						}
						temp4=temp4->next;
					}
				}

			}
		}
	}
	return 0;

}

bool insertGlobalId(GlobalTable* table , tokenInfo temp,TERMINAL type)
{
	if(findGlobalId(table, temp.lexeme)!=NULL)
	{
		fprintf(stderr, "Redeclaration Error Line number:%d\n",temp.lineNum);
		return 0;
	}
	if( checkLocalDeclaration(table->finalFuncTable,temp.lexeme)==1)
	{
		fprintf(stderr, "Error ,also declared locally Line Num:%d\n", temp.lineNum);
		return 0;
	}
	entry* new_entry;
	new_entry = (entry*) malloc(sizeof(entry));
	new_entry->token = temp;
	new_entry->type = type;
	if(type== TK_INT)
		new_entry->offset = INTSPACE;
	else
		new_entry->offset = REALSPACE;


	int k=computeHashVal(new_entry->token.lexeme);

	//printf("%s %d\n",new_entry->token.lexeme,k);
	entry* temp2 = table->entryArray[k];


	if(temp2==NULL)
	{
		table->entryArray[k]=new_entry;
	}
	else
	{
		while(temp2->next!=NULL)
		{
			temp2=temp2->next;
		}
		temp2->next = new_entry ;
	}
	return 1;
}


entry* findGlobalId(GlobalTable* table,char* name)
{

	int  k = computeHashVal(name);
	//printf("%s %d\n",name,k);
	entry* temp = table->entryArray[k];



	while(temp!=NULL)
	{
		//printf("i dont know");
		if( strcmp(temp->token.lexeme , name)==0   )
		{
			//printf("isthere\n");
			//printf("%s",temp->token.lexeme);
			return temp;
		}
		temp = temp->next;
	}
	//printf("hello\n");
	return NULL;
}

bool insertGlobalRecord(GlobalTable* table,tokenInfo temp,TERMINAL type, char* recordtype , recordTable* record_table)
{
	int offset =0 ;
	//printf("*****************\n");
	if(findGlobalId(table, temp.lexeme)!=NULL)
	{
		fprintf(stderr, "Redeclaration Error Line number:%d\n",temp.lineNum);
		return 0;
	}
	//printf("*****************\n");
	if( checkLocalDeclaration(table->finalFuncTable,temp.lexeme)==1)
	{
		fprintf(stderr, "Error ,also declared locally Line Num:%d\n", temp.lineNum);
		return 0;
	}
	//printf("*****************\n");


	entry* new_entry;
	new_entry = (entry*) malloc(sizeof(entry));
	new_entry->token = temp;
	new_entry->type = findRecordEntry(recordtype,record_table)->identifier;

	strcpy( new_entry->recordType,recordtype);


    recordEntry* tempRecordEntry = findRecordEntry(recordtype ,record_table);

    entry* temp2 = tempRecordEntry->arr ;
    //printf("**********************\n");
    while(temp2!=NULL)
    {
    	offset+=temp2->offset;
    	tokenInfo tk = temp2->token;
    	char ch[100];
    	strcpy(ch, temp.lexeme);
    	strcat(ch,".");
    	strcat(ch,temp2->token.lexeme);
    	strcpy(tk.lexeme,ch);
    	insertGlobalId(table ,tk, temp2->type);
    	temp2=temp2->next;
    }

	// add the a.x a.y .az etc to the global or local table
    new_entry->offset = offset;
	int k=computeHashVal(new_entry->token.lexeme);

	entry* temp5 = table->entryArray[k];

	if(temp5==NULL)
	{
		table->entryArray[k]=new_entry;
	}
	else
	{
		while(temp5->next!=NULL)
		{
			temp5=temp5->next;
		}
		temp5->next = new_entry ;
	}
	return 1;

}

funcIdTable* insertFuncIdTable(GlobalTable* table , char* funcName)
{
	//printf("%d",)
	if( checkFunctiondeclaration(table->finalFuncTable,funcName))
	{
		fprintf(stderr,"ERROR : Function redeclared  %s\n",funcName);
		return NULL;
	}
	funcTable *curr = &table->finalFuncTable;

	funcIdTable* curr_funcidtable  = (funcIdTable*) malloc(sizeof(funcIdTable));
	curr_funcidtable->input_num=0;
	curr_funcidtable->output_num=0;
	curr_funcidtable->identifer = func_num; 
	strcpy(curr_funcidtable->funcName,funcName);
	int k = computeHashVal(funcName);

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
	return curr_funcidtable;
}

funcIdTable* findFuncIdTable(funcTable *curr, char* curr_name)
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


bool insertLocalId(GlobalTable* global_table,funcIdTable* function_table,tokenInfo temp,TERMINAL type)
{
	IdTable *table = &function_table->table;
	if(findLocalId(function_table, temp.lexeme)!=NULL)
	{
		fprintf(stderr, "Redeclaration Error in local table  Line number:%d\n",temp.lineNum);
		return 0;
	}
	if( findGlobalId(global_table,temp.lexeme)!=NULL)
	{
		fprintf(stderr, "Error ,also declared globally Line Num:%d\n", temp.lineNum);
		return 0;
	}

	entry* new_entry;
	new_entry = (entry*) malloc(sizeof(entry));
	new_entry->token = temp;
	new_entry->type = type;
	if(type== TK_INT)
		new_entry->offset = INTSPACE;
	else
		new_entry->offset = REALSPACE;


	int k=computeHashVal(new_entry->token.lexeme);

	entry* temp2 = table->entryArray[k];

	if(temp2==NULL)
	{
		table->entryArray[k]=new_entry;
	}
	else
	{
		while(temp2->next!=NULL)
		{
			temp2=temp2->next;
		}
		temp2->next = new_entry ;
	}
	return 1;
}

entry* findLocalId(funcIdTable* table,char* name)
{
	IdTable* curr = &(table->table);

	int k = computeHashVal(name);

	entry* temp = curr->entryArray[k];

	while(temp!=NULL)
	{
		if( strcmp(temp->token.lexeme , name)==0   )
			return temp;
		temp = temp->next;
	}

	return NULL;

}

bool insertLocalRecord(GlobalTable *t,funcIdTable *table , tokenInfo temp,TERMINAL type,char* recordtype , recordTable* record_table)
{
	//int k=computeHashVal(temp->lexeme);
	int offset =0 ;
	if(findLocalId(table,temp.lexeme)!=NULL)
	{
		fprintf(stderr, "Redeclaration Error Line number:%d\n",temp.lineNum);
		return 0;
	}
	if( findGlobalId(t,temp.lexeme)!=NULL)
	{
		fprintf(stderr, "Error ,also declared locally Line Num:%d\n", temp.lineNum);
		return 0;
	}
	entry* new_entry;
	new_entry = (entry*) malloc(sizeof(entry));
	new_entry->token = temp;
	new_entry->type = findRecordEntry(recordtype,record_table)->identifier;

	strcpy( new_entry->recordType,recordtype);


    recordEntry* tempRecordEntry = findRecordEntry(recordtype ,record_table);

    entry* temp2 = tempRecordEntry->arr ;

    while(temp2!=NULL)
    {
    	offset+=temp2->offset;
    	tokenInfo tk = temp2->token;
    	char ch[100];
    	strcpy(ch, temp.lexeme);
    	strcat(ch,".");
    	strcat(ch,temp2->token.lexeme);
    	strcpy(tk.lexeme,ch);
    	insertLocalId(t,table ,tk, temp2->type);
    	temp2=temp2->next;
    }

	// add the a.x a.y .az etc to the global or local table
    new_entry->offset = offset;
	int k=computeHashVal(new_entry->token.lexeme);

	entry* temp5 = table->table.entryArray[k];

	if(temp5==NULL)
	{
		table->table.entryArray[k]=new_entry;
	}
	else
	{
		while(temp5->next!=NULL)
		{
			temp5=temp5->next;
		}
		temp5->next = new_entry ;
	}
	return 1;
}


void insertInputParameterRecord(GlobalTable *g,funcIdTable* temp,tokenInfo tk,char* name,recordTable *currRecordTable)
{
	int offset;
	recordEntry* t = findRecordEntry(name,currRecordTable);
	TERMINAL type = t->identifier;
	temp->input_num++;
	insertLocalId(g,temp,tk,type);

	entry* temp1 = (entry*) malloc(sizeof(entry));
	temp1->token =tk ;
	temp1->type = type;


	entry* temp2 = temp->inputParameterList;
	if(temp2==NULL)
	{
		temp->inputParameterList = temp1;
	}
	else
	{
		while(temp2->next!=NULL)
		{
			temp2=temp2->next;
		}
		temp2->next = temp1;
	}

	entry* temp3 = t->arr ;

    while(temp3!=NULL)
    {
    	offset+=temp3->offset;
    	tokenInfo tk1 = temp3->token;
    	char ch[100];
    	strcpy(ch, tk.lexeme);
    	strcat(ch,".");
    	strcat(ch,temp3->token.lexeme);
    	strcpy(tk1.lexeme,ch);
    	insertLocalId(g,temp ,tk1,temp3->type);
    	temp3=temp3->next;
    }
    temp1->offset  = offset;
}
void insertOutputParameterRecord(GlobalTable *g,funcIdTable* temp,tokenInfo tk,char* name,recordTable *currRecordTable)
{
	int offset=0;
	recordEntry* t = findRecordEntry(name,currRecordTable);
	TERMINAL type = t->identifier;
	temp->output_num++;
	insertLocalId(g,temp,tk,type);

	entry* temp1 = (entry*) malloc(sizeof(entry));
	temp1->token =tk ;
	temp1->type = type;

	entry* temp2 = temp->outputParameterList;
	if(temp2==NULL)
	{
		temp->outputParameterList = temp1;
	}
	else
	{
		while(temp2->next!=NULL)
		{
			temp2=temp2->next;
		}
		temp2->next = temp1;
	}

	entry* temp3 = t->arr ;

    while(temp3!=NULL)
    {
    	offset+=temp3->offset;
    	tokenInfo tk1 = temp3->token;
    	char ch[100];
    	strcpy(ch, tk.lexeme);
    	strcat(ch,".");
    	strcat(ch,temp3->token.lexeme);
    	strcpy(tk1.lexeme,ch);
    	insertLocalId(g,temp ,tk1,temp3->type);
    	temp3=temp3->next;
    }
    temp1->offset = offset;
}



void insertInputParameter(GlobalTable *g,funcIdTable* temp,tokenInfo tk,TERMINAL type)
{
	insertLocalId(g,temp,tk,type);
	entry* temp1 = (entry*) malloc(sizeof(entry));
	temp1->token =tk ;
	temp1->type = type;
	if(type==TK_INT)
		temp1->offset = INTSPACE;
	else
		temp1->offset = REALSPACE;
	temp->input_num++;
	entry* temp2 = temp->inputParameterList;
	if(temp2==NULL)
	{
		temp->inputParameterList = temp1;
	}
	else
	{
		while(temp2->next!=NULL)
		{
			temp2=temp2->next;
		}
		temp2->next = temp1;
	}
}
void insertOutputParameter(GlobalTable *g,funcIdTable* temp,tokenInfo tk,TERMINAL type)
{
	insertLocalId(g,temp,tk,type);
	entry* temp1 = (entry*) malloc(sizeof(entry));
	temp1->token =tk ;
	temp1->type = type;
	if(type==TK_INT)
		temp1->offset = INTSPACE;
	else
		temp1->offset = REALSPACE;
	temp->output_num++;
	entry* temp2 = temp->outputParameterList;
	if(temp2==NULL)
	{
		temp->outputParameterList = temp1;
	}
	else
	{
		while(temp2->next!=NULL)
		{
			temp2=temp2->next;
		}
		temp2->next = temp1;
	}
}
recordTable* initializeRecordTable()
{
	recordTable* t = (recordTable*) malloc(sizeof(recordTable));
	t->next_identifer =RECORD_OFFSET;
	return t;
}

GlobalTable* initalizeGlobalTable()
{
	GlobalTable* t = (GlobalTable*) malloc(sizeof(GlobalTable));
	return t;
}

funcIdTable* initalizeLocalTable()
{
	funcIdTable* f = (funcIdTable*) malloc(sizeof(funcIdTable));
	return f;
}

void insertRecord(char* name,recordTable* curr)
{
	int k = computeHashVal(name);
	k=k%7;

	recordEntry* new_entry = (recordEntry*) malloc( sizeof(recordEntry)  );

	strcpy(new_entry->name,name);

	new_entry->identifier = curr->next_identifer;
	curr->next_identifer++;

	if(curr->arr[k]==NULL)
	{
		curr->arr[k] = new_entry;
	}
	else
	{
		recordEntry *temp = curr->arr[k];
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}

		temp->next = new_entry;
	}

}
void insertRecordEntry(char* name,recordTable* curr,tokenInfo tk , TERMINAL type)
{
	int k = computeHashVal(name);
	k = k%7;

	recordEntry* new_entry = curr->arr[k];

	while(  strcmp(new_entry->name,name)!=0)
	{
		new_entry=new_entry->next;
	}

	entry* temp_entry = (entry*) malloc(sizeof(entry));


	temp_entry->type = type;
	temp_entry->token = tk;
	if(type==TK_INT)
		temp_entry->offset = INTSPACE;
	else
		temp_entry->offset = REALSPACE;
	entry* temp = new_entry->arr;

	if(temp==NULL)
	{
		new_entry->arr= temp_entry;
	}
	else
	{
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next = temp_entry;
	}
}

recordEntry* findRecordEntry(char* name,recordTable* curr)
{
	int k = computeHashVal(name);
	k=k%7;


	recordEntry* temp = curr->arr[k];

	while(temp!=NULL)
	{
		if( strcmp(temp->name,name)==0   )
		{
			return temp;
		}
	}
	return NULL;
}

recordEntry* getRecordEntry(int identifier,recordTable *table)
{
	int i;
	for(i=0;i<7;i++)
	{
		recordEntry *temp = table->arr[i];

		while(temp!=NULL)
		{
			if(temp->identifier==identifier)
				return temp;
			temp=temp->next; 
		}
	}
	return NULL;
}














