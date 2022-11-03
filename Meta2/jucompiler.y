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
Program             :          CLASS ID LBRACE RBRACE                                           {$$ = novoNo("Program"); $$->filho=$2; sprintf(id, "Id(%s)", $2); $2 = novoNo(strdup(id));}
                    |          CLASS ID LBRACE ProgramRec RBRACE                                {$$ = novoNo("Program"); $$->filho=$2; sprintf(id, "Id(%s)", $2); $2 = novoNo(strdup(id)); novoIrmao($2,$4);}
                    ;

ProgramRec          :       
                    |          MethodDecl                                                       {$$ = $1;}
                    |          FieldDecl                                                        {$$ = $1;}
                    |          SEMICOLON                                                        {$$ = NULL;}
                    |          ProgramRec MethodDecl                                            {$$ = $1; novoIrmao($$,$2);}
                    |          ProgramRec FieldDecl                                             {$$ = $1; novoIrmao($$,$2);}
                    |          ProgramRec SEMICOLON                                             {$$ = $1;}
                    ;

                    
MethodDecl          :          PUBLIC STATIC MethodHeader MethodBody                            {$$ = novoNo("MethodDecl"); $$->filho=$3; novoIrmao($3,$4);}
                    ;


FieldDecl           :          PUBLIC STATIC Type ID SEMICOLON                                  {$$ = novoNo("FieldDecl"); $$->filho=$3; sprintf(id, "Id(%s)", $4); novoIrmao($3,novoNo(strdup(id)));}
                    |          PUBLIC STATIC Type ID FieldDeclRec SEMICOLON                     {$$ = novoNo("FieldDecl"); $$->filho=$3; sprintf(id, "Id(%s)", $4); novo * ID = novoNo(strdup(id)); novoIrmao($3,ID); novoIrmao(ID,$5);}
                    |          error SEMICOLON                                                  {$$ = novoNo(NULL);}
                    ;

FieldDeclRec        :           COMMA ID                                                        {sprintf(id, "Id(%s)", $2); novoIrmao($$,novoNo(strdup(id)));}
                    |           FieldDeclRec COMMA ID                                           {$$ = $1; sprintf(id, "Id(%s)", $3); novoIrmao($$,novoNo(strdup(id)));}
                    ;


Type                :           BOOL                                                            {$$ = novoNo("Bool");}
                    |           INT                                                             {$$ = novoNo("Int");}
                    |           DOUBLE                                                          {$$ = novoNo("Double");}
                    ;


MethodHeader        :           Type ID LPAR RPAR                                               {$$ = novoNo("MethodHeader"); $$->filho=$1; sprintf(id, "Id(%s)", $2); novoIrmao($1,novoNo(strdup(id)));}
                    |           VOID ID LPAR RPAR                                               {$$ = novoNo("MethodHeader"); no * Void = novoNo("Void") ;$$->filho=Void; sprintf(id, "Id(%s)", $2); novoIrmao(Void,novoNo(strdup(id)));}
                    |           Type ID LPAR FormalParams RPAR                                  {$$ = novoNo("MethodHeader"); $$->filho=$1; sprintf(id, "Id(%s)", $2); novo * ID = novoNo(strdup(id)); novoIrmao($1,ID); novoIrmao(ID,$4);}
                    |           VOID ID LPAR FormalParams RPAR                                  {$$ = novoNo("MethodHeader"); no * Void = novoNo("Void"); $$->filho=Void; sprintf(id, "Id(%s)", $2); no * ID = novoNo(strdup(id)); novoIrmao(Void,ID); novoIrmao(ID, $4);}
                    ;


FormalParams        :           Type ID                                                         {$$ = novoNo("MethodParams"); $$->filho=$1; sprintf(id, "Id(%s)", $2); novoIrmao($1,novoNo(strdup(id)));}
                    |           Type ID FormalParamsRec                                         {$$ = novoNo("MethodParams"); $$->filho=$1; sprintf(id, "Id(%s)", $2); novo * ID = novoNo(strdup(id); novoIrmao($1,ID)); novoIrmao(ID,$3);}
                    |           STRLIT LSQ RSQ ID                                               {$$ = novoNo("MethodParams"); $$->filho=$1; sprintf(id, "Id(%s)", $4); $1 = novoNo("StringArray"); novoIrmao($1,novoNo(strdup(id)));}
                    ;

FormalParamsRec     :           COMMA Type ID                                                   {$$ = $2; sprintf(id, "Id(%s)", $3); novoIrmao($$,novoNo(strdup(id)));}
                    |           FormalParamsRec COMMA Type ID                                   {$$ = $1; novoIrmao($1,$3); printf(id, "Id(%s)", $4); novo * ID = novoNo(strdup(id)); novoIrmao($3,ID);}
                    ;


MethodBody          :           LBRACE RBRACE                                                   {$$ = NULL;}
                    |           LBRACE MethodBodyRec RBRACE                                     {$$ = $2;}
                    ;

MethodBodyRec       :           Statement                                                       {$$=$1;}
                    |           VarDecl                                                         {$$=$1;}
                    |           MethodBodyRec Statement                                         {$$=$1; novoIrmao($$,$2);}
                    |           MethodBodyRec VarDecl                                           {$$=$1; novoIrmao($$,$2);}
                    ;


VarDecl             :           Type ID SEMICOLON                                               {$$ = novoNo("VarDecl"); $$->filho = $1; sprintf(id, "Id(%s)", $2); novoIrmao($1,novoNo(strdup(id)));}                               
                    |           Type ID VarDeclRec SEMICOLON                                    {$$ = novoNo("VarDecl"); $$->filho = $1; sprintf(id, "Id(%s)", $2); novo * ID = novoNo(id); novoIrmao($1,ID)); novoIrmao(ID,$3);}
                    ;

VarDeclRec          :           COMMA ID                                                        {$$ = NULL;}
                    |           VarDeclRec COMMA ID                                             {$$ = $1; sprintf(id, "Id(%s)", $3); novoIrmao($$,novoNo(strdup(id))); }

Statement           :           LBRACE Statement RBRACE                                         {$$ = $2;}
                    |           LBRACE RBRACE                                                   {$$ = NULL;}
                    |           IF LPAR Expr RPAR Statement                                     {$$ = novoNo("If"); $$->filho = $3; novoIrmao($3,$5); }
                    |           IF LPAR Expr RPAR Statement ELSE Statement                      {$$ = novoNo("If"); $$->filho = $3; novoIrmao($3,$5); novoIrmao($5,$7); }
                    |           WHILE LPAR Expr RPAR Statement                                  {$$ = novoNo("While"); $$->filho = $3; novoIrmao($3,$5); }
                    |           RETURN SEMICOLON                                                {$$ = novoNo("Return");}
                    |           RETURN Expr SEMICOLON                                           {$$ = novoNo("Return"); $$->filho = $2;}
                    |           SEMICOLON                                                       {$$ = NULL;}
                    |           MethodInvocation SEMICOLON                                      {$$ = $1;}
                    |           Assignment SEMICOLON                                            {$$ = $1;}
                    |           ParseArgs SEMICOLON                                             {$$ = $1;}
                    |           PRINT LPAR Expr RPAR SEMICOLON                                  {$$ = novoNo("Print"); $$->filho = $3;}
                    |           PRINT LPAR STRLIT RPAR SEMICOLON                                {$$ = novoNo("Print"); $$->filho = $3; sprintf(strlit, "Strlit(%s)", $3); $3 = novoNo(strdup(strlit));}
                    |           error SEMICOLON                                                 {$$ = NULL;}
                    ;


MethodInvocation    :           ID LPAR RPAR                                                    {$$ = novoNo("MethodInvocation"); $$->filho=$1; sprintf(id, "Id(%s)", $1); $1 = novoNo(id);}
                    |           ID LPAR Expr MethodInvocationRec RPAR                           {$$ = novoNo("MethodInvocation"); $$->filho=$1; sprintf(id, "Id(%s)", $1);  novo * ID = novoNo(id); novoIrmao(ID,$3); novoIrmao($3,$4);}
                    |           ID LPAR Expr RPAR                                               {$$ = novoNo("MethodInvocation"); $$->filho=$1; sprintf(id, "Id(%s)", $1); novoIrmao(novoNo(id),$3);}
                    |           ID LPAR error RPAR                                              {$$ = novoNo(NULL); $$->filho=$1; sprintf(id, "Id(%s)", $1); novoNo(id);} //FIX
                    ;

MethodInvocationRec             :      COMMA Expr                                               {novoIrmao($$,$2);}
                                |      MethodInvocationRec COMMA Expr                           {novoIrmao($$,$1); novoIrmao($1,$3);}
                                ;


Assignment          :           ID ASSIGN Expr                                                  {$$=novoNo("Assign"); $$->filho=$1; sprintf(id, "Id(%s)", $1); $1 = novoNo(id); novoIrmao($1,$3);}
                    ;


ParseArgs           :           PARSEINT LPAR ID LSQ Expr RSQ RPAR                              {$$ = novoNo("ParseArgs"); $$->filho=$3; sprintf(id, "Id(%s)", $3); $3 = novoNo(id); novoIrmao($3,$5);}
                    |           PARSEINT LPAR error RPAR                                        {$$=novoNo(NULL);}
                    ;


Expr                :           Expr PLUS Expr                                                  {$$ = novoNo("PLUS"); $$->filho=$1; novoIrmao($1,$3);}
                    |           Expr MINUS Expr                                                 {$$ = novoNo("MINUS"); $$->filho=$1; novoIrmao($1,$3);}
                    |           Expr STAR Expr                                                  {$$ = novoNo("STAR"); $$->filho=$1; novoIrmao($1,$3);}
                    |           Expr DIV Expr                                                   {$$ = novoNo("DIV"); $$->filho=$1; novoIrmao($1,$3);}
                    |           Expr MOD Expr                                                   {$$ = novoNo("MOD"); $$->filho=$1; novoIrmao($1,$3);}
                    |           Expr AND Expr                                                   {$$ = novoNo("AND"); $$->filho=$1; novoIrmao($1,$3);}
                    |           Expr OR Expr                                                    {$$ = novoNo("OR"); $$->filho=$1; novoIrmao($1,$3);}
                    |           Expr XOR Expr                                                   {$$ = novoNo("XOR"); $$->filho=$1; novoIrmao($1,$3);}
                    |           Expr LSHIFT Expr                                                {$$ = novoNo("LSHIFT"); $$->filho=$1; novoIrmao($1,$3);}
                    |           Expr RSHIFT Expr                                                {$$ = novoNo("RSHIFT"); $$->filho=$1; novoIrmao($1,$3);}
                    |           Expr EQ Expr                                                    {$$ = novoNo("EQ"); $$->filho=$1; novoIrmao($1,$3);}
                    |           Expr GE Expr                                                    {$$ = novoNo("GE"); $$->filho=$1; novoIrmao($1,$3);}
                    |           Expr GT Expr                                                    {$$ = novoNo("GT"); $$->filho=$1; novoIrmao($1,$3);}
                    |           Expr LE Expr                                                    {$$ = novoNo("LE"); $$->filho=$1; novoIrmao($1,$3);}
                    |           Expr LT Expr                                                    {$$ = novoNo("LT"); $$->filho=$1; novoIrmao($1,$3);}
                    |           Expr NE Expr                                                    {$$ = novoNo("NE"); $$->filho=$1; novoIrmao($1,$3);}
                    |           MINUS Expr                                                      {$$ = novoNo("MINUS"); $$->filho=$2;}
                    |           NOT Expr                                                        {$$ = novoNo("NOT"); $$->filho=$2;} 
                    |           PLUS Expr                                                       {$$ = novoNo("PLUS"); $$->filho=$2;}
                    |           LPAR Expr RPAR                                                  {$$ = $2;}
                    |           MethodInvocation                                                {$$ = $1;}
                    |           Assignment                                                      {$$ = $1;}
                    |           ParseArgs                                                       {$$ = $1;}
                    |           ID                                                              {sprintf(temp, "Id(%s)", $1); $$ = novoNo(strdup(temp));}
                    |           ID DOTLENGTH                                                    {$$ = novoNo("Call"); sprintf(temp, "Id(%s)", $1); $$->filho = novoNo(strdup(temp));}
                    |           INTLIT                                                          {sprintf(temp, "Intllit(%s)", $1); $$ = novoNo(strdup(temp));}
                    |           REALLIT                                                         {sprintf(temp, "Reallit(%s)", $1); $$ = novoNo(strdup(temp));}
                    |           BOOLLIT                                                         {sprintf(temp, "Boollit(%s)", $1); $1 = novoNo(strdup(temp));}
                    |           LPAR error RPAR                                                 {$$=novoNo(NULL);}
                    ;
 %%
