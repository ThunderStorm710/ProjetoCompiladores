%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
STR                                                    ([^\\(\\|[^(n|t|f|r|\n|\t|\f|\r)])])+
CR_LN                                                  (\n|\r\n|\r)
RESERVED                                               ("System"|"Integer"|"null"|"++"|"--"|"break")
ESCAPE                                                 "\\"[^(n|t|f|r)]

%X COMENTARIO COMENTARIO_SIMPLES STRING STRING_AFTER_ERROR

/****************************************************** REGRAS *********************************************************************/

%%
"/*"                                                   {BEGIN COMENTARIO;}
<COMENTARIO>{CR_LN}                                    ;
<COMENTARIO>.                                          ;
<COMENTARIO><<EOF>>                                    {BEGIN 0;printf("unterminated comment\n");}
<COMENTARIO>"*/"                                       {BEGIN 0;}

"//"                                                   {BEGIN COMENTARIO_SIMPLES;}
<COMENTARIO_SIMPLES>{CR_LN}                            {BEGIN 0;}
<COMENTARIO_SIMPLES>.                                  ;

"\""                                                   {BEGIN STRING;}
<STRING>({STR})?"\\"({SPACE})?                         {BEGIN STRING_AFTER_ERROR; printf("invalid escape sequence (%c)\n",yytext[yyleng-2]);}
<STRING>({STR})?"\\"[^ntfr]                            {BEGIN STRING_AFTER_ERROR; printf("invalid escape sequence (%c%c)\n", yytext[yyleng-2],yytext[yyleng-1]);}

<STRING><<EOF>>                                        {BEGIN 0; printf("unterminated string literal\n");}
<STRING>{STR}?{CR_LN}                                  {BEGIN 0; printf("unterminated string literal\n");}
<STRING>{STR}?"\""                                     {BEGIN 0; printf("STRLIT(\"%s)\n",yytext);}

<STRING_AFTER_ERROR>"\\"[^ntfr]?                       {printf("invalid escape sequence (%c%c)\n", yytext[yyleng-2],yytext[yyleng-1]);}
<STRING_AFTER_ERROR>{CR_LN}                            {BEGIN 0;printf("unterminated string literal\n");}
<STRING_AFTER_ERROR>[^\"]                              ;
<STRING_AFTER_ERROR>\"                                 {BEGIN 0;}



{CLASS}                                                {printf("CLASS\n");}
{COMMA}                                                {printf("COMMA\n");}
{MINUS}                                                {printf("MINUS\n");}
{LT}                                                   {printf("LT\n");}
{LSQ}                                                  {printf("LSQ\n");}
{LPAR}                                                 {printf("LPAR\n");}
{LE}                                                   {printf("LE\n");}
{LBRACE}                                               {printf("LBRACE\n");}
{GT}                                                   {printf("GT\n");}
{GE}                                                   {printf("GE");}
{DIV}                                                  {printf("DIV\n");}
{STAR}                                                 {printf("STAR\n");}
{EQ}                                                   {printf("EQ\n");}
{ASSIGN}                                               {printf("ASSIGN\n");}
{AND}                                                  {printf("AND\n");}
{SEMICOLON}                                            {printf("SEMICOLON\n");}
{RSQ}                                                  {printf("RSQ\n");}
{RPAR}                                                 {printf("RPAR\n");}
{RBRACE}                                               {printf("RBRACE\n");}
{PLUS}                                                 {printf("PLUS\n");}
{OR}                                                   {printf("OR\n");}
{NOT}                                                  {printf("NOT\n");}
{NE}                                                   {printf("NE\n");}
{MOD}                                                  {printf("MOD\n");}
{XOR}                                                  {printf("XOR\n");}
{RSHIFT}                                               {printf("RSHIFT\n");}
{LSHIFT}                                               {printf("LSHIFT\n");}
{ARROW}                                                {printf("ARROW\n");}
{BOOL}                                                 {printf("BOOL\n");}
{INT}                                                  {printf("INT\n");}
{IF}                                                   {printf("IF\n");}
{ELSE}                                                 {printf("ELSE\n");}
{DOUBLE}                                               {printf("DOUBLE\n");}
{DOTLENGTH}                                            {printf("DOTLENGTH\n");}
{PRINT}                                                {printf("PRINT\n");}
{BOOLLIT}                                              {printf("BOOLLIT\n");}
{WHILE}                                                {printf("WHILE\n");}
{VOID}                                                 {printf("VOID\n");}
{STRING}                                               {printf("STRING\n");}
{STATIC}                                               {printf("STATIC\n");}
{RETURN}                                               {printf("RETURN\n");}
{PUBLIC}                                               {printf("PUBLIC\n");}
{PARSEINT}                                             {printf("PARSEINT\n");}

{RESERVED}                                             {printf("RESERVED(%s)\n",yytext);}
{ID}                                                   {printf("ID(%s)\n",yytext);}
{INTLIT}                                               {printf("INTLIT(%s)\n",yytext);}
{REALLIT}                                              {printf("REALLIT(%s)\n",yytext);}
{SPACE}                                                ;

{ESCAPE}                                               {printf("invalid escape sequence (%c%c)\n", yytext[yyleng-2],yytext[yyleng-1]);}
.                                                      {printf("illegal character (%s)\n",yytext);}


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
