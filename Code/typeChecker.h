/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: typeChecker.h
* @Date:      2016-03-29 10:44:42
*/

#ifndef TYPECHECKER_H
#define TYPECHECKER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"

enum _Type
{
    TYPE_ERROR = -1,
    TYPE_NULL,
    TYPE_INT,
    TYPE_REAL,
    TYPE_BOOL
};
typedef enum _Type Type;

int getType(ASTNode* AT);
void runTypeCheckerAST(ASTNode* AT);

#endif