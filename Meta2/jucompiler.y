%{
    /************Autores*************
    * Pedro Ascensão   -   2020233012
    * Leonardo Pina    -   2019234318
    *********************************/
    #include <stdio.h>
    #include "Tree.h"
    #define true 1
    #define false 0
    int yylex(void);
    void yyerror (const char *s);

    char* yytext;
    int printTree;
    int hasError;
    char temp[256];
%}

%union{
    struct no* no;
    char* id;
    char* strlit;
    int intlit;
    float reallit;
};


%type <no> Program
%type <no> ProgramRec
%type <no> MethodDecl
%type <no> FieldDeclRec
%type <no> FieldDecl
%type <no> Type
%type <no> MethodHeader
%type <no> FormalParamsRec
%type <no> FormalParams
%type <no> MethodBody
%type <no> MethodBodyRec
%type <no> VarDecl
%type <no> VarDeclRec
%type <no> Statement
%type <no> MethodInvocation
%type <no> MethodInvocationRec
%type <no> Assignment
%type <no> Expr
%type <no> ParseArgs


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

%%
Program             :          CLASS ID LBRACE RBRACE                                           {}
                    |          CLASS ID LBRACE ProgramRec RBRACE                                {$$ = novoNo("Program")}
                    ;

ProgramRec          :       
                    |          MethodDecl                                                       {$$ = $1;}
                    |          FieldDecl                                                        {$$ = $1;}
                    |          SEMICOLON                                                        {$$ = NULL;}
                    |          ProgramRec MethodDecl                                            {$$ = $1;}
                    |          ProgramRec FieldDecl                                             {$$ = $1;}
                    |          ProgramRec SEMICOLON                                             {$$ = $1;}
                    ;

                    
MethodDecl          :          PUBLIC STATIC MethodHeader MethodBody     {$$ = $;}
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
                    |           ID LPAR Expr MethodInvocationRec RPAR
                    |           ID LPAR Expr RPAR
                    |           ID LPAR error RPAR
                    ;

MethodInvocationRec             :      COMMA Expr
                                |      MethodInvocationRec COMMA Expr
                                ;


Assignment          :           ID ASSIGN Expr
                    ;


ParseArgs           :           PARSEINT LPAR ID LSQ Expr RSQ RPAR                              {$$=novoNo(NULL);}
                    |           PARSEINT LPAR error RPAR                                        {$$=novoNo(NULL);}
                    ;


Expr                :           Expr PLUS Expr                                                  {$$ = novoNo("PLUS"); $$->child=$1; novoIrmao($1,$3);}
                    |           Expr MINUS Expr                                                 {$$ = novoNo("MINUS"); $$->child=$1; novoIrmao($1,$3);}
                    |           Expr STAR Expr                                                  {$$ = novoNo("STAR"); $$->child=$1; novoIrmao($1,$3);}
                    |           Expr DIV Expr                                                   {$$ = novoNo("DIV"); $$->child=$1; novoIrmao($1,$3);}
                    |           Expr MOD Expr                                                   {$$ = novoNo("MOD"); $$->child=$1; novoIrmao($1,$3);}
                    |           Expr AND Expr                                                   {$$ = novoNo("AND"); $$->child=$1; novoIrmao($1,$3);}
                    |           Expr OR Expr                                                    {$$ = novoNo("OR"); $$->child=$1; novoIrmao($1,$3);}
                    |           Expr XOR Expr                                                   {$$ = novoNo("XOR"); $$->child=$1; novoIrmao($1,$3);}
                    |           Expr LSHIFT Expr                                                {$$ = novoNo("LSHIFT"); $$->child=$1; novoIrmao($1,$3);}
                    |           Expr RSHIFT Expr                                                {$$ = novoNo("RSHIFT"); $$->child=$1; novoIrmao($1,$3);}
                    |           Expr EQ Expr                                                    {$$ = novoNo("EQ"); $$->child=$1; novoIrmao($1,$3);}
                    |           Expr GE Expr                                                    {$$ = novoNo("GE"); $$->child=$1; novoIrmao($1,$3);}
                    |           Expr GT Expr                                                    {$$ = novoNo("GT"); $$->child=$1; novoIrmao($1,$3);}
                    |           Expr LE Expr                                                    {$$ = novoNo("LE"); $$->child=$1; novoIrmao($1,$3);}
                    |           Expr LT Expr                                                    {$$ = novoNo("LT"); $$->child=$1; novoIrmao($1,$3);}
                    |           Expr NE Expr                                                    {$$ = novoNo("NE"); $$->child=$1; novoIrmao($1,$3);}
                    |           MINUS Expr                                                      {$$ = novoNo("MINUS"); $$->child=$2;}
                    |           NOT Expr                                                        {$$ = novoNo("NOT"); $$->child=$2;} 
                    |           PLUS Expr                                                       {$$ = novoNo("PLUS"); $$->child=$2;}
                    |           LPAR Expr RPAR                                                  
                    |           MethodInvocation | Assignment | ParseArgs
                    |           ID                                                              {sprintf(temp, "Id(%s)", $1); $$ = novoNo(strdup(temp));}
                    |           ID DOTLENGTH                                                    {$$ = novoNo("Call"); sprintf(temp, "Id(%s)", $1); $$->child = novoNo(strdup(temp));}
                    |           INTLIT                                                          {sprintf(temp, "Intllit(%s)", $1); $$ = novoNo(strdup(temp));}
                    |           REALLIT                                                         {sprintf(temp, "Reallit(%s)", $1); $$ = novoNo(strdup(temp));}
                    |           BOOLLIT                                                         {sprintf(temp,"Boollit(%s)", $1);$$ = novoNo(strdup(temp));}
                    |           LPAR error RPAR                                                 {$$=novoNo(NULL);}
                    ;
 %%
