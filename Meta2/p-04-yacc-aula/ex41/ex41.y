%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "symtab.h"
#define NSYMS 100

symtab tab[NSYMS];

symtab *symlook(char *varname);
void varlist();
int yylex (void);
void yyerror(char* s);
%}

%token <id> VAR 
%token <value> NUMBER
%type  <value> expression

%token PLUSPLUS MINUSMINUS VARLIST SQRT

%union{
  double value;
  char* id;
}

%left '+' '-'
%left '*' '/'
%nonassoc PLUSPLUS MINUSMINUS

%%
statement: expression '\n'            {printf("%lf\n", $1);}
	 | statement expression '\n'  {printf("%lf\n", $2);}
         | assignment '\n'            {;}
         | statement assignment '\n'  {;}
         | VARLIST '\n'               {varlist();}
         | statement VARLIST '\n'     {varlist();}
	 ;

assignment: VAR '=' expression {symlook($1)->value = $3;}
 
expression: VAR	                        {$$=symlook($1)->value;}
          | NUMBER                      {$$=$1;}
          | expression '+' expression   {$$=$1+$3;}
          | expression '-' expression   {$$=$1-$3;}
          | expression '*' expression   {$$=$1*$3;}
          | expression '/' expression   {$$=$1/$3;}
          | '(' expression ')'          {$$=$2;}
          | '-' expression              {$$=-$2;}
          | '+' expression              {$$=$2;}
          | PLUSPLUS VAR                {$$=++(symlook($2)->value);}
          | MINUSMINUS VAR              {$$=--(symlook($2)->value);}
          | VAR PLUSPLUS                {$$=(symlook($1)->value)++;}
          | VAR MINUSMINUS              {$$=(symlook($1)->value)--;}
          | SQRT '(' expression ')'     {$$=sqrt($3);}
	  ;
%%

symtab *symlook(char *varname) {
    int i;
    for(i=0; i<NSYMS; i++) {
        if(tab[i].name && strcmp(varname, tab[i].name)==0)   
            return &tab[i];
        if(!tab[i].name) {
            tab[i].name=varname;
            return &tab[i];
        }
    }
    yyerror("variaveis a mais...");
    exit(1);
}

void varlist() {
  for (int i = 0; i < NSYMS; i++) {
    if (tab[i].name) {
      printf("%s = %lf\n", tab[i].name, tab[i].value);
    }
  }
}
