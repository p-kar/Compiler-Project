#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lexerDef.h"
#include "ASTDef.h"
#include "symbolTable.h"


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
char* findVarName(char* lexeme);
int solveAssignmentStmt(ASTNode* curr);
int solve(ASTNode* curr);
void solveStmt(ASTNode* impStmtNode);
void solveStmtHelper(ASTNode* stmtNode , ASTNode* impStmtNode);
void solveBool(ASTNode* curr , int label_succ , int label_fail);
void solveConditionalOne(ASTNode* curr);
void solveConditionalTwo(ASTNode* curr);
void solveIterative(ASTNode* curr);
void generateCode(ASTNode* t);
