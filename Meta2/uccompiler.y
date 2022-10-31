%{
    /********************************
    ************AUTORES**************
    *********************************
    * Dylan Perdigão   -   2018233092
    * Bruno Faria      -   2018295474
    ********************************/
    #include <stdio.h>
    #include "ASTree.h"
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
%type <node> FunctionsAndDeclarations
%type <node> FunctionDefinition
%type <node> FunctionBody
%type <node> DeclarationsAndStatements
%type <node> FunctionDeclaration
%type <node> FunctionDeclarator
%type <node> ParameterList
%type <node> recursionPL
%type <node> ParameterDeclaration
%type <node> Declaration
%type <node> recursionD
%type <node> TypeSpec
%type <node> Declarator
%type <node> Statement
%type <node> StatementOrError
%type <node> recursionS
%type <node> Expr
%type <node> FuncArgs

%token  <id> ID
%token  <id> INTLIT
%token  <id> CHRLIT
%token  <id> REALLIT    /* %token  <reallit> REALLIT*/
%token  CHAR
%token  ELSE
%token  WHILE
%token  IF
%token  INT
%token  SHORT
%token  DOUBLE
%token  RETURN
%token  VOID
%token  BITWISEAND
%token  BITWISEOR
%token  BITWISEXOR
%token  AND
%token  ASSIGN
%token  MUL
%token  COMMA
%token  DIV
%token  EQ
%token  GE
%token  GT
%token  LBRACE
%token  LE
%token  LPAR
%token  LT
%token  MINUS
%token  MOD
%token  NE
%token  NOT
%token  OR
%token  PLUS
%token  RBRACE
%token  RPAR
%token  SEMI
%token  RESERVED
%token  LINE_COMMENT
%token  SPACE
%token  NEWLINE



%left   COMMA
%right  ASSIGN
%left   OR
%left   AND
%left   BITWISEOR
%left   BITWISEXOR
%left   BITWISEAND
%left   EQ NE
%left   LE LT GE GT
%left   PLUS MINUS
%left   MUL DIV MOD
%right  NOT
%left   LPAR
%left   RPAR

%nonassoc LOWER
%nonassoc ELSE
%nonassoc HIGHER


%union{
    struct node* node;
    char* id;
    char chrlit;
    int intlit;
    float reallit;
};

%%
Program                     :   FunctionsAndDeclarations                                    {$$ = newNode("Program"); $$->child=$1; if (printTree==true && hasError==false){printASTree($$,0);} else{freeASTree($$);}}
                            ;
FunctionsAndDeclarations    :   FunctionDefinition                                          {$$=$1;}
                            |   FunctionDeclaration                                         {$$=$1;}
                            |   Declaration                                                 {$$=$1;}
                            |   FunctionsAndDeclarations FunctionDefinition                 {$$=$1; addBrother($$,$2);}
                            |   FunctionsAndDeclarations FunctionDeclaration                {$$=$1; addBrother($$,$2);}
                            |   FunctionsAndDeclarations Declaration                        {$$=$1; addBrother($$,$2);}
                            ;

FunctionDefinition          :   TypeSpec FunctionDeclarator FunctionBody                    {$$ = newNode("FuncDefinition"); $$->child=$1; addBrother($1,$2); addBrother($2,$3);}
                            ;

FunctionBody                :   LBRACE DeclarationsAndStatements RBRACE                     {$$ = newNode("FuncBody"); $$->child=$2;}
                            |   LBRACE RBRACE                                               {$$ = newNode("FuncBody");}
                            ;

DeclarationsAndStatements   :   Statement                                                   {$$=$1;}
                            |   Declaration                                                 {$$=$1;}
                            |   Statement DeclarationsAndStatements                         {if($1) {$$=$1; addBrother($$,$2);} else{$$=$2;}}
                            |   Declaration DeclarationsAndStatements                       {$$=$1; addBrother($$,$2);}

                            ;

FunctionDeclaration         :   TypeSpec FunctionDeclarator SEMI                            {$$ = newNode("FuncDeclaration"); $$->child=$1; addBrother($1,$2);}
                            ;

FunctionDeclarator          :   ID LPAR ParameterList RPAR                                  {sprintf(temp, "Id(%s)", $1); $$ = newNode(strdup(temp)); addBrother($$,$3);}
                            ;

ParameterList               :   ParameterDeclaration                                        {$$ = newNode("ParamList"); $$->child=$1;}
                            |   ParameterDeclaration recursionPL                            {$$ = newNode("ParamList"); $$->child=$1; addBrother($1,$2);}
                            ;

recursionPL                 :   COMMA ParameterDeclaration                                  {$$=$2;}
                            |   recursionPL COMMA ParameterDeclaration                      {$$=$1; addBrother($1,$3);}
                            ;

ParameterDeclaration        :   TypeSpec ID                                                 {$$ = newNode("ParamDeclaration"); $$->child=$1;sprintf(temp, "Id(%s)", $2);addBrother($1,newNode(strdup(temp)));}
                            |   TypeSpec                                                    {$$ = newNode("ParamDeclaration"); $$->child=$1;}
                            ;

Declaration                 :   TypeSpec Declarator recursionD SEMI                         {$$=newNode("Declaration"); $$->child=$1; addBrother($1,$2); addBrother($$,$3);
                                                                                                Node *tempNode, *currentNode = $3;
                                                                                                char *type = $1->message;
                                                                                                while(currentNode){
                                                                                                    tempNode=currentNode->child;
                                                                                                    currentNode->child=newNode(type);
                                                                                                    currentNode->child->brother=tempNode;
                                                                                                    currentNode=currentNode->brother;
                                                                                                }

                                                                                            }
                            |   TypeSpec Declarator SEMI                                    {$$=newNode("Declaration"); $$->child=$1; addBrother($1,$2);}
                            |   error SEMI                                                  {$$=newNode(NULL); hasError=true;}
                            ;

recursionD                  :   COMMA Declarator                                            {$$=newNode("Declaration");$$->child=$2;}
                            |   recursionD COMMA Declarator                                 {$$=$1; Node* tempNode=newNode("Declaration");tempNode->child=$3; addBrother($$,tempNode);}
                            ;

TypeSpec                    :   CHAR                                                        {$$ = newNode("Char");}
                            |   INT                                                         {$$ = newNode("Int");}
                            |   VOID                                                        {$$ = newNode("Void");}
                            |   SHORT                                                       {$$ = newNode("Short");}
                            |   DOUBLE                                                      {$$ = newNode("Double");}
                            ;

Declarator                  :   ID ASSIGN Expr                                              {sprintf(temp, "Id(%s)", $1);$$ = newNode(strdup(temp)); addBrother($$,$3);}
                            |   ID                                                          {sprintf(temp, "Id(%s)", $1);$$ = newNode(strdup(temp));}
                            ;

Statement                   :   Expr SEMI                                                   {$$=$1;}
                            |   SEMI                                                        {$$=NULL;}
                            |   LBRACE RBRACE                                               {$$=NULL;}
                            |   LBRACE recursionS RBRACE                                    {if($2 && $2->brother){$$=newNode("StatList"); $$->child=$2;} else{$$=$2;}}
                            |   IF LPAR Expr RPAR StatementOrError      %prec LOWER         {$$ = newNode("If"); $$->child=$3; if(!$5){$5=newNode("Null");} addBrother($3,$5); addBrother($5,newNode("Null"));}
                            |   IF LPAR Expr RPAR StatementOrError ELSE StatementOrError    {$$ = newNode("If"); $$->child=$3; if(!$5){$5=newNode("Null");} if(!$7){$7=newNode("Null");} addBrother($3,$5);addBrother($5,$7);}
                            |   WHILE LPAR Expr RPAR StatementOrError                       {$$ = newNode("While"); $$->child=$3; if(!$5){$5=newNode("Null");} addBrother($3,$5);}
                            |   RETURN Expr SEMI                                            {$$ = newNode("Return"); $$->child=$2;}
                            |   RETURN SEMI                                                 {$$ = newNode("Return"); $$->child=newNode("Null");}
                            |   LBRACE error RBRACE                                         {$$=newNode(NULL); hasError=true;}
                            ;

StatementOrError            :   Statement                                                   {$$=$1;}
                            |   error SEMI                                                  {$$=newNode(NULL); hasError=true;}
                            ;

recursionS                  :   StatementOrError                                            {$$=$1;}
                            |   recursionS StatementOrError                                 {if($1){$$=$1; addBrother($1,$2);} else{$$=$2;}}
                            ;

Expr                        :   Expr ASSIGN Expr                                            {$$ = newNode("Store"); $$->child=$1; addBrother($1,$3);}
                            |   Expr COMMA Expr                                             {$$ = newNode("Comma"); $$->child=$1; addBrother($1,$3);}
                            |   Expr PLUS Expr                                              {$$ = newNode("Add"); $$->child=$1; addBrother($1,$3);}
                            |   Expr MINUS Expr                                             {$$ = newNode("Sub"); $$->child=$1; addBrother($1,$3);}
                            |   Expr MUL Expr                                               {$$ = newNode("Mul"); $$->child=$1; addBrother($1,$3);}
                            |   Expr DIV Expr                                               {$$ = newNode("Div"); $$->child=$1; addBrother($1,$3);}
                            |   Expr MOD Expr                                               {$$ = newNode("Mod"); $$->child=$1; addBrother($1,$3);}
                            |   Expr OR Expr                                                {$$ = newNode("Or"); $$->child=$1; addBrother($1,$3);}
                            |   Expr AND Expr                                               {$$ = newNode("And"); $$->child=$1; addBrother($1,$3);}
                            |   Expr BITWISEAND Expr                                        {$$ = newNode("BitWiseAnd"); $$->child=$1; addBrother($1,$3);}
                            |   Expr BITWISEOR Expr                                         {$$ = newNode("BitWiseOr"); $$->child=$1; addBrother($1,$3);}
                            |   Expr BITWISEXOR Expr                                        {$$ = newNode("BitWiseXor"); $$->child=$1; addBrother($1,$3);}
                            |   Expr EQ Expr                                                {$$ = newNode("Eq"); $$->child=$1; addBrother($1,$3);}
                            |   Expr NE Expr                                                {$$ = newNode("Ne"); $$->child=$1; addBrother($1,$3);}
                            |   Expr LE Expr                                                {$$ = newNode("Le"); $$->child=$1; addBrother($1,$3);}
                            |   Expr GE Expr                                                {$$ = newNode("Ge"); $$->child=$1; addBrother($1,$3);}
                            |   Expr LT Expr                                                {$$ = newNode("Lt"); $$->child=$1; addBrother($1,$3);}
                            |   Expr GT Expr                                                {$$ = newNode("Gt"); $$->child=$1; addBrother($1,$3);}
                            |   PLUS Expr                               %prec NOT           {$$ = newNode("Plus"); $$->child=$2;}
                            |   MINUS Expr                              %prec NOT           {$$ = newNode("Minus"); $$->child=$2;}
                            |   NOT Expr                                                    {$$ = newNode("Not"); $$->child=$2;}
                            |   ID LPAR FuncArgs RPAR                                       {$$ = newNode("Call"); sprintf(temp, "Id(%s)", $1); $$->child = newNode(strdup(temp)); addBrother($$->child,$3);}
                            |   ID LPAR RPAR                                                {$$ = newNode("Call"); sprintf(temp, "Id(%s)", $1); $$->child = newNode(strdup(temp));}
                            |   ID                                                          {sprintf(temp, "Id(%s)", $1);$$ = newNode(strdup(temp));}
                            |   INTLIT                                                      {sprintf(temp, "IntLit(%s)", $1);$$ = newNode(strdup(temp));}
                            |   CHRLIT                                                      {sprintf(temp, "ChrLit(%s)", $1);$$ = newNode(strdup(temp));}
                            |   REALLIT                                                     {sprintf(temp, "RealLit(%s)", $1);$$ = newNode(strdup(temp));}
                            |   LPAR Expr RPAR                                              {$$ = $2;}
                            |   ID LPAR error RPAR                                          {$$=newNode(NULL); hasError=true;}
                            |   LPAR error RPAR                                             {$$=newNode(NULL); hasError=true;}
                            ;

FuncArgs                    :   Expr                                    %prec LOWER                                  {$$ = $1;}
                            |   FuncArgs COMMA Expr                     %prec HIGHER                                      {$$ = $1; addBrother($$, $3);}

%%
