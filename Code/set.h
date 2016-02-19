/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: set.h
* @Date:      2016-02-18 01:10:02
*/
#ifndef SET_H
#define SET_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "parserDef.h"
#include "parserUtils.h"

struct _set
{
    int val;
    struct _set *left, *right;
};
typedef struct _set set;

set* createEmptyNode();
bool isPresent(int value, set *root);
set* setAdd(int value, set *root);
// adds the second set to the first set
// ensure that TK_EPS is handled
set* setUnion(set *first, set *second);

#endif