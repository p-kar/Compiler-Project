/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: codeGen.c
* @Date:      2016-03-29 10:44:42
*/

#include "codeGen.h"

ASTNode *root ;
int curr_index=0;
int curr_label=0;
triple* currTriple;

#define INF 1000000000

void displayTriple()
{
	int i;
	for(i=0;i<curr_index;i++)
	{
		printf("%d   %s    %d          %d               %d         %d\n",i,currTriple[i].op , currTriple[i].val1 ,
			currTriple[i].val2,currTriple[i].mylabel,currTriple[i].jumplabel);
	}

}

int addTriple(char* op , int val1 , int val2)
{
	currTriple = (triple*) realloc(currTriple , (curr_index+1)*sizeof(triple) ) ;
    //printf("???????????????????%s\n",op);
    strcpy(currTriple[curr_index].op, op );
	currTriple[curr_index].val1 = val1;
	currTriple[curr_index].val2 = val2;
	curr_index++;
	return curr_index - 1;
}

void addTriple2(char* op,int val1,int val2,int mylabel,int jumplabel)
{
	currTriple = (triple*) realloc(currTriple , (curr_index+1)*sizeof(triple) );
    //printf("???????????????????%s\n",op);
    strcpy(currTriple[curr_index].op, op );
	currTriple[curr_index].val1 = val1;
	currTriple[curr_index].val2 = val2;
	currTriple[curr_index].mylabel = mylabel;
	currTriple[curr_index].jumplabel = jumplabel;
	curr_index++;

}
char* findVarName(char* lexeme)
{
	return lexeme;
}

tuple* solveAssignmentStmt(ASTNode* curr)
{

	if(curr->nodeid == getNonTerminalfromStr("<assignmentStmt>"))
	{
		//printf("%d %d\n",curr->children[1]->nodeid , getNonTerminalfromStr("<arithmeticExpression>"));
		//printf("Assignment Stmt ////\n");
		//printf("%s\n", getIDStr(curr->children[1]->nodeid));
		tuple* left = solveAssignmentStmt(curr->children[0]);
		tuple* right = solveAssignmentStmt(curr->children[1]);
		tuple *t = (tuple*) malloc(sizeof(tuple));
		t->arr = NULL;
		t->len = 0;
		int i;
		for (i = 0; i < left->len; ++i)
		{
			t->arr = (int*) realloc(t->arr, sizeof(int) * (t->len + 1));
			t->arr[t->len] = addTriple("=", left->arr[i], right->arr[i]);
			t->len++;
		}
		return t;
	}
	else if(curr->nodeid == getNonTerminalfromStr("<arithmeticExpression>"))
	{
		//printf("arithmetic expression\n");
		if(curr->children[1]==NULL)
		{
			//printf("no second child\n");
			 return solveAssignmentStmt(curr->children[0]);
		}
		else
		{
			tuple *t = (tuple*) malloc(sizeof(tuple));
			t->arr = NULL;
			t->len = 0;
			if(curr->children[1]->children[0]->tk.tokenType==TK_PLUS)
			{
				//printf("//////////plus\n");
				//printf("%d %d",curr->children[0]->nodeid, getNonTerminalfromStr("<term>"));
				tuple* left = solveAssignmentStmt(curr->children[0]);
				//printf("%d",temp1);
				tuple* right = solveAssignmentStmt(curr->children[1]);
				int i;
				for (i = 0; i < left->len; ++i)
				{
					t->arr = (int*) realloc(t->arr, sizeof(int) * (t->len + 1));
					t->arr[t->len] = addTriple("+", left->arr[i], right->arr[i]);
					t->len++;
				}
			}
			else if(curr->children[1]->children[0]->tk.tokenType==TK_MINUS)
			{
				tuple* left = solveAssignmentStmt(curr->children[0]);
				tuple* right = solveAssignmentStmt(curr->children[1]);
				int i;
				for (i = 0; i < left->len; ++i)
				{
					t->arr = (int*) realloc(t->arr, sizeof(int) * (t->len + 1));
					t->arr[t->len] = addTriple("-", left->arr[i], right->arr[i]);
					t->len++;
				}
			}
			return t;
		}
	}
	else if(curr->nodeid == getNonTerminalfromStr("<term>"))
	{
		//printf("term\n");
		if(curr->children[1]==NULL)
		{
			return solveAssignmentStmt(curr->children[0]);
		}
		else
		{
			tuple *t = (tuple*) malloc(sizeof(tuple));
			t->arr = NULL;
			t->len = 0;
			if(curr->children[1]->children[0]->tk.tokenType==TK_MUL)
			{
				tuple* left = solveAssignmentStmt(curr->children[0]);
				tuple* right = solveAssignmentStmt(curr->children[1]);
				if(left->len > 1)
				{
					int i;
					for (i = 0; i < left->len; ++i)
					{
						t->arr = (int*) realloc(t->arr, sizeof(int) * (t->len + 1));
						t->arr[t->len] = addTriple("*", left->arr[i], right->arr[0]);
						t->len++;
					}
				}
				else if(right->len > 1)
				{
					int i;
					for (i = 0; i < right->len; ++i)
					{
						t->arr = (int*) realloc(t->arr, sizeof(int) * (t->len + 1));
						t->arr[t->len] = addTriple("*", left->arr[0], right->arr[i]);
						t->len++;
					}
				}
				else
				{
					t->arr = (int*) malloc(sizeof(int));
					t->arr[0] = addTriple("*", left->arr[0], right->arr[0]);
					t->len++;
				}
			}
			else if(curr->children[1]->children[0]->tk.tokenType==TK_DIV)
			{
				tuple* left = solveAssignmentStmt(curr->children[0]);
				tuple* right = solveAssignmentStmt(curr->children[1]);
				if(left->len > 1)
				{
					int i;
					for (i = 0; i < left->len; ++i)
					{
						t->arr = (int*) realloc(t->arr, sizeof(int) * (t->len + 1));
						t->arr[t->len] = addTriple("/", left->arr[i], right->arr[0]);
						t->len++;
					}
				}
				else if(right->len > 1)
				{
					int i;
					for (i = 0; i < right->len; ++i)
					{
						t->arr = (int*) realloc(t->arr, sizeof(int) * (t->len + 1));
						t->arr[t->len] = addTriple("/", left->arr[0], right->arr[i]);
						t->len++;
					}
				}
				else
				{
					t->arr = (int*) malloc(sizeof(int));
					t->arr[0] = addTriple("/", left->arr[0], right->arr[0]);
					t->len++;
				}
			}
			return t;
		}
	}
	else if(curr->nodeid == getNonTerminalfromStr("<expPrime>"))
	{
		//printf("exp prime\n");
		if(curr->children[2]==NULL)
		{
			//printf("///////////okay\n");
			return solveAssignmentStmt(curr->children[1]);

		}
		else
		{
			tuple *t = (tuple*) malloc(sizeof(tuple));
			t->arr = NULL;
			t->len = 0;
			if(curr->children[2]->children[0]->tk.tokenType==TK_PLUS)
			{
				tuple* left = solveAssignmentStmt(curr->children[1]);
				tuple* right = solveAssignmentStmt(curr->children[2]);
				int i;
				for (i = 0; i < left->len; ++i)
				{
					t->arr = (int*) realloc(t->arr, sizeof(int) * (t->len + 1));
					t->arr[t->len] = addTriple("+", left->arr[i], right->arr[i]);
					t->len++;
				}
			}
			else if(curr->children[2]->children[0]->tk.tokenType==TK_MINUS)
			{
				tuple* left = solveAssignmentStmt(curr->children[1]);
				tuple* right = solveAssignmentStmt(curr->children[2]);
				int i;
				for (i = 0; i < left->len; ++i)
				{
					t->arr = (int*) realloc(t->arr, sizeof(int) * (t->len + 1));
					t->arr[t->len] = addTriple("-", left->arr[i], right->arr[i]);
					t->len++;
				}
			}
			return t;
		}
	}
	else if(curr->nodeid == getNonTerminalfromStr("<factor>"))
	{
		//printf("factor\n");
		return solveAssignmentStmt(curr->children[0]);
	}
	else if(curr->nodeid == getNonTerminalfromStr("<termPrime>"))
	{
		//printf("term prime\n");
		if(curr->children[2] == NULL)
		{
			return solveAssignmentStmt(curr->children[1]);
		}
		tuple *t = (tuple*) malloc(sizeof(tuple));
		t->arr = NULL;
		t->len = 0;
		if(curr->children[2]->children[0]->tk.tokenType==TK_MUL)
		{
			tuple* left = solveAssignmentStmt(curr->children[1]);
			tuple* right = solveAssignmentStmt(curr->children[2]);
			if(left->len > 1)
			{
				int i;
				for (i = 0; i < left->len; ++i)
				{
					t->arr = (int*) realloc(t->arr, sizeof(int) * (t->len + 1));
					t->arr[t->len] = addTriple("*", left->arr[i], right->arr[0]);
					t->len++;
				}
			}
			else if(right->len > 1)
			{
				int i;
				for (i = 0; i < right->len; ++i)
				{
					t->arr = (int*) realloc(t->arr, sizeof(int) * (t->len + 1));
					t->arr[t->len] = addTriple("*", left->arr[0], right->arr[i]);
					t->len++;
				}
			}
			else
			{
				t->arr = (int*) malloc(sizeof(int));
				t->arr[0] = addTriple("*", left->arr[0], right->arr[0]);
				t->len++;
			}
		}
		else if(curr->children[2]->children[0]->tk.tokenType==TK_DIV)
		{
			tuple* left = solveAssignmentStmt(curr->children[1]);
			tuple* right = solveAssignmentStmt(curr->children[2]);
			if(left->len > 1)
			{
				int i;
				for (i = 0; i < left->len; ++i)
				{
					t->arr = (int*) realloc(t->arr, sizeof(int) * (t->len + 1));
					t->arr[t->len] = addTriple("/", left->arr[i], right->arr[0]);
					t->len++;
				}
			}
			else if(right->len > 1)
			{
				int i;
				for (i = 0; i < right->len; ++i)
				{
					t->arr = (int*) realloc(t->arr, sizeof(int) * (t->len + 1));
					t->arr[t->len] = addTriple("/", left->arr[0], right->arr[i]);
					t->len++;
				}
			}
			else
			{
				t->arr = (int*) malloc(sizeof(int));
				t->arr[0] = addTriple("/", left->arr[0], right->arr[0]);
				t->len++;
			}
		}

		return t;
	}
	else if(curr->nodeid == getNonTerminalfromStr("<singleOrRecId>"))
	{
		//printf("singleor recordid\n");
		int type = getType(curr);
		/*if(curr->children[1] == NULL)
			printf("Line %d: %s type = %d\n", getLineNumber(curr), curr->children[0]->tk.lexeme, type);
		else
			printf("Line %d: %s.%s type = %d\n", getLineNumber(curr), curr->children[0]->tk.lexeme, curr->children[1]->tk.lexeme, type);
		*/
		tuple* t = (tuple*) malloc(sizeof(tuple));
		t->arr = NULL;
		t->len = 0;
		if(type >= RECORD_OFFSET)
		{
			recordEntry* rent = getRecordEntry(type, curr->record_table);
			entry* p = rent->arr;
			t->len = 0;
			while(p != NULL)
			{
				char identifier[100];
				sprintf(identifier, "%s.%s", curr->children[0]->tk.lexeme, p->token.lexeme);
				t->arr = (int*) realloc(t->arr, sizeof(int) * (t->len + 1));
				//printf("??????????%s %s\n",curr->children[0]->tk.lexeme,p->token.lexeme);
				//printf("?????????%s\n\n",identifier);
				t->arr[t->len] = addTriple(identifier, INF, INF);
				t->len++;
				p = p->next;
			}
		}
		else
		{

			char identifier[100];
			if(curr->children[1] == NULL)
				sprintf(identifier, "%s", curr->children[0]->tk.lexeme);
			else
				sprintf(identifier, "%s.%s", curr->children[0]->tk.lexeme, curr->children[1]->tk.lexeme);
			//printf("??????????? %s\n",identifier);
			t->arr = (int*) malloc(sizeof(int));
			t->len = 1;
			t->arr[0] = addTriple(identifier, INF, INF);
		}
		return t;
	}
	else if(curr->tk.tokenType == TK_NUM)
	{
		//printf("num\n");
		tuple* t = (tuple*) malloc(sizeof(tuple));
		t->arr = (int*) malloc(sizeof(int));
		t->len = 1;
		t->arr[0] = addTriple( "NUM" , atoi(curr->tk.lexeme) , INF);
		return t;

	}
	return NULL;
}

int solve(ASTNode* curr)
{
	if(curr->tk.tokenType == TK_ID)
	{
		addTriple(curr->tk.lexeme , INF , INF);
		return curr_index-1;
	}
	else if(curr->tk.tokenType== TK_NUM)
	{
		addTriple("NUM",atoi(curr->tk.lexeme),INF);
		return curr_index-1;
	}
	return -1;
}

void solveStmt(ASTNode* impStmtNode)
{
	if(impStmtNode==NULL)
	{
		return;
	}
	while(1)
	{
		//printf(".................aaaaaaaaaaa\n");
		ASTNode* stmtNode = impStmtNode->children[0];
		//checking which type of statement it is
		if( stmtNode->child_cnt<1 )
			fprintf(stderr, " Statement Node Has only one child\n");
		else if( stmtNode->nodeid == getNonTerminalfromStr("<iterativeStmt>"))
		{
			//printf("\nIterative Stmt\n");
			solveIterative(stmtNode);
			// while loop
		}
		else if(stmtNode->nodeid ==
			getNonTerminalfromStr("<conditionalStmt>"))
		{
			//printf("\n Conditional Stmt \n");
			if(stmtNode->children[4]==NULL)
				solveConditionalOne(stmtNode);
			else
				solveConditionalTwo(stmtNode);
		}
		else if(stmtNode->nodeid== getNonTerminalfromStr("<assignmentStmt>") )
		{
			//printf("Assignment Stmt\n");
			solveAssignmentStmt(stmtNode);
			// assignment statement
		}
		else if(stmtNode->children[0]->tk.tokenType == TK_WRITE)
		{

			//printf("Write Stmt\n");
			tuple* t = solveAssignmentStmt(stmtNode->children[1]);
			int i;
			for (i = 0; i < t->len; ++i)
				addTriple("write" , t->arr[i], INF);
		}
		else if(stmtNode->children[0]->tk.tokenType == TK_READ)
		{
			//printf("Read Stmt\n");
			tuple* t = solveAssignmentStmt(stmtNode->children[1]);
			addTriple("read" , t->arr[0] ,INF);
		}
		else
			fprintf(stderr, "Code generation cannot handle this case\n" );

		//printf("okay\n");
		//printf("%d\n",(int) impStmtNode->child_cnt);
		impStmtNode = impStmtNode->children[1];
		if(impStmtNode==NULL)
			break;
		//printf("ffgh\n");
	}
}
void solveStmtHelper(ASTNode* stmtNode , ASTNode* impStmtNode)
{
		if( stmtNode->nodeid == getNonTerminalfromStr("<iterativeStmt>"))
		{
			//printf("Iterative Stmt\n");
			solveIterative(stmtNode);
			// while loop
		}
		else if(stmtNode->nodeid ==
			getNonTerminalfromStr("<conditionalStmt>"))
		{
			//printf("Conditional Stmt\n");
			if(stmtNode->children[4]==NULL)
				solveConditionalOne(stmtNode);
			else
				solveConditionalTwo(stmtNode);
		}
		else if(stmtNode->nodeid== getNonTerminalfromStr("<assignmentStmt>") )
		{

			//printf("Assignment Stmt\n");
			solveAssignmentStmt(stmtNode);
			// assignment statement
		}
		else if(stmtNode->children[0]->tk.tokenType == TK_WRITE)
		{

			//printf("Write stmt\n");
			tuple* t = solveAssignmentStmt(stmtNode->children[1]);
			int i;
			for (i = 0; i < t->len; ++i)
				addTriple("write" , t->arr[i], INF);
		}
		else if(stmtNode->children[0]->tk.tokenType == TK_READ)
		{
			//printf("Read stmt\n");
			tuple* t = solveAssignmentStmt(stmtNode->children[1]);
			addTriple("read" , t->arr[0] ,INF);
		}
		else
			fprintf(stderr, "Code generation cannot handle this case\n" );

		//printf(".......okay\n");
		solveStmt(impStmtNode);
}

void solveBool(ASTNode* curr , int label_succ , int label_fail)
{
	if(curr->rno == 65)
	{
		if(curr->children[1]->tk.tokenType == TK_OR)
		{
			int new_label = curr_label;
			curr_label++;
			solveBool(curr->children[0],label_succ,new_label);
			addTriple2("Label",INF,INF,new_label,INF);
			solveBool(curr->children[2],label_succ,label_fail);
		}
		else
		{
			int new_label = curr_label;
			curr_label++;
			solveBool(curr->children[0],new_label,label_fail);
			addTriple2("Label",INF,INF,new_label,INF);
			solveBool(curr->children[2],label_succ,label_fail);
		}

	}
	else if(curr->rno==66)
	{
		if(curr->children[1]->tk.tokenType == TK_LT)
		{
			addTriple2("<",solve(curr->children[0]),solve(curr->children[2]),
				INF,label_succ);
			addTriple2("Jump",INF,INF,INF,label_fail);
		}
		else if(curr->children[1]->tk.tokenType == TK_LE)
		{
			addTriple2("<=",solve(curr->children[0]),solve(curr->children[2]),
				INF,label_succ);
			addTriple2("Jump",INF,INF,INF,label_fail);
		}
		else if(curr->children[1]->tk.tokenType == TK_GT)
		{
			addTriple2(">",solve(curr->children[0]),solve(curr->children[2]),
				INF,label_succ);
			addTriple2("Jump",INF,INF,INF,label_fail);
		}
		else if(curr->children[1]->tk.tokenType == TK_GE)
		{
			addTriple2(">=",solve(curr->children[0]),solve(curr->children[2]),
				INF,label_succ);
			addTriple2("Jump",INF,INF,INF,label_fail);
		}
		else if(curr->children[1]->tk.tokenType == TK_EQ)
		{
			addTriple2("==",solve(curr->children[0]),solve(curr->children[2]),
				INF,label_succ);
			addTriple2("Jump",INF,INF,INF,label_fail);
		}
		else if(curr->children[1]->tk.tokenType == TK_NE)
		{
			addTriple2("!=",solve(curr->children[0]),solve(curr->children[2]),
				INF,label_succ);
			addTriple2("Jump",INF,INF,INF,label_fail);
		}

	}
	else if(curr->rno==67)
	{
		solveBool(curr->children[1],label_fail,label_succ);
	}
}

void solveConditionalOne(ASTNode* curr)
{
	int temp  = curr_label;
	curr_label+=2;
	solveBool(curr->children[1], temp, temp+1);
	addTriple2("Label",INF,INF,temp,INF);

	//ASTNode* temp= (ASTNode*) malloc( sizeof(ASTNode) );
	//temp->children = (ASTNode*) malloc(sizeof(ASTNode)*2);

	solveStmtHelper(curr->children[2], curr->children[3]);
	//solving stmt , other stmts
	addTriple2("Label",INF,INF,temp+1,INF);

}

void solveConditionalTwo(ASTNode* curr)
{
	//printf("aaaaaaaaaaaaaaaaaaaaa\n");
	int label_succ = curr_label;
	curr_label++;
	int label_fail = curr_label;
	curr_label++;
	int s_next = curr_label;
	curr_label++;

	solveBool(curr->children[1],label_succ,label_fail);
	addTriple2("Label",INF,INF,label_succ,INF);
	solveStmtHelper(curr->children[2],curr->children[3]);
	//solving stmt and other stmts
	addTriple2("Jump",INF,INF,INF,s_next);
	addTriple2("Label",INF,INF,label_fail,INF);
	//printf(">>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<< Else part\n");
	solveStmtHelper(curr->children[4]->children[0],curr->children[4]->children[1]);
	//solveing s2.code
	addTriple2("Label",INF,INF,s_next,INF);
}


void solveIterative(ASTNode* curr)
{
	int new_label = curr_label;
	curr_label++;
	int new_label2 = curr_label;
	curr_label++;
	int next_label = curr_label;
	curr_label++;

	addTriple2("Label",INF,INF,new_label,INF);
	solveBool(curr->children[1],new_label2,next_label);
	addTriple2("Label",INF,INF,new_label2,INF);
	solveStmtHelper(curr->children[2] , curr->children[3]);
	addTriple2("Jump",INF,INF,INF,new_label);
	addTriple2("Label",INF,INF,next_label,INF);

}




void generateCode(ASTNode* t,const char* asmFile)
{

	curr_label = 0 ;

	//printf("okay\n");
	root =t ;
	ASTNode* mainNode = root->children[1];
	ASTNode* stmtsNode = mainNode->children[1];
	ASTNode* impStmtNode = stmtsNode->children[2];


	solveStmt(impStmtNode);
	//printf("///////////////////\n");
	//displayTriple();
	printf("Starting assembly code gen... ");
	generateAssemblyCode(currTriple,curr_index,asmFile);
	printf("Done\n");
}



