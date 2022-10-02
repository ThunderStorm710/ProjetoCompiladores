%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

int numeroChavetas = 0;
char c;

int isPrinted=false;
int line=1;
int col=1;
int commentBegin[2];
%}

/************************************************TOKEN SIMPLES************************************************/

SEQ_S0                                                          [1-9]"_"+[0-9]
SEQ_C0                                                          [0-9]"_"+[0-9]
EXPONENTIAL                                                     "e"|"E"
LETRA                                                           [A-Za-z]        
NUM                                                             ("0"|([1-9]+)) 
NON_ZERO_DIGIT                                                  [1-9]
DIGIT                                                           [0-9]         

/***********************************************TOKEN COMPOSTOS***********************************************/

ID                                                              [{LETRA},_,$][{LETRA},{DIGIT},_,$]* 
INTLIT                                                          0|({NON_ZERO_DIGIT}+(("_")*{DIGIT}*)*)
REALLIT                                                         ({SEQ_C0}+|{DIGIT}+).({SEQ_C0}+|{DIGIT}+)({EXPONENTIAL}[+,-](({SEQ_C0}+|{DIGIT}+)))?
STRLIT                                                          "\""([{LETRA},{DIGIT},\f,\n,\t,\\,\r])*"\"" 
ESPACO                                                          [" "|"\t"]+
COMENTARIO_LINHA                                                "//".*
COMENTARIO_MULTILINHA                                           "/**"."**/"
CR_LN                                                           ("\n"|"\r\n"|"\r")
RESERVED                                                        ("++"|"--"|break|float|if|long|static|return|public|class|main|)


%X CLASS PAR_RETO PAR CHAVETAS COMENTARIO NAME_ID METODO IF_STAT



/****************************************************** REGRAS *************************************************/

%%
"class"                                                         {printf("CLASS\n"); BEGIN CLASS;}

<CLASS>{ESPACOS}                                                ;
<CLASS>{ID}                                                     {printf("ID(%s)\n",yytext);}
<CLASS>"{"                                                      {printf("LBRACE\n");numeroChavetas++;}
<CLASS>"}"                                                      {printf("LBRACE\n");numeroChavetas--;}
    
"/*"                    {BEGIN COMMENT;commentBegin[0]=line;commentBegin[1]=col;col+=yyleng;}
<COMMENT>{NEWLINE}      {line++;col=1;}
<COMMENT>.              {col+=yyleng;}
<COMMENT><<EOF>>        {BEGIN 0;printf("Line %i, col %i: unterminated comment\n",commentBegin[0],commentBegin[1]);}
<COMMENT>"*/"           {BEGIN 0;col+=yyleng;}


<CLASS>"public"                                                 {printf("PUBLIC\n"); BEGIN METODO;}
<METODO>{ESPACOS}                                               ;
<METODO>"static"                                                {printf("STATIC\n");}
<METODO>"int"                                                   {printf("INT\n");}
<METODO>"double"                                                {printf("DOUBLE\n");}
<METODO>"boolean"                                               {printf("BOOLEAN\n");}
<METODO>"void"                                                  {printf("VOID\n");}
<METODO>{ID}                                                    {printf("ID(%s)\n",yytext);}
<METODO>"("                                                     {printf("LPAR\n");}
<METODO>")"                                                     {printf("RPAR\n")}
<METODO>"{"                                                     {printf("LBRACE\n");numeroChavetas++;}
<METODO>"}"                                                     {printf("LBRACE\n");numeroChavetas--;}



        /*<METODO>[^(({STRLIT}|" ")"static")]                             {printf("ERRO FALTA STATIC");   exit(1);}
<METODO>[^(({STRLIT}|" ")["int","double","boolean","void"])]    {printf("ERRO FALTA TIPO RETORNO");exit(1);} */
<METODO>"if"                                                     {printf("IF\n");BEGIN IF_STAT;}
<IF_STAT>{ESPACOS}                                               ;
<IF_STAT>"("                                                     {printf("LPAR\n");}
<IF_STAT>")"                                                     {printf("RPAR\n")}
<IF_STAT>"=="                                                    {printf("EQ\n")}
<IF_STAT>"!="                                                    {printf("NE\n")}
<IF_STAT>">="                                                    {printf("GE\n")}
<IF_STAT>">"                                                    {printf("GT\n")}
<IF_STAT>"<"                                                    {printf("LT\n")}
<IF_STAT>"<="                                                    {printf("LE\n")}
<IF_STAT>"=="                                                    {printf("EQ\n")}





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
