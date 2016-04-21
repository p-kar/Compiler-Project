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

#include "parserDef.h"
#include "parserUtils.h"
#include "set.h"
#include "parserSets.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

// #define DEBUG_PARSER
// #define PANIC_MODE_PRINTING

typedef int** table;
extern bool PARSING_ERROR_FLAG;

set* getFirstSetsRule(int* prodrule, int rule_length, set** firststs);
table initialiseParserTable();
void addRuleinSet(int ntid, int ruleno, set* st, table p);
void createParseTable(grammar rulelist, table p);
void displayParserTable(table p);
parseTreeNode* createEmptyTreeNode(int nodeid, tokenInfo tk, NONTERMINAL pntid);
parseTree parseInputSourceCode(const char *testcaseFile, grammar rulelist, table T);
void printParseTree(parseTree PT, const char* outfile);
void displayParseTreeSTDOUT(parseTree PT);
int getPTNodeCount(parseTree PT);
int getPTSize(parseTree PT);

#endif