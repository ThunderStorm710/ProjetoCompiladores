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

    limparParametros(var->paramTypes);
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
            auxP = auxV->paramTypes;
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
    new->n_params = 0;
    new->paramTypes = NULL;
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

    nErrorsSemantic = 0;

    if (atual == NULL) {
        return;
    }

    if (strcmp(atual->Type, "Program") == 0) { //Fazemos primeiro a tabela global toda
        aux1 = atual->child; //ID

        global_table = criarTabela(aux1->value, "Class");

        auxProgram = aux1->brother; //FieldDecl ou MethodDecl
        atual = aux1->brother; //FieldDecl ou MethodDecl

        while (atual != NULL) { //Fazemos primeiro a tabela global toda
            if (strcmp(atual->Type, "FieldDecl") == 0) {
                aux1 = atual->child; //TYPE - int/bool/double
                aux2 = aux1->brother; //ID - NOME
                auxVar = criarVariavel(aux2->value, alterarTipo(aux1->Type));

                if (procuraTipoVariavel(global_table, NULL, aux2->value) != NULL) {
                    nErrorsSemantic = 1;
                    printf("Line %d, col %d: Symbol %s already defined\n", aux2->line, aux2->column, aux2->value);
                    limparVariaveis(auxVar);

                } else {
                    if (global_table->vars == NULL) {
                        global_table->vars = auxVar;

                    } else {
                        adicionarVariavel(global_table->vars, auxVar);
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

                        auxVar = criarVariavel(aux3->value, alterarTipo(aux2->Type)); //ADD TO GLOBAL

                        aux4 = aux3->brother; //MethodParams
                        aux5 = aux4->child; //ParamDecl ou nada
                        while (aux5 != NULL) { //WHILE EXISTS ParamDecl's
                            if (strcmp(aux5->Type, "NULL") != 0) {
                                count_params++;
                                //add to auxVar to global_table
                                auxParam = CriarParametroTipo(alterarTipo(aux5->child->Type),
                                                             (aux5->child)->brother->value);

                                aux = procurarVariavel(auxVar->paramTypes, (aux5->child)->brother->value);
                                if (aux != NULL) {
                                    nErrorsSemantic = 1;
                                    printf("Line %d, col %d: Symbol %s already defined\n", (aux5->child)->brother->line,
                                           (aux5->child)->brother->column, (aux5->child)->brother->value);
                                }

                                if (auxVar->paramTypes == NULL) {
                                    auxVar->paramTypes = auxParam;

                                } else {
                                    adicionarParametro(auxVar->paramTypes, auxParam);
                                }
                            }
                            aux5 = aux5->brother;
                        }

                        auxVar->function = 1; //ITS FUNCTION
                        auxVar->n_params = count_params;
                        if (procurarFuncao(global_table, auxVar->paramTypes, count_params, aux3->value) == 1) {
                            nErrorsSemantic = 1;
                            printf("Line %d, col %d: Symbol %s(", aux3->line, aux3->column, aux3->value);
                            auxParamPrint = auxVar->paramTypes;
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
                            if (global_table->vars == NULL) {
                                global_table->vars = auxVar;

                            } else {
                                adicionarVariavel(global_table->vars, auxVar);
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

                        auxTable = criarTabela(aux3->value, "Method");

                        auxVar = criarVariavel("return", alterarTipo(aux2->Type)); //CREATE VAR TYPE
                        auxVar->flag = 0;
                        auxTable->vars = auxVar; //TO LOCAL TABLE

                        aux4 = aux3->brother; //MethodParams
                        aux5 = aux4->child; //ParamDecl ou nada
                        while (aux5 != NULL) { //WHILE EXISTS ParamDecl's
                            if (strcmp(aux5->Type, "NULL") != 0) {
                                //add to auxVar to global_table
                                auxParam = CriarParametroTipo(alterarTipo(aux5->child->Type),
                                                             (aux5->child)->brother->value);

                                aux = procurarVariavel(auxVar->paramTypes, (aux5->child)->brother->value);

                                if (auxVar->paramTypes == NULL) {
                                    auxVar->paramTypes = auxParam;

                                } else {
                                    adicionarParametro(auxVar->paramTypes, auxParam);
                                }

                                //add to local_table
                                aux6 = (aux5->child)->brother; //ID OF ParamDecl
                                auxVarLocal = criarVariavel(aux6->value, alterarTipo(aux5->child->Type));
                                if (aux != NULL) {
                                    auxVarLocal->flag = 2; //DONT PRINT, ITS REPEATED

                                } else {
                                    auxVarLocal->flag = 1; //ITS VAR
                                }
                                auxTable->params = auxVar->paramTypes;
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

                                if (procuraTipoVariavel(NULL, auxTable, aux4->value) != NULL) {
                                    nErrorsSemantic = 1;
                                    printf("Line %d, col %d: Symbol %s already defined\n", aux4->line, aux4->column,
                                           aux4->value);

                                } else {
                                    auxVar = criarVariavel(aux4->value, alterarTipo(aux3->Type));
                                    auxVar->flag = 0;
                                    adicionarVariavel(auxTable->vars, auxVar); //TO LOCAL TABLE
                                }

                            } else {
                                if (!(strcmp(aux2->Type, "NULL") == 0)) {
                                    anotarArvore(global_table, auxTable, aux2);
                                }
                            }

                            aux2 = aux2->brother;
                        }
                    }

                    aux1 = aux1->brother; //MethodHeader ou MethodBody
                }

                if (error != 1) {
                    if (local_table == NULL) {
                        local_table = auxTable;

                    } else {
                        adicionarATabelaLocal(local_table, auxTable); //ADD TO LOCAL TABLE
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

int procurarFuncao(sym_table *table_global, param_list *aux_paramTypes, int count_params, char *name) {
    var_list *aux_vars;
    param_list *aux_params1, *aux_params2;
    int count_equals = 0;

    aux_vars = table_global->vars;
    while (aux_vars != NULL) {
        if (aux_vars->function == 1 && aux_vars->n_params == count_params && strcmp(aux_vars->name, name) == 0) {
            count_equals = 0;
            aux_params1 = aux_vars->paramTypes;
            aux_params2 = aux_paramTypes;
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
        aux = procuraTipoVariavel(table_global, table_local, atual->value);
        if (aux != NULL) {
            atual->anoted = aux;

        } else {
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Cannot find symbol %s\n", atual->line, atual->column, atual->value);
            atual->anoted = "undef";
        }

    } else if (strcmp(atual->Type, "If") == 0) {
        aux1 = atual->child;
        anotarArvore(table_global, table_local, aux1);
        aux1 = aux1->brother;

        aux2 = atual->child;
        if (aux2->anoted != NULL && strcmp(aux2->anoted, "boolean")) { //MUDAR OS <= E TIRAR ESTE NULL
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Incompatible type %s in if statement\n", aux2->line, aux2->column, aux2->anoted);
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
        if (strcmp(aux2->anoted, "boolean")) {
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Incompatible type %s in while statement\n", aux2->line, aux2->column,
                   aux2->anoted);
            atual->anoted = "undef";
        } else {
            atual->anoted = "boolean";
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
        if (strcmp(aux2->anoted, "undef") == 0 || strcmp(aux2->anoted, "String[]") == 0 ||
            strcmp(aux2->anoted, "void") == 0) {
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Incompatible type %s in System.out.print statement\n", aux2->line, aux2->column,
                   aux2->anoted);
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
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Incompatible type %s in return statement\n", aux2->line, aux2->column,
                       aux2->anoted);
            } else if (strcmp(table_local->vars->type, aux2->anoted) == 0) {
                return;
            } else if (strcmp(table_local->vars->type, "double") == 0) {
                if ((strcmp(aux2->anoted, "int") && strcmp(aux2->anoted, "double"))) {
                    nErrorsSemantic = 1;
                    printf("Line %d, col %d: Incompatible type %s in return statement\n", aux2->line, aux2->column,
                           aux2->anoted);
                }
            } else {
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Incompatible type %s in return statement\n", aux2->line, aux2->column,
                       aux2->anoted);
            }
        } else {
            if (strcmp(table_local->vars->type, "void")) {
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Incompatible type void in return statement\n", atual->line, atual->column);
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

        atual->anoted = aux2->anoted;

        if (strcmp(aux2->anoted, aux3->anoted) == 0 && strcmp(aux2->anoted, "undef") &&
            strcmp(aux2->anoted, "String[]")) {
            return;
        } else if (strcmp(aux2->anoted, "double") == 0 && strcmp(aux3->anoted, "int") == 0) {
            return;
        } else {
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator = cannot be applied to types %s, %s\n", atual->line, atual->column,
                   aux2->anoted, aux3->anoted);
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
            if (aux_vars->function == 1 && aux_vars->n_params == count_params &&
                strcmp(aux_vars->name, atual->child->value) == 0) {
                aux_params = aux_vars->paramTypes;
                aux1 = (atual->child)->brother;
                while (aux1 != NULL) {
                    if (strcmp(aux1->Type, "NULL")) {
                        if (strcmp(aux_params->type, aux1->anoted) == 0) {
                            count_all_equals++;
                            count_equals++;
                        } else if (strcmp(aux1->anoted, "int") == 0 && strcmp(aux_params->type, "double") == 0) {
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
                    final_params = aux_vars->paramTypes;
                    break;
                } else if (count_equals == count_params) {
                    aux = aux_vars->type;
                    final_params = aux_vars->paramTypes;
                    find_function++;
                }
            }
            aux_vars = aux_vars->next;
        }

        if (find_function == 1) {
            atual->child->n_params = count_params;
            if (final_params == NULL) {
                atual->child->params = NULL;
            } else {
                atual->child->params = final_params;
            }
            atual->anoted = aux;
        } else if (find_function > 1) {
            nErrorsSemantic = 1;

            printf("Line %d, col %d: Reference to method %s(", atual->child->line, atual->child->column,
                   atual->child->value);
            aux1 = (atual->child)->brother;
            while (aux1 != NULL) {
                if (strcmp(aux1->Type, "NULL")) {
                    printf("%s", aux1->anoted);
                    if (aux1->brother != NULL) {
                        printf(",");
                    }
                }
                aux1 = aux1->brother;
            }
            printf(") is ambiguous\n");
            atual->anoted = "undef";
            atual->child->anoted = "undef";
        } else {
            atual->child->anoted = "undef";
            atual->child->params = NULL;
            atual->anoted = "undef";

            nErrorsSemantic = 1;

            printf("Line %d, col %d: Cannot find symbol %s(", atual->child->line, atual->child->column,
                   atual->child->value);
            aux1 = (atual->child)->brother;
            while (aux1 != NULL) {
                if (strcmp(aux1->Type, "NULL")) {
                    printf("%s", aux1->anoted);
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
        if (strcmp(aux2->anoted, "String[]")) {
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator Integer.parseInt cannot be applied to types %s, %s\n", atual->line,
                   atual->column, aux2->anoted, aux3->anoted);
        } else if (strcmp(aux3->anoted, "int")) {
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator Integer.parseInt cannot be applied to types %s, %s\n", atual->line,
                   atual->column, aux2->anoted, aux3->anoted);
        }

        atual->anoted = "int";

    } else if (strcmp(atual->Type, "Xor") == 0) {
        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        aux3 = aux2->brother;

        if (strcmp(aux2->anoted, "int") == 0 && strcmp(aux3->anoted, "int") == 0) {
            atual->anoted = "int";

        } else if (strcmp(aux2->anoted, "boolean")) {

            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator ^ cannot be applied to types %s, %s\n", atual->line, atual->column,
                   aux2->anoted, aux3->anoted);

        } else if (strcmp(aux3->anoted, "boolean")) {

            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator ^ cannot be applied to types %s, %s\n", atual->line, atual->column,
                   aux2->anoted, aux3->anoted);

        }

        if (strcmp(aux2->anoted, "int") == 0 && strcmp(aux3->anoted, "int") == 0) {
            atual->anoted = "int";
        } else {
            atual->anoted = "boolean"; //TODO MELHORAR ISTO
        }

    } else if (strcmp(atual->Type, "And") == 0 || strcmp(atual->Type, "Or") == 0) {
        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        aux3 = aux2->brother;

        if (strcmp(aux2->anoted, "boolean") && strcmp(atual->Type, "And") == 0) {
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator && cannot be applied to types %s, %s\n", atual->line, atual->column,
                   aux2->anoted, aux3->anoted);

        } else if (strcmp(aux2->anoted, "boolean") && strcmp(atual->Type, "Or") == 0) {
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator || cannot be applied to types %s, %s\n", atual->line, atual->column,
                   aux2->anoted, aux3->anoted);

        } else if (strcmp(aux3->anoted, "boolean") && strcmp(atual->Type, "And") == 0) {
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator && cannot be applied to types %s, %s\n", atual->line, atual->column,
                   aux2->anoted, aux3->anoted);

        } else if (strcmp(aux3->anoted, "boolean") && strcmp(atual->Type, "Or") == 0) {
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator || cannot be applied to types %s, %s\n", atual->line, atual->column,
                   aux2->anoted, aux3->anoted);
        }

        atual->anoted = "boolean";

    } else if (strcmp(atual->Type, "Eq") == 0 || strcmp(atual->Type, "Gt") == 0 || strcmp(atual->Type, "Ge") == 0
               || strcmp(atual->Type, "Le") == 0 || strcmp(atual->Type, "Lt") == 0 || strcmp(atual->Type, "Ne") == 0) {

        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        aux3 = aux2->brother;

        atual->anoted = "boolean";

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
            if (strcmp(aux2->anoted, "boolean") == 0 && strcmp(aux3->anoted, "boolean") == 0) {
                return;
            }
        }

        if (strcmp(aux2->anoted, "int") && strcmp(aux2->anoted, "double")) {
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->column, aux,
                   aux2->anoted, aux3->anoted);
        } else if (strcmp(aux3->anoted, "double") && strcmp(aux3->anoted, "int")) {
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->column, aux,
                   aux2->anoted, aux3->anoted);
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

        if (strcmp(aux2->anoted, "int") == 0) {
            if (strcmp(aux3->anoted, "int") == 0) {
                atual->anoted = "int";
            } else {
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->column,
                       aux, aux2->anoted, aux3->anoted);
                atual->anoted = "undef";
            }

        } else if (strcmp(aux3->anoted, "int") == 0) {
            if (strcmp(aux2->anoted, "int") == 0) {
                atual->anoted = "int";
            } else {
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->column,
                       aux, aux2->anoted, aux3->anoted);
                atual->anoted = "undef";
            }

        } else {
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->column, aux,
                   aux2->anoted, aux3->anoted);
            atual->anoted = "undef";
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

        if (strcmp(aux2->anoted, "int") == 0) {
            if (strcmp(aux3->anoted, "int") == 0) {
                atual->anoted = "int";
            } else if (strcmp(aux3->anoted, "double") == 0) {
                atual->anoted = "double";
            } else {
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->column,
                       aux, aux2->anoted, aux3->anoted);
                atual->anoted = "undef";
            }
        } else if (strcmp(aux2->anoted, "double") == 0) {
            if (strcmp(aux3->anoted, "int") && strcmp(aux3->anoted, "double")) {
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->column,
                       aux, aux2->anoted, aux3->anoted);
                atual->anoted = "undef";
            } else {
                atual->anoted = "double";
            }
        } else {
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->column, aux,
                   aux2->anoted, aux3->anoted);
            atual->anoted = "undef";
        }
    } else if (strcmp(atual->Type, "Plus") == 0 || strcmp(atual->Type, "Minus") == 0) {
        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        atual->anoted = aux2->anoted;
        if (strcmp(aux2->anoted, "int") == 0 || strcmp(aux2->anoted, "double") == 0) {
            atual->anoted = aux2->anoted;
        } else {
            atual->anoted = "undef";
            if (strcmp(atual->Type, "Plus") == 0) {
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Operator + cannot be applied to type %s\n", atual->line, atual->column,
                       aux2->anoted);
            } else {
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Operator - cannot be applied to type %s\n", atual->line, atual->column,
                       aux2->anoted);
            }
        }
    } else if (strcmp(atual->Type, "Not") == 0) {
        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        if (strcmp(aux2->anoted, "boolean")) {
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator ! cannot be applied to type %s\n", atual->line, atual->column,
                   aux2->anoted);
        }

        atual->anoted = "boolean";
    } else if (strcmp(atual->Type, "Length") == 0) {
        aux1 = atual->child;
        while (aux1 != NULL) {
            anotarArvore(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->child;
        if (strcmp(aux2->anoted, "String[]")) {
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator .length cannot be applied to type %s\n", atual->line, atual->column,
                   aux2->anoted);
        }
        atual->anoted = "int";
    } else if (strcmp(atual->Type, "BoolLit") == 0) {
        atual->anoted = "boolean";
    } else if (strcmp(atual->Type, "DecLit") == 0) {
        long l = strtol(atual->value, NULL, 10);
        if (l >= 0 && l <= INT_MAX) {
            atual->anoted = "int";
        } else {
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Number %s out of bounds\n", atual->line, atual->column, atual->value);
        }

        atual->anoted = "int";
    } else if (strcmp(atual->Type, "RealLit") == 0) {
        char *value = atual->value;
        char *aux = (char *) malloc(sizeof(char) * 1024);
        int found = 0, zeros = 1, i = 0, j = 0;

        while (value[i] != '\0') {
            if ((value[i] >= '0' && value[i] <= '9') || value[i] == 'e' || value[i] == 'E' || value[i] == '.' ||
                value[i] == '-') {
                if (value[i] == 'e' || value[i] == 'E') {
                    found = 1;
                }
                if (value[i] != '.' && value[i] != '0' && !found) {
                    zeros = 0;
                }
                aux[j] = value[i];
                j++;
            }
            i++;
        }
        aux[j] = '\0';

        if (!zeros) {
            double d = atof(aux);
            if (isinf(d) || d == 0 || d > DBL_MAX) {
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Number %s out of bounds\n", atual->line, atual->column, atual->value);
            }
        }

        atual->anoted = "double";

        free(aux);
        aux = NULL;
    } else if (strcmp(atual->Type, "StrLit") == 0) {
        atual->anoted = "String";
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

        if (current->value != NULL) {
            if (current->n_params >= 0 && isExpressao(current->Type) == 1) {
                printf("%s(%s) - (", current->Type, current->value);
                aux = current->params;
                while (aux != NULL) {
                    printf("%s", aux->type);
                    if (aux->next != NULL) {
                        printf(",");
                    }
                    aux = aux->next;
                }
                printf(")");
            } else if (current->anoted != NULL && isExpressao(current->Type) == 1) {
                printf("%s(%s) - %s", current->Type, current->value, current->anoted);
            } else {
                printf("%s(%s)", current->Type, current->value);
            }
        } else {
            if (current->anoted != NULL && isExpressao(current->Type) == 1) {
                printf("%s - %s", current->Type, current->anoted);
            } else {
                printf("%s", current->Type);
            }
        }
        printf("\n");
    }

    imprimirArvoreAnotada(current->child, n + 1);
    imprimirArvoreAnotada(current->brother, n);
}
