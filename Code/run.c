/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: run.c
* @Date:      2016-02-18 01:54:45
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parserDef.h"
#include "parserUtils.h"
#include "parserSets.h"
#include "parserTable.h"
#include "set.h"

int main(int argc, char const *argv[])
{
    // remember add a new line at the end of grammar.txt
    // TODO need to handle this error
    char filename[] = "./Grammar/final_grammar.txt";
    // char filename[] = "./Grammar/test_grammar.txt";
    FILE* file = fopen(filename, "r");
    char line[1000];
    prodRuleNode** rulelist = initialiseProdRuleList();
    while(fgets(line, sizeof(line), file) != NULL)
    {
        line[strlen(line) - 1] = '\0';
        rulelist = addProdRule(line, rulelist);
    }
    // printAllRules(rulelist);
    set** firststs = createFirstSets(rulelist);
    set** followsts = createFollowSets(rulelist, firststs);
    parserTable p = populateParserTable(rulelist, firststs, followsts);
    displayParserTable(p);
    fclose(file);
    return 0;
}