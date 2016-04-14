/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: AST.h
* @Date:      2016-03-29 10:44:42
*/

#ifndef AST_H
#define AST_H

#include "ASTDef.h"
#include "parserDef.h"
#include "parserUtils.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

ASTRuleNode** readASTRuleList(const char* filename);
ASTNode* createASTfromPT(parseTree PT, ASTRuleNode** ast_rule_list);
void displayASTRuleList(ASTRuleNode** ast_rule_list, grammar rulelist);
void displayAST(ASTNode* a, const char* outfile);
ASTNode* makeASTSymbolTableLinks(ASTNode* AT, GlobalTable* global_table, funcIdTable* local_table, recordTable* record_table);
ASTNode* insertRecordDeclarations(ASTNode* AT, recordTable* record_table);

#endif