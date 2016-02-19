/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: parserSets.h
* @Date:      2016-02-18 10:26:52
*/
#ifndef PARSERSETS_H
#define PARSERSETS_H

// #define ENABLE_PRINTING_FIRST_SETS
// #define ENABLE_PRINTING_FOLLOW_SETS

#include "parserUtils.h"
#include "parserDef.h"
#include "set.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

set** initialiseSetList();
bool hasEpsRule(int ntid, prodRuleNode** rulelist);
void displaySet(set* st);
set* computeFirstSets(int id, prodRuleNode** rulelist, set** firststs);
set* computeFollowSets(int id, prodRuleNode** rulelist, set **firststs, set** followsts, int* rec_stack, int stack_size);
set** createFirstSets(prodRuleNode** rulelist);
set** createFollowSets(prodRuleNode** rulelist, set** firststs);

#endif