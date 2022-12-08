#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

/* AS TREE */

/*TOKEN struct atributes*/
typedef struct token{
    char *valor;
    int linha, coluna;
} token;

/*NODE struct atributes*/
typedef struct node{
    struct node *brother;
    struct node *child;
    char *Type;
    char *value;
    int line, column;
    char *anoted;
    int numeroParametros;
    int to_anote;
    struct _param_list *params;
} node;

/*Declared functions*/
void astreePrint(node *Node, int numPontos);

void astreeClean(node *Node);

token *criaToken(char *valor, int linha, int coluna);

void libertaToken(token *t);

node *criaNode(char *Type, char *value, int line, int column);

int countBlock(node *Node);

void joinType(node *nodeType, node *nodeX);

void addBrother(node *Node, node *newNodeBrother);

void addChild(node *node1, node *node2);


typedef struct _var_list {
    int line, colunm;
    char *name;
    char *type;
    int flag; //indica se é param ou não (1 se for) (2 se nao for para imprimir)
    int function; //indica se é funçao ou nao
    int numeroParametros; //se for function tem o numero de parametros
    struct _param_list *parametroTipos;
    struct _var_list *next;
} var_list;

typedef struct _param_list {
    int line, colunm;
    char *id;
    char *type;
    struct _param_list *next;
} param_list;

typedef struct _sym_table {
    char *tableName;
    char *tableType;
    struct _var_list *vars;
    struct _param_list *params;
    struct _sym_table *next;
} sym_table;

typedef struct _strlit_list {
    char *value;
    char *type;
    struct _strlit_list *next;
} strlit_list;

extern sym_table *tabelaGlobal, *tabelaLocal;
extern int errosSemantica;

void limparParametros(param_list *param);

void limparVariaveis(var_list *var);

void limparTabLocais(sym_table *local);

void limparTabelas(sym_table *global, sym_table *local);

void criarTabelaSemantica(node *atual);

void adicionarATabelaLocal(sym_table *tabelaLocal, sym_table *element);

void imprimirTabelaGlobal(sym_table *atual);

void imprimirTabelasLocais(sym_table *atual);

char *alterarTipo(char *nodeType);

var_list *criarVariavel(char *name, char *type);

void adicionarVariavel(var_list *varList, var_list *new);

param_list *CriarParametroTipo(char *type, char *id);

void adicionarParametro(param_list *paramList, param_list *new);

sym_table *criarTabela(char *name, char *type);

char *procurarVariavel(param_list *params, char *var_name);

int procurarFuncao(sym_table *table_global, param_list *aux_parametroTipos, int count_params, char *name);

void anotarArvore(sym_table *table_global, sym_table *table_local, node *atual);

int isExpressao(char *nodeType);

void imprimirArvoreAnotada(node *current, int n);

char *procurarTipoVariavelTabela(sym_table *table, char *var_name);

char *procuraTipoVariavel(sym_table *table_global, sym_table *table_local, char *var_name);
