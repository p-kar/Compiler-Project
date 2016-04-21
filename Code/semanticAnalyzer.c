/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: semanticAnalyzer.c
* @Date:      2016-03-29 10:44:42
*/

#include "semanticAnalyzer.h"

// add better error flags
void verifyFunctionParameters(ASTNode* AT, int idx, GlobalTable* global_table, funcIdTable* local_table, recordTable* record_table, funcIdTable* func_table, bool input)
{
    if(AT == NULL)
        return;
    if(getNonTerminalfromStr("<idList>") == AT->nodeid)
    {
        entry* ent = findGlobalId(global_table, AT->children[0]->tk.lexeme);
        if(ent == NULL)
            ent = findLocalId(local_table, AT->children[0]->tk.lexeme);
        if(ent == NULL)
        {
            fprintf(stderr, "Line %d: Identifier %s not declared.\n", getLineNumber(AT), AT->children[0]->tk.lexeme);
            return;
        }
        entry* fent;
        if(input)
            fent = func_table->inputParameterList;
        else
            fent = func_table->outputParameterList;
        int fidx = idx;
        while(fent != NULL && fidx)
        {
            fent = fent->next;
            fidx--;
        }
        if(fent == NULL)
        {
            if(input)
                fprintf(stderr, "Line %d: Too many input parameters received for function %s.\n", getLineNumber(AT), func_table->funcName);
            else
                fprintf(stderr, "Line %d: Too many output parameters received for function %s.\n", getLineNumber(AT), func_table->funcName);
            return;
        }
        if(fent->type != ent->type)
        {
            if(input)
                fprintf(stderr, "Line %d: Function %s input parameters type mismatch between %s and %s.\n", getLineNumber(AT), func_table->funcName, fent->token.lexeme, ent->token.lexeme);
            else
                fprintf(stderr, "Line %d: Function %s output parameters type mismatch between %s and %s.\n", getLineNumber(AT), func_table->funcName, fent->token.lexeme, ent->token.lexeme);
            return;
        }
        if(AT->children[1] == NULL && input && func_table->input_num != idx + 1)
        {
            fprintf(stderr, "Line %d: Too few input parameters received for function %s.\n", getLineNumber(AT), func_table->funcName);
            return;
        }
        if(AT->children[1] == NULL && !input && func_table->output_num != idx + 1)
        {
            fprintf(stderr, "Line %d: Too few output parameters received for function %s.\n", getLineNumber(AT), func_table->funcName);
            return;
        }
        verifyFunctionParameters(AT->children[1], idx + 1, global_table, local_table, record_table, func_table, input);
        return;
    }
    int i;
    for (i = 0; i < AT->child_cnt; ++i)
        verifyFunctionParameters(AT->children[i], idx, global_table, local_table, record_table, func_table, input);
    return;
}

void verifyFunctionReturnStmt(ASTNode* AT, int idx, funcIdTable* local_table)
{
    if(AT == NULL)
        return;
    entry* fent = local_table->outputParameterList;
    int fidx = idx;
    while(fent != NULL && fidx)
    {
        fent = fent->next;
        fidx--;
    }
    if(fent == NULL)
    {
        fprintf(stderr, "Line %d: Too many parameters in function %s return statement.\n", getLineNumber(AT), local_table->funcName);
        return;
    }
    if(strcmp(fent->token.lexeme, AT->children[0]->tk.lexeme) != 0)
    {
        fprintf(stderr, "Line %d: Function %s return statement parameter mismatch between %s and %s.\n", getLineNumber(AT), local_table->funcName, fent->token.lexeme, AT->children[0]->tk.lexeme);
        return;
    }
    if(AT->children[1] == NULL && local_table->output_num != idx + 1)
    {
        fprintf(stderr, "Line %d: Too few parameters in function %s return statement.\n", getLineNumber(AT), local_table->funcName);
        return;
    }
    verifyFunctionReturnStmt(AT->children[1], idx + 1, local_table);
}

bool inModSet(modSet* head, char* identifier)
{
    modSet* p = head;
    while(p != NULL)
    {
        if(strcmp(p->id, identifier) == 0)
            return true;
        p = p->next;
    }
    return false;
}

modSet* addModSet(modSet* head, char* identifier)
{
    modSet* p = (modSet*) malloc(sizeof(modSet));
    strcpy(p->id, identifier);
    p->next = head;
    return p;
}

modSet* addIdListModSet(ASTNode* AT, modSet* head)
{
    if(AT == NULL)
        return head;
    if(getNonTerminalfromStr("<idList>") == AT->nodeid)
    {
        head = addModSet(head, AT->children[0]->tk.lexeme);
        head = addIdListModSet(AT->children[1], head);
        return head;
    }
    int i;
    for (i = 0; i < AT->child_cnt; ++i)
        head = addIdListModSet(AT->children[i], head);
    return head;
}

modSet* getModifySetStmts(ASTNode* AT, modSet* head)
{
    if(AT == NULL)
        return head;
    if(getNonTerminalfromStr("<assignmentStmt>") == AT->nodeid)
    {
        char identifier[500];
        strcpy(identifier, AT->children[0]->children[0]->tk.lexeme);
        head = addModSet(head, identifier);
        return head;
    }
    else if(getNonTerminalfromStr("<funCallStmt>") == AT->nodeid)
    {
        head = addIdListModSet(AT->children[0], head);
        return head;
    }
    else if(getNonTerminalfromStr("<ioStmt>") == AT->nodeid && AT->children[0]->nodeid == TK_READ)
    {
        char identifier[500];
        strcpy(identifier, AT->children[1]->children[0]->tk.lexeme);
        head = addModSet(head, identifier);
        return head;
    }
    int i;
    for (i = 0; i < AT->child_cnt; ++i)
        head = getModifySetStmts(AT->children[i], head);
    return head;
}

bool checkWhileCondition(ASTNode* AT, modSet* head)
{
    if(AT == NULL)
        return false;
    if(AT->nodeid == TK_ID)
    {
        return inModSet(head, AT->tk.lexeme);
    }
    int i;
    for (i = 0; i < AT->child_cnt; ++i)
    {
        if(checkWhileCondition(AT->children[i], head))
            return true;
    }
    return false;
}

void runSemanticAnalyzer(ASTNode* AT)
{
    if(AT == NULL)
        return;
    GlobalTable* global_table = AT->global_table;
    funcIdTable* local_table = AT->local_table;
    recordTable* record_table = AT->record_table;
    if(getNonTerminalfromStr("<funCallStmt>") == AT->nodeid)
    {
        if(strcmp(AT->children[1]->tk.lexeme, local_table->funcName) == 0)
        {
            fprintf(stderr, "Line %d: Recursion detected in function %s.\n", getLineNumber(AT), local_table->funcName);
            return;
        }
        funcIdTable* func_table = findFuncIdTable(&(global_table->finalFuncTable), AT->children[1]->tk.lexeme);
        if(func_table == NULL)
        {
            fprintf(stderr, "Line %d: The function %s is undefined.\n", getLineNumber(AT), AT->children[1]->tk.lexeme);
            return;
        }
        if(func_table->identifier > local_table->identifier)
        {
            fprintf(stderr, "Line %d: The function %s has been declared after the function call statement.\n", getLineNumber(AT), AT->children[1]->tk.lexeme);
            return;
        }
        if(func_table->input_num > 0 && AT->children[2] == NULL)
        {
            fprintf(stderr, "Line %d: Too few input parameters received for function %s.\n", getLineNumber(AT), func_table->funcName);
            return;
        }
        if(func_table->output_num > 0 & AT->children[0] == NULL)
        {
            fprintf(stderr, "Line %d: Too few output parameters received for function %s.\n", getLineNumber(AT), func_table->funcName);
            return;
        }
        verifyFunctionParameters(AT->children[0], 0, global_table, local_table, record_table, func_table, false);
        verifyFunctionParameters(AT->children[2], 0, global_table, local_table, record_table, func_table, true);
    }
    /*
    else if(getNonTerminalfromStr("<singleOrRecId>") == AT->nodeid)
    {
        if(AT->children[1] != NULL)     // TK_RECORD
        {
            char record_id[500];
            sprintf(record_id, "%s.%s", AT->children[0]->tk.lexeme, AT->children[1]->tk.lexeme);
            if(findGlobalId(global_table, record_id) == NULL && findLocalId(local_table, record_id) == NULL)
            {
                fprintf(stderr, "Line %d: Identifier %s not declared.\n", getLineNumber(AT), record_id);
            }
        }
        else
        {
            if(findGlobalId(global_table, AT->children[0]->tk.lexeme) == NULL && findLocalId(local_table, AT->children[0]->tk.lexeme) == NULL)
                fprintf(stderr, "Line %d: Identifier %s not declared.\n", getLineNumber(AT), AT->children[0]->tk.lexeme);
        }
    }
    */
    else if(getNonTerminalfromStr("<returnStmt>") == AT->nodeid)
    {
        if(local_table->output_num > 0 && AT->children[1] == NULL)
        {
            fprintf(stderr, "Line %d: Too few parameters in function %s return statement.\n", getLineNumber(AT), local_table->funcName);
            return;
        }
        verifyFunctionReturnStmt(AT->children[1], 0, local_table);
    }
    else if(getNonTerminalfromStr("<iterativeStmt>") == AT->nodeid)
    {
        modSet* head = NULL;
        head = getModifySetStmts(AT->children[2], head);
        head = getModifySetStmts(AT->children[3], head);
        if(!checkWhileCondition(AT->children[1], head))
        {
            fprintf(stderr, "Line %d: None of the variables participating in the iterations of the while loop gets updated.\n", getLineNumber(AT));
        }
    }
    else if(getNonTerminalfromStr("<function>") == AT->nodeid)
    {
        modSet* head = NULL;
        head = getModifySetStmts(AT->children[3], head);
        entry *fent = local_table->outputParameterList;
        while(fent != NULL)
        {
            if(!inModSet(head, fent->token.lexeme))
            {
                fprintf(stderr, "Line %d: Function %s return parameter %s never updated.\n", getLineNumber(AT), local_table->funcName, fent->token.lexeme);
            }
            fent = fent->next;
        }
    }
    int i;
    for (i = 0; i < AT->child_cnt; ++i)
        runSemanticAnalyzer(AT->children[i]);
}
