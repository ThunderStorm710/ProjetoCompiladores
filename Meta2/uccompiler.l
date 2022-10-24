%{
/********************************
************AUTORES**************
*********************************
* Dylan Perdigão   -   2018233092
* Bruno Faria      -   2018295474
*********************************/

/*****************************
************INCLUDES**********
******************************/
    #include "y.tab.h"
/*****************************
************CONSTANTES********
******************************/
    #define false 0
    #define true 1
/*****************************
************FUNCOES**********
******************************/
    int yyparse(void);

/*****************************
************VARIAVEIS*********
******************************/
    int printLex=false;
    int printTree=false;
    int doYacc=false;
    int hasError=false;
    int line=1;
    int col=1;
    int commentBegin[2];
 /*****************************
 ************TOKENS************
 ******************************/
%}
ID          		[a-zA-Z_][a-zA-Z0-9_]*
INTLIT      		[0-9]+
CHRLIT              ([^\n\'\\]|\\n|\\t|\\\\|\\\'|\\\"|\\([0-7]{1,3}))
REALLIT     		[0-9]+"."[0-9]*([eE][+-]?([0-9]+))?|"."[0-9]+([eE][+-]?([0-9]+))?|[0-9]+"."?[0-9]*([eE][+-]?([0-9]+))?
CHAR			    char
ELSE			    else
WHILE			    while
IF			        if
INT			        int
SHORT		        short
DOUBLE		  	    double
RETURN		  	    return
VOID			    void
BITWISEAND		    "&"
BITWISEOR		    "|"
BITWISEXOR		    "^"
AND			        "&&"
ASSIGN		  	    "="
MUL			        "*"
COMMA		   	    ","
DIV			        "/"
EQ			        "=="
GE			        ">="
GT			        ">"
LBRACE		  	    "{"
LE			        "<="
LPAR			    "("
LT			        "<"
MINUS		    	"-"
MOD			        "%"
NE			        "!="
NOT			        "!"
OR			        "||"
PLUS			    "+"
RBRACE		  	    "}"
RPAR			    ")"
SEMI			    ";"
RESERVED            ("["|"]"|"++"|"--"|auto|break|case|const|continue|default|do|enum|extern|float|for|goto|inline|long|register|restrict|signed|sizeof|static|struct|switch|typedef|union|unsigned|volatile|_Bool|_Complex|_Imaginary)
LINE_COMMENT        "//".*
SPACE               (" "|"\t")
NEWLINE             ("\n"|"\r\n"|"\r")


%X                  COMMENT
/******************************
 *************RULES************
 ******************************/
%%
"/*"                    {BEGIN COMMENT;commentBegin[0]=line;commentBegin[1]=col;col+=yyleng;}
<COMMENT>{NEWLINE}      {line++;col=1;}
<COMMENT>.              {col+=yyleng;}
<COMMENT><<EOF>>        {BEGIN 0;printf("Line %i, col %i: unterminated comment\n",commentBegin[0],commentBegin[1]);}
<COMMENT>"*/"           {BEGIN 0;col+=yyleng;}

{LINE_COMMENT}          {col=1;}

{SPACE}                 {col+=yyleng;}
{NEWLINE}               {line++;col=1;}

{CHAR}				{if(printLex)printf("CHAR\n");col+=yyleng;                  if(doYacc){return CHAR;}}
{ELSE}				{if(printLex)printf("ELSE\n");col+=yyleng;                  if(doYacc){return ELSE;}}
{WHILE}				{if(printLex)printf("WHILE\n");col+=yyleng;                 if(doYacc){return WHILE;}}
{IF}				{if(printLex)printf("IF\n");col+=yyleng;                    if(doYacc){return IF;}}
{INT}				{if(printLex)printf("INT\n");col+=yyleng;                   if(doYacc){return INT;}}
{SHORT}			  	{if(printLex)printf("SHORT\n");col+=yyleng;                 if(doYacc){return SHORT;}}
{DOUBLE}			{if(printLex)printf("DOUBLE\n");col+=yyleng;                if(doYacc){return DOUBLE;}}
{RETURN}			{if(printLex)printf("RETURN\n");col+=yyleng;                if(doYacc){return RETURN;}}
{VOID}				{if(printLex)printf("VOID\n");col+=yyleng;                  if(doYacc){return VOID;}}
{RESERVED}          {if(printLex)printf("RESERVED(%s)\n",yytext);col+=yyleng;   if(doYacc){return RESERVED;}}

{BITWISEAND}	    {if(printLex)printf("BITWISEAND\n");col+=yyleng;            if(doYacc){return BITWISEAND;}}
{BITWISEOR}			{if(printLex)printf("BITWISEOR\n");col+=yyleng;             if(doYacc){return BITWISEOR;}}
{BITWISEXOR}	    {if(printLex)printf("BITWISEXOR\n");col+=yyleng;            if(doYacc){return BITWISEXOR;}}
{AND}				{if(printLex)printf("AND\n");col+=yyleng;                   if(doYacc){return AND;}}
{ASSIGN}			{if(printLex)printf("ASSIGN\n");col+=yyleng;                if(doYacc){return ASSIGN;}}
{MUL}				{if(printLex)printf("MUL\n");col+=yyleng;                   if(doYacc){return MUL;}}
{COMMA}			  	{if(printLex)printf("COMMA\n");col+=yyleng;                 if(doYacc){return COMMA;}}
{DIV}				{if(printLex)printf("DIV\n");col+=yyleng;                   if(doYacc){return DIV;}}
{EQ}				{if(printLex)printf("EQ\n");col+=yyleng;                    if(doYacc){return EQ;}}
{GE}				{if(printLex)printf("GE\n");col+=yyleng;                    if(doYacc){return GE;}}
{GT}				{if(printLex)printf("GT\n");col+=yyleng;                    if(doYacc){return GT;}}
{LBRACE}			{if(printLex)printf("LBRACE\n");col+=yyleng;                if(doYacc){return LBRACE;}}
{LE}				{if(printLex)printf("LE\n");col+=yyleng;                    if(doYacc){return LE;}}
{LPAR}			  	{if(printLex)printf("LPAR\n");col+=yyleng;                  if(doYacc){return LPAR;}}
{LT}				{if(printLex)printf("LT\n");col+=yyleng;                    if(doYacc){return LT;}}
{MINUS}			  	{if(printLex)printf("MINUS\n");col+=yyleng;                 if(doYacc){return MINUS;}}
{MOD}				{if(printLex)printf("MOD\n");col+=yyleng;                   if(doYacc){return MOD;}}
{NE}			 	{if(printLex)printf("NE\n");col+=yyleng;                    if(doYacc){return NE;}}
{NOT}				{if(printLex)printf("NOT\n");col+=yyleng;                   if(doYacc){return NOT;}}
{OR}				{if(printLex)printf("OR\n");col+=yyleng;                    if(doYacc){return OR;}}
{PLUS}			  	{if(printLex)printf("PLUS\n");col+=yyleng;                  if(doYacc){return PLUS;}}
{RBRACE}			{if(printLex)printf("RBRACE\n");col+=yyleng;                if(doYacc){return RBRACE;}}
{RPAR}			 	{if(printLex)printf("RPAR\n");col+=yyleng;                  if(doYacc){return RPAR;}}
{SEMI}				{if(printLex)printf("SEMI\n");col+=yyleng;                  if(doYacc){return SEMI;}}

'{CHRLIT}'          {if(printLex)printf("CHRLIT(%s)\n",yytext);col+=yyleng;     if(doYacc){yylval.id = strdup(yytext);return CHRLIT;}}
'([^\n\'\\]|\\.)*\\?{NEWLINE}   {printf("Line %i, col %i: unterminated char constant\n",line,col);col=1;line++;         hasError=true;}
'([^\n\'\\]|\\.)*'              {printf("Line %i, col %i: invalid char constant (%s)\n",line,col,yytext);col+=yyleng;   hasError=true;}

{ID}				{if(printLex)printf("ID(%s)\n",yytext);col+=yyleng;         if(doYacc){yylval.id = strdup(yytext);return ID;}}
{INTLIT}			{if(printLex)printf("INTLIT(%s)\n",yytext);col+=yyleng;     if(doYacc){yylval.id = strdup(yytext);return INTLIT;}} /*yylval.intlit = atoi(yytext)*/
{REALLIT}           {if(printLex)printf("REALLIT(%s)\n",yytext);col+=yyleng;    if(doYacc){yylval.id = strdup(yytext);return REALLIT;}} /*yylval.reallit = atof(yytext)*/

.                               {printf("Line %i, col %i: illegal character (%s)\n",line,col,yytext);col+=yyleng;       hasError=true;}
%%

int main(int argc,char* argv[]){
    switch(argc){
        case 1:
            //erros do lex e yacc
            printLex=false;
            printTree=false;
            doYacc=true;
            yyparse();
            break;
        case 2:
            //tokens e erros do lex
            if (strcmp(argv[1], "-l") == 0){
                printLex=true;
                doYacc=false;
                yylex();
            //erros do lex
            }else if(strcmp(argv[1], "-e1") == 0){
                printLex=false;
                doYacc=false;
                yylex();
            //tokens e erros do yyac
            }else if (strcmp(argv[1], "-t") == 0){
                printTree=true;
                doYacc=true;
                yyparse();
            //erros do yyac
            }else if(strcmp(argv[1], "-e2") == 0){
                printLex=false;
                printTree=false;
                doYacc=true;
                yyparse();
            }
            break;
    }
    return 0;
}

int yywrap(){
    return 1;
}

void yyerror ( const char *s) {
    switch(strlen(yytext)){
        case 0:
            printf("Line %d, col %d: %s: %s\n", line,col,s, yytext);
            break;
        default:
            printf("Line %d, col %d: %s: %s\n", line,(int)(col-yyleng),s, yytext);
            break;
    }

}
