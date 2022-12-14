%{
/************Autores*************
* Pedro Ascensão   -   2020233012
* Leonardo Pina    -   2019234318
*********************************/
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "semantic.h"

    int yylex(void);
    void yyerror (const char *s);

    node *head = NULL;
    node *node1 = NULL;
    node *node2 = NULL;
    node *node3 = NULL;
%}

%union{
    struct token* token;
    struct node* node;
};

%token <token>  COMMA MINUS RSHIFT LSHIFT LT LSQ LPAR LE LBRACE GT GE DIV STAR EQ ASSIGN AND SEMICOLON RSQ RPAR RBRACE PLUS OR NOT NE MOD XOR ARROW BOOL 
                INT IF ELSE DOUBLE DOTLENGTH PRINT WHILE VOID STATIC RETURN PUBLIC PARSEINT CLASS BOOLLIT STRLIT ID INTLIT REALLIT RESERVED


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
Program                 :   CLASS ID LBRACE ProgramRec RBRACE               {head = criaNode("Program", NULL, 0, 0);
                                                                            node1 = criaNode("Id", $2->valor, $2->linha, $2->coluna);
                                                                            addChild(head, node1);
                                                                            addBrother(node1, $4);
                                                                            libertaToken($2);}

ProgramRec              :                                                   {$$ = criaNode("NULL", NULL, 0, 0);}
                        |   ProgramRec MethodDecl                           {$$ = $1; addBrother($1, $2);}
                        |   ProgramRec FieldDecl                            {$$ = $1; addBrother($1, $2);}
                        |   ProgramRec SEMICOLON                            {$$ = $1;}
                        ;

                    
MethodDecl              :   PUBLIC STATIC MethodHeader MethodBody           {$$ = criaNode("MethodDecl", NULL, 0, 0);
                                                                            addChild($$, $3);
                                                                            addBrother($3, $4);}
                        ;

FieldDecl               :   PUBLIC STATIC Type ID FieldDeclRec SEMICOLON    {$$ = criaNode("FieldDecl", NULL, 0, 0);
                                                                            addChild($$, $3);
                                                                            node1 = criaNode("Id", $4->valor, $4->linha, $4->coluna);
                                                                            addBrother($3, node1);
                                                                            joinType($3, $5);
                                                                            addBrother($$, $5);
                                                                            libertaToken($4);}
                        |   error SEMICOLON                                 {$$ = criaNode("Error", NULL, 0, 0);}
                        ;

FieldDeclRec            :                                                   {$$ = criaNode("NULL", NULL, 0, 0);}
                        |   FieldDeclRec COMMA ID                           {$$ = criaNode("FieldDecl", NULL, 0, 0);
                                                                            addBrother($1, $$);
                                                                            node1 = criaNode("Id", $3->valor, $3->linha, $3->coluna);
                                                                            addChild($$, node1);
                                                                            $$ = $1; 
                                                                            libertaToken($3);}
                        ;


Type                    :   BOOL                                            {$$ = criaNode("Bool", NULL, 0, 0);}
                        |   INT                                             {$$ = criaNode("Int", NULL, 0, 0);}
                        |   DOUBLE                                          {$$ = criaNode("Double", NULL, 0, 0);}
                        ;


MethodHeader            :   Type ID LPAR RPAR                               {$$ = criaNode("MethodHeader", NULL, 0, 0);
                                                                            addChild($$, $1);
                                                                            node1 = criaNode("Id", $2->valor, $2->linha, $2->coluna);
                                                                            addBrother($1, node1);
                                                                            addBrother(node1, criaNode("MethodParams", NULL, 0, 0));
                                                                            libertaToken($2);}

                        |   VOID ID LPAR RPAR                               {$$ = criaNode("MethodHeader", NULL, 0, 0);
                                                                            node1 = criaNode("Void", NULL, $1->linha, $1->coluna);
                                                                            addChild($$, node1);
                                                                            node2 = criaNode("Id", $2->valor, $2->linha, $2->coluna);
                                                                            addBrother(node1, node2);
                                                                            addBrother(node2, criaNode("MethodParams", NULL, 0, 0));
                                                                            libertaToken($1);
                                                                            libertaToken($2);}

                        |   Type ID LPAR FormalParams RPAR                  {$$ = criaNode("MethodHeader", NULL, 0, 0);
                                                                            addChild($$, $1);
                                                                            node1 = criaNode("Id", $2->valor, $2->linha, $2->coluna);
                                                                            addBrother($1, node1);
                                                                            addBrother(node1, $4);
                                                                            libertaToken($2);}

                        |   VOID ID LPAR FormalParams RPAR                  {$$ = criaNode("MethodHeader", NULL, 0, 0);
                                                                            node1 = criaNode("Void", NULL, $1->linha, $1->coluna);
                                                                            addChild($$, node1);
                                                                            node2 = criaNode("Id", $2->valor, $2->linha, $2->coluna);
                                                                            addBrother(node1, node2);
                                                                            addBrother(node2, $4);
                                                                            libertaToken($1);
                                                                            libertaToken($2);}
                        ;


FormalParams            :   Type ID FormalParamsRec                         {$$ = criaNode("MethodParams", NULL, 0, 0);
                                                                            node1 = criaNode("ParamDecl", NULL, 0, 0);
                                                                            addChild($$, node1);
                                                                            node2 = criaNode("Id", $2->valor, $2->linha, $2->coluna);
                                                                            addBrother($1, node2);
                                                                            addChild(node1, $1);
                                                                            addBrother(node1, $3);
                                                                            libertaToken($2);}

                        |   STRLIT LSQ RSQ ID                               {$$ = criaNode("MethodParams", NULL, 0, 0);
                                                                            node1 = criaNode("ParamDecl", NULL, 0, 0);
                                                                            addChild($$, node1);
                                                                            node2 = criaNode("StringArray", NULL, $1->linha, $1->coluna);
                                                                            addChild(node1, node2);
                                                                            node3 = criaNode("Id", $4->valor, $4->linha, $4->coluna);
                                                                            addBrother(node2, node3);
                                                                            libertaToken($1);
                                                                            libertaToken($4);}
                        ;

FormalParamsRec         :                                                   {$$ = criaNode("NULL", NULL, 0, 0);}
                        |   FormalParamsRec COMMA Type ID                   {$$ = criaNode("ParamDecl", NULL, 0, 0);
                                                                            node1 = criaNode("Id", $4->valor, $4->linha, $4->coluna);
                                                                            addChild($$, $3);
                                                                            addBrother($3, node1);
                                                                            addBrother($1, $$);
                                                                            $$ = $1;
                                                                            libertaToken($4);}
                        ;


MethodBody              :   LBRACE MethodBodyRec RBRACE                     {$$ = criaNode("MethodBody", NULL, 0, 0);
                                                                            addChild($$, $2);}
                        ;

MethodBodyRec           :                                                   {$$ = criaNode("NULL", NULL, 0, 0);}
                        |   MethodBodyRec Statement                         {$$ = $1; addBrother($1, $2);}
                        |   MethodBodyRec VarDecl                           {$$ = $1; addBrother($1, $2);}
                        ;


VarDecl                 :   Type ID VarDeclRec SEMICOLON                    {$$ = criaNode("VarDecl", NULL, 0, 0);
                                                                            addChild($$, $1);
                                                                            node1 = criaNode("Id", $2->valor, $2->linha, $2->coluna);
                                                                            addBrother($1, node1);
                                                                            joinType($1, $3);
                                                                            addBrother($$, $3);
                                                                            libertaToken($2);}

VarDeclRec              :                                                   {$$ = criaNode("NULL", NULL, 0, 0);}
                        |   VarDeclRec COMMA ID                             {$$ = criaNode("VarDecl", NULL, 0, 0);
                                                                            node1 = criaNode("Id", $3->valor, $3->linha, $3->coluna);
                                                                            addChild($$, node1);
                                                                            addBrother($1, $$);
                                                                            $$ = $1;
                                                                            libertaToken($3);}
                        ;

Statement               :   LBRACE StatementRec RBRACE                      {if(countBlock($2)>2){$$ = criaNode("Block", NULL, 0, 0); addChild($$, $2);}
                                                                            else if(countBlock($2)==0){$$ = NULL; limparArvore($2);}
                                                                            else{$$ = $2;}}

                        |   IF LPAR Expr RPAR Statement %prec IFX           {$$ = criaNode("If",NULL, $1->linha, $1->coluna); 
                                                                            if($5 == NULL){node1=criaNode("Block",NULL, 0, 0); addBrother($3, node1);}
                                                                            else{addBrother($3,$5);} addBrother($3, criaNode("Block",NULL, 0, 0)); addChild($$,$3);
                                                                            libertaToken($1);}

                        |   IF LPAR Expr RPAR Statement ELSE Statement      {$$ = criaNode("If", NULL, $1->linha, $1->coluna); 
                                                                            if($5 == NULL){node1=criaNode("Block", NULL, 0, 0); addBrother($3, node1);}
                                                                            else{addBrother($3, $5);}
                                                                            if($7 == NULL){node1 = criaNode("Block", NULL, 0, 0); addBrother($3, node1);}
                                                                            else{addBrother($3, $7);} addChild($$,$3);
                                                                            libertaToken($1);}

                        |   WHILE LPAR Expr RPAR Statement                  {$$ = criaNode("While",NULL, $1->linha, $1->coluna);
                                                                            if($5 == NULL){node1=criaNode("Block",NULL, 0, 0); addBrother($3, node1);}
                                                                            else{addBrother($3,$5);}
                                                                            addChild($$,$3);
                                                                            libertaToken($1);}

                        |   RETURN SEMICOLON                                {$$ = criaNode("Return", NULL, $1->linha, $1->coluna);
                                                                            libertaToken($1);}

                        |   RETURN Expr SEMICOLON                           {$$ = criaNode("Return", NULL, $1->linha, $1->coluna);
                                                                            addChild($$, $2);
                                                                            libertaToken($1);}

                        |   SEMICOLON                                       {$$ = NULL;}

                        |   MethodInvocation SEMICOLON                      {$$ = $1;}

                        |   Assignment SEMICOLON                            {$$ = $1;}

                        |   ParseArgs SEMICOLON                             {$$ = $1;}

                        |   PRINT LPAR Expr RPAR SEMICOLON                  {$$ = criaNode("Print", NULL, $1->linha, $1->coluna);
                                                                            addChild($$, $3);
                                                                            libertaToken($1);}

                        |   PRINT LPAR STRLIT RPAR SEMICOLON                {$$ = criaNode("Print", NULL, $1->linha, $1->coluna);
                                                                            node1 = criaNode("StrLit", $3->valor, $3->linha, $3->coluna);
                                                                            addChild($$, node1);
                                                                            libertaToken($1);
                                                                            libertaToken($3);}

                        |   error SEMICOLON                                 {$$ = criaNode("Error", NULL, 0, 0);}
                        ;

StatementRec            :                                                   {$$ = criaNode("NULL", NULL, 0, 0);}

                        |   StatementRec Statement                          {addBrother($1, $2); $$ = $1;}
                        ;




MethodInvocation        :   ID LPAR RPAR                                    {$$ = criaNode("Call", NULL, $1->linha, $1->coluna);
                                                                            node1 = criaNode("Id", $1->valor, $1->linha, $1->coluna);
                                                                            addChild($$, node1);
                                                                            libertaToken($1);}

                        |   ID LPAR Expr MethodInvocationRec RPAR           {$$ = criaNode("Call", NULL, $1->linha, $1->coluna);
                                                                            node1 = criaNode("Id", $1->valor, $1->linha, $1->coluna);
                                                                            addChild($$, node1);
                                                                            addBrother(node1, $3);
                                                                            addBrother(node1, $4);
                                                                            libertaToken($1);}

                        |   ID LPAR error RPAR                              {$$ = criaNode("Error", NULL, 0, 0); 
                                                                            libertaToken($1);}
                        ;

MethodInvocationRec     :                                                   {$$ = criaNode("NULL", NULL, 0, 0);}
                        |   MethodInvocationRec COMMA Expr                  {$$ = $1; addBrother($1, $3);}
                        ;


Assignment              :   ID ASSIGN Expr                                  {$$ = criaNode("Assign", NULL, $2->linha, $2->coluna);
                                                                            node1 = criaNode("Id", $1->valor, $1->linha, $1->coluna);
                                                                            addChild($$, node1);
                                                                            addBrother(node1, $3);
                                                                            libertaToken($2);
                                                                            libertaToken($1);}

ParseArgs               :   PARSEINT LPAR ID LSQ Expr RSQ RPAR              {$$ = criaNode("ParseArgs", NULL, $1->linha, $1->coluna);
                                                                            node1 = criaNode("Id", $3->valor, $3->linha, $3->coluna);
                                                                            addChild($$, node1);
                                                                            addBrother(node1, $5);
                                                                            libertaToken($1);
                                                                            libertaToken($3);}

                        |   PARSEINT LPAR error RPAR                        {$$ = criaNode("Error", NULL, 0, 0);}
                        ;

Expr                    :   Assignment                                      {$$ = $1;}

                        |   Expr2                                           {$$ = $1;}
                        ;

Expr2                   :   Expr2 PLUS Expr2                                {$$ = criaNode("Add", NULL, $2->linha, $2->coluna);
                                                                            addChild($$,$1); addBrother($1,$3); libertaToken($2);}  

                        |   Expr2 MINUS Expr2                               {$$ = criaNode("Sub", NULL, $2->linha, $2->coluna);
                                                                            addChild($$,$1); addBrother($1,$3); libertaToken($2);}

                        |   Expr2 STAR Expr2                                {$$ = criaNode("Mul", NULL, $2->linha, $2->coluna);
                                                                            addChild($$,$1); addBrother($1,$3); libertaToken($2);}

                        |   Expr2 DIV Expr2                                 {$$ = criaNode("Div", NULL, $2->linha, $2->coluna);
                                                                            addChild($$,$1); addBrother($1,$3); libertaToken($2);}

                        |   Expr2 MOD Expr2                                 {$$ = criaNode("Mod", NULL, $2->linha, $2->coluna);
                                                                            addChild($$,$1); addBrother($1,$3); libertaToken($2);}

                        |   Expr2 AND Expr2                                 {$$ = criaNode("And", NULL, $2->linha, $2->coluna);
                                                                            addChild($$,$1); addBrother($1,$3); libertaToken($2);}

                        |   Expr2 OR Expr2                                  {$$ = criaNode("Or", NULL, $2->linha, $2->coluna);
                                                                            addChild($$,$1); addBrother($1,$3); libertaToken($2);}

                        |   Expr2 XOR Expr2                                 {$$ = criaNode("Xor", NULL, $2->linha, $2->coluna);
                                                                            addChild($$,$1); addBrother($1,$3); libertaToken($2);}

                        |   Expr2 LSHIFT Expr2                              {$$ = criaNode("Lshift", NULL, $2->linha, $2->coluna);
                                                                            addChild($$,$1); addBrother($1,$3); libertaToken($2);}

                        |   Expr2 RSHIFT Expr2                              {$$ = criaNode("Rshift", NULL, $2->linha, $2->coluna);
                                                                            addChild($$,$1); addBrother($1,$3); libertaToken($2);}

                        |   Expr2 EQ Expr2                                  {$$ = criaNode("Eq", NULL, $2->linha, $2->coluna);
                                                                            addChild($$,$1); addBrother($1,$3); libertaToken($2);}

                        |   Expr2 GE Expr2                                  {$$ = criaNode("Ge", NULL, $2->linha, $2->coluna);
                                                                            addChild($$,$1); addBrother($1,$3); libertaToken($2);}

                        |   Expr2 GT Expr2                                  {$$ = criaNode("Gt", NULL, $2->linha, $2->coluna);
                                                                            addChild($$,$1); addBrother($1,$3); libertaToken($2);}

                        |   Expr2 LE Expr2                                  {$$ = criaNode("Le", NULL, $2->linha, $2->coluna);
                                                                            addChild($$,$1); addBrother($1,$3); libertaToken($2);}

                        |   Expr2 LT Expr2                                  {$$ = criaNode("Lt", NULL, $2->linha, $2->coluna);
                                                                            addChild($$,$1); addBrother($1,$3); libertaToken($2);}

                        |   Expr2 NE Expr2                                  {$$ = criaNode("Ne", NULL, $2->linha, $2->coluna);
                                                                            addChild($$,$1); addBrother($1,$3); libertaToken($2);}

                        |   MINUS Expr2 %prec NOT                           {$$ = criaNode("Minus", NULL, $1->linha, $1->coluna);
                                                                            addChild($$,$2); libertaToken($1);}

                        |   NOT Expr2                                       {$$ = criaNode("Not", NULL, $1->linha, $1->coluna);
                                                                            addChild($$,$2); libertaToken($1);}

                        |   PLUS Expr2 %prec NOT                            {$$ = criaNode("Plus", NULL, $1->linha, $1->coluna);
                                                                            addChild($$,$2); libertaToken($1);}

                        |   LPAR Expr RPAR                                  {$$ = $2;}
                        |   MethodInvocation                                {$$ = $1;}
                        |   ParseArgs                                       {$$ = $1;}
                        |   ID                                              {$$ = criaNode("Id", $1->valor, $1->linha, $1->coluna);
                                                                            libertaToken($1);}

                        |   ID DOTLENGTH                                    {$$ = criaNode("Length", NULL, $2->linha, $2->coluna);
                                                                            node1 = criaNode("Id", $1->valor, $1->linha, $1->coluna);
                                                                            addChild($$, node1);
                                                                            libertaToken($2); libertaToken($1);}

                        |   INTLIT                                          {$$ = criaNode("DecLit", $1->valor, $1->linha, $1->coluna);
                                                                            libertaToken($1);}

                        |   REALLIT                                         {$$ = criaNode("RealLit", $1->valor, $1->linha, $1->coluna);
                                                                            libertaToken($1);}

                        |   BOOLLIT                                         {$$ = criaNode("BoolLit", $1->valor, $1->linha, $1->coluna); 
                                                                            libertaToken($1);}
                                                                            
                        |   LPAR error RPAR                                 {$$ = criaNode("Error", NULL, 0, 0);}
                        ;
%%
