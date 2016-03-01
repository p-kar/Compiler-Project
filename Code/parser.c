/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: parser.c
* @Date:      2016-02-29 10:44:42
*/

#include "parser.h"

parseTreeNode* createEmptyTreeNode(int nodeid, int lineno, float valuelfNumber, NONTERMINAL pntid)
{
    parseTreeNode *p = (parseTreeNode*) malloc(sizeof(parseTreeNode));
    p->nodeid = nodeid;
    p->lineno = lineno;
    p->valuelfNumber = valuelfNumber;
    if(isTerminal(nodeid))
        p->isLeafNode = true;
    else
        p->isLeafNode = false;
    p->parentNodeSymbol = pntid;
    p->child_cnt = 0;
    p->children = NULL;
    return p;
}

parseTree parseInputSourceCode(const char *testcaseFile, prodRuleNode** rulelist, parserTable T)
{
    FILE *tfp = fopen(testcaseFile, "r");
    tokenInfo *t = (tokenInfo*) malloc(sizeof(tokenInfo));
    getNextToken(tfp, t);
    parseTree pTree = createEmptyTreeNode(PROGRAM, -1, 0.0, -1);
    stackNode* stck = NULL;
    stck = pushStack(TK_DOLLAR, NULL, stck);  // inserting stack bottom symbol
    stck = pushStack(PROGRAM, pTree, stck);   // inserting start symbol
    while(!isEmpty(stck))
    {
        printf("\n");
        printf("Current lexeme: %s\n", getTerminalStr(t->tokenType));
        printStack(stck);
        stackNode* top = topStack(stck);
        stck = popStack(stck);
        parseTreeNode* pnode = top->pnode;
        if(top->val == t->tokenType)
        {
            int cidx = pnode->child_cnt;
            pnode->child_cnt++;
            pnode->children = (parseTreeNode**) realloc(pnode->children, sizeof(parseTreeNode*)*pnode->child_cnt);
            pnode->children[cidx] = createEmptyTreeNode(t->tokenType, t->lineNum, 0.0, pnode->nodeid);
            getNextToken(tfp, t);
            continue;
        }
        else if(isTerminal(top->val))
        {
            fprintf(stderr, "Syntax Error. Expected: %s\n", getTerminalStr(top->val));
            return pTree;
        }
        else if(T[top->val][t->tokenType - TERMINAL_OFFSET] == -1)
        {
            fprintf(stderr, "No rule in the parse table to expand.\n");
            return pTree;
        }
        int rno = T[top->val][t->tokenType - TERMINAL_OFFSET];
        int ridx = rulelist[top->val]->rule_length[rno] - 1;
        printProdRule(top->val, rno, rulelist); // for debugging
        if(rulelist[top->val]->prod_rules[rno][ridx] == TK_EPS)
            continue;
        for (; ridx >= 0; --ridx)
        {
            int idx = pnode->child_cnt;
            pnode->child_cnt++;
            pnode->children = (parseTreeNode**) realloc(pnode->children, sizeof(parseTreeNode*)*pnode->child_cnt);
            pnode->children[idx] = createEmptyTreeNode(rulelist[top->val]->prod_rules[rno][ridx], -1, 0.0, pnode->nodeid);
            int childid = rulelist[top->val]->prod_rules[rno][ridx];
            // printf("inserting: %d %s\n", childid, getIDStr(rulelist[top->val]->prod_rules[rno][ridx]));
            stck = pushStack(childid, pnode->children[idx], stck);
        }
    }
    printf("Compiled Successfully: Input source code is syntactically correct.\n");
    return pTree;
}
