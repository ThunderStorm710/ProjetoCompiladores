/************Autores*************
* Pedro Ascensão   -   2020233012
* Leonardo Pina    -   2019234318
*********************************/
%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define false 0
#define true 1
int getPrint=false;
int getPrintEronly=false;
int getTree = false;
int getYacc = false;
int numLinha=1;
int numColuna=1;
int aspaPos, barraPos, commentColuna, commentLinha;
int yyparse(void);
%}

/************************************************TOKEN SIMPLES**********************************************************************/

LETRA                                                  [A-Za-z]        
DIGIT                                                  [0-9]
DIGITW0                                                [1-9]
COMMA                                                  ","
MINUS                                                  "-"
RSHIFT                                                 ">>"
LSHIFT                                                 "<<"
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
XOR                                                    "^"
ARROW                                                  "->"
BOOL                                                   boolean
INT                                                    int
IF                                                     if
ELSE                                                   else
DOUBLE                                                 double
DOTLENGTH                                              "."length
PRINT                                                  System"."out"."print
BOOLLIT                                                true|false
WHILE                                                  while
VOID                                                   void
STRING                                                 String
STATIC                                                 static
RETURN                                                 return
PUBLIC                                                 public
PARSEINT                                               Integer"."parseInt   
CLASS                                                  class 

/***********************************************TOKEN COMPOSTOS*********************************************************************/
STRLIT                                                 (\.|\\\"|[^\r\n\"\\.]|\\n|\\t|\\\\|\\r|\\f)+
SPACE                                                  (\t|\f|" ")+
ID                                                     ({LETRA}|"_"|"$")({LETRA}|"_"|"$"|{DIGIT})* 
INTLIT                                                 ("0"|{DIGITW0}+(("_")*{DIGIT}+)*)
INTLIT2                                                ({DIGIT}+(("_")*{DIGIT}+)*)
REALLIT                                                {INTLIT2}"."({INTLIT2}|(("E"|"e")("+"|"-")?{INTLIT2}))?|"."{INTLIT2}((("E"|"e")("+"|"-")?{INTLIT2}))?|{INTLIT2}"."{INTLIT2}(("E"|"e")("+"|"-")?{INTLIT2})|{INTLIT2}(("E"|"e")("+"|"-")?{INTLIT2})
CR_LN                                                  (\n|\r\n|\r)
RESERVED                                               (private|goto|do|synchronized|package|default|assert|switch|continue|abstract|System|Integer|null|"++"|"--"|break|byte|case|catch|char|const|enum|extends|final|finally|float|for|implements|import|instanceof|interface|long|native|new|protected|short|strictfp|super|this|throw|throws|transient|try|volatile)


%X COMENTARIO COMENTARIO_SIMPLES STRING STRING_AFTER_ERROR ESCAPE_ERROR

/****************************************************** REGRAS *********************************************************************/
%%
"/*"                                                   {BEGIN COMENTARIO; commentColuna = numColuna; commentLinha = numLinha; numColuna+=yyleng;}
<COMENTARIO>{CR_LN}                                    {numColuna=1;numLinha++;}
<COMENTARIO>.                                          {numColuna+=yyleng;}
<COMENTARIO><<EOF>>                                    {BEGIN 0;if(getPrint || getPrintEronly)printf("Line %d, col %d: unterminated comment\n", commentLinha, commentColuna);numColuna=1;numLinha++;}
<COMENTARIO>"*/"                                       {BEGIN 0; numColuna+=yyleng;}

"//"                                                   {BEGIN COMENTARIO_SIMPLES;numColuna+=yyleng;}
<COMENTARIO_SIMPLES>{CR_LN}                            {BEGIN 0;numColuna=1;numLinha++;}
<COMENTARIO_SIMPLES>.                                  ;


"\""                                                   {BEGIN STRING; aspaPos = numColuna; numColuna+=yyleng;} 
<STRING><<EOF>>                                        {BEGIN 0; if(getPrint || getPrintEronly) printf("Line %d, col %d: unterminated string literal\n", numLinha, aspaPos);}
<STRING>{STRLIT}?\"                                    {BEGIN 0; if(getPrint) printf("STRLIT(\"%s)\n",yytext);numColuna+=yyleng;}
<STRING>{STRLIT}?{CR_LN}                               {BEGIN 0; if(getPrint || getPrintEronly) printf("Line %d, col %d: unterminated string literal\n", numLinha, aspaPos);numColuna=1;numLinha++;}
<STRING>{STRLIT}?\\                                    {BEGIN ESCAPE_ERROR;  numColuna+=yyleng; barraPos = numColuna - 1;}


<ESCAPE_ERROR>{CR_LN}                                  {BEGIN 0; if(getPrint || getPrintEronly) {
                                                                    printf("Line %d, col %d: invalid escape sequence (\\)\n" , numLinha, barraPos); 
                                                                    printf("Line %d, col %d: unterminated string literal\n", numLinha, aspaPos); 
                                                                    numColuna=1;numLinha++;}}
<ESCAPE_ERROR>[^ntfr\"\\]                              {BEGIN STRING_AFTER_ERROR; if(getPrint || getPrintEronly) printf("Line %d, col %d: invalid escape sequence (\\%s)\n", numLinha, barraPos, yytext); numColuna+=yyleng;}


<STRING_AFTER_ERROR>{STRLIT}?\"                        {BEGIN 0;numColuna+=yyleng;}
<STRING_AFTER_ERROR><<EOF>>                            {BEGIN 0; if(getPrint || getPrintEronly) printf("Line %d, col %d: unterminated string literal\n", numLinha, aspaPos);}
<STRING_AFTER_ERROR>{STRLIT}?{CR_LN}                   {BEGIN 0;if(getPrint || getPrintEronly) printf("Line %d, col %d: unterminated string literal\n", numLinha, aspaPos);numColuna=1;numLinha++;}
<STRING_AFTER_ERROR>{STRLIT}?\\                        {BEGIN ESCAPE_ERROR; numColuna+=yyleng; barraPos = numColuna - 1;}


{CLASS}                                                {if(getPrint)printf("CLASS\n");numColuna+=yyleng;}
{COMMA}                                                {if(getPrint)printf("COMMA\n");numColuna+=yyleng;}
{MINUS}                                                {if(getPrint)printf("MINUS\n");numColuna+=yyleng;}
{LT}                                                   {if(getPrint)printf("LT\n");numColuna+=yyleng;}
{LSQ}                                                  {if(getPrint)printf("LSQ\n");numColuna+=yyleng;}
{LPAR}                                                 {if(getPrint)printf("LPAR\n");numColuna+=yyleng;}
{LE}                                                   {if(getPrint)printf("LE\n");numColuna+=yyleng;}
{LBRACE}                                               {if(getPrint)printf("LBRACE\n");numColuna+=yyleng;}
{GT}                                                   {if(getPrint)printf("GT\n");numColuna+=yyleng;}
{GE}                                                   {if(getPrint)printf("GE\n");numColuna+=yyleng;}
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
{BOOLLIT}                                              {if(getPrint)printf("BOOLLIT(%s)\n",yytext);numColuna+=yyleng;}
{WHILE}                                                {if(getPrint)printf("WHILE\n");numColuna+=yyleng;}
{VOID}                                                 {if(getPrint)printf("VOID\n");numColuna+=yyleng;}
{STRING}                                               {if(getPrint)printf("STRING\n");numColuna+=yyleng;}
{STATIC}                                               {if(getPrint)printf("STATIC\n");numColuna+=yyleng;}
{RETURN}                                               {if(getPrint)printf("RETURN\n");numColuna+=yyleng;}
{PUBLIC}                                               {if(getPrint)printf("PUBLIC\n");numColuna+=yyleng;}
{PARSEINT}                                             {if(getPrint)printf("PARSEINT\n");numColuna+=yyleng;}
{RESERVED}                                             {if(getPrint)printf("RESERVED(%s)\n",yytext);numColuna+=yyleng;}
{ID}                                                   {if(getPrint)printf("ID(%s)\n",yytext); numColuna+=yyleng;}
{INTLIT}                                               {if(getPrint)printf("INTLIT(%s)\n",yytext);numColuna+=yyleng;}
{REALLIT}                                              {if(getPrint)printf("REALLIT(%s)\n",yytext);numColuna+=yyleng;}

{CR_LN}                                                {numColuna=1; numLinha++;}; 
{SPACE}                                                {numColuna+=yyleng;}
.                                                      {if(getPrint || getPrintEronly)printf("Line %d, col %d: illegal character (%s)\n", numLinha, numColuna, yytext);numColuna+=yyleng;}


%%

int main(int argc,char* argv[]){
    switch(argc){
    case 1:
    //imprimir erros do lex/flex e do yacc
        getPrint = false;
        getPrintEronly = true;
        getTree = false;
        getYacc = true;
        yyparse();
        break;

    case 2:
        //imprimir tokens e erros do lex/flex
        if (strcmp(argv[1], "-l") == 0){
            getPrint = true;
            getPrintEronly = true;
            yylex();

            //imprimir apenas erros do lex/flex
        } else if (strcmp(argv[1], "-e1") == 0){
            getPrintEronly = true;
            getPrint = false;
            yylex();

        //imprimir tokens e erros do yyac
        } else if (strcmp(argv[1], "-t") == 0){
            getTree = true;
            getYacc = true;
            yyparse();

        //imprimir erros do yyac
        } else if (strcmp(argv[1], "-e2") == 0){
            getYacc = true;
            yyparse();
        }
        break;
    }  
    return 0;    
}
    
int yywrap(){
    return 1;
}

void yyerror(const char *s) {
    switch(strlen(yytext)){
        case 0:
            printf("Line %d, col %d: %s: %s\n", line, col, s, yytext);
            break;
        default:
            printf("Line %d, col %d: %s: %s\n", line, (int)(col-yyleng), s, yytext);
            break;
    }

}
