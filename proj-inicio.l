%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int numeroChavetas = 0;
char c;
%}

NON_ZERO_DIGIT                                                  [1-9]
DIGIT                                                           [0-9]
LETRA                                                           [A-Za-z]
NUM                                                             ("0"|([1-9]+))
EXPONENTIAL                                                     "e"|"E"
SEQ_S0                                                          [1-9]"_"+[0-9]
SEQ_C0                                                          [0-9]"_"+[0-9]
INTLIT                                                          ("0"|{NON_ZERO_DIGIT}{DIGIT}*|{SEQ_S0})
REALLIT                                                         ({SEQ_C0}+|{DIGIT}+).({SEQ_C0}+|{DIGIT}+)({EXPONENTIAL}[+,-](({SEQ_C0}+|{DIGIT}+)))?
ID                                                              (_|$|{LETRA})+({DIGIT}|{LETRA}|_|$)*
STRLIT                                                          [\f,\n,\t,\\,\",\r]([\f,\n,\t,\\,\",\r])+
ESPACOS                                                         ({STRLIT}|" ")+

%X CLASS PAR_RETO PAR CHAVETAS COMENTARIO NAME_ID METODO

%%
"class"                                                         {printf("CLASS\n"); BEGIN CLASS;}

<CLASS>{ESPACOS}{ID}                      {numeroChavetas++; printf("ID("); 

                                                                while(!isspace(c = getchar())){
                                                                    printf("%c", c);
                                                                }
                                                                printf(")\n");  
                                                                }

<CLASS>[^{ID}]                                                  {printf("ERRO CLASSE SEM NOME");exit(1);}


<CLASS>"public"                                                 {printf("PUBLIC\n"); BEGIN METODO;}
<METODO>({STRLIT}|" ")"static"                                  {printf("STATIC\n");}
<METODO>[^(({STRLIT}|" ")"static")]                             {printf("ERRO FALTA STATIC");   exit(1);}
<METODO>[^(({STRLIT}|" ")["int","double","boolean","void"])]    {printf("ERRO FALTA TIPO RETORNO");exit(1);}
<METODO>({STRLIT}|" ")"int"                                     {printf("INT\n");}
<METODO>({STRLIT}|" ")"double"                                  {printf("DOUBLE\n");}
<METODO>({STRLIT}|" ")"boolean"                                 {printf("BOOLEAN\n");}
<METODO>({STRLIT}|" ")"void"                                    {printf("VOID\n");}
<CLASS>({STRLIT}|" "){ID}({STRLIT}|" ")"{"                      {numeroChavetas++; printf("ID(");} 

<METODO>({STRLIT}|" "){ID}"()"({STRLIT}|" ")?"{"                {numeroChavetas++; printf("ID("); 


<METODO>({STRLIT}|" "){ID}["()","int","boolean","double"]            ({STRLIT}|" ")"{"                      {numeroChavetas++; printf("ID("); 

                                                                while(!isspace(c = getchar())){
                                                                    printf("%c", c);
                                                                }
                                                                printf(")\n");  
                                                                }






<NAME_ID>{STRLIT}                                               ;
<NOME_CLASS>({STRLIT}|" ")                                      {print("SAIR ID"); BEGIN CHAVETAS_CLASS;}



","                                                             {printf("COMMA\n");}
{STRLIT}                                                        {printf("STRLIT\n");}
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
{ID}                                                            {printf("ID\n");}
{INTLIT}                                                        {printf("INTLIT\n");} //({NUM}|"_"+|{NON_ZERO_DIGIT}"_"+{DIGIT}*)                       {printf("INTLIT\n");}
{REALLIT}                                                       {printf("REALLIT\n");}
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
