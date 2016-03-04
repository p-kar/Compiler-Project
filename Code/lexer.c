/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: lexer.c
* @Date:      2016-02-18 12:26:23
*/

//#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexerDef.h"

int currLine=1;
char buffer[20];
int bufferIndex;
int bufferSize=-1 ;

void printFileWithoutComments(const char* filename)
{
    FILE* fp = fopen(filename,"r");

    int buffersize ; 

    char buffer[20];
    int i;
    int state=0;
    
    while(1)
    {
        buffersize = fread(buffer,sizeof(char),(size_t)20,fp);
        if(buffersize==0)
            return;
        
        for(i=0;i<buffersize;i++)
        {
            if(buffer[i]==EOF)
                return;
            if(state==0 && buffer[i]=='%' )
            {
                state =1 ;
            }
            else if(state==1 &&  buffer[i]=='\n'  )
            {
                state=0;
            }
            if(state==0)
            {
                printf("%c",buffer[i]);
            }

        }
    }


}
TERMINAL getTerminalfromStr(const char* str)
{
    if(strcmp(str, "TK_MAIN") == 0)
        return TK_MAIN;
    else if(strcmp(str, "TK_END") == 0)
        return TK_END;
    else if(strcmp(str, "TK_FUNID") == 0)
        return TK_FUNID;
    else if(strcmp(str, "TK_SEM") == 0)
        return TK_SEM;
    else if(strcmp(str, "TK_COMMENT") == 0)
        return TK_COMMENT;
    else if(strcmp(str, "TK_INPUT") == 0)
        return TK_INPUT;
    else if(strcmp(str, "TK_PARAMETER") == 0)
        return TK_PARAMETER;
    else if(strcmp(str, "TK_LIST") == 0)
        return TK_LIST;
    else if(strcmp(str, "TK_SQL") == 0)
        return TK_SQL;
    else if(strcmp(str, "TK_SQR") == 0)
        return TK_SQR;
    else if(strcmp(str, "TK_OUTPUT") == 0)
        return TK_OUTPUT;
    else if(strcmp(str, "TK_ID") == 0)
        return TK_ID;
    else if(strcmp(str, "TK_INT") == 0)
        return TK_INT;
    else if(strcmp(str, "TK_REAL") == 0)
        return TK_REAL;
    else if(strcmp(str, "TK_RECORD") == 0)
        return TK_RECORD;
    else if(strcmp(str, "TK_RECORDID") == 0)
        return TK_RECORDID;
    else if(strcmp(str, "TK_COMMA") == 0)
        return TK_COMMA;
    else if(strcmp(str, "TK_ENDRECORD") == 0)
        return TK_ENDRECORD;
    else if(strcmp(str, "TK_TYPE") == 0)
        return TK_TYPE;
    else if(strcmp(str, "TK_COLON") == 0)
        return TK_COLON;
    else if(strcmp(str, "TK_FIELDID") == 0)
        return TK_FIELDID;
    else if(strcmp(str, "TK_GLOBAL") == 0)
        return TK_GLOBAL;
    else if(strcmp(str, "TK_ASSIGNOP") == 0)
        return TK_ASSIGNOP;
    else if(strcmp(str, "TK_DOT") == 0)
        return TK_DOT;
    else if(strcmp(str, "TK_CALL") == 0)
        return TK_CALL;
    else if(strcmp(str, "TK_WITH") == 0)
        return TK_WITH;
    else if(strcmp(str, "TK_PARAMETERS") == 0)
        return TK_PARAMETERS;
    else if(strcmp(str, "TK_WHILE") == 0)
        return TK_WHILE;
    else if(strcmp(str, "TK_OP") == 0)
        return TK_OP;
    else if(strcmp(str, "TK_CL") == 0)
        return TK_CL;
    else if(strcmp(str, "TK_ENDWHILE") == 0)
        return TK_ENDWHILE;
    else if(strcmp(str, "TK_IF") == 0)
        return TK_IF;
    else if(strcmp(str, "TK_THEN") == 0)
        return TK_THEN;
    else if(strcmp(str, "TK_ELSE") == 0)
        return TK_ELSE;
    else if(strcmp(str, "TK_ENDIF") == 0)
        return TK_ENDIF;
    else if(strcmp(str, "TK_READ") == 0)
        return TK_READ;
    else if(strcmp(str, "TK_WRITE") == 0)
        return TK_WRITE;
    else if(strcmp(str, "TK_PLUS") == 0)
        return TK_PLUS;
    else if(strcmp(str, "TK_MUL") == 0)
        return TK_MUL;
    else if(strcmp(str, "TK_MINUS") == 0)
        return TK_MINUS;
    else if(strcmp(str, "TK_DIV") == 0)
        return TK_DIV;
    else if(strcmp(str, "TK_NOT") == 0)
        return TK_NOT;
    else if(strcmp(str, "TK_NUM") == 0)
        return TK_NUM;
    else if(strcmp(str, "TK_RNUM") == 0)
        return TK_RNUM;
    else if(strcmp(str, "TK_AND") == 0)
        return TK_AND;
    else if(strcmp(str, "TK_OR") == 0)
        return TK_OR;
    else if(strcmp(str, "TK_LT") == 0)
        return TK_LT;
    else if(strcmp(str, "TK_LE") == 0)
        return TK_LE;
    else if(strcmp(str, "TK_EQ") == 0)
        return TK_EQ;
    else if(strcmp(str, "TK_GT") == 0)
        return TK_GT;
    else if(strcmp(str, "TK_GE") == 0)
        return TK_GE;
    else if(strcmp(str, "TK_NE") == 0)
        return TK_NE;
    else if(strcmp(str, "TK_RETURN") == 0)
        return TK_RETURN;
    else if(strcmp(str, "TK_EPS") == 0)
        return TK_EPS;
    else if(strcmp(str, "TK_DOLLAR") == 0)
        return TK_DOLLAR;
    else if(strcmp(str, "TK_EOF") == 0)
        return TK_EOF;
    return TK_ERROR;
}

char* getTerminalStr(TERMINAL termid)
{
    char* str = (char*) malloc(sizeof(char) * 100);
    if(TK_MAIN == termid)
        strcpy(str, "TK_MAIN");
    else if(TK_END == termid)
        strcpy(str, "TK_END");
    else if(TK_FUNID == termid)
        strcpy(str, "TK_FUNID");
    else if(TK_SEM == termid)
        strcpy(str, "TK_SEM");
    else if(TK_INPUT == termid)
        strcpy(str, "TK_INPUT");
    else if(TK_PARAMETER == termid)
        strcpy(str, "TK_PARAMETER");
    else if(TK_LIST == termid)
        strcpy(str, "TK_LIST");
    else if(TK_COMMENT == termid)
        strcpy(str, "TK_COMMENT");
    else if(TK_SQL == termid)
        strcpy(str, "TK_SQL");
    else if(TK_SQR == termid)
        strcpy(str, "TK_SQR");
    else if(TK_OUTPUT == termid)
        strcpy(str, "TK_OUTPUT");
    else if(TK_ID == termid)
        strcpy(str, "TK_ID");
    else if(TK_INT == termid)
        strcpy(str, "TK_INT");
    else if(TK_REAL == termid)
        strcpy(str, "TK_REAL");
    else if(TK_RECORD == termid)
        strcpy(str, "TK_RECORD");
    else if(TK_RECORDID == termid)
        strcpy(str, "TK_RECORDID");
    else if(TK_COMMA == termid)
        strcpy(str, "TK_COMMA");
    else if(TK_ENDRECORD == termid)
        strcpy(str, "TK_ENDRECORD");
    else if(TK_TYPE == termid)
        strcpy(str, "TK_TYPE");
    else if(TK_COLON == termid)
        strcpy(str, "TK_COLON");
    else if(TK_FIELDID == termid)
        strcpy(str, "TK_FIELDID");
    else if(TK_GLOBAL == termid)
        strcpy(str, "TK_GLOBAL");
    else if(TK_ASSIGNOP == termid)
        strcpy(str, "TK_ASSIGNOP");
    else if(TK_DOT == termid)
        strcpy(str, "TK_DOT");
    else if(TK_CALL == termid)
        strcpy(str, "TK_CALL");
    else if(TK_WITH == termid)
        strcpy(str, "TK_WITH");
    else if(TK_PARAMETERS == termid)
        strcpy(str, "TK_PARAMETERS");
    else if(TK_WHILE == termid)
        strcpy(str, "TK_WHILE");
    else if(TK_OP == termid)
        strcpy(str, "TK_OP");
    else if(TK_CL == termid)
        strcpy(str, "TK_CL");
    else if(TK_ENDWHILE == termid)
        strcpy(str, "TK_ENDWHILE");
    else if(TK_IF == termid)
        strcpy(str, "TK_IF");
    else if(TK_THEN == termid)
        strcpy(str, "TK_THEN");
    else if(TK_ELSE == termid)
        strcpy(str, "TK_ELSE");
    else if(TK_ENDIF == termid)
        strcpy(str, "TK_ENDIF");
    else if(TK_READ == termid)
        strcpy(str, "TK_READ");
    else if(TK_WRITE == termid)
        strcpy(str, "TK_WRITE");
    else if(TK_PLUS == termid)
        strcpy(str, "TK_PLUS");
    else if(TK_MUL == termid)
        strcpy(str, "TK_MUL");
    else if(TK_MINUS == termid)
        strcpy(str, "TK_MINUS");
    else if(TK_DIV == termid)
        strcpy(str, "TK_DIV");
    else if(TK_NOT == termid)
        strcpy(str, "TK_NOT");
    else if(TK_NUM == termid)
        strcpy(str, "TK_NUM");
    else if(TK_RNUM == termid)
        strcpy(str, "TK_RNUM");
    else if(TK_AND == termid)
        strcpy(str, "TK_AND");
    else if(TK_OR == termid)
        strcpy(str, "TK_OR");
    else if(TK_LT == termid)
        strcpy(str, "TK_LT");
    else if(TK_LE == termid)
        strcpy(str, "TK_LE");
    else if(TK_EQ == termid)
        strcpy(str, "TK_EQ");
    else if(TK_GT == termid)
        strcpy(str, "TK_GT");
    else if(TK_GE == termid)
        strcpy(str, "TK_GE");
    else if(TK_NE == termid)
        strcpy(str, "TK_NE");
    else if(TK_RETURN == termid)
        strcpy(str, "TK_RETURN");
    else if(TK_EPS == termid)
        strcpy(str, "eps");
    else if(TK_DOLLAR == termid)
        strcpy(str, "$");
    else if(TK_EOF == termid)
        strcpy(str, "TK_EOF");
    else
        strcpy(str, "TK_ERROR");
    return str;
}

bool isTerminal(int termid)
{
    if(termid >= TERMINAL_OFFSET && termid <= TERMINAL_OFFSET + NUM_TERMINALS)
        return true;
    return false;
}

TERMINAL findToken(char str[])
{
    if(strcmp(str,"with") == 0 )
        return TK_WITH;
    else if(strcmp(str, "parameters") == 0)
        return TK_PARAMETERS;
    else if(strcmp(str, "end") == 0)
        return TK_END;
    else if(strcmp(str, "while") == 0)
        return TK_WHILE;
    else if(strcmp(str, "int") == 0)
        return TK_INT;
    else if(strcmp(str, "real") == 0)
        return TK_REAL;
    else if(strcmp(str, "type") == 0)
        return TK_TYPE;
    else if(strcmp(str, "global") == 0)
        return TK_GLOBAL;
    else if(strcmp(str, "parameter") == 0)
        return TK_PARAMETER;
    else if(strcmp(str, "list") == 0)
        return TK_LIST;
    else if(strcmp(str, "input") == 0)
        return TK_INPUT;
    else if(strcmp(str, "output") == 0)
        return TK_OUTPUT;
    else if(strcmp(str, "endwhile") == 0)
        return TK_ENDWHILE;
    else if(strcmp(str, "if") == 0)
        return TK_IF;
    else if(strcmp(str, "then") == 0)
        return TK_THEN;
    else if(strcmp(str, "endif") == 0)
        return TK_ENDIF;
    else if(strcmp(str, "read") == 0)
        return TK_READ;
    else if(strcmp(str, "write") == 0)
        return TK_WRITE;
    else if(strcmp(str, "return") == 0)
        return TK_RETURN;
    else if(strcmp(str, "call") == 0)
        return TK_CALL;
    else if(strcmp(str, "record") == 0)
        return TK_RECORD;
    else if(strcmp(str, "endrecord") == 0)
        return TK_ENDRECORD;
    else if(strcmp(str, "else") == 0)
        return TK_ELSE;
    else
        return TK_FIELDID;
}

void getStream(FILE* fp)
{
        bufferSize =  fread(buffer,sizeof(char),(size_t)20,fp);
        bufferIndex = 0;
}

char getCharacter(FILE* fp)
{
    if(bufferSize==-1 || bufferIndex==bufferSize  )
    {
        getStream(fp);
        if(bufferSize==0)
        {
            return 127;
            // EOF
        }
    }
    //printf("ok\n");
    //printf("%c",buffer[bufferIndex]);
    if(bufferSize!=0)
    {
        return buffer[bufferIndex++];
    }
    else
    {
        return 127;
    }
}

tokenInfo getNextToken(FILE *fp)
{
    //char c;
    long long int lexCount=0;
    int currState=1;
    tokenInfo tk;
    memset(tk.lexeme,'\0', ( sizeof(tk.lexeme)/ sizeof(char) ) );
    //tk = (tokenInfo*) malloc(sizeof(tokenInfo));
    while(1)
    {

        char c = getCharacter(fp);
        if(c==EOF)
        {
            c = 127;
        }
        tk.lexeme[lexCount] = c ;
        lexCount++;
        switch(currState)
        {
            case 1:
                    if(c==',')
                    {
                        tk.lexeme[lexCount]='\0';
                        tk.lineNum = currLine;
                        tk.tokenType = TK_COMMA;
                        return tk;
                    }
                    else if(c=='[')
                    {
                        tk.lexeme[lexCount]='\0';
                        tk.lineNum = currLine;
                        tk.tokenType = TK_SQL;
                        return tk;
                    }
                    else if(c==']')
                    {
                        tk.lexeme[lexCount]='\0';
                        tk.lineNum = currLine;
                        tk.tokenType = TK_SQR;
                        return tk;
                    }
                    else if(c==':')
                    {
                        tk.lexeme[lexCount]='\0';
                        tk.lineNum = currLine;
                        tk.tokenType = TK_COLON;
                        return tk;
                    }
                    else if(c==';')
                    {
                        tk.lexeme[lexCount]='\0';
                        tk.lineNum = currLine;
                        tk.tokenType = TK_SEM;
                        return tk;
                    }
                    else if(c=='.')
                    {
                        tk.lineNum = currLine;
                        tk.lexeme[lexCount]='\0';
                        tk.tokenType = TK_DOT;
                        return tk;
                    }
                    else if(c=='(')
                    {
                        tk.lexeme[lexCount]='\0';
                        tk.lineNum = currLine;
                        tk.tokenType = TK_OP;
                        return tk;
                    }
                    else if(c==')')
                    {
                        tk.lexeme[lexCount]='\0';
                        tk.lineNum = currLine;
                        tk.tokenType = TK_CL;
                        return tk;
                    }
                    else if(c=='+')
                    {
                        tk.lexeme[lexCount]='\0';
                        tk.lineNum = currLine;
                        tk.tokenType = TK_PLUS;
                        return tk;
                    }
                    else if(c=='-')
                    {
                        tk.lexeme[lexCount]='\0';
                        tk.lineNum = currLine;
                        tk.tokenType = TK_MINUS;
                        return tk;
                    }
                    else if(c=='*')
                    {
                        tk.lexeme[lexCount]='\0';
                        tk.lineNum = currLine;
                        tk.tokenType = TK_MUL;
                        return tk;
                    }
                    else if(c=='/')
                    {
                        tk.lexeme[lexCount]='\0';
                        tk.lineNum = currLine;
                        tk.tokenType = TK_DIV;
                        return tk;
                    }
                    else if(c=='~')
                    {
                        tk.lexeme[lexCount]='\0';
                        tk.lineNum = currLine;
                        tk.tokenType = TK_NOT;
                        return tk;
                    }
                    else if(c==127)
                    {
                        tk.lexeme[lexCount]='\0';
                        tk.lineNum = currLine;
                        tk.tokenType = TK_EOF;
                        return tk;
                    }
                    else if(c==' '||c=='\t'||c=='\v'||c=='\r')
                    {
                        lexCount=0;
                    }
                    else if(c=='\n')
                    {
                        currLine++;
                        lexCount=0;
                    }
                    else if(c=='@')
                    {
                        currState=11;
                    }

                    else if(c=='&')
                    {
                        currState=21;
                    }

                    else if(c=='=')
                    {
                        currState = 31;
                    }

                    else if(c=='!')
                    {
                        currState=41;
                    }

                    else if(c=='<')
                    {
                        currState=51;
                    }
                    else if(c=='>')
                    {
                        currState=61;
                    }
                    else if(c=='%')
                    {
                        currState=71;
                    }
                    else if(c=='b' || c=='c' || c=='d')
                    {
                        currState = 81;
                    }
                    else if(c>='a' && c<='z')
                    {
                        currState = 91;

                    }
                    else if(c>='0' && c<='9')
                    {
                        currState = 101;
                    }
                    else if(c=='_')
                    {
                        currState = 111;
                    }
                    else if(c=='#')
                    {
                        currState = 121;
                    }
                    else
                    {
                        tk.tokenType = TK_ERROR;
                        tk.lineNum   = currLine;
                        printf("ERROR_2: Unknown Symbol   %c at line %d\n",c,currLine);
                        sprintf(tk.lexeme,"ERROR_2");
                        //sprintf(tk.lexeme,"ERROR_2: Unknown Symbol   %c at line %d",c,currLine);
                        return tk;
                    }
                break;

            case 11:
                    if(c=='@')
                    {
                        currState=12;
                    }
                    else
                    {
                        bufferIndex--;
                        tk.lexeme[lexCount]='\0';
                        char temp[lexCount+1];
                        strncpy(temp,tk.lexeme,lexCount+1);
                        printf("ERROR_3:Unknown pattern %s at line %d\n", temp,currLine);
                        sprintf(tk.lexeme, "ERROR_3");                        
                        //sprintf(tk.lexeme, "ERROR_3:Unknown pattern %s at line %d", temp,currLine);
                        tk.tokenType = TK_ERROR;
                        tk.lineNum = currLine;
                        if(c == '\n')
                            currLine++;
                        return tk;
                    }
                break;
            case 12:
                    if(c=='@')
                    {
                        tk.lexeme[lexCount]='\0';
                        tk.tokenType = TK_OR;
                        tk.lineNum = currLine;
                        return tk;
                    }
                    else
                    {
                        bufferIndex--;
                        tk.lexeme[lexCount]='\0';
                        char temp[lexCount+1];
                        strncpy(temp,tk.lexeme,lexCount+1);
                        printf("ERROR_3:Unknown pattern %s at line %d\n", temp,currLine);
                        sprintf(tk.lexeme, "ERROR_3");//:Unknown pattern %s at line %d", temp,currLine);
                        //sprintf(tk.lexeme,"ERROR_3:Unknown pattern %s at line %d", tk.lexeme,currLine);
                        tk.tokenType = TK_ERROR;
                        tk.lineNum = currLine;
                        if(c == '\n')
                            currLine++;
                        return tk;
                    }
                break;
            case 21:
                    if(c=='&')
                    {
                        currState=22;
                    }
                    else
                    {
                        bufferIndex--;
                        tk.lexeme[lexCount]='\0';
                        char temp[lexCount+1];
                        strncpy(temp,tk.lexeme,lexCount+1);
                        printf("ERROR_3:Unknown pattern %s at line %d\n", temp,currLine);
                        sprintf(tk.lexeme, "ERROR_3");//:Unknown pattern %s at line %d", temp,currLine);
                        //sprintf(tk.lexeme,"ERROR_3:Unknown pattern %s at line %d", tk.lexeme,currLine);
                        tk.tokenType = TK_ERROR;
                        tk.lineNum = currLine;
                        //if(c == '\n')
                        //    currLine++;
                        return tk;
                    }
                break;
            case 22:
                    if(c=='&')
                    {
                        tk.tokenType = TK_AND;
                        tk.lineNum = currLine;
                        tk.lexeme[lexCount]='\0';
                        return tk;
                    }
                    else
                    {
                        bufferIndex--;
                        tk.lexeme[lexCount]='\0';
                        char temp[lexCount+1];
                        strncpy(temp,tk.lexeme,lexCount+1);
                        printf("ERROR_3:Unknown pattern %s at line %d\n", temp,currLine);
                        sprintf(tk.lexeme, "ERROR_3");//:Unknown pattern %s at line %d", temp,currLine);
                        //sprintf(tk.lexeme,"ERROR_3:Unknown pattern %s at line %d", tk.lexeme,currLine);
                        tk.tokenType = TK_ERROR;
                        tk.lineNum = currLine;
                        //if(c == '\n')
                        //    currLine++;
                        return tk;
                    }
                break;
            case 31:
                    if(c=='=')
                    {
                        tk.tokenType = TK_EQ;
                        tk.lineNum = currLine;
                        tk.lexeme[lexCount]='\0';
                        return tk;
                    }
                    else if(c==' '||c=='\n'||c=='\t'||c=='\r'||c=='\v')
                    {
                        tk.tokenType = TK_ASSIGNOP;
                        tk.lexeme[lexCount]='\0';
                        tk.lineNum=currLine;
                        return tk;
                    }
                    else
                    {
                        bufferIndex--;
                        tk.lexeme[lexCount]='\0';
                        char temp[lexCount+1];
                        strncpy(temp,tk.lexeme,lexCount+1);
                        printf("ERROR_3:Unknown pattern %s at line %d\n", temp,currLine);
                        sprintf(tk.lexeme, "ERROR_3");//:Unknown pattern %s at line %d", temp,currLine);
                        //sprintf(tk.lexeme,"ERROR_3:Unknown pattern %s at line %d", tk.lexeme,currLine);
                        tk.tokenType = TK_ERROR;
                        tk.lineNum = currLine;
                        //if(c == '\n')
                        //    currLine++;
                        return tk;
                    }
                break;
            case 41:
                    if(c=='=')
                    {
                        tk.tokenType = TK_NE;
                        tk.lineNum = currLine;
                        tk.lexeme[lexCount]='\0';
                        return tk;
                    }
                    else
                    {
                        bufferIndex--;
                        tk.lexeme[lexCount]='\0';
                        char temp[lexCount+1];
                        strncpy(temp,tk.lexeme,lexCount+1);
                        printf("ERROR_3:Unknown pattern %s at line %d\n", temp,currLine);
                        sprintf(tk.lexeme, "ERROR_3");//:Unknown pattern %s at line %d", temp,currLine);
                        //sprintf(tk.lexeme,"ERROR_3:Unknown pattern %s at line %d", tk.lexeme,currLine);
                        tk.tokenType = TK_ERROR;
                        tk.lineNum = currLine;
                        //if(c == '\n')
                        //    currLine++;
                        return tk;
                    }
                break;
            case 51:
                    if(c=='=')
                    {
                        tk.tokenType = TK_LE;
                        tk.lineNum = currLine ;
                        tk.lexeme[lexCount]='\0';
                        return tk;
                    }
                    else if(c=='-')
                    {
                        currState=52;
                    }
                    else
                    {
                        bufferIndex--;
                        tk.lexeme[lexCount-1]='\0';
                        tk.tokenType = TK_LT;
                        tk.lineNum = currLine;
                        return tk;
                    }
                break;
            case 52:
                    if(c=='-')
                    {
                        currState=53;
                    }
                    else
                    {
                        bufferIndex--;
                        tk.lexeme[lexCount]='\0';
                        char temp[lexCount+1];
                        strncpy(temp,tk.lexeme,lexCount+1);
                        printf("ERROR_3:Unknown pattern %s at line %d\n", temp,currLine);
                        sprintf(tk.lexeme, "ERROR_3");//:Unknown pattern %s at line %d", temp,currLine);
                        //sprintf(tk.lexeme,"ERROR_3:Unknown pattern %s at line %d", tk.lexeme,currLine);
                        tk.tokenType = TK_ERROR;
                        tk.lineNum = currLine;
                         //if(c == '\n')
                         //   currLine++;
                         return tk;
                    }
                break;
            case 53:
                    if(c=='-')
                    {
                        tk.tokenType = TK_ASSIGNOP;
                        tk.lineNum = currLine;
                        tk.lexeme[lexCount]='\0';
                        return tk;
                    }
                    else
                    {
                        bufferIndex--;
                        tk.lexeme[lexCount]='\0';
                        char temp[lexCount+1];
                        strncpy(temp,tk.lexeme,lexCount+1);
                        printf("ERROR_3:Unknown pattern %s at line %d\n", temp,currLine);
                        sprintf(tk.lexeme, "ERROR_3");//:Unknown pattern %s at line %d", temp,currLine);
                        //sprintf(tk.lexeme,"ERROR_3:Unknown pattern %s at line %d", tk.lexeme,currLine);
                        tk.tokenType = TK_ERROR;
                        tk.lineNum = currLine;
                         //if(c == '\n')
                         //   currLine++;
                         return tk;
                    }
                break;
            case 61:
                    if(c=='=')
                    {
                        tk.tokenType = TK_GE;
                        tk.lineNum = currLine ;
                        tk.lexeme[lexCount]='\0';
                        return tk;
                    }
                    else
                    {
                        bufferIndex--;
                        tk.lexeme[lexCount-1]='\0';

                        // buffer position wala panga
                        tk.tokenType = TK_GT;
                        tk.lineNum = currLine;
                        return tk;
                    }
                break;
            case 71:
                    if(c=='\n')
                    {
                        currLine++;
                        currState=1;
                        lexCount=0;
                        //tk.tokenType= TK_COMMENT;
                        //tk.lineNum = currLine ;
                        //tk.lexeme[lexCount]='\0';
                        //return tk;
                    }
                    else if(c==127)
                    {
                        tk.tokenType = TK_EOF;
                        tk.lexeme[0]='\0';
                        return tk ;
                    }
                break;
            case 81:
                    if(c>='a' && c<='z')
                        currState = 91;
                    else if(c>='2' && c<='7')
                        currState = 82;
                    else
                    {
                        bufferIndex--;
                        tk.tokenType = TK_ERROR ;
                        tk.lexeme[lexCount]='\0';
                        char temp[lexCount+1];
                        strncpy(temp,tk.lexeme,lexCount+1);
                        printf("ERROR_3:Unknown pattern %s at line %d\n", temp,currLine);
                        sprintf(tk.lexeme, "ERROR_3");//:Unknown pattern %s at line %d", temp,currLine);
                        //sprintf(tk.lexeme,"ERROR_3:Unknown pattern %s at line %d", tk.lexeme,currLine);
                        //tk.lexeme[lexCount-1]= '\0';
                        tk.lineNum = currLine ;
                        return tk;
                    }
                break;
            case 82:
                    if(c>='2' && c<='7')
                    {
                        currState = 83;
                    }
                    else if(!(c>='b' && c<='d') )
                    {
                        if(lexCount>20)
                        {
                            printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n",currLine);
                            sprintf(tk.lexeme,"ERROR_1");// : Identifier at line %d is longer than the prescribed length of 20 characters",currLine);
                            bufferIndex--;
                            tk.tokenType = TK_ERROR;
                            tk.lineNum = currLine;
                            return tk;
                        }

                        bufferIndex--;
                        tk.tokenType    = TK_ID;
                        tk.lineNum = currLine;
                        tk.lexeme[lexCount-1]='\0';
                        return tk;
                    }
                break;
            case 83:
                    if(!(c>='2' && c<='7') )
                    {
                        if(lexCount>20)
                        {
                            printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n",currLine);
                            sprintf(tk.lexeme,"ERROR_1");// : Identifier at line %d is longer than the prescribed length of 20 characters",currLine);
                            bufferIndex--;
                            tk.tokenType = TK_ERROR;
                            tk.lineNum = currLine;
                            return tk;
                        }
                        bufferIndex--;
                        tk.tokenType = TK_ID;
                        tk.lineNum = currLine ;
                        tk.lexeme[lexCount-1]='\0';
                        return tk;
                    }
                break;
            case 91:
                    if ( !(c>='a' && c<='z') )
                    {
                         if(lexCount>20)
                        {
                            printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n",currLine);
                            sprintf(tk.lexeme,"ERROR_1");// : Identifier at line %d is longer than the prescribed length of 20 characters",currLine);
                            bufferIndex--;
                            tk.tokenType = TK_ERROR;
                            tk.lineNum = currLine;
                            return tk;
                        }
                        //buffer thing
                        bufferIndex--;
                        tk.lexeme[lexCount-1] = '\0';
                        tk.tokenType = findToken(tk.lexeme);
                        tk.lineNum = currLine ;
                        return tk;
                    }
                break;
            case 101:
                    if(c>='0' && c<='9')
                    {
                        if(lexCount>20)
                        {
                            tk.tokenType = TK_ERROR ;
                            tk.lineNum = currLine;
                            printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n",currLine);
                            sprintf(tk.lexeme,"ERROR_1");// : Identifier at line %d is longer than the prescribed length of 20 characters",currLine);
                            return tk;
                        }
                    }
                    else if(c=='.')
                    {
                        currState = 102;
                    }
                    else
                    {
                        // buffer position wala problem
                        //  managing the lexemee
                        bufferIndex--;
                        tk.lexeme[lexCount-1] = '\0';
                        tk.tokenType = TK_NUM;
                        tk.lineNum = currLine ;
                        return tk ;

                    }
                break;
            case 102:
                    if(c>='0' && c<='9')
                    {
                        currState  = 103;
                    }
                    else
                    {
                        bufferIndex--;
                        tk.tokenType = TK_ERROR;
                        tk.lineNum = currLine;
                        tk.lexeme[lexCount]='\0';
                        char temp[lexCount+1];
                        strncpy(temp,tk.lexeme,lexCount+1);
                        printf("ERROR_3:Unknown pattern %s at line %d\n", temp,currLine);
                        sprintf(tk.lexeme, "ERROR_3");//:Unknown pattern %s at line %d", temp,currLine);
                        //sprintf(tk.lexeme,"ERROR_3:Unknown pattern %s at line %d", tk.lexeme,currLine);
                        return tk;
                    }
                break;
            case 103:
                    if(c>='0' && c<='9')
                    {
                        tk.tokenType = TK_RNUM;
                        tk.lineNum = currLine ;
                        tk.lexeme[lexCount] = '\0';
                        return tk;
                    }
                    else
                    {
                        bufferIndex--;
                        tk.lexeme[lexCount]='\0';
                        tk.tokenType = TK_ERROR ;
                        tk.lineNum = currLine;
                        char temp[lexCount+1];
                        strncpy(temp,tk.lexeme,lexCount+1);
                        printf("ERROR_3:Unknown pattern %s at line %d\n", temp,currLine);
                        sprintf(tk.lexeme, "ERROR_3");//:Unknown pattern %s at line %d", temp,currLine);
                        //sprintf(tk.lexeme,"ERROR_3:Unknown pattern %s at line %d", tk.lexeme,currLine);
                        return tk;
                    }
                break;
            case 111:
                    if( (c>='a' && c<='z') || (c>='A' && c<='Z') )
                    {

                        currState = 112;
                    }
                    else
                    {
                        // buffer wala problem;
                        bufferIndex--;
                        tk.tokenType = TK_ERROR;
                        tk.lineNum = currLine;
                        tk.lexeme[lexCount]='\0';
                        char temp[lexCount+1];
                        strncpy(temp,tk.lexeme,lexCount+1);
                        printf("ERROR_3:Unknown pattern %s at line %d\n", temp,currLine);
                        sprintf(tk.lexeme, "ERROR_3");//:Unknown pattern %s at line %d", temp,currLine);
                        //sprintf(tk.lexeme,"ERROR_3:Unknown pattern %s at line %d", tk.lexeme,currLine);
                        return tk;
                    }
                break;
            case 112:
                    if(c>='0' && c<='9')
                    {
                        currState = 113 ;
                    }
                    else if(c==' '|| c=='\t' || c=='\r' || c=='\v' || c=='\n')
                    {

                        if(lexCount>30)
                        {
                            printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n",currLine);
                            sprintf(tk.lexeme,"ERROR_1");// : Identifier at line %d is longer than the prescribed length of 20 characters",currLine);
                            //bufferIndex--;
                            tk.tokenType = TK_ERROR;
                            tk.lineNum = currLine;
                            return tk;
                        }

                            bufferIndex--;
                            tk.lexeme[lexCount-1] = '\0';
                            tk.lineNum = currLine;
                            if(strcmp(tk.lexeme,"_main")==0)
                                tk.tokenType = TK_MAIN;
                            else
                                tk.tokenType = TK_FUNID;
                            return tk;
                    }
                    else if( !( (c>='a' && c<='z')||
                         (c>='A' && c<='Z') ||
                         (c>='0' && c<='9') ) )
                         {
                            bufferIndex--;
                            tk.lexeme[lexCount]='\0';
                            char temp[lexCount+1];
                            strncpy(temp,tk.lexeme,lexCount+1);
                            printf("ERROR_3:Unknown pattern %s at line %d\n", temp,currLine);
                            sprintf(tk.lexeme, "ERROR_3");//:Unknown pattern %s at line %d", temp,currLine);
                            //sprintf(tk.lexeme,"ERROR_3:Unknown pattern %s at line %d", tk.lexeme,currLine);
                            tk.tokenType = TK_ERROR ;
                            tk.lineNum = currLine;
                            return tk;

                         }
                break;
            case 113:
                if(c==' '|| c=='\t' || c=='\r' || c=='\v' || c=='\n')
                    {
                        if(lexCount>30)
                        {
                            printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n",currLine);
                            
                            sprintf(tk.lexeme,"ERROR_1");// : Identifier at line %d is longer than the prescribed length of 20 characters",currLine);
                           //bufferIndex--;
                            tk.tokenType = TK_ERROR;
                            tk.lineNum = currLine;
                            return tk;
                        }
                            bufferIndex--;
                            tk.lexeme[lexCount-1] = '\0';
                            tk.lineNum = currLine;
                            if(strcmp(tk.lexeme,"_main")==0)
                                tk.tokenType = TK_MAIN;
                            else
                                tk.tokenType = TK_FUNID;
                            return tk;
                    }
                else if( !(c>='0' && c<='9') )
                         {
                            bufferIndex--;
                            tk.lexeme[lexCount]='\0';
                            char temp[lexCount+1];
                            strncpy(temp,tk.lexeme,lexCount+1);
                            printf("ERROR_3:Unknown pattern %s at line %d\n", temp,currLine);
                            sprintf(tk.lexeme, "ERROR_3");//:Unknown pattern %s at line %d", temp,currLine);
                            //sprintf(tk.lexeme,"ERROR_3:Unknown pattern %s at line %d", tk.lexeme,currLine);
                            tk.tokenType = TK_ERROR ;
                            tk.lineNum = currLine;
                            return tk;

                         }
                break;
            case 121:
                    if(c>='a' && c<='z')
                    {
                        currState =122;
                    }
                    else
                    {
                        //buffer stuff
                        bufferIndex--;
                        tk.tokenType = TK_ERROR ;
                        tk.lineNum = currLine ;
                        tk.lexeme[lexCount]='\0';
                        char temp[lexCount+1];
                        strncpy(temp,tk.lexeme,lexCount+1);
                        printf("ERROR_3:Unknown pattern %s at line %d\n", temp,currLine);
                        sprintf(tk.lexeme, "ERROR_3");//:Unknown pattern %s at line %d", temp,currLine);
                        //sprintf(tk.lexeme,"ERROR_3:Unknown pattern %s at line %d", tk.lexeme,currLine);
                        if(c=='\n')
                        {
                            currLine++;
                        }
                        return tk;
                    }
                break;
            case 122:
                    if(!  ( (c>='a') && (c<='z') )  )
                    {
                        //buffer wala problem
                        // some bullshit about lexeme

                        if(lexCount>20)
                        {
                            printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n",currLine);
                            
                            sprintf(tk.lexeme,"ERROR_1");// : Identifier at line %d is longer than the prescribed length of 20 characters",currLine);
                            bufferIndex--;
                            tk.tokenType = TK_ERROR;
                            tk.lineNum = currLine;
                            return tk;
                        }

                        bufferIndex--;
                        tk.lexeme[lexCount-1]='\0';
                        tk.tokenType = TK_RECORDID;
                        tk.lineNum = currLine ;
                        return tk;
                    }
                break;
            default:
                 break;
                 //this should never be executed
        }
    }
}

void printTokenList(const char* src_code_filename)
{
    FILE *tfp = fopen(src_code_filename, "r");
    tokenInfo t = getNextToken(tfp);
    int space = 20;
    char tokenType[20] = "tokenType";
    char lexeme[20] = "lexeme";
    char lineNum[20] = "lineNum";
    printf("%*s%*s%*s\n", space, tokenType, space, lexeme, space, lineNum);
    while(t.tokenType != TK_EOF)
    {
        printf("%*s%*s%*d\n", space, getTerminalStr(t.tokenType), space, t.lexeme, space, t.lineNum);
        t = getNextToken(tfp);
    }
}