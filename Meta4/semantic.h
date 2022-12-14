#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <limits.h>

typedef struct token{
    char *valor;
    int linha, coluna;
} token;

typedef struct node{
    struct node *brother;
    struct node *child;
    char *tipoNo;
    char *valor;
    int linha, coluna;
    char *anotacao;
    int numeroParametros;
    int aAnotar;
    struct _listaParametros *params;
} node;

void imprimirArvore(node *Node, int numPontos);

void limparArvore(node *Node);

token *criaToken(char *valor, int linha, int coluna);

void libertaToken(token *t);

node *criaNode(char *tipoNo, char *valor, int linha, int coluna);

int countBlock(node *Node);

void joinType(node *nodeType, node *nodeX);

void addBrother(node *Node, node *newNodeBrother);

void addChild(node *node1, node *node2);

typedef struct _listaVariaveis {
    int linha, coluna;
    char *nome;
    char *tipo;
    int isParametro; //0-não é parametro 1-é parametro 2-é parametro mas não imprimir
    bool isFunction;
    int numeroParametros; //se for funcao tem o numero de parametros
    struct _listaParametros *parametroTipos;
    struct _listaVariaveis *seguinte;
} listaVariaveis;

typedef struct _listaParametros {
    int linha, coluna;
    char *id;
    char *tipo;
    struct _listaParametros *seguinte;
} listaParametros;

typedef struct _tabelaSimbolos {
    char *tableName;
    char *tableType;
    struct _listaVariaveis *vars;
    struct _listaParametros *params;
    struct _tabelaSimbolos *seguinte;
} tabelaSimbolos;

extern tabelaSimbolos *tabelaGlobal, *tabelaLocal;
extern int errosSemantica;

void limparParametros(listaParametros *param);

void limparVariaveis(listaVariaveis *var);

void limparTabLocais(tabelaSimbolos *local);

void limparTabelas(tabelaSimbolos *global, tabelaSimbolos *local);

void criarTabelaSemantica(node *atual);

void adicionarATabelaLocal(tabelaSimbolos *tabelaLocal, tabelaSimbolos *element);

void imprimirTabelaGlobal(tabelaSimbolos *atual);

void imprimirTabelasLocais(tabelaSimbolos *atual);

char *alterarTipo(char *nodeType);

listaVariaveis *criarVariavel(char *nome, char *tipo);

void adicionarVariavel(listaVariaveis *varList, listaVariaveis *new);

listaParametros *CriarParametroTipo(char *tipo, char *id);

void adicionarParametro(listaParametros *paramList, listaParametros *new);

tabelaSimbolos *criarTabela(char *nome, char *tipo);

char *procurarVariavel(listaParametros *params, char *var_name);

int procurarFuncao(tabelaSimbolos *table_global, listaParametros *backUp_parametroTipos, int count_params, char *nome);

void anotarArvore(tabelaSimbolos *table_global, tabelaSimbolos *table_local, node *atual);

int isExpressao(char *nodeType);

void imprimirArvoreAnotada(node *current, int n);

char *procurarTipoVariavelTabela(tabelaSimbolos *table, char *var_name);

char *procuraTipoVariavel(tabelaSimbolos *table_global, tabelaSimbolos *table_local, char *var_name);

typedef struct _strlit_list{
    char *valor;
    char *tipo;
    struct _strlit_list *seguinte;
} strlit_list;

void limpaLista(strlit_list *variavel);
void acertarStr(char *strlit);
void print_stringlit(strlit_list *stringlit_List);
strlit_list *criarStr(char *valor, char *tipo);
void add_strlit(strlit_list *strList, strlit_list *new);
void print_declaracao_var_func_global(node *atual);
void gera_codigo_llvm(node *atual);
void criarHeaderInicial(node *atual);
void gera_llvm(node *atual);
void fazer_llvm_rec(node *atual);
char *verify_its_global(char *nome);
void tratarVarDecl(char *tipo, char *nome);
void acertarReal(char *valor);
void acertarDec(char *valor);
void tratarPrint(node *atual);
void tratarDec(node *atual);
void tratarBool(node *atual);
void tratarAtr(node *atual);
void tratarId(node *atual);
void tratarMenos(node *atual);
void tratarParse(node *atual);
void tratarReal(node *atual);
void tratarLen(node *atual);
void tratarAdd(node *atual, int var1, int var2);
void tratarSub(node *atual, int var1, int var2);
void tratarMul(node *atual, int var1, int var2);
void tratarDiv(node *atual, int var1, int var2);
void tratarMod(node *atual, int var1, int var2);
void tratarNot(node *atual, int var1);
void tratarAnd(node *atual);
void tratarOr(node *atual);
void tratarIgual(node *atual, int var1, int var2);
void tratarDif(node *atual, int var1, int var2);
void tratarMenor(node *atual, int var1, int var2);
void tratarMaior(node *atual, int var1, int var2);
void tratarMenorIgual(node *atual, int var1, int var2);
void tratarMaiorIgual(node *atual, int var1, int var2);
void tratarIf(node *atual);
void tratarWhile(node *atual);
void tratarReturn(node *atual);
void tratarChamada(node *atual);
