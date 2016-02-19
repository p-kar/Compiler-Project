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

TERMINAL getTerminalfromStr(const char* str)
{
    if(strcmp(str, "TK_MAIN") == 0)
        return TK_MAIN;
    else if(strcmp(str, "TK_END") == 0)
        return TK_END;
    else if(strcmp(str, "TK_FUNID") == 0)
        return TK_FUNID;
    else if(strcmp(str, "TK_SEM") == 0)
        return TK_SEM;
    else if(strcmp(str, "TK_INPUT") == 0)
        return TK_INPUT;
    else if(strcmp(str, "TK_PARAMETER") == 0)
        return TK_PARAMETER;
    else if(strcmp(str, "TK_LIST") == 0)
        return TK_LIST;
    else if(strcmp(str, "TK_SQL") == 0)
        return TK_SQL;
    else if(strcmp(str, "TK_SQR") == 0)
        return TK_SQR;
    else if(strcmp(str, "TK_OUTPUT") == 0)
        return TK_OUTPUT;
    else if(strcmp(str, "TK_ID") == 0)
        return TK_ID;
    else if(strcmp(str, "TK_INT") == 0)
        return TK_INT;
    else if(strcmp(str, "TK_REAL") == 0)
        return TK_REAL;
    else if(strcmp(str, "TK_RECORD") == 0)
        return TK_RECORD;
    else if(strcmp(str, "TK_RECORDID") == 0)
        return TK_RECORDID;
    else if(strcmp(str, "TK_COMMA") == 0)
        return TK_COMMA;
    else if(strcmp(str, "TK_ENDRECORD") == 0)
        return TK_ENDRECORD;
    else if(strcmp(str, "TK_TYPE") == 0)
        return TK_TYPE;
    else if(strcmp(str, "TK_COLON") == 0)
        return TK_COLON;
    else if(strcmp(str, "TK_FIELDID") == 0)
        return TK_FIELDID;
    else if(strcmp(str, "TK_GLOBAL") == 0)
        return TK_GLOBAL;
    else if(strcmp(str, "TK_ASSIGNOP") == 0)
        return TK_ASSIGNOP;
    else if(strcmp(str, "TK_DOT") == 0)
        return TK_DOT;
    else if(strcmp(str, "TK_CALL") == 0)
        return TK_CALL;
    else if(strcmp(str, "TK_WITH") == 0)
        return TK_WITH;
    else if(strcmp(str, "TK_PARAMETERS") == 0)
        return TK_PARAMETERS;
    else if(strcmp(str, "TK_WHILE") == 0)
        return TK_WHILE;
    else if(strcmp(str, "TK_OP") == 0)
        return TK_OP;
    else if(strcmp(str, "TK_CL") == 0)
        return TK_CL;
    else if(strcmp(str, "TK_ENDWHILE") == 0)
        return TK_ENDWHILE;
    else if(strcmp(str, "TK_IF") == 0)
        return TK_IF;
    else if(strcmp(str, "TK_THEN") == 0)
        return TK_THEN;
    else if(strcmp(str, "TK_ELSE") == 0)
        return TK_ELSE;
    else if(strcmp(str, "TK_ENDIF") == 0)
        return TK_ENDIF;
    else if(strcmp(str, "TK_READ") == 0)
        return TK_READ;
    else if(strcmp(str, "TK_WRITE") == 0)
        return TK_WRITE;
    else if(strcmp(str, "TK_PLUS") == 0)
        return TK_PLUS;
    else if(strcmp(str, "TK_MUL") == 0)
        return TK_MUL;
    else if(strcmp(str, "TK_MINUS") == 0)
        return TK_MINUS;
    else if(strcmp(str, "TK_DIV") == 0)
        return TK_DIV;
    else if(strcmp(str, "TK_NOT") == 0)
        return TK_NOT;
    else if(strcmp(str, "TK_NUM") == 0)
        return TK_NUM;
    else if(strcmp(str, "TK_RNUM") == 0)
        return TK_RNUM;
    else if(strcmp(str, "TK_AND") == 0)
        return TK_AND;
    else if(strcmp(str, "TK_OR") == 0)
        return TK_OR;
    else if(strcmp(str, "TK_LT") == 0)
        return TK_LT;
    else if(strcmp(str, "TK_LE") == 0)
        return TK_LE;
    else if(strcmp(str, "TK_EQ") == 0)
        return TK_EQ;
    else if(strcmp(str, "TK_GT") == 0)
        return TK_GT;
    else if(strcmp(str, "TK_GE") == 0)
        return TK_GE;
    else if(strcmp(str, "TK_NE") == 0)
        return TK_NE;
    else if(strcmp(str, "TK_RETURN") == 0)
        return TK_RETURN;
    else if(strcmp(str, "TK_EPS") == 0)
        return TK_EPS;
    else if(strcmp(str, "TK_DOLLAR") == 0)
        return TK_DOLLAR;
    return TK_ERROR;
}

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

char* getTerminalStr(TERMINAL termid)
{
    char* str = (char*) malloc(sizeof(char) * 100);
    if(TK_MAIN == termid)
        strcpy(str, "TK_MAIN");
    else if(TK_END == termid)
        strcpy(str, "TK_END");
    else if(TK_FUNID == termid)
        strcpy(str, "TK_FUNID");
    else if(TK_SEM == termid)
        strcpy(str, "TK_SEM");
    else if(TK_INPUT == termid)
        strcpy(str, "TK_INPUT");
    else if(TK_PARAMETER == termid)
        strcpy(str, "TK_PARAMETER");
    else if(TK_LIST == termid)
        strcpy(str, "TK_LIST");
    else if(TK_SQL == termid)
        strcpy(str, "TK_SQL");
    else if(TK_SQR == termid)
        strcpy(str, "TK_SQR");
    else if(TK_OUTPUT == termid)
        strcpy(str, "TK_OUTPUT");
    else if(TK_ID == termid)
        strcpy(str, "TK_ID");
    else if(TK_INT == termid)
        strcpy(str, "TK_INT");
    else if(TK_REAL == termid)
        strcpy(str, "TK_REAL");
    else if(TK_RECORD == termid)
        strcpy(str, "TK_RECORD");
    else if(TK_RECORDID == termid)
        strcpy(str, "TK_RECORDID");
    else if(TK_COMMA == termid)
        strcpy(str, "TK_COMMA");
    else if(TK_ENDRECORD == termid)
        strcpy(str, "TK_ENDRECORD");
    else if(TK_TYPE == termid)
        strcpy(str, "TK_TYPE");
    else if(TK_COLON == termid)
        strcpy(str, "TK_COLON");
    else if(TK_FIELDID == termid)
        strcpy(str, "TK_FIELDID");
    else if(TK_GLOBAL == termid)
        strcpy(str, "TK_GLOBAL");
    else if(TK_ASSIGNOP == termid)
        strcpy(str, "TK_ASSIGNOP");
    else if(TK_DOT == termid)
        strcpy(str, "TK_DOT");
    else if(TK_CALL == termid)
        strcpy(str, "TK_CALL");
    else if(TK_WITH == termid)
        strcpy(str, "TK_WITH");
    else if(TK_PARAMETERS == termid)
        strcpy(str, "TK_PARAMETERS");
    else if(TK_WHILE == termid)
        strcpy(str, "TK_WHILE");
    else if(TK_OP == termid)
        strcpy(str, "TK_OP");
    else if(TK_CL == termid)
        strcpy(str, "TK_CL");
    else if(TK_ENDWHILE == termid)
        strcpy(str, "TK_ENDWHILE");
    else if(TK_IF == termid)
        strcpy(str, "TK_IF");
    else if(TK_THEN == termid)
        strcpy(str, "TK_THEN");
    else if(TK_ELSE == termid)
        strcpy(str, "TK_ELSE");
    else if(TK_ENDIF == termid)
        strcpy(str, "TK_ENDIF");
    else if(TK_READ == termid)
        strcpy(str, "TK_READ");
    else if(TK_WRITE == termid)
        strcpy(str, "TK_WRITE");
    else if(TK_PLUS == termid)
        strcpy(str, "TK_PLUS");
    else if(TK_MUL == termid)
        strcpy(str, "TK_MUL");
    else if(TK_MINUS == termid)
        strcpy(str, "TK_MINUS");
    else if(TK_DIV == termid)
        strcpy(str, "TK_DIV");
    else if(TK_NOT == termid)
        strcpy(str, "TK_NOT");
    else if(TK_NUM == termid)
        strcpy(str, "TK_NUM");
    else if(TK_RNUM == termid)
        strcpy(str, "TK_RNUM");
    else if(TK_AND == termid)
        strcpy(str, "TK_AND");
    else if(TK_OR == termid)
        strcpy(str, "TK_OR");
    else if(TK_LT == termid)
        strcpy(str, "TK_LT");
    else if(TK_LE == termid)
        strcpy(str, "TK_LE");
    else if(TK_EQ == termid)
        strcpy(str, "TK_EQ");
    else if(TK_GT == termid)
        strcpy(str, "TK_GT");
    else if(TK_GE == termid)
        strcpy(str, "TK_GE");
    else if(TK_NE == termid)
        strcpy(str, "TK_NE");
    else if(TK_RETURN == termid)
        strcpy(str, "TK_RETURN");
    else if(TK_EPS == termid)
        strcpy(str, "eps");
    else if(TK_DOLLAR == termid)
        strcpy(str, "$");
    else
        strcpy(str, "TK_ERROR");
    return str;
}

char* getNonTerminalStr(NONTERMINAL ntid)
{
    char* str = (char*) malloc(sizeof(char) * 100);
    if(ntid == PROGRAM)
        strcpy(str, "PROGRAM");
    else if(ntid == OTHERFUNCTIONS)
        strcpy(str, "OTHERFUNCTIONS");
    else if(ntid == MAINFUNCTION)
        strcpy(str, "MAINFUNCTION");
    else if(ntid == STMTS)
        strcpy(str, "STMTS");
    else if(ntid == FUNCTION)
        strcpy(str, "FUNCTION");
    else if(ntid == DATATYPE)
        strcpy(str, "DATATYPE");
    else if(ntid == PRIMITIVEDATATYPE)
        strcpy(str, "PRIMITIVEDATATYPE");
    else if(ntid == CONSTRUCTEDDATATYPE)
        strcpy(str, "CONSTRUCTEDDATATYPE");
    else if(ntid == TYPEDEFINITIONS)
        strcpy(str, "TYPEDEFINITIONS");
    else if(ntid == DECLARATIONS)
        strcpy(str, "DECLARATIONS");
    else if(ntid == OTHERSTMTS)
        strcpy(str, "OTHERSTMTS");
    else if(ntid == RETURNSTMT)
        strcpy(str, "RETURNSTMT");
    else if(ntid == TYPEDEFINITION)
        strcpy(str, "TYPEDEFINITION");
    else if(ntid == FIELDDEFINITIONS)
        strcpy(str, "FIELDDEFINITIONS");
    else if(ntid == FIELDDEFINITION)
        strcpy(str, "FIELDDEFINITION");
    else if(ntid == MOREFIELDS)
        strcpy(str, "MOREFIELDS");
    else if(ntid == DECLARATION)
        strcpy(str, "DECLARATION");
    else if(ntid == STMT)
        strcpy(str, "STMT");
    else if(ntid == ASSIGNMENTSTMT)
        strcpy(str, "ASSIGNMENTSTMT");
    else if(ntid == ITERATIVESTMT)
        strcpy(str, "ITERATIVESTMT");
    else if(ntid == CONDITIONALSTMT)
        strcpy(str, "CONDITIONALSTMT");
    else if(ntid == ELSEPART)
        strcpy(str, "ELSEPART");
    else if(ntid == IOSTMT)
        strcpy(str, "IOSTMT");
    else if(ntid == FUNCALLSTMT)
        strcpy(str, "FUNCALLSTMT");
    else if(ntid == SINGLEORRECID)
        strcpy(str, "SINGLEORRECID");
    else if(ntid == NEW24)
        strcpy(str, "NEW24");
    else if(ntid == ARITHMETICEXPRESSION)
        strcpy(str, "ARITHMETICEXPRESSION");
    else if(ntid == SINGLEORRECID)
        strcpy(str, "SINGLEORRECID");
    else if(ntid == OUTPUTPARAMETERS)
        strcpy(str, "OUTPUTPARAMETERS");
    else if(ntid == INPUTPARAMETERS)
        strcpy(str, "INPUTPARAMETERS");
    else if(ntid == IDLIST)
        strcpy(str, "IDLIST");
    else if(ntid == BOOLEANEXPRESSION)
        strcpy(str, "BOOLEANEXPRESSION");
    else if(ntid == ALLVAR)
        strcpy(str, "ALLVAR");
    else if(ntid == VAR)
        strcpy(str, "VAR");
    else if(ntid == LOGICALOP)
        strcpy(str, "LOGICALOP");
    else if(ntid == RELATIONALOP)
        strcpy(str, "RELATIONALOP");
    else if(ntid == OPTIONALRETURN)
        strcpy(str, "OPTIONALRETURN");
    else if(ntid == INPUTPAR)
        strcpy(str, "INPUTPAR");
    else if(ntid == OUTPUTPAR)
        strcpy(str, "OUTPUTPAR");
    else if(ntid == GLOBALORNOT)
        strcpy(str, "GLOBALORNOT");
    else if(ntid == PARAMETERLIST)
        strcpy(str, "PARAMETERLIST");
    else if(ntid == REMAININGLIST)
        strcpy(str, "REMAININGLIST");
    else if(ntid == MOREIDS)
        strcpy(str, "MOREIDS");
    else if(ntid == TERM)
        strcpy(str, "TERM");
    else if(ntid == EXPPRIME)
        strcpy(str, "EXPPRIME");
    else if(ntid == LOWPRECEDENCEOPERATORS)
        strcpy(str, "LOWPRECEDENCEOPERATORS");
    else if(ntid == FACTOR)
        strcpy(str, "FACTOR");
    else if(ntid == HIGHPRECEDENCEOPERATORS)
        strcpy(str, "HIGHPRECEDENCEOPERATORS");
    else if(ntid == TERMPRIME)
        strcpy(str, "TERMPRIME");
   else if(ntid ==  ALL)
        strcpy(str, "ALL");
    else if(ntid == TEMP)
        strcpy(str, "TEMP,");
    else
        strcpy(str, "NONTERMERROR");
    return str;
}

bool isTerminal(int termid)
{
    if(termid >= TERMINAL_OFFSET && termid <= TERMINAL_OFFSET + NUM_TERMINALS)
        return true;
    return false;
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

void printProdRule(int ntid, prodRuleNode** rulelist)
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
        printProdRule(i, rulelist);
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
