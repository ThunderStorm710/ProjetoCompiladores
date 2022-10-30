%{
/************Autores*************
* Pedro Ascensão   -   2020233012
* Leonardo Pina    -   2019234318
*********************************/
#include <stdio.h>
//#include "ASTree.h"
#define true 1
#define false 0
int yylex(void);

void yyerror (const char *s);
char* yytext;
int printTree;
int hasError;
char temp[256];
%}


%type <node> Program
%type <node> MethodDecl
%type <node> FieldDecl
%type <node> Type
%type <node> MethodHeader
%type <node> FormalParams
%type <node> MethodBody
%type <node> VarDecl
%type <node> Statement
%type <node> MethodInvocation
%type <node> MethodInvocationRecursive
%type <node> Assignment
%type <node> Expr
%type <node> ParseArgs


%token                  COMMA
%token                  MINUS
%token                  RSHIFT
%token                  LSHIFT
%token                  LT
%token                  LSQ
%token                  LPAR
%token                  LE
%token                  LBRACE
%token                  GT
%token                  GE
%token                  DIV
%token                  STAR
%token                  EQ
%token                  ASSIGN
%token                  AND
%token                  SEMICOLON
%token                  RSQ
%token                  RPAR
%token                  RBRACE
%token                  PLUS
%token                  OR
%token                  NOT
%token                  NE
%token                  MOD
%token                  XOR
%token                  ARROW
%token                  BOOL
%token                  INT
%token                  IF
%token                  ELSE
%token                  DOUBLE
%token                  DOTLENGTH
%token                  PRINT
%token                  BOOLLIT
%token                  WHILE
%token                  VOID
%token                  STATIC
%token                  RETURN
%token                  PUBLIC
%token                  PARSEINT
%token                  CLASS
%token                  SPACE

%token <strlit>         STRLIT
%token <id>             ID
%token <intlit>         INTLIT
%token <reallit>        REALLIT
%token                  CR_LN
%token                  RESERVED



%left                   COMMA
%right                  ASSIGN
%left                   OR
%left                   AND
%left                   XOR
%left                   AND
%left                   EQ NE
%left                   LE LT GE GT
%left                   PLUS MINUS
%left                   DIV MOD
%right                  NOT
%left                   LPAR
%left                   RPAR

%nonassoc               LOWER
%nonassoc               ELSE
%nonassoc               HIGHER


%union{
    //struct node* node;
    char* id;
    char* strlit;
    int intlit;
    float reallit;
};

%%
Program             :          CLASS ID LBRACE RBRACE
                    |          CLASS ID LBRACE ProgramRec RBRACE
                    ;

ProgramRec          :       
                    |          MethodDecl
                    |          FieldDecl
                    |          SEMICOLON   
                    |          ProgramRec MethodDecl
                    |          Program FieldDecl
                    |          Program SEMICOLON
                    ;

                    
MethodDecl          :          PUBLIC STATIC MethodHeader MethodBody
                    ;


FieldDecl           :          PUBLIC STATIC Type ID SEMICOLON
                    |          PUBLIC STATIC Type ID FieldDeclRec SEMICOLON 
                    |          error SEMICOLON
                    ;

FieldDeclRec        :           COMMA ID
                    |           FieldDeclRec COMMA ID
                    ;


Type                :           BOOL
                    |           INT
                    |           DOUBLE
                    ;


MethodHeader        :           Type ID LPAR RPAR
                    |           VOID ID LPAR RPAR
                    |           Type ID LPAR FormalParams RPAR
                    |           VOID ID LPAR FormalParams RPAR
                    ;


FormalParams        :           Type ID
                    |           Type ID FormalParamsRec
                    |           STRLIT LSQ RSQ ID
                    ;

FormalParamsRec     :           COMMA Type ID
                    |           FormalParamsRec COMMA Type ID
                    ;


MethodBody          :           LBRACE RBRACE
                    |           LBRACE MethodBodyRec RBRACE
                    ;

MethodBodyRec       :           Statement
                    |           VarDecl
                    |           MethodBodyRec Statement
                    |           MethodBodyRec VarDecl
                    ;


VarDecl             :           Type ID SEMICOLON
                    |           Type ID VarDeclRec SEMICOLON
                    ;

VarDeclRec          :           COMMA ID
                    |           VarDeclRec COMMA ID

Statement           :           LBRACE Statement RBRACE
                    |           LBRACE RBRACE
                    |           IF LPAR Expr RPAR Statement
                    |           IF LPAR Expr RPAR Statement ELSE Statement
                    |           WHILE LPAR Expr RPAR Statement
                    |           RETURN SEMICOLON
                    |           RETURN Expr SEMICOLON
                    |           SEMICOLON
                    |           MethodInvocation SEMICOLON
                    |           Assignment SEMICOLON
                    |           ParseArgs SEMICOLON
                    |           PRINT LPAR Expr RPAR SEMICOLON
                    |           PRINT LPAR STRLIT RPAR SEMICOLON
                    |           error SEMICOLON
                    ;


MethodInvocation    :           ID LPAR RPAR
                    |           ID LPAR Expr MethodBodyRec RPAR
                    |           ID LPAR Expr RPAR
                    |           ID LPAR error RPAR
                    ;

MethodInvocationRecursive       :      COMMA Expr
                                |      MethodBodyRec COMMA Expr
                                ;


Assignment          :           ID ASSIGN Expr
                    ;


ParseArgs           :           PARSEINT LPAR ID LSQ Expr RSQ RPAR
                    |           PARSEINT LPAR error RPAR
                    ;


Expr                :           Expr PLUS Expr           
                    |           Expr MINUS Expr
                    |           Expr STAR Expr
                    |           Expr DIV Expr 
                    |           Expr MOD Expr
                    |           Expr AND Expr
                    |           Expr OR Expr
                    |           Expr XOR Expr
                    |           Expr LSHIFT Expr
                    |           Expr RSHIFT Expr
                    |           Expr EQ Expr
                    |           Expr GE Expr
                    |           Expr GT Expr
                    |           Expr LE Expr
                    |           Expr LT Expr
                    |           Expr NE Expr
                    |           MINUS Expr
                    |           NOT Expr
                    |           PLUS Expr
                    |           LPAR Expr RPAR
                    |           MethodInvocation | Assignment | ParseArgs
                    |           ID
                    |           ID DOTLENGTH
                    |           INTLIT
                    |           REALLIT
                    |           BOOLLIT
                    |           LPAR error RPAR
                    ;
 %%
