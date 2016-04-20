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
#include "parser.h"
#include "AST.h"
#include "typeChecker.h"
#include "semanticAnalyzer.h"
#include "codeGen.h"

int main(int argc, char const *argv[])
{
    // remember add a new line at the end of grammar.txt
    // TODO need to handle this error
    char filename[] = "./Grammar/final_grammar.txt";
    char src_filename[] = "./Semantic Testcases/testcase3.txt";
    grammar rulelist = getRuleList(filename);
    // printAllRules(rulelist);
    table T = initialiseParserTable();
    createParseTable(rulelist, T);
    //displayParserTable(T);
    parseTree PT = parseInputSourceCode(src_filename, rulelist, T);
    printParseTree(PT, "ptree.txt");
    ASTRuleNode** ast_rule_list = readASTRuleList("./Grammar/astrules.txt");
    //displayASTRuleList(ast_rule_list, rulelist);
    ASTNode* AT = createASTfromPT(PT, ast_rule_list);
    displayAST(AT, "atree.txt");
    AT = makeASTSymbolTableLinks(AT);
    // displaySymbolTable(global_table);
    runTypeCheckerAST(AT);
    runSemanticAnalyzer(AT);
    generateCode(AT);
    return 0;
}