%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
%}

/************************************************TOKEN SIMPLES**********************************************************************/

LETRA                                                           [A-Za-z]        
DIGIT                                                           [0-9]         

/***********************************************TOKEN COMPOSTOS*********************************************************************/

ID                                                              ({LETRA}|"_"|"$")({LETRA}|"_"|"$"|{DIGIT})* 
REALLIT                                                         ({INTLIT}*("."{INTLIT}*)?)?(("E"|"e")("+"|"-")?{INTLIT}+)*
INTLIT                                                          ({DIGIT}+(("_")*{DIGIT}+)*)
STR                                                             (\\n|\\t|\\r|\\f|" "|{LETRA}|{DIGIT})*
CR_LN                                                           (\n|\r\n|\r)
RESERVED                                                        ("System"|"Integer"|"null"|"++"|"--"|"break"|"float"|"long"|"main")


%X CLASS COMENTARIO COMENTARIO_SIMPLES STRING


/****************************************************** REGRAS *********************************************************************/

%%
"/*"                                                            {BEGIN COMENTARIO;}
<COMENTARIO>{CR_LN}                                             ;
<COMENTARIO>.                                                   ;
<COMENTARIO><<EOF>>                                             {BEGIN 0;printf("unterminated comment\n");}
<COMENTARIO>"*/"                                                {BEGIN 0;}

"//"                                                            {BEGIN COMENTARIO_SIMPLES;}
<COMENTARIO_SIMPLES>{CR_LN}                                     {BEGIN 0;}
<COMENTARIO_SIMPLES>.                                           ;

"\""                                                            {BEGIN STRING;}
<STRING>"\\"[^ntfr]                                             {printf("invalid escape sequence (<%s>)\n", yytext);}
<STRING><<EOF>>                                                 {printf("unterminated string literal EOF\n"); BEGIN 0;}
<STRING>{STR}{CR_LN}                                            {printf("unterminated string literal '\n' \n"); BEGIN 0;}
<STRING>{STR}"\""                                               {printf("STRLIT(\"%s)\n",yytext);BEGIN 0;}



"class"                                                         {printf("CLASS\n");}
{RESERVED}                                                      {printf("RESERVED\n");}
","                                                             {printf("COMMA\n");}
"-"                                                             {printf("MINUS\n");}
"<"                                                             {printf("LT\n");}
"["                                                             {printf("LSQ\n");}
"("                                                             {printf("LPAR\n");}
"<="                                                            {printf("LE\n");}
"{"                                                             {printf("LBRACE\n");}
">"                                                             {printf("GT\n");}
">="                                                            {printf("GE");}
"/"                                                             {printf("DIV\n");}
"*"                                                             {printf("STAR\n");}
"=="                                                            {printf("EQ\n");}
"="                                                             {printf("ASSIGN\n");}
"&&"                                                            {printf("AND\n");}
";"                                                             {printf("SEMICOLON\n");}
"]"                                                             {printf("RSQ\n");}
")"                                                             {printf("RPAR\n");}
"}"                                                             {printf("RBRACE\n");}
"+"                                                             {printf("PLUS\n");}
"||"                                                            {printf("OR\n");}
"!"                                                             {printf("NOT\n");}
"!="                                                            {printf("NE\n");}
"%"                                                             {printf("MOD\n");}
"ˆ"                                                             {printf("XOR\n");}
">>"                                                            {printf("RSHIFT\n");}
"<<"                                                            {printf("LSHIFT\n");}
"->"                                                            {printf("ARROW\n");}
"boolean"                                                       {printf("BOOL\n");}
"int"                                                           {printf("INT\n");}
"if"                                                            {printf("IF\n");}
"else"                                                          {printf("ELSE\n");}
"double"                                                        {printf("DOUBLE\n");}
".length"                                                       {printf("DOTLENGTH\n");}
"System.out.print"                                              {printf("PRINT\n");}
"true"|"false"                                                  {printf("BOOLLIT\n");}
"while"                                                         {printf("WHILE\n");}
"void"                                                          {printf("VOID\n");}
"String"                                                        {printf("STRING\n");}
"static"                                                        {printf("STATIC\n");}
"return"                                                        {printf("RETURN\n");}
"public"                                                        {printf("PUBLIC\n");}
"Integer.parseInt"                                              {printf("PARSEINT\n");}
{ID}                                                            {printf("ID(%s)\n",yytext);}
{INTLIT}                                                        {printf("INTLIT(%s)\n",yytext);}
{REALLIT}                                                       {printf("REALLIT(%s)\n",yytext);}
.                                                               ;
\n                                                              ;
%%

int main()
{
yylex();
return 0;
}

int yywrap()
{
return 1;
}
