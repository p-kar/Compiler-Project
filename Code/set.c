/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: set.c
* @Date:      2016-02-18 12:35:14
*/
#include "set.h"

set* createEmptyNode()
{
    set* p = (set*) malloc(sizeof(set));
    p->left = NULL;
    p->right = NULL;
    return p;
}

bool isPresent(int value, set *root)
{
    if(root == NULL)
        return false;
    if(root->val == value)
        return true;
    if(root->val > value)
        return isPresent(value, root->left);
    return isPresent(value, root->right);
}

set* setAdd(int value, set *root)
{
    if(root == NULL)
    {
        set* p = createEmptyNode();
        p->val = value;
        return p;
    }
    if(root->val == value)
        return root;
    if(root->val > value)
        root->left = setAdd(value, root->left);
    else
        root->right = setAdd(value, root->right);
    return root;
}

// without TK_EPS
set* setUnion(set *first, set *second)
{
    if(second == NULL)
        return first;
    if(second->val != TK_EPS)
        first = setAdd(second->val, first);
    first = setUnion(first, second->left);
    first = setUnion(first, second->right);
    return first;
}
