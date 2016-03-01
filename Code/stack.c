/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: stack.c
* @Date:      2016-02-21 15:16:23
*/
#include "stack.h"

bool isEmpty(stackNode* st)
{
    if(st == NULL)
        return true;
    if(st->val == TK_DOLLAR)
        return true;
    return false;
}

stackNode* topStack(stackNode* st)
{
    if(st == NULL)
        return NULL;
    stackNode* p = (stackNode*) malloc(sizeof(stackNode));
    p->val = st->val;
    p->pnode = st->pnode;
    p->next = NULL;
    return p;
}

stackNode* pushStack(int id, parseTree node, stackNode* st)
{
    stackNode* p = (stackNode*) malloc(sizeof(stackNode));
    p->val = id;
    p->pnode = node;
    p->next = st;
    st = p;
    return st;
}

stackNode* popStack(stackNode* st)
{
    if(st == NULL)
        return st;
    st = st->next;
    return st;
}

void printStack(stackNode* st)
{
    printf("Current Stack:- ");
    stackNode* p = st;
    while(p != NULL)
    {
        printf("%s ", getIDStr(p->val));
        p = p->next;
    }
    printf("\n");
}
