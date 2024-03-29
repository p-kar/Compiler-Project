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
#define TERMINAL_OFFSET 1000
#define NUM_TERMINALS 57
#define RECORD_OFFSET 100000

enum _TERMINAL
{
    TK_AND = TERMINAL_OFFSET,
    TK_ASSIGNOP,
    TK_CALL,
    TK_CL,
    TK_COLON,
    TK_COMMA,
    TK_COMMENT,
    TK_DIV,
    TK_DOT,
    TK_ELSE,
    TK_END,
    TK_ENDIF,
    TK_ENDRECORD,
    TK_ENDWHILE,
    TK_EQ,
    TK_FIELDID,
    TK_FUNID,
    TK_GE,
    TK_GLOBAL,
    TK_GT,
    TK_ID,
    TK_IF,
    TK_INPUT,
    TK_INT,
    TK_LE,
    TK_LIST,
    TK_LT,
    TK_MAIN,
    TK_MINUS,
    TK_MUL,
    TK_NE,
    TK_NOT,
    TK_NUM,
    TK_OP,
    TK_OR,
    TK_OUTPUT,
    TK_PARAMETER,
    TK_PARAMETERS,
    TK_PLUS,
    TK_READ,
    TK_REAL,
    TK_RECORD,
    TK_RECORDID,
    TK_RETURN,
    TK_RNUM,
    TK_SEM,
    TK_SQL,
    TK_SQR,
    TK_THEN,
    TK_TYPE,
    TK_WHILE,
    TK_WITH,
    TK_WRITE,
    TK_DOLLAR,
    TK_EPS,
    TK_EOF,
    TK_ERROR
};
typedef enum _TERMINAL TERMINAL;

typedef struct tokenInfo
{
	char lexeme[MAX_LEXEME_SIZE];
	int lineNum;
	TERMINAL tokenType;
}tokenInfo;

#endif
