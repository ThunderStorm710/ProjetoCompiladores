#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdarg.h>
#include <float.h>
#include "semantic.h"

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
                            aux3->to_anote = 0;
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

                        if (aux3->to_anote == 0) {
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

/* anotacao AST */

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

int contador_label_while = 1;
int contador_label_or_and = 1;
int return_encontrado = 0;
int contador_stringlit = 1;
int contador_comparador_label = 1;
int contador_conversoes = 1;
int contador_var_globais = 1;
int contador_var_locais = 1;
int contador_label_if = 1;

strlit_list *vars_encontradas;
strlit_list *lista_global_stringlit;

strlit_list *create_strlit(char *valor, char *type){
    strlit_list *new = (strlit_list*)malloc(sizeof(strlit_list));
    new->valor = (char*)strdup(valor);
    new->type = (char*)strdup(type);
    new->next = NULL;
    return new;
}

void LimpaLista(strlit_list *variavel){
    if(variavel == NULL){
        return;
    }

    if(variavel->valor != NULL){
        free(variavel->valor);
        variavel->valor = NULL;
    }
    if(variavel->type != NULL){
        free(variavel->type);
        variavel->type = NULL;
    }

    LimpaLista(variavel->next);

    free(variavel);
    variavel = NULL;
}

void add_strlit(strlit_list *strList, strlit_list *new){
    strlit_list *aux = strList;

    if(aux == NULL){
        strList = new;
        return;
    }

    while(aux->next != NULL){
        aux = aux->next;
    }

    aux->next = new;
}

void print_stringlit(strlit_list *stringlit_List){
    strlit_list *aux_stringList = stringlit_List;
    printf("\n");
    while(aux_stringList != NULL){
        printf("%s", aux_stringList->valor);
        aux_stringList = aux_stringList->next;
    }
}

void gera_llvm(node *raiz){
    print_declaracao_var_func_global(raiz);
    gera_codigo_llvm(raiz);
    print_stringlit(lista_global_stringlit);
    LimpaLista(lista_global_stringlit);
}

void print_declaracao_var_func_global(node *raiz){ //da print das variaveis globais e das funcoes declaradas
    var_list *aux_vars = tabelaGlobal->vars;
    int flag = 0;
    while(aux_vars != NULL){
        if(aux_vars->function == 0){
            if(strcmp(aux_vars->type, "int") == 0){
                printf("@global.var.%s = common global i32 0, align 4\n", aux_vars->name);
            }
            if(strcmp(aux_vars->type, "double") == 0){
                printf("@global.var.%s = common global double 0.000000e+00, align 4\n", aux_vars->name);
            }
            if(strcmp(aux_vars->type, "boolean") == 0){
                printf("@global.var.%s = common global i1 0, align 4\n", aux_vars->name);
            }
            contador_var_globais++;
        } else {
            if(strcmp(aux_vars->type, "void") == 0 && strcmp(aux_vars->name, "main") == 0){
                flag = 1;
            }
        }

        aux_vars = aux_vars->next;
    }

    printf("declare i32 @atoi(i8*)\n");
    printf("declare i32 @printf(i8*, ...)\n\n");
    printf("define i32 @main(i32 %%argc, i8** %%argv) {\n");
    if (flag == 1){
        printf("\tcall void @function.declaration.v.main.s.(i32 %%argc, i8** %%argv)\n");
    } 
    printf("\tret i32 0\n");
    printf("}\n\n");
}

int aux_length_strlit;
char *aux_change_strlit;
char *aux_change_declit;
char *aux_change_reallit;
char *global_function_type;

void change_strlit(char *valor){
    valor++; //removes the first "
    valor[strlen(valor)-1] = 0; //removes the last "

    int i = 0, j = 0;

    aux_length_strlit = 0;
    
    while (valor[i] != '\0') {
        if(valor[i] == '%'){
            aux_length_strlit++;
            aux_change_strlit[j] = valor[i];
            j++;
            aux_length_strlit++;
            aux_change_strlit[j] = valor[i];
            j++;
        }
        else if(valor[i] == '\\'){
            aux_length_strlit++;
            i++;
            if(valor[i] == 'n'){
                aux_change_strlit[j] = '\\';
                j++;
                aux_change_strlit[j] = '0';
                j++;
                aux_change_strlit[j] = 'A';
                j++;
            }
            else if(valor[i] == 'f'){
                aux_change_strlit[j] = '\\';
                j++;
                aux_change_strlit[j] = '0';
                j++;
                aux_change_strlit[j] = 'C';
                j++;
            }
            else if(valor[i] == 'r'){
                aux_change_strlit[j] = '\\';
                j++;
                aux_change_strlit[j] = '0';
                j++;
                aux_change_strlit[j] = 'D';
                j++;
            }
            else if(valor[i] == '"'){
                aux_change_strlit[j] = '\\';
                j++;
                aux_change_strlit[j] = '2';
                j++;
                aux_change_strlit[j] = '2';
                j++;
            }
            else if(valor[i] == 't'){
                aux_change_strlit[j] = '\\';
                j++;
                aux_change_strlit[j] = '0';
                j++;
                aux_change_strlit[j] = '9';
                j++;
            }
            else if(valor[i] == '\\'){
                aux_change_strlit[j] = '\\';
                j++;
                aux_change_strlit[j] = '5';
                j++;
                aux_change_strlit[j] = 'C';
                j++;
            }
        }
        else{
            aux_length_strlit++;
            aux_change_strlit[j] = valor[i];
            j++;
        }
        i++;
    }

    aux_length_strlit++;
    aux_change_strlit[j] = '\\';
    aux_change_strlit[j+1] = '0';
    aux_change_strlit[j+2] = '0';
    aux_change_strlit[j+3] = '\0';
}

void gera_codigo_llvm(node *atual){
    node *aux1;

    if(atual == NULL || strcmp(atual->Type, "NULL") == 0){
        return;
    }

    if(strcmp(atual->Type, "Program") == 0){
        aux1 = atual->child;
        while(aux1 != NULL){
            gera_codigo_llvm(aux1);
            aux1 = aux1->brother;
        }
    }
    else if(strcmp(atual->Type, "MethodDecl") == 0){
        aux_change_strlit = (char*)malloc(sizeof(char)*1024);
        aux_change_declit = (char*)malloc(sizeof(char)*1024);
        aux_change_reallit = (char*)malloc(sizeof(char)*1024);

        contador_var_locais = 1;
        contador_comparador_label = 1;
        contador_conversoes = 1;
        contador_label_if = 1;
        contador_label_while = 1;
        contador_label_or_and = 1;
        global_function_type = NULL;
        return_encontrado = 0;
        vars_encontradas = NULL;

        aux1 = atual->child;
        while(aux1 != NULL){
            gera_codigo_llvm(aux1);
            aux1 = aux1->brother;
        }

        LimpaLista(vars_encontradas);
        vars_encontradas = NULL;
        free(aux_change_strlit);
        aux_change_strlit = NULL;
        free(aux_change_declit);
        aux_change_declit = NULL;
        free(aux_change_reallit);
        aux_change_reallit = NULL;
    }
    else if(strcmp(atual->Type, "MethodHeader") == 0){
        create_header(atual);
    }
    else if(strcmp(atual->Type, "MethodBody") == 0){
        aux1 = atual->child;
        while(aux1 != NULL){
            code_llvm(aux1);
            aux1 = aux1->brother;
        }

        if(global_function_type != NULL && strcmp(global_function_type, "Void") == 0){
            printf("\tret void\n");
        }
        else if(global_function_type != NULL){
            if(strcmp(global_function_type, "Int") == 0){
                printf("\tret i32 0\n");
            }
            else if(strcmp(global_function_type, "Double") == 0){
                printf("\tret double 0.000000e+00\n");
            }
            else{
                printf("\tret i1 1\n");
            }
        }

        printf("}\n");
    }
}

void create_header(node *atual){
    char *aux_type, *aux_name;
    int i, found_string = 0;
    node *aux1, *aux2, *aux3, *aux_node_params;

    aux1 = atual->child; //FUNCTION TYPE
    aux_type = aux1->Type;
    global_function_type = aux1->Type;

    aux2 = aux1->brother; //FUNCTION NAME
    aux_name = aux2->valor;
    aux3 = aux2->brother; //METHOD PARAMS

    char *aux_name_f = (char*)malloc(1024*sizeof(char));
    char *aux_params_f = (char*)malloc(1024*sizeof(char));
    char *aux_main = (char*)strdup("i32 %argc, i8** %argv");
    int aux_count_f, aux_count_params_f = 0;

    aux_node_params = aux3->child;

    if(strcmp(aux_type, "Void") == 0){
        sprintf(aux_name_f, "function.declaration.%s.%s.", "v", aux_name);
    }
    else if(strcmp(aux_type, "Int") == 0){
        sprintf(aux_name_f, "function.declaration.%s.%s.", "i", aux_name);
    }
    else if(strcmp(aux_type, "Double") == 0){
        sprintf(aux_name_f, "function.declaration.%s.%s.", "d", aux_name);
    }
    else{
        sprintf(aux_name_f, "function.declaration.%s.%s.", "b", aux_name);
    }

    aux_count_f = strlen(aux_name_f);

    while(aux_node_params != NULL){
        
        node *brother = aux_node_params->child;

        if(strcmp(aux_node_params->Type, "ParamDecl") == 0){
            if(vars_encontradas == NULL){
                vars_encontradas = create_strlit(brother->brother->valor, brother->Type);
            }
            else{
                add_strlit(vars_encontradas, create_strlit(brother->brother->valor, brother->Type));
            }
        }

        aux_node_params = aux_node_params->brother;
    }

    strlit_list *aux_param_decl = vars_encontradas;

    while(aux_param_decl != NULL){

        if(strcmp(aux_param_decl->type, "StringArray") == 0){
            char *aux = (char*)strdup("s.");
            i = 0;
            while(aux[i] != '\0'){
                aux_name_f[aux_count_f] = aux[i];
                aux_count_f++;
                i++;
            }

            found_string = 1;

            free(aux);
            aux = NULL;

            break;
        }
        if(strcmp(aux_param_decl->type, "Int") == 0){
            char *aux;
            aux = (char*)strdup("i.");
            i = 0;
            while(aux[i] != '\0'){
                aux_name_f[aux_count_f] = aux[i];
                aux_count_f++;
                i++;
            }

            free(aux);
            aux = NULL;

            aux = (char*)malloc(1024*sizeof(char));
            sprintf(aux, "i32 %%%s_aux", aux_param_decl->valor);
            i = 0;
            while(aux[i] != '\0'){
                aux_params_f[aux_count_params_f] = aux[i];
                aux_count_params_f++;
                i++;
            }

            free(aux);
            aux = NULL;
        }
        if(strcmp(aux_param_decl->type, "Bool") == 0){

            char *aux;
            aux = (char*)strdup("b.");
            i = 0;
            while(aux[i] != '\0'){
                aux_name_f[aux_count_f] = aux[i];
                aux_count_f++;
                i++;
            }

            free(aux);
            aux = NULL;

            aux = (char*)malloc(1024*sizeof(char));
            sprintf(aux, "i1 %%%s_aux", aux_param_decl->valor);
            i = 0;
            while(aux[i] != '\0'){
                aux_params_f[aux_count_params_f] = aux[i];
                aux_count_params_f++;
                i++;
            }

            free(aux);
            aux = NULL;
        }
        if(strcmp(aux_param_decl->type, "Double") == 0){
            char *aux;
            aux = (char*)strdup("d.");
            i = 0;
            while(aux[i] != '\0'){
                aux_name_f[aux_count_f] = aux[i];
                aux_count_f++;
                i++;
            }

            free(aux);
            aux = NULL;

            aux = (char*)malloc(1024*sizeof(char));
            sprintf(aux, "double %%%s_aux", aux_param_decl->valor);
            i = 0;
            while(aux[i] != '\0'){
                aux_params_f[aux_count_params_f] = aux[i];
                aux_count_params_f++;
                i++;
            }

            free(aux);
            aux = NULL;
        }

        if(aux_param_decl->next != NULL){
            aux_params_f[aux_count_params_f] = ',';
            aux_count_params_f++;
            aux_params_f[aux_count_params_f] = ' ';
            aux_count_params_f++;
        }

        aux_param_decl = aux_param_decl->next;
    }

    aux_name_f[aux_count_f] = '\0';
    aux_params_f[aux_count_params_f] = '\0';

    if(strcmp(aux_type, "Void") == 0){
        if(found_string == 0){
            printf("define void @%s(%s) {\n", aux_name_f, aux_params_f);
        }
        else{
            printf("define void @%s(%s) {\n", aux_name_f, aux_main);
        }
    }
    else if(strcmp(aux_type, "Int") == 0){
        if(found_string == 0){
            printf("define i32 @%s(%s) {\n", aux_name_f, aux_params_f);
        }
        else{
            printf("define i32 @%s(%s) {\n", aux_name_f, aux_main);
        }
    }
    else if(strcmp(aux_type, "Double") == 0){
        if(found_string == 0){
            printf("define double @%s(%s) {\n", aux_name_f, aux_params_f);
        }
        else{
            printf("define double @%s(%s) {\n", aux_name_f, aux_main);
        }
    }
    else if(strcmp(aux_type, "Bool") == 0){
        if(found_string == 0){
            printf("define i1 @%s(%s) {\n", aux_name_f, aux_params_f);
        }
        else{
            printf("define i1 @%s(%s) {\n", aux_name_f, aux_main);
        }
    }

    if(found_string == 1){
        printf("\t%%argc_aux = alloca i32, align 4\n");
        printf("\t%%argv_aux = alloca i8**, align 8\n");
        printf("\tstore i32 %%argc, i32* %%argc_aux, align 4\n");
        printf("\tstore i8** %%argv, i8*** %%argv_aux, align 8\n");
        LimpaLista(vars_encontradas);
        vars_encontradas = NULL;
    }
    else{
        strlit_list *atual = vars_encontradas;
        while(atual != NULL){
            if(strcmp(atual->type, "Int") == 0){
                printf("\t%%%s = alloca i32, align 4\n", atual->valor);
                printf("\tstore i32 %%%s_aux, i32* %%%s, align 4\n", atual->valor, atual->valor);
            }
            else if(strcmp(atual->type, "Double") == 0){
                printf("\t%%%s = alloca double, align 8\n", atual->valor);
                printf("\tstore double %%%s_aux, double* %%%s, align 8\n", atual->valor, atual->valor);
            }
            else if(strcmp(atual->type, "Bool") == 0){
                printf("\t%%%s = alloca i1\n", atual->valor);
                printf("\tstore i1 %%%s_aux, i1* %%%s\n", atual->valor, atual->valor);
            }
            
            atual = atual->next;
        }
    }

    free(aux_name_f);
    aux_name_f = NULL;
    free(aux_params_f);
    aux_params_f = NULL;
    free(aux_main);
    aux_main = NULL;
}

char *verify_its_global(char *name){
    char *aux = NULL;
    strlit_list *atual = vars_encontradas;
    while(atual != NULL){
        if(strcmp(atual->valor, name) == 0){
            return name;
        }
        atual = atual->next;
    }

    return aux;
}

void function_varDecl(char *type, char *name){
    if(strcmp(type, "Int") == 0){
        printf("\t%%%s = alloca i32, align 4\n", name);
    }
    if(strcmp(type, "Double") == 0){
        printf("\t%%%s = alloca double, align 8\n", name);
    }
    if(strcmp(type, "Bool") == 0){
        printf("\t%%%s = alloca i1\n", name);
    }

    if(vars_encontradas == NULL){
        vars_encontradas = create_strlit(name, type);
    }
    else{
        add_strlit(vars_encontradas, create_strlit(name, type));
    }
}

void function_realLit(node *atual){
    /*printf("\t%%%d = alloca double, align 8\n", contador_var_locais);
    change_reallit(atual->valor);
    printf("\tstore double %.16e, double* %%%d, align 8\n", atof(aux_change_reallit), contador_var_locais);                  
    contador_var_locais++;*/
    change_reallit(atual->valor);
    printf("\t%%%d = fadd double 0.000000e+00, %.16e\n", contador_var_locais, atof(aux_change_reallit));
    contador_var_locais++;
}

void function_decLit(node *atual){
    /*printf("\t%%%d = alloca i32, align 4\n", contador_var_locais);
    change_declit(atual->valor);
    printf("\tstore i32 %d, i32* %%%d, align 4\n", atoi(aux_change_declit), contador_var_locais);                  
    contador_var_locais++;*/
    change_declit(atual->valor);
    printf("\t%%%d = add i32 0, %s\n", contador_var_locais, aux_change_declit);
    contador_var_locais++;
}

void function_boolLit(node *atual){
    /*printf("\t%%%d = alloca i1\n", contador_var_locais);
    printf("\tstore i1 %s, i1* %%%d\n", atual->valor, contador_var_locais);                  
    contador_var_locais++;
    printf("\t%%%d = load i1, i1* %%%d\n", contador_var_locais, contador_var_locais-1);*/
    if(strcmp(atual->valor, "true") == 0){
        printf("\t%%%d = add i1 0, 1\n", contador_var_locais);
    }
    else{
        printf("\t%%%d = add i1 0, 0\n", contador_var_locais);
    }
    contador_var_locais++;
}

void function_length(node *atual){
    printf("\t%%%d = load i32, i32* %%argc_aux, align 4\n", contador_var_locais);
    contador_var_locais++;
    printf("\t%%%d = sub i32 %%%d, 1\n", contador_var_locais, contador_var_locais-1);
    contador_var_locais++;
}

void function_print(node *atual){
    strlit_list *aux_str;
    char *aux = (char*)malloc(1024*sizeof(char));

    if(strcmp(atual->child->anotacao, "String") == 0){
        change_strlit(atual->child->valor);
        sprintf(aux, "@.global.strlit.%d = private unnamed_addr constant [%d x i8] c\"%s\", align 1\n", contador_stringlit, aux_length_strlit, aux_change_strlit);
        printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([%d x i8], [%d x i8]* @.global.strlit.%d, i32 0, i32 0))\n", contador_var_locais, aux_length_strlit, aux_length_strlit, contador_stringlit);
        contador_var_locais++;
    }
    else if(strcmp(atual->child->anotacao, "int") == 0){
        sprintf(aux, "@.global.strlit.%d = private unnamed_addr constant [3 x i8] c\"%%d\\00\", align 1\n", contador_stringlit);
        printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.%d, i32 0, i32 0), i32 %%%d)\n", contador_var_locais, contador_stringlit, contador_var_locais-1);
        contador_var_locais++;
    }
    else if(strcmp(atual->child->anotacao, "double") == 0){                 
        sprintf(aux, "@.global.strlit.%d = private unnamed_addr constant [6 x i8] c\"%%.16e\\00\", align 1\n", contador_stringlit);
        printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.%d, i32 0, i32 0), double %%%d)\n", contador_var_locais, contador_stringlit, contador_var_locais-1);
        contador_var_locais++;
    }
    else if(strcmp(atual->child->anotacao, "boolean") == 0){
        printf("\t%%compare.%d = icmp eq i1 %%%d, 1\n", contador_comparador_label, contador_var_locais-1);
        printf("\tbr i1 %%compare.%d, label %%compare.if.%d, label %%compare.else.%d\n", contador_comparador_label, contador_comparador_label, contador_comparador_label);
        printf("\tcompare.if.%d:\n", contador_comparador_label);
        sprintf(aux, "@.global.strlit.%d = private unnamed_addr constant [5 x i8] c\"true\\00\", align 1\n", contador_stringlit);
        printf("\t\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.global.strlit.%d, i32 0, i32 0))\n", contador_var_locais, contador_stringlit);
        printf("\t\tbr label %%compare.end.%d\n", contador_comparador_label);
        contador_var_locais++;
        contador_stringlit++;
        
        //ADD TO LIST
        if(lista_global_stringlit == NULL){
            lista_global_stringlit = create_strlit(aux, atual->child->anotacao);
        }
        else{
            aux_str = create_strlit(aux, atual->child->anotacao);
            add_strlit(lista_global_stringlit, aux_str);
        }

        printf("\tcompare.else.%d:\n", contador_comparador_label);
        printf("\t\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.%d, i32 0, i32 0))\n", contador_var_locais, contador_stringlit);
        printf("\t\tbr label %%compare.end.%d\n", contador_comparador_label);
        sprintf(aux, "@.global.strlit.%d = private unnamed_addr constant [6 x i8] c\"false\\00\", align 1\n", contador_stringlit);
        printf("\tcompare.end.%d:\n", contador_comparador_label);
        contador_comparador_label++;
        contador_var_locais++;
    }

    if(lista_global_stringlit == NULL){
        lista_global_stringlit = create_strlit(aux, atual->child->anotacao);
    }
    else{
        aux_str = create_strlit(aux, atual->child->anotacao);
        add_strlit(lista_global_stringlit, aux_str);
    }

    contador_stringlit++;

    free(aux);
    aux = NULL;
}

void function_assign(node *atual){
    node *aux = atual->child;
    if(strcmp(aux->anotacao, "int") == 0){
        if(verify_its_global(aux->valor) != NULL){
            printf("\tstore i32 %%%d, i32* %%%s, align 4\n", contador_var_locais-1, aux->valor);
        }
        else{
            printf("\tstore i32 %%%d, i32* @global.var.%s, align 4\n", contador_var_locais-1, aux->valor);
        }
    }
    else if(strcmp(aux->anotacao, "double") == 0){
        if(strcmp(aux->brother->anotacao, "int") == 0){
            printf("\t%%convertion.%d = sitofp i32 %%%d to double\n", contador_conversoes, contador_var_locais-1);
            if(verify_its_global(aux->valor) != NULL){
                printf("\tstore double %%convertion.%d, double* %%%s, align 8\n", contador_conversoes, aux->valor);                  
            }
            else{
                printf("\tstore double %%convertion.%d, double* @global.var.%s, align 8\n", contador_conversoes, aux->valor);                                     
            }
            contador_conversoes++;
        }
        else{
            if(verify_its_global(aux->valor) != NULL){
                printf("\tstore double %%%d, double* %%%s, align 8\n", contador_var_locais-1, aux->valor);                  
            }
            else{
                printf("\tstore double %%%d, double* @global.var.%s, align 8\n", contador_var_locais-1, aux->valor);                                     
            }
        }
    }
    else if(strcmp(aux->anotacao, "boolean") == 0){
        if(verify_its_global(aux->valor) != NULL){
            printf("\tstore i1 %%%d, i1* %%%s\n", contador_var_locais-1, aux->valor);                   
        }
        else{
            printf("\tstore i1 %%%d, i1* @global.var.%s\n", contador_var_locais-1, aux->valor);
        }
    }
}

void function_id(node *atual){
    if(strcmp(atual->anotacao, "String[]") == 0){
        //printf("\t%%%d = load i8**, i8*** %%argv_aux, align 8\n", contador_var_locais);
        //contador_var_locais++;
        return;
    }
    else if(verify_its_global(atual->valor) != NULL){
        if(strcmp(atual->anotacao, "int") == 0){
            printf("\t%%%d = load i32, i32* %%%s, align 4\n", contador_var_locais, atual->valor);
        }
        else if(strcmp(atual->anotacao, "double") == 0){
            printf("\t%%%d = load double, double* %%%s, align 8\n", contador_var_locais, atual->valor);
        }
        else if(strcmp(atual->anotacao, "boolean") == 0){
            printf("\t%%%d = load i1, i1* %%%s\n", contador_var_locais, atual->valor);
        }
        contador_var_locais++;
    }
    else{
        if(strcmp(atual->anotacao, "int") == 0){
            printf("\t%%%d = load i32, i32* @global.var.%s, align 4\n", contador_var_locais, atual->valor);
        }
        else if(strcmp(atual->anotacao, "double") == 0){
            printf("\t%%%d = load double, double* @global.var.%s, align 8\n", contador_var_locais, atual->valor);
        }
        else if(strcmp(atual->anotacao, "boolean") == 0){
            printf("\t%%%d = load i1, i1* @global.var.%s\n", contador_var_locais, atual->valor);
        }
        contador_var_locais++;
    }
}

void function_minus(node *atual){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = sub nsw i32 0, %%%d\n", contador_var_locais, contador_var_locais-1);
        contador_var_locais++;
    }
    else{
        printf("\t%%%d = fsub double -0.000000e+00, %%%d\n", contador_var_locais, contador_var_locais-1);
        contador_var_locais++;
    }
}

void function_parseArgs(node *atual){
    printf("\t%%%d = add i32 %%%d, 1\n", contador_var_locais, contador_var_locais-1);
    contador_var_locais++;
    printf("\t%%%d = load i8**, i8*** %%argv_aux, align 8\n", contador_var_locais);
    contador_var_locais++;
    printf("\t%%%d = getelementptr inbounds i8*, i8** %%%d, i32 %%%d\n", contador_var_locais, contador_var_locais-1, contador_var_locais-2);
    contador_var_locais++;
    printf("\t%%%d = load i8*, i8** %%%d, align 8\n", contador_var_locais, contador_var_locais-1);
    contador_var_locais++;
    printf("\t%%%d = call i32 @atoi(i8* %%%d)\n", contador_var_locais, contador_var_locais-1);
    contador_var_locais++;
}

void function_add(node *atual, int var1, int var2){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = add i32 %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var1);
            var1 = contador_var_locais;
            contador_var_locais++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var2);
            var2 = contador_var_locais;
            contador_var_locais++;
        }
        printf("\t%%%d = fadd double %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
}

void function_sub(node *atual, int var1, int var2){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = sub i32 %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var1);
            var1 = contador_var_locais;
            contador_var_locais++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var2);
            var2 = contador_var_locais;
            contador_var_locais++;
        }
        printf("\t%%%d = fsub double %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
}

void function_mul(node *atual, int var1, int var2){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = mul i32 %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var1);
            var1 = contador_var_locais;
            contador_var_locais++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var2);
            var2 = contador_var_locais;
            contador_var_locais++;
        }
        printf("\t%%%d = fmul double %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
}

void function_div(node *atual, int var1, int var2){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = sdiv i32 %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var1);
            var1 = contador_var_locais;
            contador_var_locais++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var2);
            var2 = contador_var_locais;
            contador_var_locais++;
        }
        printf("\t%%%d = fdiv double %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
}

void function_mod(node *atual, int var1, int var2){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = srem i32 %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var1);
            var1 = contador_var_locais;
            contador_var_locais++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var2);
            var2 = contador_var_locais;
            contador_var_locais++;
        }
        printf("\t%%%d = frem double %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
}

void function_not(node *atual, int var1){
    printf("\t%%%d = zext i1 %%%d to i32\n", contador_var_locais, var1);
    contador_var_locais++;
    printf("\t%%%d = icmp eq i32 %%%d, 0\n", contador_var_locais, contador_var_locais-1);
    contador_var_locais++;
}

void function_eq(node *atual, int var1, int var2){
    if(strcmp(atual->child->anotacao, "int") == 0 && strcmp(atual->child->brother->anotacao, "int") == 0){
        printf("\t%%%d = icmp eq i32 %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
    else if(strcmp(atual->child->anotacao, "boolean") == 0 && strcmp(atual->child->brother->anotacao, "boolean") == 0){
        printf("\t%%%d = zext i1 %%%d to i32\n", contador_var_locais, var1);
        contador_var_locais++;
        printf("\t%%%d = zext i1 %%%d to i32\n", contador_var_locais, var2);
        contador_var_locais++;
        printf("\t%%%d = icmp eq i32 %%%d, %%%d\n", contador_var_locais, contador_var_locais-1, contador_var_locais-2);
        contador_var_locais++;
    }
    else{
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var1);
            var1 = contador_var_locais;
            contador_var_locais++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var2);
            var2 = contador_var_locais;
            contador_var_locais++;
        }
        printf("\t%%%d = fcmp oeq double %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
}

void function_neq(node *atual, int var1, int var2){
    if(strcmp(atual->child->anotacao, "int") == 0 && strcmp(atual->child->brother->anotacao, "int") == 0){
        printf("\t%%%d = icmp ne i32 %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
    else if(strcmp(atual->child->anotacao, "boolean") == 0 && strcmp(atual->child->brother->anotacao, "boolean") == 0){
        printf("\t%%%d = zext i1 %%%d to i32\n", contador_var_locais, var1);
        contador_var_locais++;
        printf("\t%%%d = zext i1 %%%d to i32\n", contador_var_locais, var2);
        contador_var_locais++;
        printf("\t%%%d = icmp ne i32 %%%d, %%%d\n", contador_var_locais, contador_var_locais-1, contador_var_locais-2);
        contador_var_locais++;
    }
    else{ //tem um double
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var1);
            var1 = contador_var_locais;
            contador_var_locais++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var2);
            var2 = contador_var_locais;
            contador_var_locais++;
        }
        printf("\t%%%d = fcmp une double %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
}

void function_lt(node *atual, int var1, int var2){
    if(strcmp(atual->child->anotacao, "int") == 0 && strcmp(atual->child->brother->anotacao, "int") == 0){
        printf("\t%%%d = icmp slt i32 %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
    else{
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var1);
            var1 = contador_var_locais;
            contador_var_locais++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var2);
            var2 = contador_var_locais;
            contador_var_locais++;
        }
        printf("\t%%%d = fcmp olt double %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
}

void function_gt(node *atual, int var1, int var2){
    if(strcmp(atual->child->anotacao, "int") == 0 && strcmp(atual->child->brother->anotacao, "int") == 0){
        printf("\t%%%d = icmp sgt i32 %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
    else{ //tem um double
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var1);
            var1 = contador_var_locais;
            contador_var_locais++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var2);
            var2 = contador_var_locais;
            contador_var_locais++;
        }
        printf("\t%%%d = fcmp ogt double %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
}

void function_leq(node *atual, int var1, int var2){
    if(strcmp(atual->child->anotacao, "int") == 0 && strcmp(atual->child->brother->anotacao, "int") == 0){
        printf("\t%%%d = icmp sle i32 %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
    else{
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var1);
            var1 = contador_var_locais;
            contador_var_locais++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var2);
            var2 = contador_var_locais;
            contador_var_locais++;
        }
        printf("\t%%%d = fcmp ole double %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
}

void function_geq(node *atual, int var1, int var2){
    if(strcmp(atual->child->anotacao, "int") == 0 && strcmp(atual->child->brother->anotacao, "int") == 0){
        printf("\t%%%d = icmp sge i32 %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
    else{
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var1);
            var1 = contador_var_locais;
            contador_var_locais++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var2);
            var2 = contador_var_locais;
            contador_var_locais++;
        }
        printf("\t%%%d = fcmp oge double %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
}

void function_and(node *atual){
    node *first = atual->child->brother;
    while(strcmp(first->Type, "NULL") == 0){
        first = first->brother;
    }

    int aux_count_and_or = contador_label_or_and;
    contador_label_or_and++;
    printf("\tbr label %%label.entry%d\n", aux_count_and_or);
    printf("label.entry%d:        ;it's an and\n", aux_count_and_or);
    printf("\t%%%d = icmp eq i1 %%%d, 1\n", contador_var_locais, contador_var_locais-1);
    printf("\tbr i1 %%%d, label %%label.transition%d, label %%label.end%d\n", contador_var_locais, aux_count_and_or, aux_count_and_or);
    printf("label.transition%d:       ;transition of an and\n", aux_count_and_or);
    contador_var_locais++;
    code_llvm(first);
    printf("\t%%%d = icmp eq i1 %%%d, 1\n", contador_var_locais, contador_var_locais-1);
    printf("\tbr label %%label.end%d\n", aux_count_and_or);
    printf("label.end%d:      ; it's the end of an and\n", aux_count_and_or);
    contador_var_locais++;
    if(aux_count_and_or == contador_label_or_and-1){ //não existiu mais nenhum and
        printf("\t%%%d = phi i1 [ 0, %%label.entry%d ], [ %%%d, %%label.transition%d ]\n", contador_var_locais, aux_count_and_or, contador_var_locais-1, aux_count_and_or);
    }
    else{ //existiu mais um and
        printf("\t%%%d = phi i1 [ 0, %%label.entry%d ], [ %%%d, %%label.end%d ]\n", contador_var_locais, aux_count_and_or, contador_var_locais-1, aux_count_and_or+1);
    }
    contador_var_locais++;
}

void function_xor(node *atual, int var1, int var2){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = xor i32 %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var1);
            var1 = contador_var_locais;
            contador_var_locais++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var2);
            var2 = contador_var_locais;
            contador_var_locais++;
        }
        printf("\t%%%d = fxor double %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
}

void function_or(node *atual){
    node *first = atual->child->brother;
    while(strcmp(first->Type, "NULL") == 0){
        first = first->brother;
    }

    int aux_count_and_or = contador_label_or_and;
    contador_label_or_and++;
    printf("\tbr label %%label.entry%d\n", aux_count_and_or);
    printf("label.entry%d:        ;it's an or\n", aux_count_and_or);
    printf("\t%%%d = icmp eq i1 %%%d, 0\n", contador_var_locais, contador_var_locais-1);
    printf("\tbr i1 %%%d, label %%label.transition%d, label %%label.end%d\n", contador_var_locais, aux_count_and_or, aux_count_and_or);
    printf("label.transition%d:       ;transition of an or\n", aux_count_and_or);
    contador_var_locais++;
    code_llvm(first);
    printf("\t%%%d = icmp eq i1 %%%d, 1\n", contador_var_locais, contador_var_locais-1);
    printf("\tbr label %%label.end%d\n", aux_count_and_or);
    printf("label.end%d:      ; it's the end of an or\n", aux_count_and_or);
    contador_var_locais++;
    if(aux_count_and_or == contador_label_or_and-1){
        printf("\t%%%d = phi i1 [ 1, %%label.entry%d ], [ %%%d, %%label.transition%d ]\n", contador_var_locais, aux_count_and_or, contador_var_locais-1, aux_count_and_or);
    }
    else{
        printf("\t%%%d = phi i1 [ 1, %%label.entry%d ], [ %%%d, %%label.end%d ]\n", contador_var_locais, aux_count_and_or, contador_var_locais-1, aux_count_and_or+1);
    }
    contador_var_locais++;
}

void function_lshift(node *atual, int var1, int var2){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = shl i32 %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var1);
            var1 = contador_var_locais;
            contador_var_locais++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var2);
            var2 = contador_var_locais;
            contador_var_locais++;
        }
        printf("\t%%%d = fshl double %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
}

void function_rshift(node *atual, int var1, int var2){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = ashr i32 %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var1);
            var1 = contador_var_locais;
            contador_var_locais++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, var2);
            var2 = contador_var_locais;
            contador_var_locais++;
        }
        printf("\t%%%d = fashr double %%%d, %%%d\n", contador_var_locais, var1, var2);
        contador_var_locais++;
    }
}


void function_if(node *atual){
    node *first = atual->child->brother;
    while(strcmp(first->Type, "NULL") == 0){
        first = first->brother;
    }
    node *second = first->brother;

    while(strcmp(second->Type, "NULL") == 0){
        second = second->brother;
    }

    int aux_contador_label_if = contador_label_if;
    contador_label_if++;

    printf("\tbr label %%label.entry.if%d\n", aux_contador_label_if);
    printf("label.entry.if%d:       ;it's if \n", aux_contador_label_if);
    printf("\t%%%d = icmp eq i1 %%%d, 1\n", contador_var_locais, contador_var_locais-1);
    printf("\tbr i1 %%%d, label %%label.then%d, label %%label.else%d\n", contador_var_locais, aux_contador_label_if, aux_contador_label_if);
    contador_var_locais++;

    printf("label.then%d:       ;it's if \n", aux_contador_label_if);
    code_llvm(first);
    printf("br label %%label.finished.if%d\n", aux_contador_label_if);
    
    printf("label.else%d:       ;it's else \n", aux_contador_label_if);
    code_llvm(second);
    printf("br label %%label.finished.if%d\n", aux_contador_label_if);
    
    printf("label.finished.if%d:\n", aux_contador_label_if);
    
}

void function_while(node *atual){
    node *first = atual->child;
    while(strcmp(first->Type, "NULL") == 0){
        first = first->brother;
    }
    node *second = first->brother;
    while(strcmp(second->Type, "NULL") == 0){
        second = second->brother;
    }

    int aux_contador_label_while = contador_label_while;
    contador_label_while++;

    printf("\tbr label %%label.entry.while%d\n", aux_contador_label_while);
    printf("label.entry.while%d:       ;it's while \n", aux_contador_label_while);
    code_llvm(first);
    printf("\t%%%d = icmp eq i1 %%%d, 1\n", contador_var_locais, contador_var_locais-1);
    printf("\tbr i1 %%%d, label %%label.work.while%d, label %%label.finished.while%d\n", contador_var_locais, aux_contador_label_while, aux_contador_label_while);
    contador_var_locais++;
    
    printf("label.work.while%d:       ;it's while \n", aux_contador_label_while);
    code_llvm(second);
    printf("\tbr label %%label.entry.while%d\n", aux_contador_label_while);
    
    printf("label.finished.while%d:\n", aux_contador_label_while);
    
}


void function_return(node *atual){
    if(atual->child == NULL){
        printf("\tret void\n");
        contador_var_locais++;
        return;
    }
    code_llvm(atual->child);
    if(strcmp(atual->child->anotacao, "int") == 0){
        if(strcmp(global_function_type, "Double") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, contador_var_locais-1);
            contador_var_locais++;
            printf("\tret double %%%d\n", contador_var_locais-1);
        }
        else{
            printf("\tret i32 %%%d\n", contador_var_locais-1);
        }
    }
    else if(strcmp(atual->child->anotacao, "double") == 0){
        printf("\tret double %%%d\n", contador_var_locais-1);
    }
    else{
        printf("\tret i1 %%%d\n", contador_var_locais-1);
    }
    contador_var_locais++;
}

void function_call(node *atual){
    int i;
    param_list *aux_params;
    node *aux_node_params;
    char *aux_name_f = (char*)malloc(1024*sizeof(char));
    char *aux_params_f = (char*)malloc(1024*sizeof(char));
    int aux_count_f = 0, aux_count_params_f = 0, numeroParametros;

    aux_params = atual->child->params;
    numeroParametros = atual->child->numeroParametros;
    aux_node_params = atual->child->brother;

    if(strcmp(atual->anotacao, "boolean") == 0){
        sprintf(aux_name_f, "function.declaration.%s.%s.", "b", atual->child->valor);
    }
    else if(strcmp(atual->anotacao, "int") == 0){
        sprintf(aux_name_f, "function.declaration.%s.%s.", "i", atual->child->valor);
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        sprintf(aux_name_f, "function.declaration.%s.%s.", "d", atual->child->valor);
    }
    else{
        sprintf(aux_name_f, "function.declaration.%s.%s.", "v", atual->child->valor);
    }

    aux_count_f = strlen(aux_name_f);

    while(aux_params != NULL){
        if(strcmp(aux_node_params->Type, "NULL") == 0){
            aux_node_params = aux_node_params->brother;
        }

        if(strcmp(aux_params->type, "String[]") == 0){
            code_llvm(aux_node_params);

            char *aux;
            aux = (char*)strdup("s.");
            i = 0;
            while(aux[i] != '\0'){
                aux_name_f[aux_count_f] = aux[i];
                aux_count_f++;
                i++;
            }

            free(aux);
            aux = NULL;

            sprintf(aux_params_f, "i%d %%argc, i8** %%argv", 32);
            aux_count_params_f = strlen(aux_params_f);

            break;
        }
        else if(strcmp(aux_params->type, "int") == 0){
            code_llvm(aux_node_params);

            char *aux;
            aux = (char*)strdup("i.");
            i = 0;
            while(aux[i] != '\0'){
                aux_name_f[aux_count_f] = aux[i];
                aux_count_f++;
                i++;
            }

            free(aux);
            aux = NULL;

            aux = (char*)malloc(1024*sizeof(char));
            sprintf(aux, "i32 %%%d", contador_var_locais-1);

            i = 0;
            while(aux[i] != '\0'){
                aux_params_f[aux_count_params_f] = aux[i];
                aux_count_params_f++;
                i++;
            }

            free(aux);
            aux = NULL;
        }
        else if(strcmp(aux_params->type, "boolean") == 0){
            code_llvm(aux_node_params);

            char *aux;
            aux = (char*)strdup("b.");
            i = 0;
            while(aux[i] != '\0'){
                aux_name_f[aux_count_f] = aux[i];
                aux_count_f++;
                i++;
            }

            free(aux);
            aux = NULL;

            aux = (char*)malloc(1024*sizeof(char));
            sprintf(aux, "i1 %%%d", contador_var_locais-1);

            i = 0;
            while(aux[i] != '\0'){
                aux_params_f[aux_count_params_f] = aux[i];
                aux_count_params_f++;
                i++;
            }

            free(aux);
            aux = NULL;
        }
        else if(strcmp(aux_params->type, "double") == 0){
            if(strcmp(aux_node_params->anotacao, "int") == 0){
                code_llvm(aux_node_params);
                printf("\t%%%d = sitofp i32 %%%d to double\n", contador_var_locais, contador_var_locais-1);
                contador_var_locais++;
            }
            else{
                code_llvm(aux_node_params);
            }

            char *aux;
            aux = (char*)strdup("d.");
            i = 0;
            while(aux[i] != '\0'){
                aux_name_f[aux_count_f] = aux[i];
                aux_count_f++;
                i++;
            }

            free(aux);
            aux = NULL;

            aux = (char*)malloc(1024*sizeof(char));
            sprintf(aux, "double %%%d", contador_var_locais-1);

            i = 0;
            while(aux[i] != '\0'){
                aux_params_f[aux_count_params_f] = aux[i];
                aux_count_params_f++;
                i++;
            }

            free(aux);
            aux = NULL;
        }

        if(aux_params->next != NULL){
            char *aux;
            aux = (char*)strdup(", ");

            i = 0;
            while(aux[i] != '\0'){
                aux_params_f[aux_count_params_f] = aux[i];
                aux_count_params_f++;
                i++;
            }
            free(aux);
            aux = NULL;
        }

        numeroParametros--;
        aux_params = aux_params->next;
        aux_node_params = aux_node_params->brother;
    }

    aux_name_f[aux_count_f] = '\0';
    aux_params_f[aux_count_params_f] = '\0';

    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = call i32 @%s(%s)\n", contador_var_locais, aux_name_f, aux_params_f);
        contador_var_locais++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        printf("\t%%%d = call double @%s(%s)\n", contador_var_locais, aux_name_f, aux_params_f);
        contador_var_locais++;
    }
    else if(strcmp(atual->anotacao, "boolean") == 0){
        printf("\t%%%d = call i1 @%s(%s)\n", contador_var_locais, aux_name_f, aux_params_f);
        contador_var_locais++;
    }
    else{
        printf("\tcall void @%s(%s)\n", aux_name_f, aux_params_f);
    }
    
    free(aux_name_f);
    aux_name_f = NULL;
    free(aux_params_f);
    aux_params_f = NULL;
}

void change_declit(char *valor){
    int i=0, j=0;

    while(valor[i] != '\0'){
        if(valor[i] != '_'){
            aux_change_declit[j] = valor[i];
            j++;
        }
        i++;
    }

    aux_change_declit[j] = '\0';
}

void change_reallit(char *valor){
    int i=0, j=0;

    while(valor[i] != '\0'){
        if(valor[i] != '_'){
            aux_change_reallit[j] = valor[i];
            j++;
        }
        i++;
    }

    aux_change_reallit[j] = '\0';
}

void code_llvm(node *atual){
    node *aux1;

    if(strcmp(atual->Type, "VarDecl") == 0){
        function_varDecl(atual->child->Type, atual->child->brother->valor);
    }
    else if(strcmp(atual->Type, "Call") == 0){
        function_call(atual);
    }
    else if(strcmp(atual->Type, "Print") == 0){
        aux1 = atual->child;
        while(aux1 != NULL){
            code_llvm(aux1);
            aux1 = aux1->brother;
        }

        function_print(atual);
    }
    else if(strcmp(atual->Type, "RealLit") == 0){
        function_realLit(atual);
    }
    else if(strcmp(atual->Type, "DecLit") == 0){
        function_decLit(atual);
    }
    else if(strcmp(atual->Type, "BoolLit") == 0){
        function_boolLit(atual);
    }
    else if(strcmp(atual->Type, "Assign") == 0){
        aux1 = atual->child;
        while(aux1 != NULL){
            code_llvm(aux1);
            aux1 = aux1->brother;
        }
        function_assign(atual);
        function_id(atual->child);
    }
    else if(strcmp(atual->Type, "Id") == 0){
        function_id(atual);
    }
    else if(strcmp(atual->Type, "Plus") == 0){
        aux1 = atual->child;
        while(aux1 != NULL){
            code_llvm(aux1);
            aux1 = aux1->brother;
        }
    }
    else if(strcmp(atual->Type, "Minus") == 0){
        aux1 = atual->child;
        while(aux1 != NULL){
            code_llvm(aux1);
            aux1 = aux1->brother;
        }
        function_minus(atual);
    }
    else if(strcmp(atual->Type, "Length") == 0){
        function_length(atual);
    }
    else if(strcmp(atual->Type, "ParseArgs") == 0){
        code_llvm(atual->child->brother);
        function_parseArgs(atual);
    }
    else if(strcmp(atual->Type, "Add") == 0){
        aux1 = atual->child;
        code_llvm(aux1);
        int var1 = contador_var_locais-1;
        aux1 = atual->child->brother;
        code_llvm(aux1);
        int var2 = contador_var_locais-1;

        function_add(atual, var1, var2);
    }
    else if(strcmp(atual->Type, "Sub") == 0){
        aux1 = atual->child;
        code_llvm(aux1);
        int var1 = contador_var_locais-1;
        aux1 = atual->child->brother;
        code_llvm(aux1);
        int var2 = contador_var_locais-1;

        function_sub(atual, var1, var2);
    }
    else if(strcmp(atual->Type, "Mul") == 0){
        aux1 = atual->child;
        code_llvm(aux1);
        int var1 = contador_var_locais-1;
        aux1 = atual->child->brother;
        code_llvm(aux1);
        int var2 = contador_var_locais-1;

        function_mul(atual, var1, var2);
    }
    else if(strcmp(atual->Type, "Div") == 0){
        aux1 = atual->child;
        code_llvm(aux1);
        int var1 = contador_var_locais-1;
        aux1 = atual->child->brother;
        code_llvm(aux1);
        int var2 = contador_var_locais-1;

        function_div(atual, var1, var2);
    }
    else if(strcmp(atual->Type, "Mod") == 0){
        aux1 = atual->child;
        code_llvm(aux1);
        int var1 = contador_var_locais-1;
        aux1 = atual->child->brother;
        code_llvm(aux1);
        int var2 = contador_var_locais-1;

        function_mod(atual, var1, var2);
    }
    else if(strcmp(atual->Type, "Not") == 0){
        aux1 = atual->child;
        code_llvm(aux1);
        int var1 = contador_var_locais-1;

        function_not(atual, var1);
    }
    else if(strcmp(atual->Type, "And") == 0){
        code_llvm(atual->child);
        function_and(atual);
    }
    else if(strcmp(atual->Type, "Or") == 0){
        code_llvm(atual->child);
        function_or(atual);
    }
    else if(strcmp(atual->Type, "Xor") == 0){
        aux1 = atual->child;
        code_llvm(aux1);
        int var1 = contador_var_locais-1;
        aux1 = atual->child->brother;
        code_llvm(aux1);
        int var2 = contador_var_locais-1;
        function_xor(atual, var1, var2);
    }
    else if(strcmp(atual->Type, "Lshift") == 0){
        aux1 = atual->child;
        code_llvm(aux1);
        int var1 = contador_var_locais-1;
        aux1 = atual->child->brother;
        code_llvm(aux1);
        int var2 = contador_var_locais-1;
        function_lshift(atual, var1, var2);
    }
    else if(strcmp(atual->Type, "Rshift") == 0){
        aux1 = atual->child;
        code_llvm(aux1);
        int var1 = contador_var_locais-1;
        aux1 = atual->child->brother;
        code_llvm(aux1);
        int var2 = contador_var_locais-1;
        function_rshift(atual, var1, var2);
    }
    else if(strcmp(atual->Type, "Eq") == 0){
        aux1 = atual->child;
        code_llvm(aux1);
        int var1 = contador_var_locais-1;
        aux1 = atual->child->brother;
        code_llvm(aux1);
        int var2 = contador_var_locais-1;

        function_eq(atual, var1, var2);
    }
    else if(strcmp(atual->Type, "Ne") == 0){
        aux1 = atual->child;
        code_llvm(aux1);
        int var1 = contador_var_locais-1;
        aux1 = atual->child->brother;
        code_llvm(aux1);
        int var2 = contador_var_locais-1;

        function_neq(atual, var1, var2);
    }
    else if(strcmp(atual->Type, "Lt") == 0){
        aux1 = atual->child;
        code_llvm(aux1);
        int var1 = contador_var_locais-1;
        aux1 = atual->child->brother;
        code_llvm(aux1);
        int var2 = contador_var_locais-1;

        function_lt(atual, var1, var2);
    }
    else if(strcmp(atual->Type, "Gt") == 0){
        aux1 = atual->child;
        code_llvm(aux1);
        int var1 = contador_var_locais-1;
        aux1 = atual->child->brother;
        code_llvm(aux1);
        int var2 = contador_var_locais-1;

        function_gt(atual, var1, var2);
    }
    else if(strcmp(atual->Type, "Le") == 0){
        aux1 = atual->child;
        code_llvm(aux1);
        int var1 = contador_var_locais-1;
        aux1 = atual->child->brother;
        code_llvm(aux1);
        int var2 = contador_var_locais-1;

        function_leq(atual, var1, var2);
    }
    else if(strcmp(atual->Type, "Ge") == 0){
        aux1 = atual->child;
        code_llvm(aux1);
        int var1 = contador_var_locais-1;
        aux1 = atual->child->brother;
        code_llvm(aux1);
        int var2 = contador_var_locais-1;

        function_geq(atual, var1, var2);
    }
    else if(strcmp(atual->Type, "Block") == 0){
        aux1 = atual->child;
        while(aux1 != NULL){
            code_llvm(aux1);
            aux1 = aux1->brother;
        }
    }
    else if(strcmp(atual->Type, "If") == 0){
        code_llvm(atual->child);
        function_if(atual);
    }
    else if(strcmp(atual->Type, "While") == 0){
        function_while(atual);
    }
    else if(strcmp(atual->Type, "Return") == 0){
        return_encontrado = 1;
        function_return(atual);
    }
}