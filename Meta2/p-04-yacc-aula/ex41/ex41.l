%{
#include "y.tab.h"
%}
%%
"varlist"               {return VARLIST;}
"sqrt"                  {return SQRT;}
[0-9]+(\.[0-9]+)?       {yylval.value=atof(yytext); return NUMBER;}
[a-zA-Z][a-zA-Z0-9_]*   {yylval.id=(char*)strdup(yytext);return VAR;}  
[ \t]                   {;}
"++"                    {return PLUSPLUS;}
"--"                    {return MINUSMINUS;}
\n|.                    {return yytext[0];}
%%
int yywrap() {
    return 1;
}

void yyerror (char *s)
{
printf ("%s\n", s);
}

int main()
{
yyparse();
return 0;
}


