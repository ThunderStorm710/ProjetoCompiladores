%{
/************Autores*************
* Pedro Ascensão   -   2020233012
* Leonardo Pina    -   2019234318
*********************************/
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "Tree.h"

    #define true 1
    #define false 0

    int yylex(void);
    void yyerror (const char *s);

    char* yytext;
    int printTree;
    int hasError;
    char temp[256];

    node *head = NULL;
    node *auxNode = NULL;
    node *auxNode2 = NULL;
    node *auxNode3 = NULL;
%}

%union{
    struct token* value;
    struct node* node;
    char* id;
    char* strlit;
    int intlit;
    float reallit;
};

%token <value>  COMMA MINUS RSHIFT LSHIFT LT LSQ LPAR LE LBRACE GT GE DIV STAR EQ ASSIGN AND SEMICOLON RSQ RPAR RBRACE PLUS OR NOT NE MOD XOR ARROW BOOL 
                INT IF ELSE DOUBLE DOTLENGTH PRINT WHILE VOID STATIC RETURN PUBLIC PARSEINT CLASS BOOLLIT STRLIT ID INTLIT REALLIT


%nonassoc       IFX
%nonassoc       ELSE


%left           COMMA
%right          ASSIGN
%left           OR
%left           AND
%left           XOR
%left           EQ NE
%left           LT GT LE GE
%left           LSHIFT RSHIFT
%left           PLUS MINUS
%left           STAR DIV MOD
%right          NOT
%left           LPAR
%left           RPAR

%type  <node>   Program ProgramRec MethodDecl FieldDeclRec FieldDecl Type MethodHeader FormalParamsRec FormalParams MethodBody MethodBodyRec VarDecl 
                VarDeclRec Statement MethodInvocation MethodInvocationRec Assignment Expr Expr2 ParseArgs StatementRec

%%
Program                 :   CLASS ID LBRACE ProgramRec RBRACE               {head = createNode("Program", NULL, 0, 0);
                                                                            auxNode = createNode("Id", $2->value, $2->line, $2->coluna);
                                                                            insertChildren(head, auxNode);
                                                                            insertBrother(auxNode, $4);
                                                                            freeToken($2);}

ProgramRec              :                                                   {$$ = createNode("NULL", NULL, 0, 0);}
                        |   ProgramRec MethodDecl                           {$$ = $1; insertBrother($1, $2);}
                        |   ProgramRec FieldDecl                            {$$ = $1; insertBrother($1, $2);}
                        |   ProgramRec SEMICOLON                            {$$ = $1;}
                        ;

                    
MethodDecl              :   PUBLIC STATIC MethodHeader MethodBody           {$$ = createNode("MethodDecl", NULL, 0, 0);
                                                                            insertChildren($$, $3);
                                                                            insertBrother($3, $4);}
                        ;

FieldDecl               :   PUBLIC STATIC Type ID FieldDeclRec SEMICOLON    {$$ = createNode("FieldDecl", NULL, 0, 0);
                                                                            insertChildren($$, $3);
                                                                            auxNode = createNode("Id", $4->value, $4->line, $4->coluna);
                                                                            insertBrother($3, auxNode);
                                                                            atributeType($3, $5);
                                                                            insertBrother($$, $5);
                                                                            freeToken($4);}
                        |   error SEMICOLON                                 {$$ = createNode("Error", NULL, 0, 0);}
                        ;

FieldDeclRec            :                                                   {$$ = createNode("NULL", NULL, 0, 0);}
                        |   FieldDeclRec COMMA ID                           {$$ = createNode("FieldDecl", NULL, 0, 0);
                                                                            insertBrother($1, $$);
                                                                            auxNode = createNode("Id", $3->value, $3->line, $3->coluna);
                                                                            insertChildren($$, auxNode);
                                                                            $$ = $1; 
                                                                            freeToken($3);}
                        ;


Type                    :   BOOL                                            {$$ = createNode("Bool", NULL, 0, 0);}
                        |   INT                                             {$$ = createNode("Int", NULL, 0, 0);}
                        |   DOUBLE                                          {$$ = createNode("Double", NULL, 0, 0);}
                        ;


MethodHeader            :   Type ID LPAR RPAR                               {$$ = createNode("MethodHeader", NULL, 0, 0);
                                                                            insertChildren($$, $1);
                                                                            auxNode = createNode("Id", $2->value, $2->line, $2->coluna);
                                                                            insertBrother($1, auxNode);
                                                                            insertBrother(auxNode, createNode("MethodParams", NULL, 0, 0));
                                                                            freeToken($2);}

                        |   VOID ID LPAR RPAR                               {$$ = createNode("MethodHeader", NULL, 0, 0);
                                                                            auxNode = createNode("Void", NULL, $1->line, $1->coluna);
                                                                            insertChildren($$, auxNode);
                                                                            auxNode2 = createNode("Id", $2->value, $2->line, $2->coluna);
                                                                            insertBrother(auxNode, auxNode2);
                                                                            insertBrother(auxNode2, createNode("MethodParams", NULL, 0, 0));
                                                                            freeToken($1);
                                                                            freeToken($2);}

                        |   Type ID LPAR FormalParams RPAR                  {$$ = createNode("MethodHeader", NULL, 0, 0);
                                                                            insertChildren($$, $1);
                                                                            auxNode = createNode("Id", $2->value, $2->line, $2->coluna);
                                                                            insertBrother($1, auxNode);
                                                                            insertBrother(auxNode, $4);
                                                                            freeToken($2);}

                        |   VOID ID LPAR FormalParams RPAR                  {$$ = createNode("MethodHeader", NULL, 0, 0);
                                                                            auxNode = createNode("Void", NULL, $1->line, $1->coluna);
                                                                            insertChildren($$, auxNode);
                                                                            auxNode2 = createNode("Id", $2->value, $2->line, $2->coluna);
                                                                            insertBrother(auxNode, auxNode2);
                                                                            insertBrother(auxNode2, $4);
                                                                            freeToken($1);
                                                                            freeToken($2);}
                        ;


FormalParams            :   Type ID FormalParamsRec                         {$$ = createNode("MethodParams", NULL, 0, 0);
                                                                            auxNode = createNode("ParamDecl", NULL, 0, 0);
                                                                            insertChildren($$, auxNode);
                                                                            auxNode2 = createNode("Id", $2->value, $2->line, $2->coluna);
                                                                            insertBrother($1, auxNode2);
                                                                            insertChildren(auxNode, $1);
                                                                            insertBrother(auxNode, $3);
                                                                            freeToken($2);}

                        |   STRLIT LSQ RSQ ID                               {$$ = createNode("MethodParams", NULL, 0, 0);
                                                                            auxNode = createNode("ParamDecl", NULL, 0, 0);
                                                                            insertChildren($$, auxNode);
                                                                            auxNode2 = createNode("StringArray", NULL, $1->line, $1->coluna);
                                                                            insertChildren(auxNode, auxNode2);
                                                                            auxNode3 = createNode("Id", $4->value, $4->line, $4->coluna);
                                                                            insertBrother(auxNode2, auxNode3);
                                                                            freeToken($1);
                                                                            freeToken($4);}
                        ;

FormalParamsRec         :                                                   {$$ = createNode("NULL", NULL, 0, 0);}
                        |   FormalParamsRec COMMA Type ID                   {$$ = createNode("ParamDecl", NULL, 0, 0);
                                                                            auxNode = createNode("Id", $4->value, $4->line, $4->coluna);
                                                                            insertChildren($$, $3);
                                                                            insertBrother($3, auxNode);
                                                                            insertBrother($1, $$);
                                                                            $$ = $1;
                                                                            freeToken($4);}
                        ;


MethodBody              :   LBRACE MethodBodyRec RBRACE                     {$$ = createNode("MethodBody", NULL, 0, 0);
                                                                            insertChildren($$, $2);}
                        ;

MethodBodyRec           :                                                   {$$ = createNode("NULL", NULL, 0, 0);}
                        |   MethodBodyRec Statement                         {$$ = $1; insertBrother($1, $2);}
                        |   MethodBodyRec VarDecl                           {$$ = $1; insertBrother($1, $2);}
                        ;


VarDecl                 :   Type ID VarDeclRec SEMICOLON                    {$$ = createNode("VarDecl", NULL, 0, 0);
                                                                            insertChildren($$, $1);
                                                                            auxNode = createNode("Id", $2->value, $2->line, $2->coluna);
                                                                            insertBrother($1, auxNode);
                                                                            atributeType($1, $3);
                                                                            insertBrother($$, $3);
                                                                            freeToken($2);}

VarDeclRec              :                                                   {$$ = createNode("NULL", NULL, 0, 0);}
                        |   VarDeclRec COMMA ID                             {$$ = createNode("VarDecl", NULL, 0, 0);
                                                                            auxNode = createNode("Id", $3->value, $3->line, $3->coluna);
                                                                            insertChildren($$, auxNode);
                                                                            insertBrother($1, $$);
                                                                            $$ = $1;
                                                                            freeToken($3);}
                        ;

Statement               :   LBRACE StatementRec RBRACE                      {if(addBlock($2)>2){$$ = createNode("Block", NULL, 0, 0); insertChildren($$, $2);}
                                                                            else if(addBlock($2)==0){$$ = NULL; clearAST($2);}
                                                                            else{$$ = $2;}}

                        |   IF LPAR Expr RPAR Statement %prec IFX           {$$ = createNode("If",NULL, $1->line, $1->coluna); 
                                                                            if($5 == NULL){auxNode=createNode("Block",NULL, 0, 0); insertBrother($3, auxNode);}
                                                                            else{insertBrother($3,$5);} insertBrother($3, createNode("Block",NULL, 0, 0)); insertChildren($$,$3);
                                                                            freeToken($1);}

                        |   IF LPAR Expr RPAR Statement ELSE Statement      {$$ = createNode("If", NULL, $1->line, $1->coluna); 
                                                                            if($5 == NULL){auxNode=createNode("Block", NULL, 0, 0); insertBrother($3, auxNode);}
                                                                            else{insertBrother($3, $5);}
                                                                            if($7 == NULL){auxNode = createNode("Block", NULL, 0, 0); insertBrother($3, auxNode);}
                                                                            else{insertBrother($3, $7);} insertChildren($$,$3);
                                                                            freeToken($1);}

                        |   WHILE LPAR Expr RPAR Statement                  {$$ = createNode("While",NULL, $1->line, $1->coluna);
                                                                            if($5 == NULL){auxNode=createNode("Block",NULL, 0, 0); insertBrother($3, auxNode);}
                                                                            else{insertBrother($3,$5);}
                                                                            insertChildren($$,$3);
                                                                            freeToken($1);}

                        |   RETURN SEMICOLON                                {$$ = createNode("Return", NULL, $1->line, $1->coluna);
                                                                            freeToken($1);}

                        |   RETURN Expr SEMICOLON                           {$$ = createNode("Return", NULL, $1->line, $1->coluna);
                                                                            insertChildren($$, $2);
                                                                            freeToken($1);}

                        |   SEMICOLON                                       {$$ = NULL;}

                        |   MethodInvocation SEMICOLON                      {$$ = $1;}

                        |   Assignment SEMICOLON                            {$$ = $1;}

                        |   ParseArgs SEMICOLON                             {$$ = $1;}

                        |   PRINT LPAR Expr RPAR SEMICOLON                  {$$ = createNode("Print", NULL, $1->line, $1->coluna);
                                                                            insertChildren($$, $3);
                                                                            freeToken($1);}

                        |   PRINT LPAR STRLIT RPAR SEMICOLON                {$$ = createNode("Print", NULL, $1->line, $1->coluna);
                                                                            auxNode = createNode("StrLit", $3->value, $3->line, $3->coluna);
                                                                            insertChildren($$, auxNode);
                                                                            freeToken($1);
                                                                            freeToken($3);}

                        |   error SEMICOLON                                 {$$ = createNode("Error", NULL, 0, 0);}
                        ;

StatementRec            :                                                   {$$ = createNode("NULL", NULL, 0, 0);}

                        |   StatementRec Statement                          {insertBrother($1, $2); $$ = $1;}
                        ;




MethodInvocation        :   ID LPAR RPAR                                    {$$ = createNode("Call", NULL, $1->line, $1->coluna);
                                                                            auxNode = createNode("Id", $1->value, $1->line, $1->coluna);
                                                                            insertChildren($$, auxNode);
                                                                            freeToken($1);}

                        |   ID LPAR Expr MethodInvocationRec RPAR           {$$ = createNode("Call", NULL, $1->line, $1->coluna);
                                                                            auxNode = createNode("Id", $1->value, $1->line, $1->coluna);
                                                                            insertChildren($$, auxNode);
                                                                            insertBrother(auxNode, $3);
                                                                            insertBrother(auxNode, $4);
                                                                            freeToken($1);}

                        |   ID LPAR error RPAR                              {$$ = createNode("Error", NULL, 0, 0); 
                                                                            freeToken($1);}
                        ;

MethodInvocationRec     :                                                   {$$ = createNode("NULL", NULL, 0, 0);}
                        |   MethodInvocationRec COMMA Expr                  {$$ = $1; insertBrother($1, $3);}
                        ;


Assignment              :   ID ASSIGN Expr                                  {$$ = createNode("Assign", NULL, $2->line, $2->coluna);
                                                                            auxNode = createNode("Id", $1->value, $1->line, $1->coluna);
                                                                            insertChildren($$, auxNode);
                                                                            insertBrother(auxNode, $3);
                                                                            freeToken($2);
                                                                            freeToken($1);}

ParseArgs               :   PARSEINT LPAR ID LSQ Expr RSQ RPAR              {$$ = createNode("ParseArgs", NULL, $1->line, $1->coluna);
                                                                            auxNode = createNode("Id", $3->value, $3->line, $3->coluna);
                                                                            insertChildren($$, auxNode);
                                                                            insertBrother(auxNode, $5);
                                                                            freeToken($1);
                                                                            freeToken($3);}

                        |   PARSEINT LPAR error RPAR                        {$$ = createNode("Error", NULL, 0, 0);}
                        ;

Expr                    :   Assignment                                      {$$ = $1;}

                        |   Expr2                                           {$$ = $1;}
                        ;

Expr2                   :   Expr2 PLUS Expr2                                {$$ = createNode("Add", NULL, $2->line, $2->coluna);
                                                                            insertChildren($$,$1); insertBrother($1,$3); freeToken($2);}  

                        |   Expr2 MINUS Expr2                               {$$ = createNode("Sub", NULL, $2->line, $2->coluna);
                                                                            insertChildren($$,$1); insertBrother($1,$3); freeToken($2);}

                        |   Expr2 STAR Expr2                                {$$ = createNode("Mul", NULL, $2->line, $2->coluna);
                                                                            insertChildren($$,$1); insertBrother($1,$3); freeToken($2);}

                        |   Expr2 DIV Expr2                                 {$$ = createNode("Div", NULL, $2->line, $2->coluna);
                                                                            insertChildren($$,$1); insertBrother($1,$3); freeToken($2);}

                        |   Expr2 MOD Expr2                                 {$$ = createNode("Mod", NULL, $2->line, $2->coluna);
                                                                            insertChildren($$,$1); insertBrother($1,$3); freeToken($2);}

                        |   Expr2 AND Expr2                                 {$$ = createNode("And", NULL, $2->line, $2->coluna);
                                                                            insertChildren($$,$1); insertBrother($1,$3); freeToken($2);}

                        |   Expr2 OR Expr2                                  {$$ = createNode("Or", NULL, $2->line, $2->coluna);
                                                                            insertChildren($$,$1); insertBrother($1,$3); freeToken($2);}

                        |   Expr2 XOR Expr2                                 {$$ = createNode("Xor", NULL, $2->line, $2->coluna);
                                                                            insertChildren($$,$1); insertBrother($1,$3); freeToken($2);}

                        |   Expr2 LSHIFT Expr2                              {$$ = createNode("Lshift", NULL, $2->line, $2->coluna);
                                                                            insertChildren($$,$1); insertBrother($1,$3); freeToken($2);}

                        |   Expr2 RSHIFT Expr2                              {$$ = createNode("Rshift", NULL, $2->line, $2->coluna);
                                                                            insertChildren($$,$1); insertBrother($1,$3); freeToken($2);}

                        |   Expr2 EQ Expr2                                  {$$ = createNode("Eq", NULL, $2->line, $2->coluna);
                                                                            insertChildren($$,$1); insertBrother($1,$3); freeToken($2);}

                        |   Expr2 GE Expr2                                  {$$ = createNode("Ge", NULL, $2->line, $2->coluna);
                                                                            insertChildren($$,$1); insertBrother($1,$3); freeToken($2);}

                        |   Expr2 GT Expr2                                  {$$ = createNode("Gt", NULL, $2->line, $2->coluna);
                                                                            insertChildren($$,$1); insertBrother($1,$3); freeToken($2);}

                        |   Expr2 LE Expr2                                  {$$ = createNode("Le", NULL, $2->line, $2->coluna);
                                                                            insertChildren($$,$1); insertBrother($1,$3); freeToken($2);}

                        |   Expr2 LT Expr2                                  {$$ = createNode("Lt", NULL, $2->line, $2->coluna);
                                                                            insertChildren($$,$1); insertBrother($1,$3); freeToken($2);}

                        |   Expr2 NE Expr2                                  {$$ = createNode("Ne", NULL, $2->line, $2->coluna);
                                                                            insertChildren($$,$1); insertBrother($1,$3); freeToken($2);}

                        |   MINUS Expr2 %prec NOT                           {$$ = createNode("Minus", NULL, $1->line, $1->coluna);
                                                                            insertChildren($$,$2); freeToken($1);}

                        |   NOT Expr2                                       {$$ = createNode("Not", NULL, $1->line, $1->coluna);
                                                                            insertChildren($$,$2); freeToken($1);}

                        |   PLUS Expr2 %prec NOT                            {$$ = createNode("Plus", NULL, $1->line, $1->coluna);
                                                                            insertChildren($$,$2); freeToken($1);}

                        |   LPAR Expr RPAR                                  {$$ = $2;}
                        |   MethodInvocation                                {$$ = $1;}
                        |   ParseArgs                                       {$$ = $1;}
                        |   ID                                              {$$ = createNode("Id", $1->value, $1->line, $1->coluna);
                                                                            freeToken($1);}

                        |   ID DOTLENGTH                                    {$$ = createNode("Length", NULL, $2->line, $2->coluna);
                                                                            auxNode = createNode("Id", $1->value, $1->line, $1->coluna);
                                                                            insertChildren($$, auxNode);
                                                                            freeToken($2); freeToken($1);}

                        |   INTLIT                                          {$$ = createNode("DecLit", $1->value, $1->line, $1->coluna);
                                                                            freeToken($1);}

                        |   REALLIT                                         {$$ = createNode("RealLit", $1->value, $1->line, $1->coluna);
                                                                            freeToken($1);}

                        |   BOOLLIT                                         {$$ = createNode("BoolLit", $1->value, $1->line, $1->coluna); 
                                                                            freeToken($1);}
                                                                            
                        |   LPAR error RPAR                                 {$$ = createNode("Error", NULL, 0, 0);}
                        ;
%%
