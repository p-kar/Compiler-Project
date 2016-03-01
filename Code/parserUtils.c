/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: parserUtils.c
* @Date:      2016-02-18 10:25:17
*/
#include "parserUtils.h"

NONTERMINAL getNonTerminalfromStr(const char* str)
{
    if(strcmp(str, "<program>") == 0)
        return PROGRAM;
    else if(strcmp(str, "<otherFunctions>") == 0)
        return OTHERFUNCTIONS;
    else if(strcmp(str, "<mainFunction>") == 0)
        return MAINFUNCTION;
    else if(strcmp(str, "<stmts>") == 0)
        return STMTS;
    else if(strcmp(str, "<function>") == 0)
        return FUNCTION;
    else if(strcmp(str, "<dataType>") == 0)
        return DATATYPE;
    else if(strcmp(str, "<primitiveDatatype>") == 0)
        return PRIMITIVEDATATYPE;
    else if(strcmp(str, "<constructedDatatype>") == 0)
        return CONSTRUCTEDDATATYPE;
    else if(strcmp(str, "<typeDefinitions>") == 0)
        return TYPEDEFINITIONS;
    else if(strcmp(str, "<declarations>") == 0)
        return DECLARATIONS;
    else if(strcmp(str, "<otherStmts>") == 0)
        return OTHERSTMTS;
    else if(strcmp(str, "<returnStmt>") == 0)
        return RETURNSTMT;
    else if(strcmp(str, "<typeDefinition>") == 0)
        return TYPEDEFINITION;
    else if(strcmp(str, "<fieldDefinitions>") == 0)
        return FIELDDEFINITIONS;
    else if(strcmp(str, "<fieldDefinition>") == 0)
        return FIELDDEFINITION;
    else if(strcmp(str, "<moreFields>") == 0)
        return MOREFIELDS;
    else if(strcmp(str, "<declaration>") == 0)
        return DECLARATION;
    else if(strcmp(str, "<stmt>") == 0)
        return STMT;
    else if(strcmp(str, "<assignmentStmt>") == 0)
        return ASSIGNMENTSTMT;
    else if(strcmp(str, "<iterativeStmt>") == 0)
        return ITERATIVESTMT;
    else if(strcmp(str, "<conditionalStmt>") == 0)
        return CONDITIONALSTMT;
    else if(strcmp(str, "<elsePart>") == 0)
        return ELSEPART;
    else if(strcmp(str, "<ioStmt>") == 0)
        return IOSTMT;
    else if(strcmp(str, "<funCallStmt>") == 0)
        return FUNCALLSTMT;
    else if(strcmp(str, "<arithmeticExpression>") == 0)
        return ARITHMETICEXPRESSION;
    else if(strcmp(str, "<singleOrRecId>") == 0)
        return SINGLEORRECID;
    else if(strcmp(str, "<new_24>") == 0)
        return NEW24;
    else if(strcmp(str, "<outputParameters>") == 0)
        return OUTPUTPARAMETERS;
    else if(strcmp(str, "<inputParameters>") == 0)
        return INPUTPARAMETERS;
    else if(strcmp(str, "<idList>") == 0)
        return IDLIST;
    else if(strcmp(str, "<booleanExpression>") == 0)
        return BOOLEANEXPRESSION;
    else if(strcmp(str, "<allVar>") == 0)
        return ALLVAR;
    else if(strcmp(str, "<var>") == 0)
        return VAR;
    else if(strcmp(str, "<logicalOp>") == 0)
        return LOGICALOP;
    else if(strcmp(str, "<relationalOp>") == 0)
        return RELATIONALOP;
    else if(strcmp(str, "<optionalReturn>") == 0)
        return OPTIONALRETURN;
    else if(strcmp(str, "<input_par>") == 0)
        return INPUTPAR;
    else if(strcmp(str, "<output_par>") == 0)
        return OUTPUTPAR;
    else if(strcmp(str, "<global_or_not>") == 0)
        return GLOBALORNOT;
    else if(strcmp(str, "<parameter_list>") == 0)
        return PARAMETERLIST;
    else if(strcmp(str, "<remaining_list>") == 0)
        return REMAININGLIST;
    else if(strcmp(str, "<more_ids>") == 0)
        return MOREIDS;
    else if(strcmp(str, "<term>") == 0)
        return TERM;
    else if(strcmp(str, "<expPrime>") == 0)
        return EXPPRIME;
    else if(strcmp(str, "<lowPrecedenceOperators>") == 0)
        return LOWPRECEDENCEOPERATORS;
    else if(strcmp(str, "<factor>") == 0)
        return FACTOR;
    else if(strcmp(str, "<highPrecedenceOperators>") == 0)
        return HIGHPRECEDENCEOPERATORS;
    else if(strcmp(str, "<termPrime>") == 0)
        return TERMPRIME;
    else if(strcmp(str, "<all>") == 0)
        return ALL;
    else if(strcmp(str, "<temp>") == 0)
        return TEMP;
    return NONTERMERROR;
}

char* getNonTerminalStr(NONTERMINAL ntid)
{
    char* str = (char*) malloc(sizeof(char) * 100);
    if(ntid == PROGRAM)
        strcpy(str, "<PROGRAM>");
    else if(ntid == OTHERFUNCTIONS)
        strcpy(str, "<OTHERFUNCTIONS>");
    else if(ntid == MAINFUNCTION)
        strcpy(str, "<MAINFUNCTION>");
    else if(ntid == STMTS)
        strcpy(str, "<STMTS>");
    else if(ntid == FUNCTION)
        strcpy(str, "<FUNCTION>");
    else if(ntid == DATATYPE)
        strcpy(str, "<DATATYPE>");
    else if(ntid == PRIMITIVEDATATYPE)
        strcpy(str, "<PRIMITIVEDATATYPE>");
    else if(ntid == CONSTRUCTEDDATATYPE)
        strcpy(str, "<CONSTRUCTEDDATATYPE>");
    else if(ntid == TYPEDEFINITIONS)
        strcpy(str, "<TYPEDEFINITIONS>");
    else if(ntid == DECLARATIONS)
        strcpy(str, "<DECLARATIONS>");
    else if(ntid == OTHERSTMTS)
        strcpy(str, "<OTHERSTMTS>");
    else if(ntid == RETURNSTMT)
        strcpy(str, "<RETURNSTMT>");
    else if(ntid == TYPEDEFINITION)
        strcpy(str, "<TYPEDEFINITION>");
    else if(ntid == FIELDDEFINITIONS)
        strcpy(str, "<FIELDDEFINITIONS>");
    else if(ntid == FIELDDEFINITION)
        strcpy(str, "<FIELDDEFINITION>");
    else if(ntid == MOREFIELDS)
        strcpy(str, "<MOREFIELDS>");
    else if(ntid == DECLARATION)
        strcpy(str, "<DECLARATION>");
    else if(ntid == STMT)
        strcpy(str, "<STMT>");
    else if(ntid == ASSIGNMENTSTMT)
        strcpy(str, "<ASSIGNMENTSTMT>");
    else if(ntid == ITERATIVESTMT)
        strcpy(str, "<ITERATIVESTMT>");
    else if(ntid == CONDITIONALSTMT)
        strcpy(str, "<CONDITIONALSTMT>");
    else if(ntid == ELSEPART)
        strcpy(str, "<ELSEPART>");
    else if(ntid == IOSTMT)
        strcpy(str, "<IOSTMT>");
    else if(ntid == FUNCALLSTMT)
        strcpy(str, "<FUNCALLSTMT>");
    else if(ntid == SINGLEORRECID)
        strcpy(str, "<SINGLEORRECID>");
    else if(ntid == NEW24)
        strcpy(str, "<NEW24>");
    else if(ntid == ARITHMETICEXPRESSION)
        strcpy(str, "<ARITHMETICEXPRESSION>");
    else if(ntid == SINGLEORRECID)
        strcpy(str, "<SINGLEORRECID>");
    else if(ntid == OUTPUTPARAMETERS)
        strcpy(str, "<OUTPUTPARAMETERS>");
    else if(ntid == INPUTPARAMETERS)
        strcpy(str, "<INPUTPARAMETERS>");
    else if(ntid == IDLIST)
        strcpy(str, "<IDLIST>");
    else if(ntid == BOOLEANEXPRESSION)
        strcpy(str, "<BOOLEANEXPRESSION>");
    else if(ntid == ALLVAR)
        strcpy(str, "<ALLVAR>");
    else if(ntid == VAR)
        strcpy(str, "<VAR>");
    else if(ntid == LOGICALOP)
        strcpy(str, "<LOGICALOP>");
    else if(ntid == RELATIONALOP)
        strcpy(str, "<RELATIONALOP>");
    else if(ntid == OPTIONALRETURN)
        strcpy(str, "<OPTIONALRETURN>");
    else if(ntid == INPUTPAR)
        strcpy(str, "<INPUTPAR>");
    else if(ntid == OUTPUTPAR)
        strcpy(str, "<OUTPUTPAR>");
    else if(ntid == GLOBALORNOT)
        strcpy(str, "<GLOBALORNOT>");
    else if(ntid == PARAMETERLIST)
        strcpy(str, "<PARAMETERLIST>");
    else if(ntid == REMAININGLIST)
        strcpy(str, "<REMAININGLIST>");
    else if(ntid == MOREIDS)
        strcpy(str, "<MOREIDS>");
    else if(ntid == TERM)
        strcpy(str, "<TERM>");
    else if(ntid == EXPPRIME)
        strcpy(str, "<EXPPRIME>");
    else if(ntid == LOWPRECEDENCEOPERATORS)
        strcpy(str, "<LOWPRECEDENCEOPERATORS>");
    else if(ntid == FACTOR)
        strcpy(str, "<FACTOR>");
    else if(ntid == HIGHPRECEDENCEOPERATORS)
        strcpy(str, "<HIGHPRECEDENCEOPERATORS>");
    else if(ntid == TERMPRIME)
        strcpy(str, "<TERMPRIME>");
    else if(ntid ==  ALL)
        strcpy(str, "<ALL>");
    else if(ntid == TEMP)
        strcpy(str, "<TEMP>");
    else
        strcpy(str, "<NONTERMERROR>");
    return str;
}

char* getIDStr(int id)
{
    if(id == -1)    // for parse tree printing
        return "ROOT";
    if(isTerminal(id))
        return getTerminalStr(id);
    return getNonTerminalStr(id);
}

bool isNonTerminal(int nontermid)
{
    if(nontermid >= NONTERMINAL_OFFSET && nontermid <= NONTERMINAL_OFFSET + NUM_NONTERMINALS)
        return true;
    return false;
}

prodRuleNode* createProdRuleNode(NONTERMINAL ntid)
{
    prodRuleNode* p = (prodRuleNode*) malloc(sizeof(prodRuleNode));
    p->ntid = ntid;
    p->prod_rule_cnt = 0;
    p->rule_length = NULL;
    p->prod_rules = NULL;
    p->rhs_occ_cnt = 0;
    p->rhs_occs = NULL;
    p->follow_set_flag = 0;
    return p;
}

prodRuleNode** initialiseProdRuleList()
{
    prodRuleNode** rulelist = (prodRuleNode**) malloc(sizeof(prodRuleNode*) * NUM_NONTERMINALS);
    int i;
    for (i = 0; i < NUM_NONTERMINALS; ++i)
        rulelist[i] = createProdRuleNode(i);
    return rulelist;
}

void printProdRule(int ntid, int rno, prodRuleNode** rulelist)
{
    if(rulelist == NULL)
        return;
    prodRuleNode* p = rulelist[ntid];
    int i = rno, j;
    if(rno >= p->prod_rule_cnt)
    {
        fprintf(stderr, "Not a valid rule\n");
        return;
    }
    char* token = getNonTerminalStr(ntid);
    printf("%s ===> ", token);
    for (j = 0; j < p->rule_length[i]; ++j)
    {
        if(isTerminal(p->prod_rules[i][j]))
            token = getTerminalStr(p->prod_rules[i][j]);
        else
            token = getNonTerminalStr(p->prod_rules[i][j]);
        printf("%s ", token);
    }
    printf("\n");
}

void printProdRules(int ntid, prodRuleNode** rulelist)
{
    if(rulelist == NULL)
        return;
    prodRuleNode* p = rulelist[ntid];
    int i, j;
    for (i = 0; i < p->prod_rule_cnt; ++i)
    {
        char* token = getNonTerminalStr(ntid);
        printf("%s ===> ", token);
        for (j = 0; j < p->rule_length[i]; ++j)
        {
            if(isTerminal(p->prod_rules[i][j]))
                token = getTerminalStr(p->prod_rules[i][j]);
            else
                token = getNonTerminalStr(p->prod_rules[i][j]);
            printf("%s ", token);
        }
        printf("\n");
    }
}

void printAllRules(prodRuleNode** rulelist)
{
    int i;
    for (i = 0; i < NUM_NONTERMINALS; ++i)
        printProdRules(i, rulelist);
}

prodRuleNode** addProdRule(char* str, prodRuleNode** rulelist)
{
    char* token;
    token = strtok(str, " \n");
    int ntid = getNonTerminalfromStr(token);
    int prod_rule_idx = rulelist[ntid]->prod_rule_cnt;
    rulelist[ntid]->prod_rule_cnt++;
    rulelist[ntid]->rule_length = (int*) realloc(rulelist[ntid]->rule_length, sizeof(int) * (prod_rule_idx + 1));
    rulelist[ntid]->rule_length[prod_rule_idx] = 0;
    rulelist[ntid]->prod_rules = (int**) realloc(rulelist[ntid]->prod_rules, sizeof(int*) * (prod_rule_idx + 1));
    rulelist[ntid]->prod_rules[prod_rule_idx] = NULL;
    // to get ===>
    token = strtok(NULL, " \n");
    // to get the next element
    token = strtok(NULL, " \n");
    while(token != NULL)
    {
        if(strlen(token) == 0)
            break;
        int id;
        id = getTerminalfromStr(token);
        if(id == TK_ERROR)
        {
            id = getNonTerminalfromStr(token);
            rulelist[id]->rhs_occ_cnt++;
            rulelist[id]->rhs_occs = (rhsOcc*) realloc(rulelist[id]->rhs_occs, sizeof(rhsOcc) * (rulelist[id]->rhs_occ_cnt));
            rulelist[id]->rhs_occs[rulelist[id]->rhs_occ_cnt - 1].ntid = ntid;
            rulelist[id]->rhs_occs[rulelist[id]->rhs_occ_cnt - 1].i = prod_rule_idx;
            rulelist[id]->rhs_occs[rulelist[id]->rhs_occ_cnt - 1].j = rulelist[ntid]->rule_length[prod_rule_idx];
        }
        rulelist[ntid]->rule_length[prod_rule_idx]++;
        rulelist[ntid]->prod_rules[prod_rule_idx] = (int*) realloc(rulelist[ntid]->prod_rules[prod_rule_idx], sizeof(int) * rulelist[ntid]->rule_length[prod_rule_idx]);
        rulelist[ntid]->prod_rules[prod_rule_idx][rulelist[ntid]->rule_length[prod_rule_idx] - 1] = id;
        token = strtok(NULL, " ");
    }
    return rulelist;
}

prodRuleNode** getRuleList(const char* grammar_filename)
{
    FILE* file = fopen(grammar_filename, "r");
    char line[1000];
    prodRuleNode** rulelist = initialiseProdRuleList();
    while(fgets(line, sizeof(line), file) != NULL)
    {
        line[strlen(line) - 1] = '\0';
        rulelist = addProdRule(line, rulelist);
    }
    fclose(file);
    return rulelist;
}
