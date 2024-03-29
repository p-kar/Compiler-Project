/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: AST.c
* @Date:      2016-03-29 10:44:42
*/

#include "AST.h"

void displayASTRuleList(ASTRuleNode** ast_rule_list, grammar rulelist)
{
    int i;
    for (i = 0; i < NUM_NONTERMINALS; ++i)
    {
        int j, k;
        for (j = 0; j < rulelist[i]->prod_rule_cnt; ++j)
        {
            int rno = rulelist[i]->rule_no[j];
            if(ast_rule_list[rno]->action == -1)
                printf("REMOVE    %d. NULL\n", rno);
            else
            {
                if(ast_rule_list[rno]->action == 1)
                    printf("COLLAPSE  ");
                else
                    printf("TRIM      ");
                printf("%d. %s ===> ", rno, getIDStr(i));
                for (k = 0; k < rulelist[i]->rule_length[j]; ++k)
                {
                    if(ast_rule_list[rno]->flags[k])
                        printf("%s ", getIDStr(rulelist[i]->prod_rules[j][k]));
                }
                printf("\n");
            }
        }
    }
}

ASTRuleNode** readASTRuleList(const char* filename)
{
    FILE* fp = fopen(filename, "r");
    int n;
    fscanf(fp, "%d", &n);
    ASTRuleNode** ast_rule_list = (ASTRuleNode**) malloc(sizeof(ASTRuleNode*) * n);
    int i;
    for (i = 0; i < n; ++i)
    {
        ast_rule_list[i] = (ASTRuleNode*) malloc(sizeof(ASTRuleNode));
        ast_rule_list[i]->ast_child_cnt = 0;
        fscanf(fp, "%d", &ast_rule_list[i]->action);
        if(ast_rule_list[i]->action == -1)
        {
            ast_rule_list[i]->flags = NULL;
            ast_rule_list[i]->rule_length = 0;
            continue;
        }
        fscanf(fp, "%d", &ast_rule_list[i]->rule_length);
        ast_rule_list[i]->flags = (bool*) malloc(sizeof(bool) * ast_rule_list[i]->rule_length);
        int j;
        for (j = 0; j < ast_rule_list[i]->rule_length; ++j)
        {
            int temp;
            fscanf(fp, "%d", &temp);
            if(temp)
            {
                ast_rule_list[i]->ast_child_cnt++;
                ast_rule_list[i]->flags[j] = true;
            }
            else
                ast_rule_list[i]->flags[j] = false;
        }
    }
    return ast_rule_list;
}

ASTNode* createEmptyASTNode(int rno, int nodeid, tokenInfo tk)
{
    ASTNode *a = (ASTNode*) malloc(sizeof(ASTNode));
    a->child_cnt = 0;
    a->children = NULL;
    a->nodeid = nodeid;
    a->rno = rno;
    a->tk.lineNum = tk.lineNum;
    strcpy(a->tk.lexeme, tk.lexeme);
    a->tk.tokenType = tk.tokenType;
    a->global_table = NULL;
    a->local_table = NULL;
    return a;
}

ASTNode* createASTfromPT(parseTree p, ASTRuleNode** ast_rule_list)
{
    if(p == NULL)
        return NULL;
    int rno = p->rno;
    // printf("%s%*s\n", getIDStr(p->nodeid), 50, p->tk.lexeme);
    if(rno == -1)   // Is a terminal
        return createEmptyASTNode(rno, p->nodeid, p->tk);
    if(ast_rule_list[rno]->action == -1)    //return NULL
        return NULL;
    if(ast_rule_list[rno]->action == 0)     //trim the parse tree
    {
        int i, j = 0;
        ASTNode *a = createEmptyASTNode(rno, p->nodeid, p->tk);
        a->child_cnt = ast_rule_list[rno]->ast_child_cnt;
        a->children = (ASTNode**) malloc(sizeof(ASTNode*) * a->child_cnt);
        for (i = 0; i < p->child_cnt; ++i)
        {
            if(ast_rule_list[rno]->flags[i] == false)
                continue;
            a->children[j] = createASTfromPT(p->children[i], ast_rule_list);
            j++;
        }
        return a;
    }
    // collapsing linear chains
    int i;
    for (i = 0; i < p->child_cnt; ++i)
    {
        if(ast_rule_list[rno]->flags[i] == true)
            break;
    }
    return createASTfromPT(p->children[i], ast_rule_list);
}

void displayASTHelper(ASTNode* a, FILE* fp)
{
    if(a == NULL)
    {
        // fprintf(stderr, "abstract syntax tree is NULL\n");
        return;
    }
    char empty[10] = "----";
    char yes[10] = "YES";
    char no[10] = "NO";
    int space = 25;
    int space_small = 15;
    if(a->child_cnt == 0)
    {
        if(isTerminal(a->nodeid))
        {
            if(a->nodeid == TK_EPS)
                fprintf(fp, "%*s%*s%*s%*s%*s%*s\n", 20, empty, space_small, empty, space_small, getIDStr(a->nodeid), space_small, empty, space_small, yes, space, empty);
            else if(a->nodeid == TK_NUM || a->nodeid == TK_RNUM)
                fprintf(fp, "%*s%*d%*s%*s%*s%*s\n", 20, empty, space_small, a->tk.lineNum, space_small, getIDStr(a->nodeid), space_small, a->tk.lexeme, space_small, yes, space, empty);
            else
                fprintf(fp, "%*s%*d%*s%*s%*s%*s\n", 20, a->tk.lexeme, space_small, a->tk.lineNum, space_small, getIDStr(a->nodeid), space_small, empty, space_small, yes, space, empty);
        }
        else
            fprintf(fp, "%*s%*s%*s%*s%*s%*s\n", 20, empty, space_small, empty, space_small, empty, space_small, empty, space_small, no, space, getIDStr(a->nodeid));
        return;
    }
    fprintf(fp, "%*s%*s%*s%*s%*s%*s\n", 20, empty, space_small, empty, space_small, empty, space_small, empty, space_small, no, space, getIDStr(a->nodeid));
    int idx;
    for (idx = 0; idx < a->child_cnt; ++idx)
        displayASTHelper(a->children[idx], fp);
}

void displayAST(ASTNode* a, const char* outfile)
{
    FILE* fp = fopen(outfile, "w");
    int space = 25;
    int space_small = 15;
    char lexemeCurrentNode[20] = "lexemeCurrentNode";
    char lineno[20] = "lineno";
    char token[20] = "token";
    char valuelfNumber[20] = "valuelfNumber";
    char isLeafNode[20] = "isLeafNode";
    char NodeSymbol[20] = "NodeSymbol";
    fprintf(fp, "%*s%*s%*s%*s%*s%*s\n", 20, lexemeCurrentNode, space_small, lineno, space_small, token, space_small, valuelfNumber, space_small, isLeafNode, space, NodeSymbol);
    displayASTHelper(a, fp);
    fclose(fp);
}

void displayASTSTDOUT(ASTNode* a)
{
    FILE* fp = stdout;
    int space = 25;
    int space_small = 15;
    char lexemeCurrentNode[20] = "lexemeCurrentNode";
    char lineno[20] = "lineno";
    char token[20] = "token";
    char valuelfNumber[20] = "valuelfNumber";
    char isLeafNode[20] = "isLeafNode";
    char NodeSymbol[20] = "NodeSymbol";
    fprintf(fp, "%*s%*s%*s%*s%*s%*s\n", 20, lexemeCurrentNode, space_small, lineno, space_small, token, space_small, valuelfNumber, space_small, isLeafNode, space, NodeSymbol);
    displayASTHelper(a, fp);
    fclose(fp);
}

// handle for record case
ASTNode* insertFunctionParameters(ASTNode* AT, GlobalTable* global_table, funcIdTable* local_table, recordTable* record_table, bool input)
{
    if(AT == NULL)
        return NULL;
    AT->global_table = global_table;
    AT->local_table = local_table;
    AT->record_table = record_table;
    if(getNonTerminalfromStr("<parameter_list>") == AT->nodeid)
    {
        if(input)
        {
            if(AT->children[0]->nodeid == TK_INT || AT->children[0]->nodeid == TK_REAL)
                insertInputParameter(global_table, local_table, AT->children[1]->tk, AT->children[0]->nodeid);
            else
                insertInputParameterRecord(global_table, local_table, AT->children[1]->tk, AT->children[0]->children[1]->tk.lexeme, record_table);
        }
        else
        {
            if(AT->children[0]->nodeid == TK_INT || AT->children[0]->nodeid == TK_REAL)
                insertOutputParameter(global_table, local_table, AT->children[1]->tk, AT->children[0]->nodeid);
            else
                insertOutputParameterRecord(global_table, local_table, AT->children[1]->tk, AT->children[0]->children[1]->tk.lexeme, record_table);
        }
    }
    int i;
    for (i = 0; i < AT->child_cnt; ++i)
        AT->children[i] = insertFunctionParameters(AT->children[i], global_table, local_table, record_table, input);
    return AT;
}

ASTNode* insertRecordEntries(ASTNode* AT, char* record_name, recordTable* record_table)
{
    if(AT == NULL)
        return NULL;
    AT->record_table = record_table;
    if(getNonTerminalfromStr("<fieldDefinition>") == AT->nodeid)
    {
        insertRecordEntry(record_name, record_table, AT->children[1]->tk, AT->children[0]->nodeid);
        return AT;
    }
    int i;
    for (i = 0; i < AT->child_cnt; ++i)
        AT->children[i] = insertRecordEntries(AT->children[i], record_name, record_table);
    return AT;
}

ASTNode* insertRecordDeclarations(ASTNode* AT, recordTable* record_table)
{
    if(AT == NULL)
        return AT;
    AT->record_table = record_table;
    if(getNonTerminalfromStr("<typeDefinition>") != AT->nodeid)
    {
        int i;
        for (i = 0; i < AT->child_cnt; ++i)
            AT->children[i] = insertRecordDeclarations(AT->children[i], record_table);
        return AT;
    }
    insertRecord(AT->children[1]->tk.lexeme, record_table);
    AT->children[2] = insertRecordEntries(AT->children[2], AT->children[1]->tk.lexeme, record_table);
    return AT;
}

ASTNode* makeGlobalSymbolTableLinks(ASTNode* AT, GlobalTable* global_table, recordTable* record_table)
{
    if(AT == NULL)
        return NULL;
    if(isTerminal(AT->nodeid))
    {
        AT->global_table = global_table;
        AT->record_table = record_table;
        return AT;
    }
    if(getNonTerminalfromStr("<typeDefinition>") == AT->nodeid)
        return AT;
    else if(getNonTerminalfromStr("<declaration>") == AT->nodeid)
    {
        AT->global_table = global_table;
        AT->record_table = record_table;
        if(AT->children[2] != NULL)     // TK_GLOBAL
        {
            if(AT->children[0]->nodeid == TK_INT || AT->children[0]->nodeid == TK_REAL)
            {
                insertGlobalId(global_table, AT->children[1]->tk, AT->children[0]->nodeid);
            }
            else
            {
                insertGlobalRecord(global_table, AT->children[1]->tk, TK_RECORD, AT->children[0]->children[1]->tk.lexeme, record_table);
            }
        }
    }
    int i;
    AT->global_table = global_table;
    AT->record_table = record_table;
    for (i = 0; i < AT->child_cnt; ++i)
        AT->children[i] = makeGlobalSymbolTableLinks(AT->children[i], global_table, record_table);
    return AT;
}

ASTNode* makeLocalSymbolTableLinks(ASTNode* AT, GlobalTable* global_table, funcIdTable* local_table, recordTable* record_table)
{
    if(AT == NULL)
        return NULL;
    // printf("%s\n", getIDStr(AT->nodeid));
    if(isTerminal(AT->nodeid))
    {
        AT->global_table = global_table;
        AT->local_table = local_table;
        AT->record_table = record_table;
        return AT;
    }
    // for all these cases ensure return AT because the rest is handled later
    if(getNonTerminalfromStr("<function>") == AT->nodeid)
    {
        local_table = insertFuncIdTable(global_table, AT->children[0]->tk.lexeme);
        if(local_table == NULL)
            return NULL;
        AT->global_table = global_table;
        AT->local_table = local_table;
        AT->record_table = record_table;
        AT->children[1] = insertFunctionParameters(AT->children[1], global_table, local_table, record_table, true);
        AT->children[2] = insertFunctionParameters(AT->children[2], global_table, local_table, record_table, false);
        AT->children[3] = makeLocalSymbolTableLinks(AT->children[3], global_table, local_table, record_table);
        return AT;
    }
    else if(getNonTerminalfromStr("<declaration>") == AT->nodeid)
    {
        // manage TK_INT, TK_REAL, TK_RECORD, TK_GLOBAL
        AT->global_table = global_table;
        AT->local_table = local_table;
        AT->record_table = record_table;
        if(AT->children[2] == NULL)
        {
            if(AT->children[0]->nodeid == TK_INT || AT->children[0]->nodeid == TK_REAL)
            {
                insertLocalId(global_table, local_table, AT->children[1]->tk, AT->children[0]->nodeid);
            }
            else
            {
                insertLocalRecord(global_table, local_table, AT->children[1]->tk, TK_RECORD, AT->children[0]->children[1]->tk.lexeme, record_table);
            }
        }
        return AT;
    }
    else if(getNonTerminalfromStr("<typeDefinition>") == AT->nodeid)
    {
        return AT;
    }
    else if(getNonTerminalfromStr("<mainFunction>") == AT->nodeid)
    {
        local_table = insertFuncIdTable(global_table, AT->children[0]->tk.lexeme);
        if(local_table == NULL)
            return NULL;
        AT->global_table = global_table;
        AT->local_table = local_table;
        AT->record_table = record_table;
        AT->children[1] = makeLocalSymbolTableLinks(AT->children[1], global_table, local_table, record_table);
        return AT;
    }
    int i;
    AT->global_table = global_table;
    AT->local_table = local_table;
    AT->record_table = record_table;
    for (i = 0; i < AT->child_cnt; ++i)
        AT->children[i] = makeLocalSymbolTableLinks(AT->children[i], global_table, local_table, record_table);
    return AT;
}

ASTNode* makeASTSymbolTableLinks(ASTNode* AT)
{
    recordTable* record_table = initializeRecordTable();
    GlobalTable* global_table = initalizeGlobalTable();
    funcIdTable* local_table = NULL;
    AT = insertRecordDeclarations(AT, record_table);
    AT = makeGlobalSymbolTableLinks(AT, global_table, record_table);
    AT = makeLocalSymbolTableLinks(AT, global_table, local_table, record_table);
    return AT;
}

int getLineNumber(ASTNode* AT)
{
    if(AT == NULL)
        return -1;
    if(isTerminal(AT->nodeid))
        return AT->tk.lineNum;
    int i;
    for (i = 0; i < AT->child_cnt; ++i)
    {
        int ln = getLineNumber(AT->children[i]);
        if(ln != -1)
            return ln;
    }
    return -1;
}

int getASTNodeCount(ASTNode* AT)
{
    if(AT == NULL)
        return 0;
    int nd_cnt = 1;
    int i = 0;
    for (i = 0; i < AT->child_cnt; ++i)
        nd_cnt += getASTNodeCount(AT->children[i]);
    return nd_cnt;
}

int getASTSize(ASTNode* AT)
{
    if(AT == NULL)
        return 0;
    return getASTNodeCount(AT) * sizeof(ASTNode);
}
