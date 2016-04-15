/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: semanticAnalyzer.h
* @Date:      2016-03-29 10:44:42
*/

#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"

struct _modSet
{
    char id[500];
    struct _modSet *next;
};
typedef struct _modSet modSet;

void runSemanticAnalyzer(ASTNode* AT);

#endif