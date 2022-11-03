/************Autores*************
* Pedro Ascensão   -   2020233012
* Leonardo Pina    -   2019234318
*********************************/
%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Tree.h"
#include "y.tab.h"

#define false 0
#define true 1
int getPrint=false;
int getPrintEronly=false;
int numLinha=1;
int numColuna=1;
int numErrors=0;
int aspaPos, barraPos, commentColuna, commentLinha;

extern node* head;
%}

/************************************************TOKEN SIMPLES**********************************************************************/

LETRA                                      [A-Za-z]        
DIGIT                                      [0-9]
DIGITW0                                    [1-9]
COMMA                                      ","
MINUS                                      "-"
RSHIFT                                     ">>"
LSHIFT                                     "<<"
LT                                         "<"
LSQ                                        "["
LPAR                                       "("
LE                                         "<="
LBRACE                                     "{"
GT                                         ">"
GE                                         ">="
DIV                                        "/"
STAR                                       "*"
EQ                                         "=="
ASSIGN                                     "="
AND                                        "&&"
SEMICOLON                                  ";"
RSQ                                        "]"
RPAR                                       ")"
RBRACE                                     "}"
PLUS                                       "+"
OR                                         "||"
NOT                                        "!"
NE                                         "!="
MOD                                        "%"
XOR                                        "^"
ARROW                                      "->"
BOOL                                       boolean
INT                                        int
IF                                         if
ELSE                                       else
DOUBLE                                     double
DOTLENGTH                                  "."length
PRINT                                      System"."out"."print
BOOLLIT                                    true|false
WHILE                                      while
VOID                                       void
STRING                                     String
STATIC                                     static
RETURN                                     return
PUBLIC                                     public
PARSEINT                                   Integer"."parseInt   
CLASS                                      class 

/***********************************************TOKEN COMPOSTOS*********************************************************************/
STRLIT                                     (\.|\\\"|[^\r\n\"\\.]|\\n|\\t|\\\\|\\r|\\f)+
SPACE                                      (\t|\f|" ")+
ID                                         ({LETRA}|"_"|"$")({LETRA}|"_"|"$"|{DIGIT})* 
INTLIT                                     ("0"|{DIGITW0}+(("_")*{DIGIT}+)*)
INTLIT2                                    ({DIGIT}+(("_")*{DIGIT}+)*)
REALLIT                                    {INTLIT2}"."({INTLIT2}|(("E"|"e")("+"|"-")?{INTLIT2}))?|"."{INTLIT2}((("E"|"e")("+"|"-")?{INTLIT2}))?|{INTLIT2}"."{INTLIT2}(("E"|"e")("+"|"-")?{INTLIT2})|{INTLIT2}(("E"|"e")("+"|"-")?{INTLIT2})
CR_LN                                      (\n|\r\n|\r)
RESERVED                                   (private|goto|do|synchronized|package|default|assert|switch|continue|abstract|System|Integer|null|"++"|"--"|break|byte|case|catch|char|const|enum|extends|final|finally|float|for|implements|import|instanceof|interface|long|native|new|protected|short|strictfp|super|this|throw|throws|transient|try|volatile)


%X COMENTARIO COMENTARIO_SIMPLES STRING STRING_AFTER_ERROR ESCAPE_ERROR

/****************************************************** REGRAS *********************************************************************/
%%
"/*"                                       {BEGIN COMENTARIO; commentColuna = numColuna; commentLinha = numLinha; numColuna+=yyleng;}
<COMENTARIO>{CR_LN}                        {numColuna=1;numLinha++;}
<COMENTARIO>.                              {numColuna+=yyleng;}
<COMENTARIO><<EOF>>                        {BEGIN 0;if(getPrint || getPrintEronly)printf("Line %d, col %d: unterminated comment\n", commentLinha, commentColuna);numColuna=1;numLinha++;}
<COMENTARIO>"*/"                           {BEGIN 0; numColuna+=yyleng;}

"//"                                       {BEGIN COMENTARIO_SIMPLES;numColuna+=yyleng;}
<COMENTARIO_SIMPLES>{CR_LN}                {BEGIN 0;numColuna=1;numLinha++;}
<COMENTARIO_SIMPLES>.                      ;


"\""                                       {BEGIN STRING; aspaPos = numColuna; numColuna+=yyleng;} 
<STRING><<EOF>>                            {BEGIN 0; if(getPrint || getPrintEronly) printf("Line %d, col %d: unterminated string literal\n", numLinha, aspaPos);}
<STRING>{STRLIT}?\"                        {BEGIN 0; if(getPrint) printf("STRLIT(\"%s)\n",yytext);numColuna+=yyleng;}
<STRING>{STRLIT}?{CR_LN}                   {BEGIN 0; if(getPrint || getPrintEronly) printf("Line %d, col %d: unterminated string literal\n", numLinha, aspaPos);numColuna=1;numLinha++;}
<STRING>{STRLIT}?\\                        {BEGIN ESCAPE_ERROR;  numColuna+=yyleng; barraPos = numColuna - 1;}


<ESCAPE_ERROR>{CR_LN}                      {BEGIN 0; if(getPrint || getPrintEronly) {printf("Line %d, col %d: invalid escape sequence (\\)\n" , numLinha, barraPos); printf("Line %d, col %d: unterminated string literal\n", numLinha, aspaPos); numColuna=1;numLinha++;}}
<ESCAPE_ERROR>[^ntfr\"\\]                  {BEGIN STRING_AFTER_ERROR; if(getPrint || getPrintEronly) printf("Line %d, col %d: invalid escape sequence (\\%s)\n", numLinha, barraPos, yytext); numColuna+=yyleng;}


<STRING_AFTER_ERROR>{STRLIT}?\"            {BEGIN 0;numColuna+=yyleng;}
<STRING_AFTER_ERROR><<EOF>>                {BEGIN 0; if(getPrint || getPrintEronly) printf("Line %d, col %d: unterminated string literal\n", numLinha, aspaPos);}
<STRING_AFTER_ERROR>{STRLIT}?{CR_LN}       {BEGIN 0;if(getPrint || getPrintEronly) printf("Line %d, col %d: unterminated string literal\n", numLinha, aspaPos);numColuna=1;numLinha++;}
<STRING_AFTER_ERROR>{STRLIT}?\\            {BEGIN ESCAPE_ERROR; numColuna+=yyleng; barraPos = numColuna - 1;}


{CLASS}                                    {if(getPrint)printf("CLASS\n");numColuna+=yyleng;{return CLASS;}}
{COMMA}                                    {if(getPrint)printf("COMMA\n");numColuna+=yyleng;{return COMMA;}}
{MINUS}                                    {if(getPrint)printf("MINUS\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return MINUS;}}
{LT}                                       {if(getPrint)printf("LT\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return LT;}}
{LSQ}                                      {if(getPrint)printf("LSQ\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return LSQ;}}
{LPAR}                                     {if(getPrint)printf("LPAR\n");numColuna+=yyleng;{return LPAR;}}
{LE}                                       {if(getPrint)printf("LE\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return LE;}}
{LBRACE}                                   {if(getPrint)printf("LBRACE\n");numColuna+=yyleng;{return LBRACE;}}
{GT}                                       {if(getPrint)printf("GT\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return GT;}}
{GE}                                       {if(getPrint)printf("GE\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return GE;}}
{DIV}                                      {if(getPrint)printf("DIV\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return DIV;}}
{STAR}                                     {if(getPrint)printf("STAR\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return STAR;}}
{EQ}                                       {if(getPrint)printf("EQ\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return EQ;}}
{ASSIGN}                                   {if(getPrint)printf("ASSIGN\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return ASSIGN;}}
{AND}                                      {if(getPrint)printf("AND\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return AND;}}
{SEMICOLON}                                {if(getPrint)printf("SEMICOLON\n");numColuna+=yyleng;{return SEMICOLON;}}
{RSQ}                                      {if(getPrint)printf("RSQ\n");numColuna+=yyleng;{return RSQ;}}
{RPAR}                                     {if(getPrint)printf("RPAR\n");numColuna+=yyleng;{return RPAR;}}
{RBRACE}                                   {if(getPrint)printf("RBRACE\n");numColuna+=yyleng;{return RBRACE;}}
{PLUS}                                     {if(getPrint)printf("PLUS\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return PLUS;}}
{OR}                                       {if(getPrint)printf("OR\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return OR;}}
{NOT}                                      {if(getPrint)printf("NOT\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return NOT;}}
{NE}                                       {if(getPrint)printf("NE\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return NE;}}
{MOD}                                      {if(getPrint)printf("MOD\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return MOD;}}
{XOR}                                      {if(getPrint)printf("XOR\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return XOR;}}
{RSHIFT}                                   {if(getPrint)printf("RSHIFT\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return RSHIFT;}}
{LSHIFT}                                   {if(getPrint)printf("LSHIFT\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return LSHIFT;}}
{ARROW}                                    {if(getPrint)printf("ARROW\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return ARROW;}}
{BOOL}                                     {if(getPrint)printf("BOOL\n");numColuna+=yyleng;{return BOOL;}}
{INT}                                      {if(getPrint)printf("INT\n");numColuna+=yyleng;{return INT;}}
{IF}                                       {if(getPrint)printf("IF\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return IF;}}
{ELSE}                                     {if(getPrint)printf("ELSE\n");numColuna+=yyleng;{return ELSE;}}
{DOUBLE}                                   {if(getPrint)printf("DOUBLE\n");numColuna+=yyleng;{return DOUBLE;}}
{DOTLENGTH}                                {if(getPrint)printf("DOTLENGTH\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return DOTLENGTH;}}
{PRINT}                                    {if(getPrint)printf("PRINT\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return PRINT;}}
{BOOLLIT}                                  {if(getPrint)printf("BOOLLIT(%s)\n",yytext);numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return BOOLLIT;}}
{WHILE}                                    {if(getPrint)printf("WHILE\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return WHILE;}}
{VOID}                                     {if(getPrint)printf("VOID\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return VOID;}}
{STRING}                                   {if(getPrint)printf("STRING\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return STRLIT;}}
{STATIC}                                   {if(getPrint)printf("STATIC\n");numColuna+=yyleng;{return STATIC;}}
{RETURN}                                   {if(getPrint)printf("RETURN\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return RETURN;}}
{PUBLIC}                                   {if(getPrint)printf("PUBLIC\n");numColuna+=yyleng;{return PUBLIC;}}
{PARSEINT}                                 {if(getPrint)printf("PARSEINT\n");numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return PARSEINT;}}
{RESERVED}                                 {if(getPrint)printf("RESERVED(%s)\n",yytext);numColuna+=yyleng;}
{ID}                                       {if(getPrint)printf("ID(%s)\n",yytext); numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return ID;}}
{INTLIT}                                   {if(getPrint)printf("INTLIT(%s)\n",yytext);numColuna+=yyleng;{yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return INTLIT;}}
{REALLIT}                                  {if(getPrint)printf("REALLIT(%s)\n",yytext);numColuna+=yyleng; yylval.value = createToken(yytext, numLinha, numColuna-strlen(yytext));return REALLIT;}

{CR_LN}                                    {numColuna=1; numLinha++;}; 
{SPACE}                                    {numColuna+=yyleng;}
.                                          {if(getPrint || getPrintEronly)printf("Line %d, col %d: illegal character (%s)\n", numLinha, numColuna, yytext);numColuna+=yyleng;}


%%

int main(int argc,char* argv[]){
    if (argc == 2){
        if (strcmp(argv[1], "-l") == 0){
            getPrint=true;
            yylex();
        }else if(strcmp(argv[1], "-e1") == 0){
            getPrint=false;
            getPrintEronly=true;
            yylex();
        }else if(strcmp(argv[1],"-e2")==0){
			yyparse();
        }else if(strcmp(argv[1],"-t")==0){
			yyparse();
			if(numErrors == 0){
				printAST(head, 0);
			}
		}
    }
    clearAST(head);
    return 0;
}

void yyerror (const char *s) {
	numErrors = 1;
	printf ("Line %d, col %d: %s: %s\n", numLinha, (int)(numColuna-(int)yyleng), s, yytext);
}

int yywrap() {
    return 1;
}
