/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: lexerDef.h
* @Date:      2016-02-18 12:26:23
*/

#ifndef LEXERDEF_H
#define LEXERDEF_H

#define MAX_LEXEME_SIZE 650 // doubt here
#define TERMINAL_OFFSET 1234
#define NUM_TERMINALS 56

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
    TK_ERROR,
    TK_EOF
};
typedef enum _TERMINAL TERMINAL;

typedef struct tokenInfo
{
	char lexeme[MAX_LEXEME_SIZE];
	long long int lineNum;
	TERMINAL tokenType;
}tokenInfo;

#endif
