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

#include <stdbool.h>

#define TERMINAL_OFFSET 112233
#define NONTERMINAL_OFFSET 0
#define NUM_TERMINALS 55
#define NUM_NONTERMINALS 51

enum _TERMINAL
{
    TK_MAIN = TERMINAL_OFFSET,
    TK_END,
    TK_FUNID,
    TK_SEM,
    TK_INPUT,
    TK_PARAMETER,
    TK_LIST,
    TK_SQL,
    TK_SQR,
    TK_OUTPUT,
    TK_ID,
    TK_INT,
    TK_REAL,
    TK_RECORD,
    TK_RECORDID,
    TK_COMMA,
    TK_ENDRECORD,
    TK_TYPE,
    TK_COLON,
    TK_FIELDID,
    TK_GLOBAL,
    TK_ASSIGNOP,
    TK_DOT,
    TK_CALL,
    TK_WITH,
    TK_PARAMETERS,
    TK_WHILE,
    TK_OP,
    TK_CL,
    TK_ENDWHILE,
    TK_IF,
    TK_THEN,
    TK_ELSE,
    TK_ENDIF,
    TK_READ,
    TK_WRITE,
    TK_PLUS,
    TK_MUL,
    TK_MINUS,
    TK_DIV,
    TK_NOT,
    TK_NUM,
    TK_RNUM,
    TK_AND,
    TK_OR,
    TK_LT,
    TK_LE,
    TK_EQ,
    TK_GT,
    TK_GE,
    TK_NE,
    TK_RETURN,
    TK_EPS,
    TK_DOLLAR,
    TK_ERROR
};
typedef enum _TERMINAL TERMINAL;

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
    int ntid;
    int i;
    int j;
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

#endif