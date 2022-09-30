%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
%}

NATURAL                                 [1-9]
NUMERO                                  [0-9]

%%
[\f,\n,\t,\\,\",\r]                                 {printf("STRLIT");}
"-"                                                 {printf("MINUS");}
"<"                                                 {printf("LT");}
"["                                                 {printf("LSQ");}
"("                                                 {printf("LPAR");}
"<="                                                 {printf("LE");}
"{"                                                             {printf("LBRACE");}
">"     {printf("GT");}
">="    {printf("GE");}
"/"    {printf("DIV");}
","    {printf("COMMA");}
"*"    {printf("STAR");}
"="    {printf("ASSIGN");}
"&&"    {printf("AND");}
";"                                                 {printf("SEMICOLON");}
"]"                                               {printf("RSQ");}
")"                                                {printf("RPAR");}
"}"                                                {printf("RBRACE");}
"+"                                                  {printf("PLUS");}
"||"                                                   {printf("OR");}
"!"                                                      {printf("NOT");}
"!="                                                    {printf("NE");}
"%"                                                      {printf("MOD");}
"boolean"                                                {printf("BOOL");}
"ˆ"                                                {printf("XOR");}
">>"                                                {printf("RSHIFT");}
"<<"                                                {printf("LSHIFT");}
"->"                                                {printf("ARROW");}
"int"                                                {printf("INT");}
"if"                                                {printf("IF");}
"else"                                                {printf("ELSE");}
"double"                                                {printf("DOUBLE");}
".length"                                                {printf("DOTLENGTH");}
"class"                                                {printf("CLASS");}

"System.out.print"                                  {printf("PRINT");}
"++","--","null","Integer","System"                      {printf("RESERVED");}
"true"|"false"                                         {printf("BOOLLIT");}
"while"                                                {printf("WHILE");}
"void"                                                {printf("VOID");}
"String"                                                {printf("STRING");}
"static"                                                {printf("STATIC");}
"return"                                                {printf("RETURN");}
"public"                                                {printf("PUBLIC");}
"Integer.parseInt"                                                {printf("PARSEINT");}
(_|$|[A-Za-z])+([0-9]|[A-Za-z]|_|$)*                   {printf("ID");}
("0"|[1-9]+|"_"+)                                      {printf("INTLIT");}

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
