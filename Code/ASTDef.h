/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: ASTDef.h
* @Date:      2016-03-29 10:44:42
*/

#ifndef ASTDEF_H
#define ASTDEF_H

#include "parserDef.h"
#include "parserUtils.h"
#include "symbolTable.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct _ASTRuleNode
{
    int action; // 0: trim, 1: collapse linear chain, -1: replace with NULL
    int ast_child_cnt;
    int rule_length;
    bool *flags;
};
typedef struct _ASTRuleNode ASTRuleNode;

struct _ASTNode
{
    int nodeid;
    int rno;
    tokenInfo tk;
    int child_cnt;
    struct _ASTNode** children;
    GlobalTable* global_table;
    funcIdTable* local_table;
    recordTable* record_table;
};
typedef struct _ASTNode ASTNode;

#endif