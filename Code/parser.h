/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: parser.h
* @Date:      2016-02-29 10:14:56
*/

#ifndef PARSER_H
#define PARSER_H

#include "parserTable.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

parseTreeNode* createEmptyTreeNode(int nodeid, int lineno, float valuelfNumber, NONTERMINAL pntid);
// the last token that comes in the source code file is TK_EOF
// add TK_DOLLAR before TK_EOF so that we can use TK_EOF as the loop break condition
parseTree parseInputSourceCode(const char *testcaseFile, prodRuleNode** rulelist, parserTable T);

#endif