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

set* computeFirstSets(int id, prodRuleNode** rulelist, set** firststs)
{
    if(isTerminal(id))
    {
        set* st = createEmptySet();
        st->val = id;
        return st;
    }
    if(firststs[id] != NULL)
        return firststs[id];
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
            set* st2 = computeFirstSets(p->prod_rules[i][j], rulelist, firststs);
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
    firststs[id] = st;
    return st;
}

set** createFirstSets(prodRuleNode** rulelist)
{
    set** sts = initialiseSetList();
    int i;
    for (i = 0; i < NUM_NONTERMINALS - 1; ++i)
    {
        computeFirstSets(i, rulelist, sts);
    }
    #ifdef ENABLE_PRINTING_FIRST_SETS
    printf("FIRST SETS\n###################\n\n");
    for (i = 0; i < NUM_NONTERMINALS; ++i)
    {
        char* token = getNonTerminalStr(i);
        printf("%s ===> ", token);
        displaySet(sts[i]);
        printf("\n");
    }
    printf("###################\n\n");
    #endif
    return sts;
}

set* computeFollowSets(int id, prodRuleNode** rulelist, set **firststs, set** followsts, int** rec_stack, int stack_size)
{
    if(rulelist[id]->rhs_occ_cnt == 0)
    {
        set* st = createEmptySet();
        st->val = TK_DOLLAR;
        followsts[id] = st;
        return st;
    }
    if(rulelist[id]->follow_set_flag == 2)
        return followsts[id];
    if(rulelist[id]->follow_set_flag == 1)
    {
        set* com_st = NULL;
        int k;
        int idx;
        // to find the start of the cycle
        for (idx = 0; idx < stack_size; ++idx)
            if((*rec_stack)[idx] == id)
                break;
        for (k = idx; k < stack_size; ++k)
            com_st = setUnion(com_st, followsts[(*rec_stack)[k]]);
        for (k = idx; k < stack_size; ++k)
            followsts[(*rec_stack)[k]] = com_st;
        return followsts[id];
    }
    rulelist[id]->follow_set_flag = 1;
    followsts[id] = NULL;
    int rhs_cnt = rulelist[id]->rhs_occ_cnt;
    int i;
    for (i = 0; i < rhs_cnt; ++i)
    {
        rhsOcc temp = rulelist[id]->rhs_occs[i];
        bool term_flag = false;
        int j = temp.j + 1;
        while(j < rulelist[temp.ntid]->rule_length[temp.i])
        {
            set* fst = computeFirstSets(rulelist[temp.ntid]->prod_rules[temp.i][j], rulelist, firststs);
            followsts[id] = setUnion(followsts[id], fst);
            if(!isPresent(TK_EPS, fst))
            {
                term_flag = true;
                break;
            }
            j++;
        }
        if(term_flag)
            continue;
        (*rec_stack) = (int*) realloc((*rec_stack), sizeof(int) * (stack_size + 1));
        (*rec_stack)[stack_size] = temp.ntid;
        set* flst = computeFollowSets(temp.ntid, rulelist, firststs, followsts, rec_stack, stack_size + 1);
        followsts[id] = setUnion(followsts[id], flst);
    }
    rulelist[id]->follow_set_flag = 2;
    return followsts[id];
}

set** createFollowSets(prodRuleNode** rulelist, set** firststs)
{
    set** sts = initialiseSetList();
    int i;
    for (i = 0; i < NUM_NONTERMINALS - 1; ++i)
    {
        int* rec_stack = NULL;
        rec_stack = (int*) malloc(sizeof(int));
        rec_stack[0] = i;
        int stack_size = 1;
        computeFollowSets(i, rulelist, firststs, sts, &rec_stack, stack_size);
    }
    #ifdef ENABLE_PRINTING_FOLLOW_SETS
    printf("FOLLOW SETS\n###################\n\n");
    for (i = 0; i < NUM_NONTERMINALS - 1; ++i)
    {
        char* token = getNonTerminalStr(i);
        printf("%s ===> ", token);
        displaySet(sts[i]);
        printf("\n");
    }
    printf("###################\n\n");
    #endif
    return sts;
}

set* getFirstSet(int id, set** firststs)
{
    // ensure that computeFirstSets has been called for that id earlier
    if(isTerminal(id))
    {
        set* st = createEmptySet();
        st->val = id;
        return st;
    }
    return firststs[id];
}

set* getFollowSet(int ntid, set** followsts)
{
    return followsts[ntid];
}
