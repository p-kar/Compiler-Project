/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: stack.h
* @Date:      2016-02-21 15:07:03
*/
#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "parserDef.h"

struct _stackNode
{
    int val;
    struct _stackNode* next;
};
typedef struct _stackNode stackNode;

bool isEmpty(stackNode* st);
int topStack(stackNode* st);
stackNode* pushStack(int val, stackNode* st);
stackNode* popStack(stackNode* st);

#endif