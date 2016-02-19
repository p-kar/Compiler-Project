/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: parserUtils.h
* @Date:      2016-02-18 00:15:57
*/
#ifndef PARSERUTILS_H
#define PARSERUTILS_H

#include "parserDef.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

TERMINAL getTerminalfromStr(const char* str);
NONTERMINAL getNonTerminalfromStr(const char* str);
prodRuleNode* createProdRuleNode(NONTERMINAL ntid);
prodRuleNode** initialiseProdRuleList();
prodRuleNode** addProdRule(char* str, prodRuleNode** rulelist);
void printProdRule(int ntid, prodRuleNode** rulelist);
void printAllRules(prodRuleNode** rulelist);
bool isTerminal(int termid);
bool isNonTerminal(int nontermid);
char* getTerminalStr(TERMINAL termid);
char* getNonTerminalStr(NONTERMINAL ntid);

#endif