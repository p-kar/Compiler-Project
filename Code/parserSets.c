/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: parserSets.c
* @Date:      2016-02-18 10:31:27
*/
#include "parserSets.h"

bool hasEpsRule(int ntid, prodRuleNode** rulelist)
{
    if(rulelist[ntid] == NULL)
        return false;
    prodRuleNode* p = rulelist[ntid];
    int i;
    for (i = 0; i < p->prod_rule_cnt; ++i)
    {
        if(p->prod_rules[i][0] == TK_EPS)
            return true;
    }
    return false;
}

set** initialiseSetList()
{
    set** sets = (set**) malloc(sizeof(set*) * NUM_NONTERMINALS);
    int i;
    for (i = 0; i < NUM_NONTERMINALS; ++i)
        sets[i] = NULL;
    return sets;
}

void displaySet(set* st)
{
    if(st == NULL)
        return;
    char* token = getTerminalStr(st->val);
    printf("%s ", token);
    displaySet(st->left);
    displaySet(st->right);
}

set* getFirstSet(int id, prodRuleNode** rulelist, set** sts)
{
    if(isTerminal(id))
    {
        set* st = createEmptyNode();
        st->val = id;
        return st;
    }
    if(sts[id] != NULL)
        return sts[id];
    set* st = NULL;
    prodRuleNode* p = rulelist[id];
    int i, j;
    for (i = 0; i < p->prod_rule_cnt; ++i)
    {
        if(p->prod_rules[i][0] == TK_EPS)
        {
            st = setAdd(TK_EPS, st);
            continue;
        }
        bool flag = false;
        for (j = 0; j < p->rule_length[i]; ++j)
        {
            set* st2 = getFirstSet(p->prod_rules[i][j], rulelist, sts);
            st = setUnion(st, st2);
            if(!isPresent(TK_EPS, st2))
            {
                flag = true;
                break;
            }
        }
        if(!flag)
            st = setAdd(TK_EPS, st);
    }
    sts[id] = st;
    return st;
}

set** createFirstSets(prodRuleNode** rulelist)
{
    set** sts = initialiseSetList();
    int i;
    for (i = 0; i < NUM_NONTERMINALS - 1; ++i)
    {
        getFirstSet(i, rulelist, sts);
        char* token = getNonTerminalStr(i);
        printf("<%s> ===> ", token);
        displaySet(sts[i]);
        printf("\n");
    }
    return sts;
}

// set* getFollowSet(int id, prodRuleNode** rulelist, set** sts)
// {

// }