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
    return false;
}

// if a pointer has to be returned
// make a deep copy of the pointer
int topStack(stackNode* st)
{
    if(st == NULL)
        return TK_ERROR;
    return st->val;
}

stackNode* pushStack(int val, stackNode* st)
{
    stackNode* p = (stackNode*) malloc(sizeof(stackNode));
    p->val = val;
    p->next = st;
    return p;
}

// remember deallocating memory here so ensure
// that in the topStack function the pointer is not returned.
stackNode* popStack(stackNode* st)
{
    if(st == NULL)
        return st;
    stackNode* p = st;
    st = st->next;
    free(p);
    return st;
}
