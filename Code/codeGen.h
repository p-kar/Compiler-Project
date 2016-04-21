#ifndef CODEGEN_H
#define CODEGEN_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lexerDef.h"
#include "ASTDef.h"
#include "symbolTable.h"
#include "typeChecker.h"
#include "assemblyGen.h"
#include "codeGenDef.h"


char* findVarName(char* lexeme);
tuple* solveAssignmentStmt(ASTNode* curr);
int solve(ASTNode* curr);
void solveStmt(ASTNode* impStmtNode);
void solveStmtHelper(ASTNode* stmtNode , ASTNode* impStmtNode);
void solveBool(ASTNode* curr , int label_succ , int label_fail);
void solveConditionalOne(ASTNode* curr);
void solveConditionalTwo(ASTNode* curr);
void solveIterative(ASTNode* curr);
void generateCode(ASTNode* t);

#endif