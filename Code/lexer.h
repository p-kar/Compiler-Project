/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: lexer.h
* @Date:      2016-02-29 13:30:38
*/

#ifndef LEXER_C
#define LEXER_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexerDef.h"
tokenInfo getNextToken(FILE *fp);
TERMINAL getTerminalfromStr(const char* str);
bool isTerminal(int termid);
char* getTerminalStr(TERMINAL termid);

#endif