%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
%}

NON_ZERO_DIGIT                                                  [1-9]
DIGIT                                                           [0-9]
LETRA                                                           [A-Za-z]
NUM                                                             ("0"|([1-9]+))
EXPONENTIAL                                                     "e"|"E"
%%
","                                                             {printf("COMMA\n");}
[\f,\n,\t,\\,\",\r]                                             {printf("STRLIT\n");}
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
"class"                                                         {printf("CLASS\n");}
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
(_|$|{LETRA})+({DIGIT}|{LETRA}|_|$)*                            {printf("ID\n");}
({NUM}|"_"+|{NON_ZERO_DIGIT}"_"+{DIGIT}*)                       {printf("INTLIT\n");}
{DIGIT}*.{DIGIT}+{EXPONENTIAL}[+,-]{DIGIT}+                     {printf("REALLIT\n");}
.                                                               ;

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
