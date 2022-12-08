/************Autores*************
* Pedro Ascensão   -   2020233012
* Leonardo Pina    -   2019234318
*********************************/
%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "y.tab.h"
#include "semantic.h"

#define false 0
#define true 1
int getPrint=false;
int getPrintEronly=false;
int getYacc = false;
int numLinha=1;
int numColuna=1;
int numErrors=0;
int aspaPos, barraPos, commentColuna, commentLinha;

int yylex_destroy();
sym_table *tabelaGlobal, *tabelaLocal;
int errosSemantica;

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
<COMENTARIO><<EOF>>                        {if(getPrint || getPrintEronly)printf("Line %d, col %d: unterminated comment\n", commentLinha, commentColuna);numColuna+=yyleng; return 0;}
<COMENTARIO>"*/"                           {BEGIN 0; numColuna+=yyleng;}

"//"                                       {BEGIN COMENTARIO_SIMPLES;numColuna+=yyleng;}
<COMENTARIO_SIMPLES>{CR_LN}                {BEGIN 0;numColuna=1;numLinha++;}
<COMENTARIO_SIMPLES>.                      ;

"\""{STRLIT}?"\""                          {if(getPrint) printf("STRLIT(%s)\n",yytext); numColuna+=yyleng; yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if (getYacc) return STRLIT;}
"\""                                       {BEGIN STRING; aspaPos = numColuna; numColuna+=yyleng;} 
<STRING><<EOF>>                            {BEGIN 0; if(getPrint || getPrintEronly) printf("Line %d, col %d: unterminated string literal\n", numLinha, aspaPos);}
<STRING>{STRLIT}?\"                        {BEGIN 0; if(getPrint) printf("STRLIT(\"%s)\n",yytext); char aux[yyleng+1]; sprintf(yytext, "\"%s",yytext); printf("'%s'\n", yytext); numColuna+=yyleng; yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if (getYacc) return STRLIT;}
<STRING>{STRLIT}?{CR_LN}                   {BEGIN 0; if(getPrint || getPrintEronly) printf("Line %d, col %d: unterminated string literal\n", numLinha, aspaPos);numColuna=1;numLinha++;}
<STRING>{STRLIT}?\\                        {BEGIN ESCAPE_ERROR;  numColuna+=yyleng; barraPos = numColuna - 1;}


<ESCAPE_ERROR>{CR_LN}                      {BEGIN 0; if(getPrint || getPrintEronly) {printf("Line %d, col %d: invalid escape sequence (\\)\n" , numLinha, barraPos); printf("Line %d, col %d: unterminated string literal\n", numLinha, aspaPos); numColuna=1;numLinha++;}}
<ESCAPE_ERROR>[^ntfr\"\\]                  {BEGIN STRING_AFTER_ERROR; if(getPrint || getPrintEronly) printf("Line %d, col %d: invalid escape sequence (\\%s)\n", numLinha, barraPos, yytext); numColuna+=yyleng;}


<STRING_AFTER_ERROR>{STRLIT}?\"            {BEGIN 0;numColuna+=yyleng;}
<STRING_AFTER_ERROR><<EOF>>                {BEGIN 0; if(getPrint || getPrintEronly) printf("Line %d, col %d: unterminated string literal\n", numLinha, aspaPos);}
<STRING_AFTER_ERROR>{STRLIT}?{CR_LN}       {BEGIN 0;if(getPrint || getPrintEronly) printf("Line %d, col %d: unterminated string literal\n", numLinha, aspaPos);numColuna=1;numLinha++;}
<STRING_AFTER_ERROR>{STRLIT}?\\            {BEGIN ESCAPE_ERROR; numColuna+=yyleng; barraPos = numColuna - 1;}


{CLASS}                                    {if(getPrint)printf("CLASS\n");numColuna+=yyleng; if (getYacc) return CLASS;}
{COMMA}                                    {if(getPrint)printf("COMMA\n");numColuna+=yyleng; if (getYacc) return COMMA;}
{MINUS}                                    {if(getPrint)printf("MINUS\n");numColuna+=yyleng; yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if (getYacc) return MINUS;}
{LT}                                       {if(getPrint)printf("LT\n");numColuna+=yyleng; yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if (getYacc) return LT;}
{LSQ}                                      {if(getPrint)printf("LSQ\n");numColuna+=yyleng; yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if (getYacc) return LSQ;}
{LPAR}                                     {if(getPrint)printf("LPAR\n");numColuna+=yyleng; if (getYacc) return LPAR;}
{LE}                                       {if(getPrint)printf("LE\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if (getYacc) return LE;}
{LBRACE}                                   {if(getPrint)printf("LBRACE\n");numColuna+=yyleng; if (getYacc)return LBRACE;}
{GT}                                       {if(getPrint)printf("GT\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if (getYacc) return GT;}
{GE}                                       {if(getPrint)printf("GE\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if (getYacc) return GE;}
{DIV}                                      {if(getPrint)printf("DIV\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if (getYacc)return DIV;}
{STAR}                                     {if(getPrint)printf("STAR\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if (getYacc) return STAR;}
{EQ}                                       {if(getPrint)printf("EQ\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext));if (getYacc) return EQ;}
{ASSIGN}                                   {if(getPrint)printf("ASSIGN\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if (getYacc) return ASSIGN;}
{AND}                                      {if(getPrint)printf("AND\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext));if (getYacc) return AND;}
{SEMICOLON}                                {if(getPrint)printf("SEMICOLON\n");numColuna+=yyleng; if (getYacc) return SEMICOLON;}
{RSQ}                                      {if(getPrint)printf("RSQ\n");numColuna+=yyleng; if (getYacc) return RSQ;}
{RPAR}                                     {if(getPrint)printf("RPAR\n");numColuna+=yyleng; if (getYacc) return RPAR;}
{RBRACE}                                   {if(getPrint)printf("RBRACE\n");numColuna+=yyleng; if (getYacc) return RBRACE;}
{PLUS}                                     {if(getPrint)printf("PLUS\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if (getYacc) return PLUS;}
{OR}                                       {if(getPrint)printf("OR\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if (getYacc) return OR;}
{NOT}                                      {if(getPrint)printf("NOT\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext));if (getYacc) return NOT;}
{NE}                                       {if(getPrint)printf("NE\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext));if (getYacc)return NE;}
{MOD}                                      {if(getPrint)printf("MOD\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext));if (getYacc)return MOD;}
{XOR}                                      {if(getPrint)printf("XOR\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext));if (getYacc)return XOR;}
{RSHIFT}                                   {if(getPrint)printf("RSHIFT\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext));if (getYacc)return RSHIFT;}
{LSHIFT}                                   {if(getPrint)printf("LSHIFT\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext));if (getYacc)return LSHIFT;}
{ARROW}                                    {if(getPrint)printf("ARROW\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext));if (getYacc)return ARROW;}
{BOOL}                                     {if(getPrint)printf("BOOL\n");numColuna+=yyleng; if (getYacc)return BOOL;}
{INT}                                      {if(getPrint)printf("INT\n");numColuna+=yyleng; if (getYacc) return INT;}
{IF}                                       {if(getPrint)printf("IF\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if(getYacc) return IF;}
{ELSE}                                     {if(getPrint)printf("ELSE\n");numColuna+=yyleng; if(getYacc) return ELSE;}
{DOUBLE}                                   {if(getPrint)printf("DOUBLE\n");numColuna+=yyleng; if(getYacc)return DOUBLE;}
{DOTLENGTH}                                {if(getPrint)printf("DOTLENGTH\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if(getYacc)return DOTLENGTH;}
{PRINT}                                    {if(getPrint)printf("PRINT\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if(getYacc) return PRINT;}
{BOOLLIT}                                  {if(getPrint)printf("BOOLLIT(%s)\n",yytext);numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if(getYacc) return BOOLLIT;}
{WHILE}                                    {if(getPrint)printf("WHILE\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if(getYacc) return WHILE;}
{VOID}                                     {if(getPrint)printf("VOID\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if(getYacc)return VOID;}
{STRING}                                   {if(getPrint)printf("STRING\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if(getYacc)return STRLIT;}
{STATIC}                                   {if(getPrint)printf("STATIC\n");numColuna+=yyleng; if(getYacc)return STATIC;}
{RETURN}                                   {if(getPrint)printf("RETURN\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if(getYacc)return RETURN;}
{PUBLIC}                                   {if(getPrint)printf("PUBLIC\n");numColuna+=yyleng; if(getYacc)return PUBLIC;}
{PARSEINT}                                 {if(getPrint)printf("PARSEINT\n");numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if(getYacc) return PARSEINT;}
{RESERVED}                                 {if(getPrint)printf("RESERVED(%s)\n",yytext);numColuna+=yyleng; if(getYacc) return RESERVED;}
{ID}                                       {if(getPrint)printf("ID(%s)\n",yytext); numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if(getYacc) return ID;}
{INTLIT}                                   {if(getPrint)printf("INTLIT(%s)\n",yytext);numColuna+=yyleng;yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if(getYacc)return INTLIT;}
{REALLIT}                                  {if(getPrint)printf("REALLIT(%s)\n",yytext);numColuna+=yyleng; yylval.token = criaToken(yytext, numLinha, numColuna-strlen(yytext)); if(getYacc) return REALLIT;}

<<EOF>>                                    {numColuna+=yyleng; return 0;}
{CR_LN}                                    {numColuna=1; numLinha++;}; 
{SPACE}                                    {numColuna+=yyleng;}
.                                          {if(getPrint || getPrintEronly)printf("Line %d, col %d: illegal character (%s)\n", numLinha, numColuna, yytext);numColuna+=yyleng;}


%%

int main(int argc,char* argv[]){
    if (argc == 1){
        //imprimir igual a flag -t (excepto a arvore de sintaxe abstrata) mais arvore de sintaxe abstrata anotada

        getYacc = true;
        getPrintEronly = true;
        tabelaGlobal = NULL;
        tabelaLocal = NULL;
        yyparse();

        if(numErrors == 0){
            errosSemantica == 0;
            criarTabelaSemantica(head);
            if (errosSemantica == 0){
                imprimirTabelaGlobal(tabelaGlobal);
                imprimirTabelasLocais(tabelaLocal);
                imprimirArvoreAnotada(head, 0);
            }
            limparTabelas(tabelaGlobal, tabelaLocal);
        }
    
    } else if (argc == 2){
        if (argc == 2 && strcmp(argv[1], "-e2") == 0){
        //imprimir erros do lex/flex e do yacc
        getPrint = false;
        getPrintEronly = true;
        getYacc = true;
        yyparse();
        }
        
        if (strcmp(argv[1], "-l") == 0){
            //imprimir tokens e erros do lex/flex
            getPrint=true;
            getPrintEronly = true;
            yylex();

        
        }else if(strcmp(argv[1], "-e1") == 0){
            //imprimir apenas erros do lex/flex
            getPrint=false;
            getPrintEronly=true;
            yylex();

        }else if(strcmp(argv[1],"-t")==0){
            //imprimir tokens e erros do yyac
            getYacc = true;
            getPrintEronly = true;
			yyparse();
			if(numErrors == 0){
				astreePrint(head, 0);
			}
		}else if(strcmp(argv[1],"-s")==0){
            //imprimir igual a flag -t (excepto a arvore de sintaxe abstrata) mais arvore de sintaxe abstrata anotada

            getYacc = true;
            getPrintEronly = true;
            tabelaGlobal = NULL;
			tabelaLocal = NULL;
			yyparse();

			if(numErrors == 0){
                criarTabelaSemantica(head);
                imprimirTabelaGlobal(tabelaGlobal);
                imprimirTabelasLocais(tabelaLocal);
                imprimirArvoreAnotada(head, 0);
                limparTabelas(tabelaGlobal, tabelaLocal);
			}
		}
    }

    astreeClean(head);
    yylex_destroy();

    return 0;
}

void yyerror (const char *s) {
	numErrors = 1;
	printf ("Line %d, col %d: %s: %s\n", numLinha, (int)(numColuna-(int)yyleng), s, yytext);
}

int yywrap() {
    return 1;
}
