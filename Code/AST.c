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
                ast_rule_list[i]->flags[i] = false;
        }
    }
    return ast_rule_list;
}

ASTNode* createASTfromPT(parseTree p, ASTRuleNode** ast_rule_list)
{
    if(p == NULL)
        return NULL;
    int rno = p->rno;
    printf("%s\n", getIDStr(p->nodeid));
    if(rno == -1)
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
        a->child_cnt = p->child_cnt;
        a->children = (ASTNode**) malloc(sizeof(ASTNode*) * p->child_cnt);
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
