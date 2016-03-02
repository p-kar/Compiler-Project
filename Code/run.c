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
#include "parserUtils.h"
#include "parserTable.h"
#include "parser.h"

int main(int argc, char const *argv[])
{
    // remember add a new line at the end of grammar.txt
    // TODO need to handle this error
    char filename[] = "./Grammar/final_grammar.txt";
    char src_filename[] = "./Testcases/testcase2.txt";
    // char filename[] = "./Grammar/test_grammar.txt";
    prodRuleNode** rulelist = getRuleList(filename);
    // printAllRules(rulelist);
    parserTable p = populateParserTable(rulelist);
    parseTree PT = parseInputSourceCode(src_filename, rulelist, p);
    printParseTree(PT, "ptree.txt");
    // displayParserTable(p);
    return 0;
}