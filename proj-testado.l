%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
%}

/************************************************TOKEN SIMPLES************************************************/

LETRA                                                           [A-Za-z]        
SEQ_S0                                                          [1-9]"_"+[0-9]
SEQ_C0                                                          [0-9]"_"+[0-9]
EXPONENTIAL                                                     "e"|"E"
NUM                                                             ("0"|([1-9]+)) 
NON_ZERO_DIGIT                                                  [1-9]
DIGIT                                                           [0-9]         

/***********************************************TOKEN COMPOSTOS***********************************************/

ID                                                              ({LETRA}|"_"|"$")({LETRA}|"_"|"$"|{DIGIT})* 
REALLIT                                                         ({INTLIT}*("."{INTLIT}*)?)?(("E"|"e")("+"|"-")?{INTLIT}+)*
INTLIT                                                          ({DIGIT}+(("_")*{DIGIT}+)*)
STRLIT                                                          \"({LETRA}|{DIGIT}|"\f"|"\n"|"\t"|"\\"|"\r")*\" 
ESPACOS                                                         [" "|"\t"]+
COMENTARIO_LINHA                                                "//".*
COMENTARIO_MULTILINHA                                           "/**"."**/"
CR_LN                                                           ("\n"|"\r\n"|"\r")
RESERVED                                                        ("++"|"--"|"break"|"float"|"if"|"long"|"static"|"return"|"public"|"class"|"main"|)


%X CLASS PAR_RETO PAR CHAVETAS COMENTARIO NAME_ID METODO IF_STAT



/****************************************************** REGRAS *************************************************/

%%
"class"                                                         {printf("CLASS\n"); BEGIN CLASS;}


","                                                             {printf("COMMA\n");}
{STRLIT}                                                        {printf("STRLIT(%s)\n",yytext);}
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
"boolean"                                                       {printf("BOOL\n");}
"ˆ"                                                             {printf("XOR\n");}
">>"                                                            {printf("RSHIFT\n");}
"<<"                                                            {printf("LSHIFT\n");}
"->"                                                            {printf("ARROW\n");}
"int"                                                           {printf("INT\n");}
"if"                                                            {printf("IF\n");}
"else"                                                          {printf("ELSE\n");}
"double"                                                        {printf("DOUBLE\n");}
".length"                                                       {printf("DOTLENGTH\n");}
"System.out.print"                                              {printf("PRINT\n");}
"++","--","null","Integer","System"                             {printf("RESERVED\n");}
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
