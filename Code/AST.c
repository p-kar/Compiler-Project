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

ASTNode* createASTfromPT(parseTree p, ASTRuleNode** ast_rule_list)
{
    if(p == NULL)
        return NULL;
    int rno = p->rno;
    printf("%s%*s\n", getIDStr(p->nodeid), 50, p->tk.lexeme);
    if(rno == -1)   // Is a terminal
    {
        ASTNode *a = (ASTNode*) malloc(sizeof(ASTNode));
        a->child_cnt = 0;
        a->children = NULL;
        a->nodeid = p->nodeid;
        a->rno = rno;
        a->tk.lineNum = p->tk.lineNum;
        strcpy(a->tk.lexeme, p->tk.lexeme);
        a->tk.tokenType = p->tk.tokenType;
        return a;
    }
    if(ast_rule_list[rno]->action == -1)    //return NULL
        return NULL;
    if(ast_rule_list[rno]->action == 0)     //trim the parse tree
    {
        int i, j = 0;
        ASTNode *a = (ASTNode*) malloc(sizeof(ASTNode));
        a->child_cnt = ast_rule_list[rno]->ast_child_cnt;
        a->children = (ASTNode**) malloc(sizeof(ASTNode*) * a->child_cnt);
        a->nodeid = p->nodeid;
        a->rno = rno;
        a->tk.lineNum = p->tk.lineNum;
        strcpy(a->tk.lexeme, p->tk.lexeme);
        a->tk.tokenType = p->tk.tokenType;
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
