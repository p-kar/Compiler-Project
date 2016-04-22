/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: codeGen.h
* @Date:      2016-03-29 10:44:42
*/


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
void generateCode(ASTNode* t,const char* asmFile);

#endif