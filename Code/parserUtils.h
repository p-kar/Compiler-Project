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

NONTERMINAL getNonTerminalfromStr(const char* str);
char* getNonTerminalStr(NONTERMINAL ntid);
bool isNonTerminal(int nontermid);
char* getIDStr(int id);
prodRuleNode* createProdRuleNode(NONTERMINAL ntid);
grammar initialiseProdRuleList();
grammar addProdRule(int rno, char* str, grammar rulelist);
grammar getRuleList(const char* grammar_file);
void printProdRule(int ntid, int rno, grammar rulelist);
void printProdRules(int ntid, grammar rulelist);
void printAllRules(grammar rulelist);

#endif