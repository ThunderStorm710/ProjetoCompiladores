#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

/* SEMANTIC */

typedef struct _var_list {
    int line, colunm;
    char *name;
    char *type;
    int flag; //indica se é param ou não (1 se for) (2 se nao for para imprimir)
    int function; //indica se é funçao ou nao
    int n_params; //se for function tem o numero de parametros
    struct _param_list *paramTypes;
    struct _var_list *next;
} var_list;

typedef struct _param_list {
    int line, colunm;
    char *id;
    char *type;
    struct _param_list *next;
} param_list;

typedef struct _sym_table{
    char *tableName;
    char *tableType;
    struct _var_list *vars;
    struct _param_list *params;
    struct _sym_table *next;
} sym_table;

typedef struct token{
    char *value;
    int line, colunm;
} token;

typedef struct _strlit_list{
    char *value;
    char *type;
    struct _strlit_list *next;
} strlit_list;

extern sym_table *global_table, *local_table;
extern int nErrorsSemantic;

/* AST */

typedef struct node{
    struct node *children;
    struct node *brother;
    char *nodeType;
    char *anoted;
    char *value;
    int n_params;
    int to_anote;
    struct _param_list *params;
    int line, colunm;
} node;

token* createToken(char *value, int line, int colunm);
void freeToken(token *aux);
int itsTerminal(char *nodeType);
node* createNode(char* nodeType, char *value, int line, int colunm);
void insertBrother(node *b1, node *b2);
void insertChildren(node *f, node *s);
void insertBrother(node *f, node *b);
void printNode(node *current);
int addBlock(node *n);
void atributeType(node *type, node *varDecl);
void printAST(node* atual, int n);
void clearAST(node* atual);
void removeNULLs(node *ant, node* atual);

/* SEMANTIC FUNCS */
void clearParams(param_list *param);
void clearVars(var_list *var);
void clearLocalTables(sym_table *local);
void clearTables(sym_table *global, sym_table *local);
void create_semantic_table(node *atual);
void add_to_local_table(sym_table *local_table, sym_table *element);
void print_table_global(sym_table *atual);
void print_tables_local(sym_table *atual);
char *changeType(char *nodeType);
var_list *create_var(char *name, char *type);
void add_var(var_list *varList, var_list *new);
param_list *create_param_type(char *type, char *id);
void add_param(param_list *paramList, param_list *new);
sym_table* create_table(char *name, char *type);

char *search_var_exists(param_list *params, char *var_name);
int search_function_exists(sym_table *table_global, param_list *aux_paramTypes, int count_params, char *name);
void anote_ast(sym_table *table_global, sym_table *table_local, node *atual);
int itsExpression(char *nodeType);
void printAnotedAST(node *current, int n);
char *search_type_var_in_table(sym_table *table, char *var_name);
char *search_type_var(sym_table *table_global, sym_table *table_local, char *var_name);

/* LLVM */
void clearList(strlit_list *var);
void change_strlit(char *strlit);
void print_strlit(strlit_list *strList);
strlit_list *create_strlit(char *value, char *type);
void add_strlit(strlit_list *strList, strlit_list *new);
void declare_all_strlit(node *atual);
void print_global_declarations(node *atual);
void generate_llvm(node *atual);
void create_header(node *atual);
void create_llvm(node *atual);
void code_llvm(node *atual);
char *verify_its_global(char *name);
void function_varDecl(char *type, char *name);
void change_reallit(char *value);
void change_declit(char *value);
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