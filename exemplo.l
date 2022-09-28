%{
#include <ctype.h>
int numeroCapitulo = 0; 
int numeroSeccao = 0;
int numeroEnumerate = 0;

%}
%X ESTADO_DOC ESTADO_ITEM ESTADO_ENUM  ESTADO_CHAPTER ESTADO_TITLE ESTADO_SECCAO
%%
"\\begin{document}" {BEGIN ESTADO_DOC;}
. ; //caso seja codigo Java
\n ; //nao faz nada
<ESTADO_DOC>"\end{document}".* {BEGIN 0; numeroCapitulo = 0; numeroEnumerate = 0; numeroSeccao = 0;}

<ESTADO_DOC>\\"begin{itemize}" {BEGIN ESTADO_ITEM;}
<ESTADO_DOC>"\\begin{enumerate}" {BEGIN ESTADO_ENUM;}

<ESTADO_DOC>"\\title{"                                                      {BEGIN ESTADO_TITLE;} //<ESTADO_DOC>"\\title{"[^}]*"}" {for (int i = 7; i < yyleng-1; i++){printf("%c", toupper(yytext[i]));} printf("\n");}
<ESTADO_DOC>"\\chapter{"                                                    {BEGIN ESTADO_CHAPTER;printf("%d.  ",++numeroCapitulo);} //<ESTADO_DOC>"\\title{"[^}]*"}" {for (int i = 7; i < yyleng-1; i++){printf("%c", toupper(yytext[i]));} printf("\n");}
<ESTADO_DOC>"\section{"                                                     {BEGIN ESTADO_SECCAO;printf("\n%d.%d.   %s", numeroCapitulo, ++numeroSeccao, &yytext[8]);}
<ESTADO_DOC>"\\"                                                            ;
<ESTADO_DOC>.                                                               ECHO;


<ESTADO_TITLE>[a-z]                                                         {printf("%c", toupper(yytext[0]));}
<ESTADO_TITLE>"}"                                                           {BEGIN ESTADO_DOC;}
<ESTADO_TITLE>[ \t\n]+                                                      {printf(" ");}
<ESTADO_TITLE>.                                                             ECHO;


<ESTADO_SECCAO>"}"                                                          {BEGIN ESTADO_DOC;}
<ESTADO_SECCAO>[ \t\n]+                                                     {printf(" ");}
<ESTADO_SECCAO>.                                                            ECHO;


<ESTADO_CHAPTER>"}"                                                         {BEGIN ESTADO_DOC;}
<ESTADO_CHAPTER>[ \t\n]+                                                    {printf(" ");}
<ESTADO_CHAPTER>.                                                           ECHO;


<ESTADO_ITEM>"\\item"                                                        {printf("\n.");}
<ESTADO_ITEM>"\\end{itemize}"                                                {BEGIN ESTADO_DOC;}
<ESTADO_ITEM>[a-z]                                                           {printf("%c", yytext[0]);}
<ESTADO_ITEM>[ \t\n]+                                                        {printf(" ");}



<ESTADO_ENUM>[a-z]                                                           {printf("%c", yytext[0]);}
<ESTADO_ENUM>[ \t\n]+                                                        {printf(" ");}
<ESTADO_ENUM>"\\item"                                                        {printf("\n%d-", ++numeroEnumerate);}
<ESTADO_ENUM>"\\end{enumerate}".*                                            {BEGIN ESTADO_DOC; printf("\n"); numeroEnumerate = 0;}

%%
int main()
{
yylex(); return 0;
}
int yywrap() {
return 1;
}



