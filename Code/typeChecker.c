/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: typeChecker.c
* @Date:      2016-03-29 10:44:42
*/

#include "typeChecker.h"

bool TYPECHECKER_ERROR = false;

int getCummulativeRecordType(int ident, recordTable* record_table)
{
    recordEntry* rent = getRecordEntry(ident, record_table);
    if(rent == NULL)
        return TYPE_ERROR;
    entry *p = rent->arr;
    int type = p->type;
    while(p != NULL)
    {
        if(type != p->type)
            return TYPE_ERROR;
        p = p->next;
    }
    if(type == TK_INT)
        return TYPE_INT;
    else if(type == TK_REAL)
        return TYPE_REAL;
    return TYPE_ERROR;
}

int getType(ASTNode* AT)
{
    if(AT == NULL)
        return TYPE_NULL;
    if(AT->nodeid == TK_NUM)
        return TYPE_INT;
    if(AT->nodeid == TK_RNUM)
        return TYPE_REAL;
    GlobalTable *global_table = AT->global_table;
    funcIdTable* local_table = AT->local_table;
    recordTable* record_table = AT->record_table;
    if(AT->nodeid == TK_ID)
    {
        entry* ent = findGlobalId(global_table, AT->tk.lexeme);
        if(ent == NULL)
            ent = findLocalId(local_table, AT->tk.lexeme);
        if(ent == NULL)
        {
            fprintf(stderr, "Line %d: Identifier %s hasn't been declared in this scope.\n", getLineNumber(AT), AT->tk.lexeme);
            TYPECHECKER_ERROR = true;
            return TYPE_ERROR;
        }
        if(ent->type == TK_INT)
            return TYPE_INT;
        else if(ent->type == TK_REAL)
            return TYPE_REAL;
        return ent->type;
    }
    if(isTerminal(AT->nodeid))
        return TYPE_ERROR;
    if(getNonTerminalfromStr("<singleOrRecId>") == AT->nodeid)
    {
        if(AT->children[1] == NULL)     // not record id
        {
            entry* ent = findGlobalId(global_table, AT->children[0]->tk.lexeme);
            if(ent == NULL)
                ent = findLocalId(local_table, AT->children[0]->tk.lexeme);
            if(ent == NULL)
            {
                fprintf(stderr, "Line %d: Identifier %s hasn't been declared in this scope.\n", getLineNumber(AT), AT->children[0]->tk.lexeme);
                TYPECHECKER_ERROR = true;
                return TYPE_ERROR;
            }
            if(ent->type == TK_INT)
                return TYPE_INT;
            else if(ent->type == TK_REAL)
                return TYPE_REAL;
            return ent->type;
        }
        else
        {
            char record_id[500];
            sprintf(record_id, "%s.%s", AT->children[0]->tk.lexeme, AT->children[1]->tk.lexeme);
            entry* ent = findGlobalId(global_table, record_id);
            if(ent == NULL)
                ent = findLocalId(local_table, record_id);
            if(ent == NULL)
            {
                fprintf(stderr, "Line %d: Identifier %s hasn't been declared in this scope.\n", getLineNumber(AT), record_id);
                TYPECHECKER_ERROR = true;
                return TYPE_ERROR;
            }
            if(ent->type == TK_INT)
                return TYPE_INT;
            else if(ent->type == TK_REAL)
                return TYPE_REAL;
            return ent->type;
        }
        return TYPE_ERROR;
    }
    // handle for TK_RECORD scalar
    else if(getNonTerminalfromStr("<arithmeticExpression>") == AT->nodeid)
    {
        Type t1 = getType(AT->children[0]);
        Type t2 = getType(AT->children[1]);
        if(t2 == TYPE_NULL)
            return t1;
        if(t1 == t2)
            return t1;
        return TYPE_ERROR;
    }
    else if(getNonTerminalfromStr("<term>") == AT->nodeid)
    {
        Type t1 = getType(AT->children[0]);
        Type t2 = getType(AT->children[1]);
        if(t2 == TYPE_NULL)
            return t1;
        if(t1 == t2 && (t1 == TYPE_INT || t1 == TYPE_REAL))
            return t1;
        if((int) t1 >= RECORD_OFFSET)
        {
            Type t3 = getCummulativeRecordType(t1, record_table);
            if(t3 == TYPE_ERROR)
                return TYPE_ERROR;
            if(t3 == t2)
                return t1;
        }
        if((int) t2 >= RECORD_OFFSET)
        {
            Type t3 = getCummulativeRecordType(t2, record_table);
            if(t3 == TYPE_ERROR)
                return TYPE_ERROR;
            if(t3 == t2)
                return t2;
        }
        return TYPE_ERROR;
    }
    else if(getNonTerminalfromStr("<factor>") == AT->nodeid)
    {
        return getType(AT->children[0]);
    }
    else if(getNonTerminalfromStr("<expPrime>") == AT->nodeid)
    {
        Type t1 = getType(AT->children[1]);
        Type t2 = getType(AT->children[2]);
        if(t2 == TYPE_NULL)
            return t1;
        if(t1 == t2)
            return t1;
        return TYPE_ERROR;
    }
    else if(getNonTerminalfromStr("<termPrime>") == AT->nodeid)
    {
        Type t1 = getType(AT->children[1]);
        Type t2 = getType(AT->children[2]);
        if(t2 == TYPE_NULL)
            return t1;
        if(t1 == t2 && (t1 == TYPE_INT || t1 == TYPE_REAL))
            return t1;
        if((int) t1 >= RECORD_OFFSET)
        {
            Type t3 = getCummulativeRecordType(t1, record_table);
            if(t3 == TYPE_ERROR)
                return TYPE_ERROR;
            if(t3 == t2)
                return t1;
        }
        if((int) t2 >= RECORD_OFFSET)
        {
            Type t3 = getCummulativeRecordType(t2, record_table);
            if(t3 == TYPE_ERROR)
                return TYPE_ERROR;
            if(t3 == t2)
                return t2;
        }
        return TYPE_ERROR;
    }
    else if(getNonTerminalfromStr("<booleanExpression>") == AT->nodeid)
    {
        if(AT->rno == 65)
        {
            Type t1 = getType(AT->children[0]);
            Type t2 = getType(AT->children[2]);
            if(t1 == TYPE_BOOL && t2 == TYPE_BOOL)
                return TYPE_BOOL;
            return TYPE_ERROR;
        }
        else if(AT->rno == 66)
        {
            Type t1 = getType(AT->children[0]);
            Type t2 = getType(AT->children[2]);
            if(t1 == t2 && (t1 == TYPE_INT || t1 == TYPE_REAL))
                return TYPE_BOOL;
            return TYPE_ERROR;
        }
        else if(AT->rno == 67)
            return getType(AT->children[1]);
        return TYPE_ERROR;
    }
    return TYPE_ERROR;
}

void runTypeCheckerAST(ASTNode* AT)
{
    if(AT == NULL)
        return;
    if(getNonTerminalfromStr("<assignmentStmt>") == AT->nodeid)
    {
        Type t1 = getType(AT->children[0]);
        Type t2 = getType(AT->children[1]);
        if(t1 != t2)
            fprintf(stderr, "Line %d: Type mismatch in assignment statement.\n", getLineNumber(AT));
        TYPECHECKER_ERROR = true;
        return;
    }
    else if(getNonTerminalfromStr("<iterativeStmt>") == AT->nodeid)
    {
        if(getType(AT->children[1]) != TYPE_BOOL)
            fprintf(stderr, "Line %d: Condition inside while statement is not of boolean type.\n", getLineNumber(AT));
        TYPECHECKER_ERROR = true;
    }
    else if(getNonTerminalfromStr("<conditionalStmt>") == AT->nodeid)
    {
        if(getType(AT->children[1]) != TYPE_BOOL)
            fprintf(stderr, "Line %d: Condition inside if statement is not of boolean type.\n", getLineNumber(AT));
        TYPECHECKER_ERROR = true;
    }
    else if(getNonTerminalfromStr("<ioStmt>") == AT->nodeid)
    {
        getType(AT->children[1]);
    }
    int i;
    for (i = 0; i < AT->child_cnt; ++i)
        runTypeCheckerAST(AT->children[i]);
}
