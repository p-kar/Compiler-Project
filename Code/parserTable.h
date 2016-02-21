/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: parserTable.h
* @Date:      2016-02-20 02:59:54
*/
#ifndef PARSERTABLE_H
#define PARSERTABLE_H

#include "parserUtils.h"
#include "parserDef.h"
#include "set.h"
#include "parserSets.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef int** parserTable;

set* getFirstSetsRule(int* prodrule, int rule_length, set** firststs);
parserTable initialiseParserTable();
void addRuleinSet(int ntid, int ruleno, set* st, parserTable p);
parserTable populateParserTable(prodRuleNode** rulelist, set **firststs, set **followsts);
void displayParserTable(parserTable p);

#endif