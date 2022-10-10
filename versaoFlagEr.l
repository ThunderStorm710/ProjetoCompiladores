%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define false 0
#define true 1
int getPrint=false;
int getPrintEronly=false;
int numLinha=1;
int numColuna=0;
%}

/************************************************TOKEN SIMPLES**********************************************************************/

LETRA                                                  [A-Za-z]        
DIGIT                                                  [0-9]   
COMMA                                                  ","
MINUS                                                  "-"
LT                                                     "<"
LSQ                                                    "["
LPAR                                                   "("
LE                                                     "<="
LBRACE                                                 "{"
GT                                                     ">"
GE                                                     ">="
DIV                                                    "/"
STAR                                                   "*"
EQ                                                     "=="
ASSIGN                                                 "="
AND                                                    "&&"
SEMICOLON                                              ";"
RSQ                                                    "]"
RPAR                                                   ")"
RBRACE                                                 "}"
PLUS                                                   "+"
OR                                                     "||"
NOT                                                    "!"
NE                                                     "!="
MOD                                                    "%"
XOR                                                    "ˆ"
RSHIFT                                                 ">>"
LSHIFT                                                 "<<"
ARROW                                                  "->"
BOOL                                                   boolean
INT                                                    int
IF                                                     if
ELSE                                                   else
DOUBLE                                                 double
DOTLENGTH                                              .length
PRINT                                                  System.out.print
BOOLLIT                                                true|false
WHILE                                                  while
VOID                                                   void
STRING                                                 String
STATIC                                                 static
RETURN                                                 return
PUBLIC                                                 public
PARSEINT                                               Integer.parseInt   
CLASS                                                  class 

/***********************************************TOKEN COMPOSTOS*********************************************************************/
SPACE                                                  (\n|\t|\r|\f|" "|\r\n|\\n|\\t|\\r|\\f|\\\\)+
ID                                                     ({LETRA}|"_"|"$")({LETRA}|"_"|"$"|{DIGIT})*
REALLIT                                                ({INTLIT}("."{INTLIT}?)?|"."{INTLIT})(("E"|"e")("+"|"-")?{INTLIT}+)*
INTLIT                                                 ("0"|{DIGIT}+(("_")*{DIGIT}+)*)
STR                                                    (\.|\\\"|[^\r\n\"\\.]|\\n|\\t|\\\\|\\r|\\f)+
CR_LN                                                  (\n|\r\n|\r)
RESERVED                                               ("System"|"Integer"|"null"|"++"|"--"|"break")
ESCAPE                                                 \\[^(n|t|f|r)]

%X COMENTARIO COMENTARIO_SIMPLES STRING STRING_AFTER_ERROR

/****************************************************** REGRAS *********************************************************************/

%%
"/*"                                                   {BEGIN COMENTARIO;numColuna+=yyleng;}
<COMENTARIO>{CR_LN}                                    {numColuna=0;numLinha++;};
<COMENTARIO>.                                          {numColuna+=yyleng;};
<COMENTARIO><<EOF>>                                    {BEGIN 0;if(getPrint || getPrintEronly)printf("Line <%d>, col <%d>: unterminated comment\n", numLinha, numColuna);numColuna=0;numLinha++;}
<COMENTARIO>"*/"                                       {BEGIN 0;}

"//"                                                   {BEGIN COMENTARIO_SIMPLES;numColuna+=yyleng;}
<COMENTARIO_SIMPLES>{CR_LN}                            {BEGIN 0;numColuna=0;numLinha++;}
<COMENTARIO_SIMPLES>.                                  {numColuna+=yyleng;};


"\""                                                   {BEGIN STRING;numColuna+=yyleng;}

<STRING>{STR}?"\""                                     {BEGIN 0; if(getPrint)printf("STRLIT(\"%s)\n",yytext);numColuna+=yyleng;}
<STRING><<EOF>>                                        {BEGIN 0; if(getPrint || getPrintEronly)printf("Line <%d>, col <%d>: unterminated string literal\n", numLinha, numColuna);}
<STRING>{STR}?{CR_LN}                                  {BEGIN 0; if(getPrint || getPrintEronly)printf("Line <%d>, col <%d>: unterminated string literal\n", numLinha, numColuna);numColuna=0;numLinha++;}

<STRING>([^\n\r\"\\\\]|\\.)*                           {BEGIN STRING_AFTER_ERROR; if(getPrint || getPrintEronly)printf("Line <%d>, col <%d>: invalid escape sequence (%c%c)\n", numLinha, numColuna, yytext[yyleng-2],yytext[yyleng-1]);}

<STRING_AFTER_ERROR>([^\n\r\"]|\\.)*{CR_LN}            {BEGIN 0;if(getPrint || getPrintEronly)printf("Line <%d>, col <%d>: unterminated string literal\n", numLinha, numColuna);numColuna=0;numLinha++;}
<STRING_AFTER_ERROR>([^\n\r\"]|\\.)*                   {if(getPrint || getPrintEronly)printf("Line <%d>, col <%d>: invalid escape sequence (%c%c)\n", numLinha, numColuna, yytext[yyleng-2],yytext[yyleng-1]);}
<STRING_AFTER_ERROR>\"                                 {BEGIN 0;numColuna+=yyleng;}


{CLASS}                                                {if(getPrint)printf("CLASS\n");numColuna+=yyleng;}
{COMMA}                                                {if(getPrint)printf("COMMA\n");numColuna+=yyleng;}
{MINUS}                                                {if(getPrint)printf("MINUS\n");numColuna+=yyleng;}
{LT}                                                   {if(getPrint)printf("LT\n");numColuna+=yyleng;}
{LSQ}                                                  {if(getPrint)printf("LSQ\n");numColuna+=yyleng;}
{LPAR}                                                 {if(getPrint)printf("LPAR\n");numColuna+=yyleng;}
{LE}                                                   {if(getPrint)printf("LE\n");numColuna+=yyleng;}
{LBRACE}                                               {if(getPrint)printf("LBRACE\n");numColuna+=yyleng;}
{GT}                                                   {if(getPrint)printf("GT\n");numColuna+=yyleng;}
{GE}                                                   {if(getPrint)printf("GE");numColuna+=yyleng;}
{DIV}                                                  {if(getPrint)printf("DIV\n");numColuna+=yyleng;}
{STAR}                                                 {if(getPrint)printf("STAR\n");numColuna+=yyleng;}
{EQ}                                                   {if(getPrint)printf("EQ\n");numColuna+=yyleng;}
{ASSIGN}                                               {if(getPrint)printf("ASSIGN\n");numColuna+=yyleng;}
{AND}                                                  {if(getPrint)printf("AND\n");numColuna+=yyleng;}
{SEMICOLON}                                            {if(getPrint)printf("SEMICOLON\n");numColuna+=yyleng;}
{RSQ}                                                  {if(getPrint)printf("RSQ\n");numColuna+=yyleng;}
{RPAR}                                                 {if(getPrint)printf("RPAR\n");numColuna+=yyleng;}
{RBRACE}                                               {if(getPrint)printf("RBRACE\n");numColuna+=yyleng;}
{PLUS}                                                 {if(getPrint)printf("PLUS\n");numColuna+=yyleng;}
{OR}                                                   {if(getPrint)printf("OR\n");numColuna+=yyleng;}
{NOT}                                                  {if(getPrint)printf("NOT\n");numColuna+=yyleng;}
{NE}                                                   {if(getPrint)printf("NE\n");numColuna+=yyleng;}
{MOD}                                                  {if(getPrint)printf("MOD\n");numColuna+=yyleng;}
{XOR}                                                  {if(getPrint)printf("XOR\n");numColuna+=yyleng;}
{RSHIFT}                                               {if(getPrint)printf("RSHIFT\n");numColuna+=yyleng;}
{LSHIFT}                                               {if(getPrint)printf("LSHIFT\n");numColuna+=yyleng;}
{ARROW}                                                {if(getPrint)printf("ARROW\n");numColuna+=yyleng;}
{BOOL}                                                 {if(getPrint)printf("BOOL\n");numColuna+=yyleng;}
{INT}                                                  {if(getPrint)printf("INT\n");numColuna+=yyleng;}
{IF}                                                   {if(getPrint)printf("IF\n");numColuna+=yyleng;}
{ELSE}                                                 {if(getPrint)printf("ELSE\n");numColuna+=yyleng;}
{DOUBLE}                                               {if(getPrint)printf("DOUBLE\n");numColuna+=yyleng;}
{DOTLENGTH}                                            {if(getPrint)printf("DOTLENGTH\n");numColuna+=yyleng;}
{PRINT}                                                {if(getPrint)printf("PRINT\n");numColuna+=yyleng;}
{BOOLLIT}                                              {if(getPrint)printf("BOOLLIT\n");numColuna+=yyleng;}
{WHILE}                                                {if(getPrint)printf("WHILE\n");numColuna+=yyleng;}
{VOID}                                                 {if(getPrint)printf("VOID\n");numColuna+=yyleng;}
{STRING}                                               {if(getPrint)printf("STRING\n");numColuna+=yyleng;}
{STATIC}                                               {if(getPrint)printf("STATIC\n");numColuna+=yyleng;}
{RETURN}                                               {if(getPrint)printf("RETURN\n");numColuna+=yyleng;}
{PUBLIC}                                               {if(getPrint)printf("PUBLIC\n");numColuna+=yyleng;}
{PARSEINT}                                             {if(getPrint)printf("PARSEINT\n");numColuna+=yyleng;}

{RESERVED}                                             {if(getPrint)printf("RESERVED(%s)\n",yytext);numColuna+=yyleng;}
{ID}                                                   {if(getPrint)printf("ID(%s)\n",yytext);numColuna+=yyleng;}
{INTLIT}                                               {if(getPrint)printf("INTLIT(%s)\n",yytext);numColuna+=yyleng;}
{REALLIT}                                              {if(getPrint)printf("REALLIT(%s)\n",yytext);numColuna+=yyleng;}

{CR_LN}                                                {numColuna=0;numLinha++;}; 
{SPACE}                                                {numColuna+=yyleng;};
{ESCAPE}                                               {if(getPrint || getPrintEronly)printf("Line <%d>, col <%d>: invalid escape sequence (%c%c)\n", numLinha, numColuna, yytext[yyleng-2],yytext[yyleng-1]);numColuna+=yyleng;}
.                                                      {if(getPrint || getPrintEronly)printf("Line <%d>, col <%d>: illegal character (%s)\n", numLinha, numColuna, yytext);numColuna+=yyleng;}


%%

int main(int argc,char* argv[]){
    if (argc == 2){
        if (strcmp(argv[1], "-l") == 0){
            getPrint=true;
        }else if(strcmp(argv[1], "-e1") == 0){
            getPrint=false;
            getPrintEronly=true;
        }
    }
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}