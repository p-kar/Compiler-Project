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

set* getFirstSetsRule(int* prodrule, int rule_length, set** firststs)
{
    set* st = NULL;
    int i;
    for (i = 0; i < rule_length; ++i)
    {
        set* fst = getFirstSet(prodrule[i], firststs);
        st = setUnion(st, getFirstSet(prodrule[i], firststs));
        if(!isPresent(TK_EPS, fst))
            return st;
        if(i == rule_length - 1 && isPresent(TK_EPS, fst))
            st = setAdd(TK_EPS, st);
    }
    return st;
}

table initialiseParserTable()
{
    table p = (table) malloc(sizeof(int*) * NUM_NONTERMINALS);
    int i, j;
    for (i = 0; i < NUM_NONTERMINALS; ++i)
        p[i] = (int*) malloc(sizeof(int) * NUM_TERMINALS);
    for (i = 0; i < NUM_NONTERMINALS; ++i)
        for (j = 0; j < NUM_TERMINALS; ++j)
            p[i][j] = -1;
    return p;
}

void addRuleinSet(int ntid, int ruleno, set* st, table p)
{
    if(st == NULL)
        return;
    if(st->val != TK_EPS)
        p[ntid][st->val - TERMINAL_OFFSET] = ruleno;
    addRuleinSet(ntid, ruleno, st->left, p);
    addRuleinSet(ntid, ruleno, st->right, p);
}

void createParseTable(grammar rulelist, table p)
{
    set **firststs = createFirstSets(rulelist);
    set **followsts = createFollowSets(rulelist, firststs);
    int i, j;
    for (i = 0; i < NUM_NONTERMINALS; ++i)
    {
        for (j = 0; j < rulelist[i]->prod_rule_cnt; ++j)
        {
            set* fst = getFirstSetsRule(rulelist[i]->prod_rules[j], rulelist[i]->rule_length[j], firststs);
            addRuleinSet(i, j, fst, p);
            if(isPresent(TK_EPS, fst))
            {
                set* flst = getFollowSet(i, followsts);
                addRuleinSet(i, j, flst, p);
            }
        }
    }
}

void displayParserTable(table p)
{
    printf("X\t");
    int i, j;
    for (i = 0; i < NUM_TERMINALS; ++i)
        printf("%s\t", getTerminalStr(i + TERMINAL_OFFSET));
    printf("\n");
    for (i = 0; i < NUM_NONTERMINALS; ++i)
    {
        printf("%s\t", getNonTerminalStr(i));
        for (j = 0; j < NUM_TERMINALS; ++j)
            printf("%d\t", p[i][j]);
        printf("\n");
    }
}

parseTreeNode* createEmptyTreeNode(int nodeid, tokenInfo tk, NONTERMINAL pntid)
{
    parseTreeNode *p = (parseTreeNode*) malloc(sizeof(parseTreeNode));
    p->nodeid = nodeid;
    p->tk.lineNum = tk.lineNum;
    strcpy(p->tk.lexeme, tk.lexeme);
    p->tk.tokenType = tk.tokenType;
    p->parentNodeSymbol = pntid;
    p->child_cnt = 0;
    p->children = NULL;
    return p;
}

parseTree parseInputSourceCode(const char *testcaseFile, grammar rulelist, table T)
{
    bool syntaxError = false;
    set** firststs = createFirstSets(rulelist); // required for PANIC MODE
    FILE *tfp = fopen(testcaseFile, "r");
    tokenInfo t = getNextToken(tfp);
    tokenInfo nttk;
    nttk.lineNum = -1;
    nttk.tokenType = TK_ERROR;
    parseTree pTree = createEmptyTreeNode(PROGRAM, nttk, -1);
    stackNode* stck = NULL;
    stck = pushStack(TK_DOLLAR, NULL, stck);  // inserting stack bottom symbol
    stck = pushStack(PROGRAM, pTree, stck);   // inserting start symbol
    while(!isEmpty(stck) && t.tokenType != TK_EOF)
    {
        #ifdef DEBUG_PARSER
        printf("\n");
        printf("Current token: %s <%d>\n", getTerminalStr(t.tokenType), t.lineNum);
        printStack(stck);
        #endif
        if(t.tokenType == TK_ERROR)
        {
            t = getNextToken(tfp);
            syntaxError = true;
            continue;
        }
        stackNode* top = topStack(stck);
        stck = popStack(stck);
        parseTreeNode* pnode = top->pnode;
        if(top->val == TK_EPS)
            continue;
        if(top->val == t.tokenType)
        {
            pnode->tk.lineNum = t.lineNum;
            strcpy(pnode->tk.lexeme, t.lexeme);
            pnode->tk.tokenType = t.tokenType;
            t = getNextToken(tfp);
            continue;
        }
        else if(isTerminal(top->val))
        {
            syntaxError = true;
            fprintf(stderr, "The token %s for lexeme <%s> does not match at line <%d>. The expected token here is %s.\n", getTerminalStr(t.tokenType), t.lexeme, t.lineNum, getTerminalStr(top->val));
            pnode->tk.lineNum = t.lineNum;
            strcpy(pnode->tk.lexeme, "Panic Mode");
            pnode->tk.tokenType = top->val;
            top = topStack(stck);
            while(t.tokenType != top->val && !isEmpty(stck) && isTerminal(top->val))
            {
                stck = popStack(stck);
                top = topStack(stck);
            }
            continue;
            // return pTree;
        }
        else if(T[top->val][t.tokenType - TERMINAL_OFFSET] == -1)
        {
            syntaxError = true;
            fprintf(stderr, "No rule in the parse table to expand. Received %s on line <%d> for %s.\n", getIDStr(t.tokenType), t.lineNum, getIDStr(top->val));
            top = topStack(stck);
            while(t.tokenType != TK_EOF && !isPresent(t.tokenType, getFirstSet(top->val, firststs)))
            {
                t = getNextToken(tfp);
            }
            continue;
            // return pTree;
        }
        int rno = T[top->val][t.tokenType - TERMINAL_OFFSET];
        int ridx = rulelist[top->val]->rule_length[rno] - 1;
        #ifdef DEBUG_PARSER
        printProdRule(top->val, rno, rulelist); // for debugging
        #endif
        int idx = pnode->child_cnt;
        pnode->child_cnt += ridx + 1;
        pnode->children = (parseTreeNode**) realloc(pnode->children, sizeof(parseTreeNode*)*pnode->child_cnt);
        for (; ridx >= 0; --ridx)
        {
            pnode->children[idx + ridx] = createEmptyTreeNode(rulelist[top->val]->prod_rules[rno][ridx], nttk, pnode->nodeid);
            int childid = rulelist[top->val]->prod_rules[rno][ridx];
            stck = pushStack(childid, pnode->children[idx + ridx], stck);
        }
    }
    if(!syntaxError)
        printf("%sCompiled Successfully: Input source code is syntactically correct.%s\n", KGRN, KNRM);
    else
        printf("%sInput source code has errors.%s\n", KRED, KNRM);
    return pTree;
}

void printParseTreeHelper(parseTree PT, FILE* fp)
{
    if(PT == NULL)
    {
        fprintf(stderr, "parse tree is NULL\n");
        return;
    }
    char empty[10] = "----";
    char yes[10] = "YES";
    char no[10] = "NO";
    int space = 30;
    if(PT->child_cnt == 0)
    {
        if(isTerminal(PT->nodeid))
        {
            if(PT->nodeid == TK_EPS)
                fprintf(fp, "%*s%*s%*s%*s%*s%*s%*s\n", 20, empty, space, empty, space, getIDStr(PT->nodeid), space, empty, space, getIDStr(PT->parentNodeSymbol), space, yes, space, empty);
            else if(PT->nodeid == TK_NUM || PT->nodeid == TK_RNUM)
                fprintf(fp, "%*s%*d%*s%*s%*s%*s%*s\n", 20, empty, space, PT->tk.lineNum, space, getIDStr(PT->nodeid), space, PT->tk.lexeme, space, getIDStr(PT->parentNodeSymbol), space, yes, space, empty);
            else
                fprintf(fp, "%*s%*d%*s%*s%*s%*s%*s\n", 20, PT->tk.lexeme, space, PT->tk.lineNum, space, getIDStr(PT->nodeid), space, empty, space, getIDStr(PT->parentNodeSymbol), space, yes, space, empty);
        }
        else
            fprintf(fp, "%*s%*s%*s%*s%*s%*s%*s\n", 20, empty, space, empty, space, empty, space, empty, space, getIDStr(PT->parentNodeSymbol), space, no, space, getIDStr(PT->nodeid));
        return;
    }
    fprintf(fp, "%*s%*s%*s%*s%*s%*s%*s\n", 20, empty, space, empty, space, empty, space, empty, space, getIDStr(PT->parentNodeSymbol), space, no, space, getIDStr(PT->nodeid));
    int idx;
    for (idx = 0; idx < PT->child_cnt; ++idx)
        printParseTreeHelper(PT->children[idx], fp);
}

void printParseTree(parseTree PT, const char* outfile)
{
    FILE* fp = fopen(outfile, "w");
    int space = 30;
    char lexemeCurrentNode[20] = "lexemeCurrentNode";
    char lineno[20] = "lineno";
    char token[20] = "token";
    char valuelfNumber[20] = "valuelfNumber";
    char parentNodeSymbol[20] = "parentNodeSymbol";
    char isLeafNode[20] = "isLeafNode";
    char NodeSymbol[20] = "NodeSymbol";
    fprintf(fp, "%*s%*s%*s%*s%*s%*s%*s\n", 20, lexemeCurrentNode, space, lineno, space, token, space, valuelfNumber, space, parentNodeSymbol, space, isLeafNode, space, NodeSymbol);
    printParseTreeHelper(PT, fp);
    fclose(fp);
}
