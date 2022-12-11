#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdarg.h>
#include <float.h>
#include "semantic.h"

/* -------- TOKEN --------- */

token *criaToken(char *valor, int linha, int coluna) {
    token *novoToken = (token *) malloc(sizeof(token));
    if (valor != NULL) {
        novoToken->valor = (char *) strdup(valor);
    } else {
        novoToken->valor = NULL;
    }
    novoToken->linha = linha;
    novoToken->coluna = coluna;
    return novoToken;
}

void libertaToken(token *t) {
    if (t->valor != NULL) {
        free(t->valor);
        t->valor = NULL;
    }
    free(t);
    t = NULL;
}

/* ++++++++++ AS TREE ++++++++++ */

node *criaNode(char *Type, char *valor, int linha, int coluna) {
    node *novoNo = (node *) malloc(sizeof(node));
    novoNo->Type = (char *) strdup(Type);
    if (valor != NULL) {
        novoNo->valor = (char *) strdup(valor);
    } else {
        novoNo->valor = NULL;
    }
    novoNo->anotacao = NULL;
    novoNo->params = NULL;
    novoNo->numeroParametros = -1;
    novoNo->aAnotar = 1;
    novoNo->linha = linha;
    novoNo->coluna = coluna;
    novoNo->child = NULL;
    novoNo->brother = NULL;

    return novoNo;
}

void addChild(node *node1, node *node2) {
    if (node1 == NULL || node2 == NULL) {
        return;
    }

    node1->child = node2;
}

void addBrother(node *Node, node *novoNoBrother) {
    if (Node == NULL || novoNoBrother == NULL) {
        return;
    }

    node *noAux = Node;
    while (noAux->brother != NULL) {
        noAux = noAux->brother;
    }

    noAux->brother = novoNoBrother;
}

int countBlock(node *Node) {
    int count = 0;
    if (Node == NULL) {
        return count;
    }

    if (Node->brother != NULL) {
        count = 1;
    }

    while (Node->brother != NULL) {
        if (strcmp((Node->brother)->Type, "NULL") != 0) {
            count++;
        }
        Node = Node->brother;
    }

    return count;
}

void joinType(node *nodeType, node *nodeX) {
    node *novoNo = NULL;
    node *noAux = nodeX;

    while (noAux != NULL) {
        novoNo = criaNode(nodeType->Type, NULL, 0, 0);
        novoNo->brother = noAux->child;
        noAux->child = novoNo;
        noAux = noAux->brother;
    }
}

void imprimirArvore(node *Node, int numPontos) {

    if (Node == NULL) {
        return;
    }

    if (strcmp(Node->Type, "NULL") == 0) {
        imprimirArvore(Node->brother, numPontos);
        return;
    }

    int i;
    if (strcmp(Node->Type, "NULL") != 0) {
        for (i = 0; i < numPontos; i++) {
            printf("..");
        }

        if (Node->valor != NULL) {
            printf("%s(%s)\n", Node->Type, Node->valor);
        } else {
            printf("%s\n", Node->Type);
        }
    }

    imprimirArvore(Node->child, numPontos + 1);
    imprimirArvore(Node->brother, numPontos);
}

void limparArvore(node *Node) {
    if (Node == NULL) {
        return;
    }

    if (Node->valor != NULL) {
        free(Node->valor);
        Node->valor = NULL;
    }

    if (Node->Type != NULL) {
        free(Node->Type);
        Node->Type = NULL;
    }

    limparArvore(Node->child);
    Node->child = NULL;
    limparArvore(Node->brother);
    Node->brother = NULL;

    free(Node);
    Node = NULL;
}

/* ------------------ SEMANTICS ---------------------- */
/* TABLES */
void limparParametros(param_list *param) {
    if (param == NULL) {
        return;
    }

    if (param->type != NULL) {
        free(param->type);
        param->type = NULL;
    }
    if (param->id != NULL) {
        free(param->id);
        param->id = NULL;
    }

    limparParametros(param->next);

    free(param);
    param = NULL;
}

void limparVariaveis(var_list *var) {
    if (var == NULL) {
        return;
    }

    if (var->type != NULL) {
        free(var->type);
        var->type = NULL;
    }
    if (var->name != NULL) {
        free(var->name);
        var->name = NULL;
    }

    limparParametros(var->parametroTipos);
    limparVariaveis(var->next);

    free(var);
    var = NULL;
}

void limparTabLocais(sym_table *local) {
    if (local == NULL) {
        return;
    }

    if (local->tableName != NULL) {
        free(local->tableName);
        local->tableName = NULL;
    }
    if (local->tableType != NULL) {
        free(local->tableType);
        local->tableType = NULL;
    }

    if (local->params != NULL) {
        limparParametros(local->params->next);
        if (local->params->type != NULL) {
            free(local->params->type);
            local->params->type = NULL;
        }
        if (local->params->id != NULL) {
            free(local->params->id);
            local->params->id = NULL;
        }
        free(local->params);
        local->params = NULL;
    }
    if (local->vars != NULL) {
        limparVariaveis(local->vars->next);
        if (local->vars->type != NULL) {
            free(local->vars->type);
            local->vars->type = NULL;
        }
        if (local->vars->name != NULL) {
            free(local->vars->name);
            local->vars->name = NULL;
        }
        free(local->vars);
        local->vars = NULL;
    }

    limparTabLocais(local->next);

    free(local);
    local = NULL;
}

void limparTabelas(sym_table *global, sym_table *local) {
    if (global != NULL) {
        if (global->tableName != NULL) {
            free(global->tableName);
            global->tableName = NULL;
        }
        if (global->tableType != NULL) {
            free(global->tableType);
            global->tableType = NULL;
        }

        limparVariaveis(global->vars);

        free(global);
        global = NULL;
    }

    if (local != NULL) {
        limparTabLocais(local);
    }
}

void imprimirTabelaGlobal(sym_table *atual) {
    var_list *auxV = atual->vars;
    param_list *auxP;

    printf("===== %s %s Symbol Table =====\n", atual->tableType, atual->tableName);
    while (auxV != NULL) {
        if (auxV->function == 1) {
            auxP = auxV->parametroTipos;
            printf("%s\t(", auxV->name);
            while (auxP != NULL) {
                printf("%s", auxP->type);
                if (auxP->next != NULL) {
                    printf(",");
                }
                auxP = auxP->next;
            }
            printf(")\t%s", auxV->type);

        } else {
            printf("%s\t\t%s", auxV->name, auxV->type);
        }

        printf("\n");

        auxV = auxV->next;
    }
    printf("\n");
}

void imprimirTabelasLocais(sym_table *atual) {
    sym_table *aux = atual;
    var_list *auxV;
    param_list *auxP;

    while (aux != NULL) {
        auxV = aux->vars;
        auxP = aux->params;
        if (auxP != NULL) {
            printf("===== %s %s(", aux->tableType, aux->tableName);
            while (auxP != NULL) {
                printf("%s", auxP->type);
                if (auxP->next != NULL) {
                    printf(",");
                }
                auxP = auxP->next;
            }
            printf(") Symbol Table =====\n");

        } else {
            printf("===== %s %s() Symbol Table =====\n", aux->tableType, aux->tableName);
        }
        while (auxV != NULL) {
            if (auxV->flag == 2) {
                //dont print, its repeated

            } else if (auxV->flag == 1) {
                printf("%s\t\t%s\t%s\n", auxV->name, auxV->type, "param");

            } else {
                printf("%s\t\t%s\n", auxV->name, auxV->type);
            }

            auxV = auxV->next;
        }

        printf("\n");

        aux = aux->next;
    }
}

void adicionarATabelaLocal(sym_table *table, sym_table *element) {
    sym_table *aux = table;

    if (aux == NULL) {
        table = element;
        return;
    }

    while (aux->next != NULL) {
        aux = aux->next;
    }

    aux->next = element;
}

param_list *CriarParametroTipo(char *type, char *id) {
    param_list *new = (param_list *) malloc(sizeof(param_list));
    new->type = (char *) strdup(type);
    new->id = (char *) strdup(id);
    new->next = NULL;
    return new;
}

void adicionarParametro(param_list *paramList, param_list *new) {
    param_list *aux = paramList;

    if (aux == NULL) {
        paramList = new;
        return;
    }

    while (aux->next != NULL) {
        aux = aux->next;
    }

    aux->next = new;
}

var_list *criarVariavel(char *name, char *type) {
    var_list *new = (var_list *) malloc(sizeof(var_list));
    new->name = (char *) strdup(name);
    new->type = (char *) strdup(type);
    new->function = 0;
    new->flag = 0;
    new->numeroParametros = 0;
    new->parametroTipos = NULL;
    new->next = NULL;
    return new;
}

void adicionarVariavel(var_list *varList, var_list *new) {
    var_list *aux = varList;

    if (aux == NULL) {
        varList = new;
        return;
    }

    while (aux->next != NULL) {
        aux = aux->next;
    }

    aux->next = new;
}

sym_table *criarTabela(char *name, char *type) {
    sym_table *aux = (sym_table *) malloc(sizeof(sym_table));
    aux->tableName = (char *) strdup(name);
    aux->tableType = (char *) strdup(type);

    aux->vars = NULL;
    aux->params = NULL;
    aux->next = NULL;
    return aux;
}

char *alterarTipo(char *Type) {

    if (strcmp(Type, "Int") == 0) {
        Type = "int";
        return Type;
    }

    if (strcmp(Type, "Double") == 0) {
        Type = "double";
        return Type;
    }

    if (strcmp(Type, "Bool") == 0) {
        Type = "boolean";
        return Type;
    }

    if (strcmp(Type, "Void") == 0) {
        Type = "void";
        return Type;
    }

    if (strcmp(Type, "StringArray") == 0) {
        Type = "String[]";
        return Type;
    }

    return Type;
}

void criarTabelaSemantica(node *atual) {
    char *aux;
    int error;
    sym_table *auxTable;
    var_list *auxVar, *auxVarLocal;
    param_list *auxParam, *auxParamPrint;
    node *aux1, *aux2, *aux3, *aux4, *aux5, *aux6, *auxProgram;
    int count_params;

    errosSemantica = 0;

    if (atual == NULL) {
        return;
    }

    if (strcmp(atual->Type, "Program") == 0) { //Fazemos primeiro a tabela global toda
        aux1 = atual->child; //ID

        tabelaGlobal = criarTabela(aux1->valor, "Class");

        auxProgram = aux1->brother; //FieldDecl ou MethodDecl
        atual = aux1->brother; //FieldDecl ou MethodDecl

        while (atual != NULL) { //Fazemos primeiro a tabela global toda
            if (strcmp(atual->Type, "FieldDecl") == 0) {
                aux1 = atual->child; //TYPE - int/bool/double
                aux2 = aux1->brother; //ID - NOME
                auxVar = criarVariavel(aux2->valor, alterarTipo(aux1->Type));

                if (procuraTipoVariavel(tabelaGlobal, NULL, aux2->valor) != NULL) {
                    errosSemantica = 1;
                    printf("Line %d, col %d: Symbol %s already defined\n", aux2->linha, aux2->coluna, aux2->valor);
                    limparVariaveis(auxVar);

                } else {
                    if (tabelaGlobal->vars == NULL) {
                        tabelaGlobal->vars = auxVar;

                    } else {
                        adicionarVariavel(tabelaGlobal->vars, auxVar);
                    }
                }
            }
            if (strcmp(atual->Type, "MethodDecl") == 0) {
                aux1 = atual->child; //MethodHeader
                count_params = 0;
                while (aux1 != NULL) {
                    if (strcmp(aux1->Type, "MethodHeader") == 0) {
                        aux2 = aux1->child; //TYPE
                        aux3 = aux2->brother; //ID

                        auxVar = criarVariavel(aux3->valor, alterarTipo(aux2->Type)); //ADD TO GLOBAL

                        aux4 = aux3->brother; //MethodParams
                        aux5 = aux4->child; //ParamDecl ou nada
                        while (aux5 != NULL) { //WHILE EXISTS ParamDecl's
                            if (strcmp(aux5->Type, "NULL") != 0) {
                                count_params++;
                                //add to auxVar to tabelaGlobal
                                auxParam = CriarParametroTipo(alterarTipo(aux5->child->Type),
                                                             (aux5->child)->brother->valor);

                                aux = procurarVariavel(auxVar->parametroTipos, (aux5->child)->brother->valor);
                                if (aux != NULL) {
                                    errosSemantica = 1;
                                    printf("Line %d, col %d: Symbol %s already defined\n", (aux5->child)->brother->linha,
                                           (aux5->child)->brother->coluna, (aux5->child)->brother->valor);
                                }

                                if (auxVar->parametroTipos == NULL) {
                                    auxVar->parametroTipos = auxParam;

                                } else {
                                    adicionarParametro(auxVar->parametroTipos, auxParam);
                                }
                            }
                            aux5 = aux5->brother;
                        }

                        auxVar->function = 1; //ITS FUNCTION
                        auxVar->numeroParametros = count_params;
                        if (procurarFuncao(tabelaGlobal, auxVar->parametroTipos, count_params, aux3->valor) == 1) {
                            errosSemantica = 1;
                            printf("Line %d, col %d: Symbol %s(", aux3->linha, aux3->coluna, aux3->valor);
                            auxParamPrint = auxVar->parametroTipos;
                            while (auxParamPrint != NULL) {
                                printf("%s", auxParamPrint->type);
                                if (auxParamPrint->next != NULL) {
                                    printf(",");
                                }
                                auxParamPrint = auxParamPrint->next;
                            }
                            printf(") already defined\n");
                            aux3->aAnotar = 0;
                            limparVariaveis(auxVar);

                        } else {
                            if (tabelaGlobal->vars == NULL) {
                                tabelaGlobal->vars = auxVar;

                            } else {
                                adicionarVariavel(tabelaGlobal->vars, auxVar);
                            }
                        }
                    }

                    aux1 = aux1->brother; //MethodHeader ou MethodBody
                }
            }

            atual = atual->brother;
        }

        atual = auxProgram;

        while (atual != NULL) { //Depois fazemos as tabelas locais
            if (strcmp(atual->Type, "MethodDecl") == 0) {
                error = 0;
                aux1 = atual->child; //MethodHeader
                while (aux1 != NULL) {
                    if (strcmp(aux1->Type, "MethodHeader") == 0) {
                        aux2 = aux1->child; //TYPE
                        aux3 = aux2->brother; //ID

                        if (aux3->aAnotar == 0) {
                            error = 1;
                            break;
                        }

                        auxTable = criarTabela(aux3->valor, "Method");

                        auxVar = criarVariavel("return", alterarTipo(aux2->Type)); //CREATE VAR TYPE
                        auxVar->flag = 0;
                        auxTable->vars = auxVar; //TO LOCAL TABLE

                        aux4 = aux3->brother; //MethodParams
                        aux5 = aux4->child; //ParamDecl ou nada
                        while (aux5 != NULL) { //WHILE EXISTS ParamDecl's
                            if (strcmp(aux5->Type, "NULL") != 0) {
                                //add to auxVar to tabelaGlobal
                                auxParam = CriarParametroTipo(alterarTipo(aux5->child->Type),
                                                             (aux5->child)->brother->valor);

                                aux = procurarVariavel(auxVar->parametroTipos, (aux5->child)->brother->valor);

                                if (auxVar->parametroTipos == NULL) {
                                    auxVar->parametroTipos = auxParam;

                                } else {
                                    adicionarParametro(auxVar->parametroTipos, auxParam);
                                }

                                //add to tabelaLocal
                                aux6 = (aux5->child)->brother; //ID OF ParamDecl
                                auxVarLocal = criarVariavel(aux6->valor, alterarTipo(aux5->child->Type));
                                if (aux != NULL) {
                                    auxVarLocal->flag = 2; //DONT PRINT, ITS REPEATED

                                } else {
                                    auxVarLocal->flag = 1; //ITS VAR
                                }
                                auxTable->params = auxVar->parametroTipos;
                                adicionarVariavel(auxTable->vars, auxVarLocal);
                            }
                            aux5 = aux5->brother;
                        }
                    }
                    if (strcmp(aux1->Type, "MethodBody") == 0) {
                        aux2 = aux1->child;
                        while (aux2 != NULL) {
                            if (strcmp(aux2->Type, "VarDecl") == 0) {
                                aux3 = aux2->child;
                                aux4 = aux3->brother;

                                if (procuraTipoVariavel(NULL, auxTable, aux4->valor) != NULL) {
                                    errosSemantica = 1;
                                    printf("Line %d, col %d: Symbol %s already defined\n", aux4->linha, aux4->coluna,
                                           aux4->valor);

                                } else {
                                    auxVar = criarVariavel(aux4->valor, alterarTipo(aux3->Type));
                                    auxVar->flag = 0;
                                    adicionarVariavel(auxTable->vars, auxVar); //TO LOCAL TABLE
                                }

                            } else {
                                if (!(strcmp(aux2->Type, "NULL") == 0)) {
                                    anotarArvore(tabelaGlobal, auxTable, aux2);
                                }
                            }

                            aux2 = aux2->brother;
                        }
                    }

                    aux1 = aux1->brother; //MethodHeader ou MethodBody
                }

                if (error != 1) {
                    if (tabelaLocal == NULL) {
                        tabelaLocal = auxTable;

                    } else {
                        adicionarATabelaLocal(tabelaLocal, auxTable); //ADD TO LOCAL TABLE
                    }
                }
            }

            atual = atual->brother;
        }
    }
}

/* ANOTED AST */

char *procurarVariavel(param_list *params, char *var_name) {
    if (params == NULL) {
        return NULL;
    }

    param_list *auxP = params;

    while (auxP != NULL) {
        if (strcmp(auxP->id, var_name) == 0) {
            return auxP->type;
        }
        auxP = auxP->next;
    }

    return NULL;
}

int procurarFuncao(sym_table *table_global, param_list *aux_parametroTipos, int count_params, char *name) {
    var_list *aux_vars;
    param_list *aux_params1, *aux_params2;
    int count_equals = 0;

    aux_vars = table_global->vars;
    while (aux_vars != NULL) {
        if (aux_vars->function == 1 && aux_vars->numeroParametros == count_params && strcmp(aux_vars->name, name) == 0) {
            count_equals = 0;
            aux_params1 = aux_vars->parametroTipos;
            aux_params2 = aux_parametroTipos;
            while (aux_params1 != NULL) {
                if (strcmp(aux_params1->type, aux_params2->type) == 0) {
                    count_equals++;
                }
                aux_params1 = aux_params1->next;
                aux_params2 = aux_params2->next;
            }
            if (count_equals == count_params) {
                return 1;
            }
        }
        aux_vars = aux_vars->next;
    }

    return 0;
}

char *procurarTipoVariavelTabela(sym_table *table, char *var_name) {
    if (table == NULL) {
        return NULL;
    }

    var_list *auxV = table->vars;

    while (auxV != NULL) {
        if (strcmp(auxV->name, var_name) == 0 && auxV->function != 1) {
            return auxV->type;
        }
        auxV = auxV->next;
    }

    return NULL;
}

char *procuraTipoVariavel(sym_table *table_global, sym_table *table_local, char *var_name) {
    char *aux = procurarTipoVariavelTabela(table_local, var_name);
    if (aux != NULL) {
        return aux;
    }
    aux = procurarTipoVariavelTabela(table_global, var_name);
    if (aux != NULL) {
        return aux;
    }
    return NULL;
}

void anotarArvore(sym_table *table_global, sym_table *table_local, node *atual) {
    char *aux;
    param_list *aux_params, *final_params;
    var_list *aux_vars;
    int count_params, count_equals, count_all_equals, find_function;
    node *aux1, *aux2, *aux3, *ant;

    if (atual == NULL) {
        return;
    }

    if (strcmp(atual->Type, "NULL") == 0) {
        return;

    } else if (strcmp(atual->Type, "Id") == 0) {
        aux = procuraTipoVariavel(table_global, table_local, atual->valor);
        if (aux != NULL) {
            atual->anotacao = aux;

        } else {
            errosSemantica = 1;
            printf("Line %d, col %d: Cannot find symbol %s\n", atual->linha, atual->coluna, atual->valor);
            atual->anotacao = "undef";
        }

    } else if (strcmp(atual->Type, "If") == 0) {
        aux1 = atual->child;
        anotarArvore(table_global, table_local, aux1);
        aux1 = aux1->brother;

        aux2 = atual->child;
        if (aux2->anotacao != NULL && strcmp(aux2->anotacao, "boolean")) { //MUDAR OS <= E TIRAR ESTE NULL
            errosSemantica = 1;
            printf("Line %d, col %d: Incompatible type %s in if statement\n", aux2->linha, aux2->coluna, aux2->anotacao);
        }

        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
    } else if (strcmp(atual->Type, "Block") == 0) {
        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
    } else if (strcmp(atual->Type, "While") == 0) {
        //dentro do while() só pode estar um boolit, gt, eq, get, le, lt, ne
        aux1 = atual->child;
        anotarArvore(table_global, table_local, aux1);
        aux1 = aux1->brother;

        aux2 = atual->child;
        if (strcmp(aux2->anotacao, "boolean")) {
            errosSemantica = 1;
            printf("Line %d, col %d: Incompatible type %s in while statement\n", aux2->linha, aux2->coluna,
                   aux2->anotacao);
            atual->anotacao = "undef";
        } else {
            atual->anotacao = "boolean";
        }

        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

    } else if (strcmp(atual->Type, "Print") == 0) {
        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        if (strcmp(aux2->anotacao, "undef") == 0 || strcmp(aux2->anotacao, "String[]") == 0 ||
            strcmp(aux2->anotacao, "void") == 0) {
            errosSemantica = 1;
            printf("Line %d, col %d: Incompatible type %s in System.out.print statement\n", aux2->linha, aux2->coluna,
                   aux2->anotacao);
        }
    } else if (strcmp(atual->Type, "Return") == 0) {
        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        if (aux2 != NULL) {
            if (strcmp(table_local->vars->type, "void") == 0) {
                errosSemantica = 1;
                printf("Line %d, col %d: Incompatible type %s in return statement\n", aux2->linha, aux2->coluna,
                       aux2->anotacao);
            } else if (strcmp(table_local->vars->type, aux2->anotacao) == 0) {
                return;
            } else if (strcmp(table_local->vars->type, "double") == 0) {
                if ((strcmp(aux2->anotacao, "int") && strcmp(aux2->anotacao, "double"))) {
                    errosSemantica = 1;
                    printf("Line %d, col %d: Incompatible type %s in return statement\n", aux2->linha, aux2->coluna,
                           aux2->anotacao);
                }
            } else {
                errosSemantica = 1;
                printf("Line %d, col %d: Incompatible type %s in return statement\n", aux2->linha, aux2->coluna,
                       aux2->anotacao);
            }
        } else {
            if (strcmp(table_local->vars->type, "void")) {
                errosSemantica = 1;
                printf("Line %d, col %d: Incompatible type void in return statement\n", atual->linha, atual->coluna);
            }
        }
    } else if (strcmp(atual->Type, "Assign") == 0) {
        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        aux3 = aux2->brother;

        atual->anotacao = aux2->anotacao;

        if (strcmp(aux2->anotacao, aux3->anotacao) == 0 && strcmp(aux2->anotacao, "undef") &&
            strcmp(aux2->anotacao, "String[]")) {
            return;
        } else if (strcmp(aux2->anotacao, "double") == 0 && strcmp(aux3->anotacao, "int") == 0) {
            return;
        } else {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator = cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                   aux2->anotacao, aux3->anotacao);
        }
    } else if (strcmp(atual->Type, "Call") == 0) {
        count_params = 0;
        count_equals = 0;
        count_all_equals = 0;
        find_function = 0;
        aux1 = (atual->child)->brother;
        while (aux1 != NULL) {
            if (strcmp(aux1->Type, "NULL")) {
                count_params++;
            }
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux_vars = table_global->vars;
        while (aux_vars != NULL) {
            count_equals = 0;
            count_all_equals = 0;
            if (aux_vars->function == 1 && aux_vars->numeroParametros == count_params &&
                strcmp(aux_vars->name, atual->child->valor) == 0) {
                aux_params = aux_vars->parametroTipos;
                aux1 = (atual->child)->brother;
                while (aux1 != NULL) {
                    if (strcmp(aux1->Type, "NULL")) {
                        if (strcmp(aux_params->type, aux1->anotacao) == 0) {
                            count_all_equals++;
                            count_equals++;
                        } else if (strcmp(aux1->anotacao, "int") == 0 && strcmp(aux_params->type, "double") == 0) {
                            count_equals++;
                        } else {
                            break;
                        }
                        aux_params = aux_params->next;
                    }
                    aux1 = aux1->brother;
                }
                if (count_all_equals == count_params) {
                    find_function = 1;
                    aux = aux_vars->type;
                    final_params = aux_vars->parametroTipos;
                    break;
                } else if (count_equals == count_params) {
                    aux = aux_vars->type;
                    final_params = aux_vars->parametroTipos;
                    find_function++;
                }
            }
            aux_vars = aux_vars->next;
        }

        if (find_function == 1) {
            atual->child->numeroParametros = count_params;
            if (final_params == NULL) {
                atual->child->params = NULL;
            } else {
                atual->child->params = final_params;
            }
            atual->anotacao = aux;
        } else if (find_function > 1) {
            errosSemantica = 1;

            printf("Line %d, col %d: Reference to method %s(", atual->child->linha, atual->child->coluna,
                   atual->child->valor);
            aux1 = (atual->child)->brother;
            while (aux1 != NULL) {
                if (strcmp(aux1->Type, "NULL")) {
                    printf("%s", aux1->anotacao);
                    if (aux1->brother != NULL) {
                        printf(",");
                    }
                }
                aux1 = aux1->brother;
            }
            printf(") is ambiguous\n");
            atual->anotacao = "undef";
            atual->child->anotacao = "undef";
        } else {
            atual->child->anotacao = "undef";
            atual->child->params = NULL;
            atual->anotacao = "undef";

            errosSemantica = 1;

            printf("Line %d, col %d: Cannot find symbol %s(", atual->child->linha, atual->child->coluna,
                   atual->child->valor);
            aux1 = (atual->child)->brother;
            while (aux1 != NULL) {
                if (strcmp(aux1->Type, "NULL")) {
                    printf("%s", aux1->anotacao);
                    if (count_params != 1) {
                        printf(",");
                    }
                    count_params--;
                }
                aux1 = aux1->brother;
            }
            printf(")\n");
        }
    } else if (strcmp(atual->Type, "ParseArgs") == 0) {
        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        aux3 = aux2->brother;
        if (strcmp(aux2->anotacao, "String[]")) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator Integer.parseInt cannot be applied to types %s, %s\n", atual->linha,
                   atual->coluna, aux2->anotacao, aux3->anotacao);
        } else if (strcmp(aux3->anotacao, "int")) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator Integer.parseInt cannot be applied to types %s, %s\n", atual->linha,
                   atual->coluna, aux2->anotacao, aux3->anotacao);
        }

        atual->anotacao = "int";

    } else if (strcmp(atual->Type, "Xor") == 0) {
        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        aux3 = aux2->brother;

        if (strcmp(aux2->anotacao, "int") == 0 && strcmp(aux3->anotacao, "int") == 0) {
            atual->anotacao = "int";

        } else if (strcmp(aux2->anotacao, "boolean")) {

            errosSemantica = 1;
            printf("Line %d, col %d: Operator ^ cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                   aux2->anotacao, aux3->anotacao);

        } else if (strcmp(aux3->anotacao, "boolean")) {

            errosSemantica = 1;
            printf("Line %d, col %d: Operator ^ cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                   aux2->anotacao, aux3->anotacao);

        }

        if (strcmp(aux2->anotacao, "int") == 0 && strcmp(aux3->anotacao, "int") == 0) {
            atual->anotacao = "int";
        } else {
            atual->anotacao = "boolean"; //TODO MELHORAR ISTO
        }

    } else if (strcmp(atual->Type, "And") == 0 || strcmp(atual->Type, "Or") == 0) {
        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        aux3 = aux2->brother;

        if (strcmp(aux2->anotacao, "boolean") && strcmp(atual->Type, "And") == 0) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator && cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                   aux2->anotacao, aux3->anotacao);

        } else if (strcmp(aux2->anotacao, "boolean") && strcmp(atual->Type, "Or") == 0) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator || cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                   aux2->anotacao, aux3->anotacao);

        } else if (strcmp(aux3->anotacao, "boolean") && strcmp(atual->Type, "And") == 0) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator && cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                   aux2->anotacao, aux3->anotacao);

        } else if (strcmp(aux3->anotacao, "boolean") && strcmp(atual->Type, "Or") == 0) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator || cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                   aux2->anotacao, aux3->anotacao);
        }

        atual->anotacao = "boolean";

    } else if (strcmp(atual->Type, "Eq") == 0 || strcmp(atual->Type, "Gt") == 0 || strcmp(atual->Type, "Ge") == 0
               || strcmp(atual->Type, "Le") == 0 || strcmp(atual->Type, "Lt") == 0 || strcmp(atual->Type, "Ne") == 0) {

        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        aux3 = aux2->brother;

        atual->anotacao = "boolean";

        if (strcmp(atual->Type, "Eq") == 0) {
            aux = "==";
        } else if (strcmp(atual->Type, "Gt") == 0) {
            aux = ">";
        } else if (strcmp(atual->Type, "Ge") == 0) {
            aux = ">=";
        } else if (strcmp(atual->Type, "Le") == 0) {
            aux = "<=";
        } else if (strcmp(atual->Type, "Lt") == 0) {
            aux = "<";
        } else if (strcmp(atual->Type, "Ne") == 0) {
            aux = "!=";
        }

        if (strcmp(atual->Type, "Eq") == 0 || strcmp(atual->Type, "Ne") == 0) {
            if (strcmp(aux2->anotacao, "boolean") == 0 && strcmp(aux3->anotacao, "boolean") == 0) {
                return;
            }
        }

        if (strcmp(aux2->anotacao, "int") && strcmp(aux2->anotacao, "double")) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->linha, atual->coluna, aux,
                   aux2->anotacao, aux3->anotacao);
        } else if (strcmp(aux3->anotacao, "double") && strcmp(aux3->anotacao, "int")) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->linha, atual->coluna, aux,
                   aux2->anotacao, aux3->anotacao);
        }
    } else if (strcmp(atual->Type, "Lshift") == 0 || strcmp(atual->Type, "Rshift") == 0) {

        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        aux3 = aux2->brother;

        if (strcmp(atual->Type, "Lshift") == 0) {
            aux = "<<";
        } else {
            aux = ">>";
        }

        if (strcmp(aux2->anotacao, "int") == 0) {
            if (strcmp(aux3->anotacao, "int") == 0) {
                atual->anotacao = "int";
            } else {
                errosSemantica = 1;
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                       aux, aux2->anotacao, aux3->anotacao);
                atual->anotacao = "undef";
            }

        } else if (strcmp(aux3->anotacao, "int") == 0) {
            if (strcmp(aux2->anotacao, "int") == 0) {
                atual->anotacao = "int";
            } else {
                errosSemantica = 1;
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                       aux, aux2->anotacao, aux3->anotacao);
                atual->anotacao = "undef";
            }

        } else {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->linha, atual->coluna, aux,
                   aux2->anotacao, aux3->anotacao);
            atual->anotacao = "undef";
        }

    } else if (strcmp(atual->Type, "Add") == 0 || strcmp(atual->Type, "Sub") == 0 || strcmp(atual->Type, "Mul") == 0
               || strcmp(atual->Type, "Div") == 0 || strcmp(atual->Type, "Mod") == 0) {

        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        aux3 = aux2->brother;

        if (strcmp(atual->Type, "Add") == 0) {
            aux = "+";
        } else if (strcmp(atual->Type, "Sub") == 0) {
            aux = "-";
        } else if (strcmp(atual->Type, "Mul") == 0) {
            aux = "*";
        } else if (strcmp(atual->Type, "Div") == 0) {
            aux = "/";
        } else {
            aux = "%";
        }

        if (strcmp(aux2->anotacao, "int") == 0) {
            if (strcmp(aux3->anotacao, "int") == 0) {
                atual->anotacao = "int";
            } else if (strcmp(aux3->anotacao, "double") == 0) {
                atual->anotacao = "double";
            } else {
                errosSemantica = 1;
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                       aux, aux2->anotacao, aux3->anotacao);
                atual->anotacao = "undef";
            }
        } else if (strcmp(aux2->anotacao, "double") == 0) {
            if (strcmp(aux3->anotacao, "int") && strcmp(aux3->anotacao, "double")) {
                errosSemantica = 1;
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                       aux, aux2->anotacao, aux3->anotacao);
                atual->anotacao = "undef";
            } else {
                atual->anotacao = "double";
            }
        } else {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->linha, atual->coluna, aux,
                   aux2->anotacao, aux3->anotacao);
            atual->anotacao = "undef";
        }
    } else if (strcmp(atual->Type, "Plus") == 0 || strcmp(atual->Type, "Minus") == 0) {
        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        atual->anotacao = aux2->anotacao;
        if (strcmp(aux2->anotacao, "int") == 0 || strcmp(aux2->anotacao, "double") == 0) {
            atual->anotacao = aux2->anotacao;
        } else {
            atual->anotacao = "undef";
            if (strcmp(atual->Type, "Plus") == 0) {
                errosSemantica = 1;
                printf("Line %d, col %d: Operator + cannot be applied to type %s\n", atual->linha, atual->coluna,
                       aux2->anotacao);
            } else {
                errosSemantica = 1;
                printf("Line %d, col %d: Operator - cannot be applied to type %s\n", atual->linha, atual->coluna,
                       aux2->anotacao);
            }
        }
    } else if (strcmp(atual->Type, "Not") == 0) {
        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        if (strcmp(aux2->anotacao, "boolean")) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator ! cannot be applied to type %s\n", atual->linha, atual->coluna,
                   aux2->anotacao);
        }

        atual->anotacao = "boolean";
    } else if (strcmp(atual->Type, "Length") == 0) {
        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        if (strcmp(aux2->anotacao, "String[]")) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator .length cannot be applied to type %s\n", atual->linha, atual->coluna,
                   aux2->anotacao);
        }
        atual->anotacao = "int";
    } else if (strcmp(atual->Type, "BoolLit") == 0) {
        atual->anotacao = "boolean";
    } else if (strcmp(atual->Type, "DecLit") == 0) {
        long l = strtol(atual->valor, NULL, 10);
        if (l >= 0 && l <= INT_MAX) {
            atual->anotacao = "int";
        } else {
            errosSemantica = 1;
            printf("Line %d, col %d: Number %s out of bounds\n", atual->linha, atual->coluna, atual->valor);
        }

        atual->anotacao = "int";
    } else if (strcmp(atual->Type, "RealLit") == 0) {
        char *valor = atual->valor;
        char *aux = (char *) malloc(sizeof(char) * 1024);
        int found = 0, zeros = 1, i = 0, j = 0;

        while (valor[i] != '\0') {
            if ((valor[i] >= '0' && valor[i] <= '9') || valor[i] == 'e' || valor[i] == 'E' || valor[i] == '.' ||
                valor[i] == '-') {
                if (valor[i] == 'e' || valor[i] == 'E') {
                    found = 1;
                }
                if (valor[i] != '.' && valor[i] != '0' && !found) {
                    zeros = 0;
                }
                aux[j] = valor[i];
                j++;
            }
            i++;
        }
        aux[j] = '\0';

        if (!zeros) {
            double d = atof(aux);
            if (isinf(d) || d == 0 || d > DBL_MAX) {
                errosSemantica = 1;
                printf("Line %d, col %d: Number %s out of bounds\n", atual->linha, atual->coluna, atual->valor);
            }
        }

        atual->anotacao = "double";

        free(aux);
        aux = NULL;
    } else if (strcmp(atual->Type, "StrLit") == 0) {
        atual->anotacao = "String";
    }
}

int isExpressao(char *Type) {
    if (strcmp(Type, "Assign") == 0 || strcmp(Type, "Or") == 0 || strcmp(Type, "And") == 0
        || strcmp(Type, "Eq") == 0 || strcmp(Type, "Ne") == 0 || strcmp(Type, "Lt") == 0
        || strcmp(Type, "Ge") == 0 || strcmp(Type, "Add") == 0 || strcmp(Type, "Sub") == 0
        || strcmp(Type, "Mul") == 0 || strcmp(Type, "Div") == 0 || strcmp(Type, "Mod") == 0
        || strcmp(Type, "Not") == 0 || strcmp(Type, "Minus") == 0 || strcmp(Type, "Plus") == 0
        || strcmp(Type, "Length") == 0 || strcmp(Type, "Call") == 0 || strcmp(Type, "ParseArgs") == 0
        || strcmp(Type, "BoolLit") == 0 || strcmp(Type, "DecLit") == 0 || strcmp(Type, "Id") == 0
        || strcmp(Type, "RealLit") == 0 || strcmp(Type, "StrLit") == 0 || strcmp(Type, "Gt") == 0
        || strcmp(Type, "Le") == 0
        || strcmp(Type, "Lshift") == 0 || strcmp(Type, "Rshift") == 0 || strcmp(Type, "Xor") == 0) {
        return 1;

    } else {
        return 0;
    }
}

void imprimirArvoreAnotada(node *current, int n) {
    int i;
    param_list *aux;

    if (current == NULL) {
        return;
    }

    if (strcmp(current->Type, "NULL") == 0) {
        imprimirArvoreAnotada(current->brother, n);
        return;
    } else {
        for (i = 0; i < n; i++) {
            printf("..");
        }

        if (current->valor != NULL) {
            if (current->numeroParametros >= 0 && isExpressao(current->Type) == 1) {
                printf("%s(%s) - (", current->Type, current->valor);
                aux = current->params;
                while (aux != NULL) {
                    printf("%s", aux->type);
                    if (aux->next != NULL) {
                        printf(",");
                    }
                    aux = aux->next;
                }
                printf(")");
            } else if (current->anotacao != NULL && isExpressao(current->Type) == 1) {
                printf("%s(%s) - %s", current->Type, current->valor, current->anotacao);
            } else {
                printf("%s(%s)", current->Type, current->valor);
            }
        } else {
            if (current->anotacao != NULL && isExpressao(current->Type) == 1) {
                printf("%s - %s", current->Type, current->anotacao);
            } else {
                printf("%s", current->Type);
            }
        }
        printf("\n");
    }

    imprimirArvoreAnotada(current->child, n + 1);
    imprimirArvoreAnotada(current->brother, n);
}
