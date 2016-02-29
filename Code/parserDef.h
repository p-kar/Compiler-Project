/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: parserDef.h
* @Date:      2016-02-18 12:26:23
*/
#ifndef PARSERDEF_H
#define PARSERDEF_H

#include "lexer.h"
#include <stdbool.h>

#define NONTERMINAL_OFFSET 0
#define NUM_NONTERMINALS 51

enum _NONTERMINAL
{
    PROGRAM = NONTERMINAL_OFFSET,
    MAINFUNCTION,
    OTHERFUNCTIONS,
    FUNCTION,
    INPUTPAR,
    OUTPUTPAR,
    PARAMETERLIST,
    DATATYPE,
    PRIMITIVEDATATYPE,
    CONSTRUCTEDDATATYPE,
    REMAININGLIST,
    STMTS,
    TYPEDEFINITIONS,
    TYPEDEFINITION,
    FIELDDEFINITIONS,
    FIELDDEFINITION,
    MOREFIELDS,
    DECLARATIONS,
    DECLARATION,
    GLOBALORNOT,
    OTHERSTMTS,
    STMT,
    ASSIGNMENTSTMT,
    SINGLEORRECID,
    NEW24,
    FUNCALLSTMT,
    INPUTPARAMETERS,
    OUTPUTPARAMETERS,
    ITERATIVESTMT,
    CONDITIONALSTMT,
    ELSEPART,
    IOSTMT,
    ALLVAR,
    ARITHMETICEXPRESSION,
    TERM,
    EXPPRIME,
    LOWPRECEDENCEOPERATORS,
    FACTOR,
    HIGHPRECEDENCEOPERATORS,
    TERMPRIME,
    ALL,
    TEMP,
    BOOLEANEXPRESSION,
    VAR,
    LOGICALOP,
    RELATIONALOP,
    RETURNSTMT,
    OPTIONALRETURN,
    IDLIST,
    MOREIDS,
    NONTERMERROR
};
typedef enum _NONTERMINAL NONTERMINAL;

// structure to maintain RHS occurences
struct _rhsOcc
{
    int ntid;   //non terminal id
    int i;      //rule number
    int j;      //occurence index
};
typedef struct _rhsOcc rhsOcc;

struct _prodRuleNode
{
    NONTERMINAL ntid;
    int prod_rule_cnt;
    int* rule_length;
    int** prod_rules;
    int rhs_occ_cnt;
    rhsOcc* rhs_occs;
    int follow_set_flag;    // 0 - not visited, 1 - currently computing, 2 - done
};
typedef struct _prodRuleNode prodRuleNode;

struct _parseTreeNode
{
    int nodeid;
    int lineno;
    float valuelfNumber;
    NONTERMINAL parentNodeSymbol;
    bool isLeafNode;
    int child_cnt;
    struct _parseTreeNode** children;
};
typedef struct _parseTreeNode parseTreeNode;
typedef parseTreeNode* parseTree;

#endif