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
    char *valor;
    int linha, coluna;
    char *anotacao;
    int numeroParametros;
    int to_anote;
    struct _param_list *params;
} node;

/*Declared functions*/
void imprimirArvore(node *Node, int numPontos);

void limparArvore(node *Node);

token *criaToken(char *valor, int linha, int coluna);

void libertaToken(token *t);

node *criaNode(char *Type, char *valor, int linha, int coluna);

int countBlock(node *Node);

void joinType(node *nodeType, node *nodeX);

void addBrother(node *Node, node *newNodeBrother);

void addChild(node *node1, node *node2);

typedef struct _var_list {
    int linha, coluna;
    char *name;
    char *type;
    int flag; //indica se é param ou não (1 se for) (2 se nao for para imprimir)
    int function; //indica se é funçao ou nao
    int numeroParametros; //se for function tem o numero de parametros
    struct _param_list *parametroTipos;
    struct _var_list *next;
} var_list;

typedef struct _param_list {
    int linha, coluna;
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

typedef struct _strlit_list{
    char *valor;
    char *type;
    struct _strlit_list *next;
} strlit_list;

/* LLVM */
void clearList(strlit_list *var);
void change_strlit(char *strlit);
void print_strlit(strlit_list *strList);
strlit_list *create_strlit(char *valor, char *type);
void add_strlit(strlit_list *strList, strlit_list *new);
void declare_all_strlit(node *atual);
void print_global_declarations(node *atual);
void generate_llvm(node *atual);
void create_header(node *atual);
void create_llvm(node *atual);
void code_llvm(node *atual);
char *verify_its_global(char *name);
void function_varDecl(char *type, char *name);
void change_reallit(char *valor);
void change_declit(char *valor);
void function_print(node *atual);
void function_decLit(node *atual);
void function_boolLit(node *atual);
void function_strLit(node *atual);
void function_assign(node *atual);
void function_id(node *atual);
void function_minus(node *atual);
void function_parseArgs(node *atual);
void function_realLit(node *atual);
void function_length(node *atual);
void function_add(node *atual, int var1, int var2);
void function_sub(node *atual, int var1, int var2);
void function_mul(node *atual, int var1, int var2);
void function_div(node *atual, int var1, int var2);
void function_mod(node *atual, int var1, int var2);
void function_not(node *atual, int var1);
void function_and(node *atual);
void function_or(node *atual);
void function_eq(node *atual, int var1, int var2);
void function_neq(node *atual, int var1, int var2);
void function_lt(node *atual, int var1, int var2);
void function_gt(node *atual, int var1, int var2);
void function_leq(node *atual, int var1, int var2);
void function_geq(node *atual, int var1, int var2);
void function_if(node *atual);
void function_while(node *atual);
void function_dowhile(node *atual);
void function_return(node *atual);
void function_call(node *atual);
