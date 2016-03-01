/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: parserTable.c
* @Date:      2016-02-20 03:00:10
*/
#include "parserTable.h"

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

parserTable initialiseParserTable()
{
    parserTable p = (parserTable) malloc(sizeof(int*) * NUM_NONTERMINALS);
    int i, j;
    for (i = 0; i < NUM_NONTERMINALS; ++i)
        p[i] = (int*) malloc(sizeof(int) * NUM_TERMINALS);
    for (i = 0; i < NUM_NONTERMINALS; ++i)
        for (j = 0; j < NUM_TERMINALS; ++j)
            p[i][j] = -1;
    return p;
}

void addRuleinSet(int ntid, int ruleno, set* st, parserTable p)
{
    if(st == NULL)
        return;
    if(st->val != TK_EPS)
        p[ntid][st->val - TERMINAL_OFFSET] = ruleno;
    addRuleinSet(ntid, ruleno, st->left, p);
    addRuleinSet(ntid, ruleno, st->right, p);
}

parserTable populateParserTable(prodRuleNode** rulelist)
{
    set **firststs = createFirstSets(rulelist);
    set **followsts = createFollowSets(rulelist, firststs);
    parserTable p = initialiseParserTable();
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
    return p;
}

void displayParserTable(parserTable p)
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
