#include "semantic.h"

tabelaSimbolos *criarTabela(char *nome, char *tipo) {
    tabelaSimbolos *backUp = (tabelaSimbolos *) malloc(sizeof(tabelaSimbolos));
    backUp->tableName = (char *) strdup(nome);
    backUp->tableType = (char *) strdup(tipo);

    backUp->vars = NULL;
    backUp->params = NULL;
    backUp->seguinte = NULL;
    return backUp;
} 


void criarTabelaSemantica(node *atual) {
    char *backUp;
    int error;
    tabelaSimbolos *backUpTable;
    listaVariaveis *backUpVar, *backUpVarLocal;
    listaParametros *backUpParam, *backUpParamPrint;
    node *backUp1, *backUp2, *backUp3, *backUp4, *backUp5, *backUp6, *backUpProgram;
    int count_params;

    errosSemantica = 0;

    if (atual == NULL) {
        return;
    }

    if (strcmp(atual->tipoNo, "Program") == 0) { //Fazemos primeiro a tabela global toda
        backUp1 = atual->child; //ID

        tabelaGlobal = criarTabela(backUp1->valor, "Class");

        backUpProgram = backUp1->brother; //FieldDecl ou MethodDecl
        atual = backUp1->brother; //FieldDecl ou MethodDecl

        while (atual != NULL) { //Fazer primeiro a tabela global
            if (strcmp(atual->tipoNo, "FieldDecl") == 0) {
                backUp1 = atual->child; //tipo - integer/boolean/double
                backUp2 = backUp1->brother; //nome - NOME
                backUpVar = criarVariavel(backUp2->valor, alterarTipo(backUp1->tipoNo));

                if (procuraTipoVariavel(tabelaGlobal, NULL, backUp2->valor) != NULL) {
                    errosSemantica = 1;
                    printf("Line %d, col %d: Symbol %s already defined\n", backUp2->linha, backUp2->coluna, backUp2->valor);
                    limparVariaveis(backUpVar);

                } else {
                    if (tabelaGlobal->vars == NULL) {
                        tabelaGlobal->vars = backUpVar;

                    } else {
                        adicionarVariavel(tabelaGlobal->vars, backUpVar);
                    }
                }
            }
            if (strcmp(atual->tipoNo, "MethodDecl") == 0) {
                backUp1 = atual->child; //MethodHeader
                count_params = 0;
                while (backUp1 != NULL) {
                    if (strcmp(backUp1->tipoNo, "MethodHeader") == 0) {
                        backUp2 = backUp1->child; //supostamente o tipo
                        backUp3 = backUp2->brother; //supostamente id

                        backUpVar = criarVariavel(backUp3->valor, alterarTipo(backUp2->tipoNo));

                        backUp4 = backUp3->brother; //MethodParams
                        backUp5 = backUp4->child; //ou e param ou nada
                        while (backUp5 != NULL) { 
                            if (strcmp(backUp5->tipoNo, "NULL") != 0) {
                                count_params++;
                                //adicionar o backUpVar a tabela global
                                backUpParam = CriarParametroTipo(alterarTipo(backUp5->child->tipoNo),
                                                             (backUp5->child)->brother->valor);

                                backUp = procurarVariavel(backUpVar->parametroTipos, (backUp5->child)->brother->valor);
                                if (backUp != NULL) {
                                    errosSemantica = 1;
                                    printf("Line %d, col %d: Symbol %s already defined\n", (backUp5->child)->brother->linha,
                                           (backUp5->child)->brother->coluna, (backUp5->child)->brother->valor);
                                }

                                if (backUpVar->parametroTipos == NULL) {
                                    backUpVar->parametroTipos = backUpParam;

                                } else {
                                    adicionarParametro(backUpVar->parametroTipos, backUpParam);
                                }
                            }
                            backUp5 = backUp5->brother;
                        }

                        backUpVar->isFunction = true; //e uma funcao
                        backUpVar->numeroParametros = count_params;
                        if (procurarFuncao(tabelaGlobal, backUpVar->parametroTipos, count_params, backUp3->valor) == 1) {
                            errosSemantica = 1;
                            printf("Line %d, col %d: Symbol %s(", backUp3->linha, backUp3->coluna, backUp3->valor);
                            backUpParamPrint = backUpVar->parametroTipos;
                            while (backUpParamPrint != NULL) {
                                printf("%s", backUpParamPrint->tipo);
                                if (backUpParamPrint->seguinte != NULL) {
                                    printf(",");
                                }
                                backUpParamPrint = backUpParamPrint->seguinte;
                            }
                            printf(") already defined\n");
                            backUp3->aAnotar = 0;
                            limparVariaveis(backUpVar);

                        } else {
                            if (tabelaGlobal->vars == NULL) {
                                tabelaGlobal->vars = backUpVar;

                            } else {
                                adicionarVariavel(tabelaGlobal->vars, backUpVar);
                            }
                        }
                    }

                    backUp1 = backUp1->brother; //Header ou Body
                }
            }

            atual = atual->brother;
        }

        atual = backUpProgram;

        while (atual != NULL) { //Depois fazemos as tabelas locais
            if (strcmp(atual->tipoNo, "MethodDecl") == 0) {
                error = 0;
                backUp1 = atual->child; //MethodHeader
                while (backUp1 != NULL) {
                    if (strcmp(backUp1->tipoNo, "MethodHeader") == 0) {
                        backUp2 = backUp1->child; //supostamente o tipo
                        backUp3 = backUp2->brother; //supostamente o id

                        if (backUp3->aAnotar == 0) {
                            error = 1;
                            break;
                        }

                        backUpTable = criarTabela(backUp3->valor, "Method");

                        backUpVar = criarVariavel("return", alterarTipo(backUp2->tipoNo));
                        backUpVar->isParametro = 0;
                        backUpTable->vars = backUpVar; //para a tabela local

                        backUp4 = backUp3->brother; //MethodParams
                        backUp5 = backUp4->child; //devera ser um param ou nada
                        while (backUp5 != NULL) {
                            if (strcmp(backUp5->tipoNo, "NULL") != 0) {
                                //adicionar o backUpVar a tabela global
                                backUpParam = CriarParametroTipo(alterarTipo(backUp5->child->tipoNo),
                                                             (backUp5->child)->brother->valor);

                                backUp = procurarVariavel(backUpVar->parametroTipos, (backUp5->child)->brother->valor);

                                if (backUpVar->parametroTipos == NULL) {
                                    backUpVar->parametroTipos = backUpParam;

                                } else {
                                    adicionarParametro(backUpVar->parametroTipos, backUpParam);
                                }

                                //adicionar a tabela local
                                backUp6 = (backUp5->child)->brother; //id do parametro
                                backUpVarLocal = criarVariavel(backUp6->valor, alterarTipo(backUp5->child->tipoNo));
                                if (backUp != NULL) {
                                    backUpVarLocal->isParametro = 2; //como e repetido, nao imprimir

                                } else {
                                    backUpVarLocal->isParametro = 1; //e uma variavel
                                }
                                backUpTable->params = backUpVar->parametroTipos;
                                adicionarVariavel(backUpTable->vars, backUpVarLocal);
                            }
                            backUp5 = backUp5->brother;
                        }
                    }
                    if (strcmp(backUp1->tipoNo, "MethodBody") == 0) {
                        backUp2 = backUp1->child;
                        while (backUp2 != NULL) {
                            if (strcmp(backUp2->tipoNo, "VarDecl") == 0) {
                                backUp3 = backUp2->child;
                                backUp4 = backUp3->brother;

                                if (procuraTipoVariavel(NULL, backUpTable, backUp4->valor) != NULL) {
                                    errosSemantica = 1;
                                    printf("Line %d, col %d: Symbol %s already defined\n", backUp4->linha, backUp4->coluna,
                                           backUp4->valor);

                                } else {
                                    backUpVar = criarVariavel(backUp4->valor, alterarTipo(backUp3->tipoNo));
                                    backUpVar->isParametro = 0;
                                    adicionarVariavel(backUpTable->vars, backUpVar); //Adicionar a tabela local
                                }

                            } else {
                                if (!(strcmp(backUp2->tipoNo, "NULL") == 0)) {
                                    anotarArvore(tabelaGlobal, backUpTable, backUp2);
                                }
                            }

                            backUp2 = backUp2->brother;
                        }
                    }

                    backUp1 = backUp1->brother; //Header ou Body
                }

                if (error != 1) {
                    if (tabelaLocal == NULL) {
                        tabelaLocal = backUpTable;

                    } else {
                        adicionarATabelaLocal(tabelaLocal, backUpTable);
                    }
                }
            }

            atual = atual->brother;
        }
    }
}


void limparTabelas(tabelaSimbolos *global, tabelaSimbolos *local) {
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

void limparTabLocais(tabelaSimbolos *tabelaLocal) {
    if (tabelaLocal == NULL) {
        return;
    }

    if (tabelaLocal->tableName != NULL) {
        free(tabelaLocal->tableName);
        tabelaLocal->tableName = NULL;
    }
    if (tabelaLocal->tableType != NULL) {
        free(tabelaLocal->tableType);
        tabelaLocal->tableType = NULL;
    }

    if (tabelaLocal->params != NULL) {
        limparParametros(tabelaLocal->params->seguinte);
        if (tabelaLocal->params->tipo != NULL) {
            free(tabelaLocal->params->tipo);
            tabelaLocal->params->tipo = NULL;
        }
        if (tabelaLocal->params->id != NULL) {
            free(tabelaLocal->params->id);
            tabelaLocal->params->id = NULL;
        }
        free(tabelaLocal->params);
        tabelaLocal->params = NULL;
    }
    if (tabelaLocal->vars != NULL) {
        limparVariaveis(tabelaLocal->vars->seguinte);
        if (tabelaLocal->vars->tipo != NULL) {
            free(tabelaLocal->vars->tipo);
            tabelaLocal->vars->tipo = NULL;
        }
        if (tabelaLocal->vars->nome != NULL) {
            free(tabelaLocal->vars->nome);
            tabelaLocal->vars->nome = NULL;
        }
        free(tabelaLocal->vars);
        tabelaLocal->vars = NULL;
    }

    limparTabLocais(tabelaLocal->seguinte);

    free(tabelaLocal);
    tabelaLocal = NULL;
}

void adicionarATabelaLocal(tabelaSimbolos *table, tabelaSimbolos *element) {
    tabelaSimbolos *backUp = table;

    if (backUp == NULL) {
        table = element;
        return;
    }

    while (backUp->seguinte != NULL) {
        backUp = backUp->seguinte;
    }

    backUp->seguinte = element;
}

void imprimirTabelaGlobal(tabelaSimbolos *atual) {
    listaVariaveis *backUpV = atual->vars;
    listaParametros *backUpP;

    printf("===== %s %s Symbol Table =====\n", atual->tableType, atual->tableName);
    while (backUpV != NULL) {
        if (backUpV->isFunction) {
            backUpP = backUpV->parametroTipos;
            printf("%s\t(", backUpV->nome);
            while (backUpP != NULL) {
                printf("%s", backUpP->tipo);
                if (backUpP->seguinte != NULL) {
                    printf(",");
                }
                backUpP = backUpP->seguinte;
            }
            printf(")\t%s", backUpV->tipo);

        } else {
            printf("%s\t\t%s", backUpV->nome, backUpV->tipo);
        }

        printf("\n");

        backUpV = backUpV->seguinte;
    }
    printf("\n");
}

void imprimirTabelasLocais(tabelaSimbolos *atual) {
    tabelaSimbolos *backUp = atual;
    listaVariaveis *backUpV;
    listaParametros *backUpP;

    while (backUp != NULL) {
        backUpV = backUp->vars;
        backUpP = backUp->params;
        if (backUpP != NULL) {
            printf("===== %s %s(", backUp->tableType, backUp->tableName);
            while (backUpP != NULL) {
                printf("%s", backUpP->tipo);
                if (backUpP->seguinte != NULL) {
                    printf(",");
                }
                backUpP = backUpP->seguinte;
            }
            printf(") Symbol Table =====\n");

        } else {
            printf("===== %s %s() Symbol Table =====\n", backUp->tableType, backUp->tableName);
        }
        while (backUpV != NULL) {
            if (backUpV->isParametro == 2) {

            } else if (backUpV->isParametro == 1) {
                printf("%s\t\t%s\t%s\n", backUpV->nome, backUpV->tipo, "param");

            } else {
                printf("%s\t\t%s\n", backUpV->nome, backUpV->tipo);
            }

            backUpV = backUpV->seguinte;
        }

        printf("\n");

        backUp = backUp->seguinte;
    }
}

void limparParametros(listaParametros *parametro) {
    if (parametro == NULL) {
        return;
    }

    if (parametro->tipo != NULL) {
        free(parametro->tipo);
        parametro->tipo = NULL;
    }
    if (parametro->id != NULL) {
        free(parametro->id);
        parametro->id = NULL;
    }

    limparParametros(parametro->seguinte);

    free(parametro);
    parametro = NULL;
}

listaParametros *CriarParametroTipo(char *tipo, char *id) {
    listaParametros *new = (listaParametros *) malloc(sizeof(listaParametros));
    new->tipo = (char *) strdup(tipo);
    new->id = (char *) strdup(id);
    new->seguinte = NULL;
    return new;
}

void adicionarParametro(listaParametros *paramList, listaParametros *new) {
    listaParametros *backUp = paramList;

    if (backUp == NULL) {
        paramList = new;
        return;
    }

    while (backUp->seguinte != NULL) {
        backUp = backUp->seguinte;
    }

    backUp->seguinte = new;
}

listaVariaveis *criarVariavel(char *nome, char *tipo) {
    listaVariaveis *new = (listaVariaveis *) malloc(sizeof(listaVariaveis));
    new->nome = (char *) strdup(nome);
    new->tipo = (char *) strdup(tipo);
    new->isFunction = false;
    new->isParametro = 0;
    new->numeroParametros = 0;
    new->parametroTipos = NULL;
    new->seguinte = NULL;
    return new;
}

void adicionarVariavel(listaVariaveis *varList, listaVariaveis *new) {
    listaVariaveis *backUp = varList;

    if (backUp == NULL) {
        varList = new;
        return;
    }

    while (backUp->seguinte != NULL) {
        backUp = backUp->seguinte;
    }

    backUp->seguinte = new;
}

void limparVariaveis(listaVariaveis *variavel) {
    if (variavel == NULL) {
        return;
    }

    if (variavel->tipo != NULL) {
        free(variavel->tipo);
        variavel->tipo = NULL;
    }
    if (variavel->nome != NULL) {
        free(variavel->nome);
        variavel->nome = NULL;
    }

    limparParametros(variavel->parametroTipos);
    limparVariaveis(variavel->seguinte);

    free(variavel);
    variavel = NULL;
}

char *alterarTipo(char *tipoNo) {

    if (strcmp(tipoNo, "Int") == 0) {
        tipoNo = "int";
        return tipoNo;
    }

    if (strcmp(tipoNo, "Double") == 0) {
        tipoNo = "double";
        return tipoNo;
    }

    if (strcmp(tipoNo, "Bool") == 0) {
        tipoNo = "boolean";
        return tipoNo;
    }

    if (strcmp(tipoNo, "Void") == 0) {
        tipoNo = "void";
        return tipoNo;
    }

    if (strcmp(tipoNo, "StringArray") == 0) {
        tipoNo = "String[]";
        return tipoNo;
    }

    return tipoNo;
}

char *procurarVariavel(listaParametros *params, char *var_name) {
    if (params == NULL) {
        return NULL;
    }

    listaParametros *backUpP = params;

    while (backUpP != NULL) {
        if (strcmp(backUpP->id, var_name) == 0) {
            return backUpP->tipo;
        }
        backUpP = backUpP->seguinte;
    }

    return NULL;
}

int procurarFuncao(tabelaSimbolos *table_global, listaParametros *backUp_parametroTipos, int count_params, char *nome) {
    listaVariaveis *backUp_vars;
    listaParametros *backUp_params1, *backUp_params2;
    int count_equals = 0;

    backUp_vars = table_global->vars;
    while (backUp_vars != NULL) {
        if (backUp_vars->isFunction && backUp_vars->numeroParametros == count_params && strcmp(backUp_vars->nome, nome) == 0) {
            count_equals = 0;
            backUp_params1 = backUp_vars->parametroTipos;
            backUp_params2 = backUp_parametroTipos;
            while (backUp_params1 != NULL) {
                if (strcmp(backUp_params1->tipo, backUp_params2->tipo) == 0) {
                    count_equals++;
                }
                backUp_params1 = backUp_params1->seguinte;
                backUp_params2 = backUp_params2->seguinte;
            }
            if (count_equals == count_params) {
                return 1;
            }
        }
        backUp_vars = backUp_vars->seguinte;
    }

    return 0;
}

char *procurarTipoVariavelTabela(tabelaSimbolos *table, char *var_name) {
    if (table == NULL) {
        return NULL;
    }

    listaVariaveis *backUpV = table->vars;

    while (backUpV != NULL) {
        if (strcmp(backUpV->nome, var_name) == 0 && !backUpV->isFunction) {
            return backUpV->tipo;
        }
        backUpV = backUpV->seguinte;
    }

    return NULL;
}

char *procuraTipoVariavel(tabelaSimbolos *table_global, tabelaSimbolos *table_local, char *var_name) {
    char *backUp = procurarTipoVariavelTabela(table_local, var_name);
    if (backUp != NULL) {
        return backUp;
    }
    backUp = procurarTipoVariavelTabela(table_global, var_name);
    if (backUp != NULL) {
        return backUp;
    }
    return NULL;
}

void anotarArvore(tabelaSimbolos *table_global, tabelaSimbolos *table_local, node *atual) {
    char *backUp;
    listaParametros *backUp_params, *final_params;
    listaVariaveis *backUp_vars;
    int count_params, count_equals, count_all_equals, find_function;
    node *backUp1, *backUp2, *backUp3, *ant;

    if (atual == NULL) {
        return;
    }

    if (strcmp(atual->tipoNo, "NULL") == 0) {
        return;

    } else if (strcmp(atual->tipoNo, "Id") == 0) {
        backUp = procuraTipoVariavel(table_global, table_local, atual->valor);
        if (backUp != NULL) {
            atual->anotacao = backUp;

        } else {
            errosSemantica = 1;
            printf("Line %d, col %d: Cannot find symbol %s\n", atual->linha, atual->coluna, atual->valor);
            atual->anotacao = "undef";
        }

    } else if (strcmp(atual->tipoNo, "If") == 0) {
        backUp1 = atual->child;
        anotarArvore(table_global, table_local, backUp1);
        backUp1 = backUp1->brother;

        backUp2 = atual->child;
        if (backUp2->anotacao != NULL && strcmp(backUp2->anotacao, "boolean")) {
            errosSemantica = 1;
            printf("Line %d, col %d: Incompatible tipo %s in if statement\n", backUp2->linha, backUp2->coluna, backUp2->anotacao);
        }

        while (backUp1 != NULL) {
            anotarArvore(table_global, table_local, backUp1);
            backUp1 = backUp1->brother;
        }
    } else if (strcmp(atual->tipoNo, "Block") == 0) {
        backUp1 = atual->child;
        while (backUp1 != NULL) {
            anotarArvore(table_global, table_local, backUp1);
            backUp1 = backUp1->brother;
        }
    } else if (strcmp(atual->tipoNo, "While") == 0) {
        backUp1 = atual->child;
        anotarArvore(table_global, table_local, backUp1);
        backUp1 = backUp1->brother;

        backUp2 = atual->child;
        if (strcmp(backUp2->anotacao, "boolean")) {
            errosSemantica = 1;
            printf("Line %d, col %d: Incompatible tipo %s in while statement\n", backUp2->linha, backUp2->coluna,
                   backUp2->anotacao);
            atual->anotacao = "undef";
        } else {
            atual->anotacao = "boolean";
        }

        while (backUp1 != NULL) {
            anotarArvore(table_global, table_local, backUp1);
            backUp1 = backUp1->brother;
        }

    } else if (strcmp(atual->tipoNo, "Print") == 0) {
        backUp1 = atual->child;
        while (backUp1 != NULL) {
            anotarArvore(table_global, table_local, backUp1);
            backUp1 = backUp1->brother;
        }

        backUp2 = atual->child;
        if (strcmp(backUp2->anotacao, "undef") == 0 || strcmp(backUp2->anotacao, "String[]") == 0 ||
            strcmp(backUp2->anotacao, "void") == 0) {
            errosSemantica = 1;
            printf("Line %d, col %d: Incompatible tipo %s in System.out.print statement\n", backUp2->linha, backUp2->coluna,
                   backUp2->anotacao);
        }
    } else if (strcmp(atual->tipoNo, "Return") == 0) {
        backUp1 = atual->child;
        while (backUp1 != NULL) {
            anotarArvore(table_global, table_local, backUp1);
            backUp1 = backUp1->brother;
        }

        backUp2 = atual->child;
        if (backUp2 != NULL) {
            if (strcmp(table_local->vars->tipo, "void") == 0) {
                errosSemantica = 1;
                printf("Line %d, col %d: Incompatible tipo %s in return statement\n", backUp2->linha, backUp2->coluna,
                       backUp2->anotacao);
            } else if (strcmp(table_local->vars->tipo, backUp2->anotacao) == 0) {
                return;
            } else if (strcmp(table_local->vars->tipo, "double") == 0) {
                if ((strcmp(backUp2->anotacao, "int") && strcmp(backUp2->anotacao, "double"))) {
                    errosSemantica = 1;
                    printf("Line %d, col %d: Incompatible tipo %s in return statement\n", backUp2->linha, backUp2->coluna,
                           backUp2->anotacao);
                }
            } else {
                errosSemantica = 1;
                printf("Line %d, col %d: Incompatible tipo %s in return statement\n", backUp2->linha, backUp2->coluna,
                       backUp2->anotacao);
            }
        } else {
            if (strcmp(table_local->vars->tipo, "void")) {
                errosSemantica = 1;
                printf("Line %d, col %d: Incompatible tipo void in return statement\n", atual->linha, atual->coluna);
            }
        }
    } else if (strcmp(atual->tipoNo, "Assign") == 0) {
        backUp1 = atual->child;
        while (backUp1 != NULL) {
            anotarArvore(table_global, table_local, backUp1);
            backUp1 = backUp1->brother;
        }

        backUp2 = atual->child;
        backUp3 = backUp2->brother;

        atual->anotacao = backUp2->anotacao;

        if (strcmp(backUp2->anotacao, backUp3->anotacao) == 0 && strcmp(backUp2->anotacao, "undef") &&
            strcmp(backUp2->anotacao, "String[]")) {
            return;
        } else if (strcmp(backUp2->anotacao, "double") == 0 && strcmp(backUp3->anotacao, "int") == 0) {
            return;
        } else {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator = cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                   backUp2->anotacao, backUp3->anotacao);
        }
    } else if (strcmp(atual->tipoNo, "Call") == 0) {
        count_params = 0;
        count_equals = 0;
        count_all_equals = 0;
        find_function = 0;
        backUp1 = (atual->child)->brother;
        while (backUp1 != NULL) {
            if (strcmp(backUp1->tipoNo, "NULL")) {
                count_params++;
            }
            anotarArvore(table_global, table_local, backUp1);
            backUp1 = backUp1->brother;
        }

        backUp_vars = table_global->vars;
        while (backUp_vars != NULL) {
            count_equals = 0;
            count_all_equals = 0;
            if (backUp_vars->isFunction && backUp_vars->numeroParametros == count_params &&
                strcmp(backUp_vars->nome, atual->child->valor) == 0) {
                backUp_params = backUp_vars->parametroTipos;
                backUp1 = (atual->child)->brother;
                while (backUp1 != NULL) {
                    if (strcmp(backUp1->tipoNo, "NULL")) {
                        if (strcmp(backUp_params->tipo, backUp1->anotacao) == 0) {
                            count_all_equals++;
                            count_equals++;
                        } else if (strcmp(backUp1->anotacao, "int") == 0 && strcmp(backUp_params->tipo, "double") == 0) {
                            count_equals++;
                        } else {
                            break;
                        }
                        backUp_params = backUp_params->seguinte;
                    }
                    backUp1 = backUp1->brother;
                }
                if (count_all_equals == count_params) {
                    find_function = 1;
                    backUp = backUp_vars->tipo;
                    final_params = backUp_vars->parametroTipos;
                    break;
                } else if (count_equals == count_params) {
                    backUp = backUp_vars->tipo;
                    final_params = backUp_vars->parametroTipos;
                    find_function++;
                }
            }
            backUp_vars = backUp_vars->seguinte;
        }

        if (find_function == 1) {
            atual->child->numeroParametros = count_params;
            if (final_params == NULL) {
                atual->child->params = NULL;
            } else {
                atual->child->params = final_params;
            }
            atual->anotacao = backUp;
        } else if (find_function > 1) {
            errosSemantica = 1;

            printf("Line %d, col %d: Reference to method %s(", atual->child->linha, atual->child->coluna,
                   atual->child->valor);
            backUp1 = (atual->child)->brother;
            while (backUp1 != NULL) {
                if (strcmp(backUp1->tipoNo, "NULL")) {
                    printf("%s", backUp1->anotacao);
                    if (backUp1->brother != NULL) {
                        printf(",");
                    }
                }
                backUp1 = backUp1->brother;
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
            backUp1 = (atual->child)->brother;
            while (backUp1 != NULL) {
                if (strcmp(backUp1->tipoNo, "NULL")) {
                    printf("%s", backUp1->anotacao);
                    if (count_params != 1) {
                        printf(",");
                    }
                    count_params--;
                }
                backUp1 = backUp1->brother;
            }
            printf(")\n");
        }
    } else if (strcmp(atual->tipoNo, "ParseArgs") == 0) {
        backUp1 = atual->child;
        while (backUp1 != NULL) {
            anotarArvore(table_global, table_local, backUp1);
            backUp1 = backUp1->brother;
        }

        backUp2 = atual->child;
        backUp3 = backUp2->brother;
        if (strcmp(backUp2->anotacao, "String[]")) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator Integer.parseInt cannot be applied to types %s, %s\n", atual->linha,
                   atual->coluna, backUp2->anotacao, backUp3->anotacao);
        } else if (strcmp(backUp3->anotacao, "int")) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator Integer.parseInt cannot be applied to types %s, %s\n", atual->linha,
                   atual->coluna, backUp2->anotacao, backUp3->anotacao);
        }

        atual->anotacao = "int";

    } else if (strcmp(atual->tipoNo, "Xor") == 0) {
        backUp1 = atual->child;
        while (backUp1 != NULL) {
            anotarArvore(table_global, table_local, backUp1);
            backUp1 = backUp1->brother;
        }

        backUp2 = atual->child;
        backUp3 = backUp2->brother;

        if (strcmp(backUp2->anotacao, "int") == 0 && strcmp(backUp3->anotacao, "int") == 0) {
            atual->anotacao = "int";

        } else if (strcmp(backUp2->anotacao, "boolean")) {

            errosSemantica = 1;
            printf("Line %d, col %d: Operator ^ cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                   backUp2->anotacao, backUp3->anotacao);

        } else if (strcmp(backUp3->anotacao, "boolean")) {

            errosSemantica = 1;
            printf("Line %d, col %d: Operator ^ cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                   backUp2->anotacao, backUp3->anotacao);

        }

        if (strcmp(backUp2->anotacao, "int") == 0 && strcmp(backUp3->anotacao, "int") == 0) {
            atual->anotacao = "int";
        } else {
            atual->anotacao = "boolean"; //TODO MELHORAR ISTO
        }

    } else if (strcmp(atual->tipoNo, "And") == 0 || strcmp(atual->tipoNo, "Or") == 0) {
        backUp1 = atual->child;
        while (backUp1 != NULL) {
            anotarArvore(table_global, table_local, backUp1);
            backUp1 = backUp1->brother;
        }

        backUp2 = atual->child;
        backUp3 = backUp2->brother;

        if (strcmp(backUp2->anotacao, "boolean") && strcmp(atual->tipoNo, "And") == 0) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator && cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                   backUp2->anotacao, backUp3->anotacao);

        } else if (strcmp(backUp2->anotacao, "boolean") && strcmp(atual->tipoNo, "Or") == 0) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator || cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                   backUp2->anotacao, backUp3->anotacao);

        } else if (strcmp(backUp3->anotacao, "boolean") && strcmp(atual->tipoNo, "And") == 0) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator && cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                   backUp2->anotacao, backUp3->anotacao);

        } else if (strcmp(backUp3->anotacao, "boolean") && strcmp(atual->tipoNo, "Or") == 0) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator || cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                   backUp2->anotacao, backUp3->anotacao);
        }

        atual->anotacao = "boolean";

    } else if (strcmp(atual->tipoNo, "Eq") == 0 || strcmp(atual->tipoNo, "Gt") == 0 || strcmp(atual->tipoNo, "Ge") == 0
               || strcmp(atual->tipoNo, "Le") == 0 || strcmp(atual->tipoNo, "Lt") == 0 || strcmp(atual->tipoNo, "Ne") == 0) {

        backUp1 = atual->child;
        while (backUp1 != NULL) {
            anotarArvore(table_global, table_local, backUp1);
            backUp1 = backUp1->brother;
        }

        backUp2 = atual->child;
        backUp3 = backUp2->brother;

        atual->anotacao = "boolean";

        if (strcmp(atual->tipoNo, "Eq") == 0) {
            backUp = "==";
        } else if (strcmp(atual->tipoNo, "Gt") == 0) {
            backUp = ">";
        } else if (strcmp(atual->tipoNo, "Ge") == 0) {
            backUp = ">=";
        } else if (strcmp(atual->tipoNo, "Le") == 0) {
            backUp = "<=";
        } else if (strcmp(atual->tipoNo, "Lt") == 0) {
            backUp = "<";
        } else if (strcmp(atual->tipoNo, "Ne") == 0) {
            backUp = "!=";
        }

        if (strcmp(atual->tipoNo, "Eq") == 0 || strcmp(atual->tipoNo, "Ne") == 0) {
            if (strcmp(backUp2->anotacao, "boolean") == 0 && strcmp(backUp3->anotacao, "boolean") == 0) {
                return;
            }
        }

        if (strcmp(backUp2->anotacao, "int") && strcmp(backUp2->anotacao, "double")) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->linha, atual->coluna, backUp,
                   backUp2->anotacao, backUp3->anotacao);
        } else if (strcmp(backUp3->anotacao, "double") && strcmp(backUp3->anotacao, "int")) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->linha, atual->coluna, backUp,
                   backUp2->anotacao, backUp3->anotacao);
        }
    } else if (strcmp(atual->tipoNo, "Lshift") == 0 || strcmp(atual->tipoNo, "Rshift") == 0) {

        backUp1 = atual->child;
        while (backUp1 != NULL) {
            anotarArvore(table_global, table_local, backUp1);
            backUp1 = backUp1->brother;
        }

        backUp2 = atual->child;
        backUp3 = backUp2->brother;

        if (strcmp(atual->tipoNo, "Lshift") == 0) {
            backUp = "<<";
        } else {
            backUp = ">>";
        }

        if (strcmp(backUp2->anotacao, "int") == 0) {
            if (strcmp(backUp3->anotacao, "int") == 0) {
                atual->anotacao = "int";
            } else {
                errosSemantica = 1;
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                       backUp, backUp2->anotacao, backUp3->anotacao);
                atual->anotacao = "undef";
            }

        } else if (strcmp(backUp3->anotacao, "int") == 0) {
            if (strcmp(backUp2->anotacao, "int") == 0) {
                atual->anotacao = "int";
            } else {
                errosSemantica = 1;
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                       backUp, backUp2->anotacao, backUp3->anotacao);
                atual->anotacao = "undef";
            }

        } else {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->linha, atual->coluna, backUp,
                   backUp2->anotacao, backUp3->anotacao);
            atual->anotacao = "undef";
        }

    } else if (strcmp(atual->tipoNo, "Add") == 0 || strcmp(atual->tipoNo, "Sub") == 0 || strcmp(atual->tipoNo, "Mul") == 0
               || strcmp(atual->tipoNo, "Div") == 0 || strcmp(atual->tipoNo, "Mod") == 0) {

        backUp1 = atual->child;
        while (backUp1 != NULL) {
            anotarArvore(table_global, table_local, backUp1);
            backUp1 = backUp1->brother;
        }

        backUp2 = atual->child;
        backUp3 = backUp2->brother;

        if (strcmp(atual->tipoNo, "Add") == 0) {
            backUp = "+";
        } else if (strcmp(atual->tipoNo, "Sub") == 0) {
            backUp = "-";
        } else if (strcmp(atual->tipoNo, "Mul") == 0) {
            backUp = "*";
        } else if (strcmp(atual->tipoNo, "Div") == 0) {
            backUp = "/";
        } else {
            backUp = "%";
        }

        if (strcmp(backUp2->anotacao, "int") == 0) {
            if (strcmp(backUp3->anotacao, "int") == 0) {
                atual->anotacao = "int";
            } else if (strcmp(backUp3->anotacao, "double") == 0) {
                atual->anotacao = "double";
            } else {
                errosSemantica = 1;
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                       backUp, backUp2->anotacao, backUp3->anotacao);
                atual->anotacao = "undef";
            }
        } else if (strcmp(backUp2->anotacao, "double") == 0) {
            if (strcmp(backUp3->anotacao, "int") && strcmp(backUp3->anotacao, "double")) {
                errosSemantica = 1;
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->linha, atual->coluna,
                       backUp, backUp2->anotacao, backUp3->anotacao);
                atual->anotacao = "undef";
            } else {
                atual->anotacao = "double";
            }
        } else {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->linha, atual->coluna, backUp,
                   backUp2->anotacao, backUp3->anotacao);
            atual->anotacao = "undef";
        }
    } else if (strcmp(atual->tipoNo, "Plus") == 0 || strcmp(atual->tipoNo, "Minus") == 0) {
        backUp1 = atual->child;
        while (backUp1 != NULL) {
            anotarArvore(table_global, table_local, backUp1);
            backUp1 = backUp1->brother;
        }

        backUp2 = atual->child;
        atual->anotacao = backUp2->anotacao;
        if (strcmp(backUp2->anotacao, "int") == 0 || strcmp(backUp2->anotacao, "double") == 0) {
            atual->anotacao = backUp2->anotacao;
        } else {
            atual->anotacao = "undef";
            if (strcmp(atual->tipoNo, "Plus") == 0) {
                errosSemantica = 1;
                printf("Line %d, col %d: Operator + cannot be applied to tipo %s\n", atual->linha, atual->coluna,
                       backUp2->anotacao);
            } else {
                errosSemantica = 1;
                printf("Line %d, col %d: Operator - cannot be applied to tipo %s\n", atual->linha, atual->coluna,
                       backUp2->anotacao);
            }
        }
    } else if (strcmp(atual->tipoNo, "Not") == 0) {
        backUp1 = atual->child;
        while (backUp1 != NULL) {
            anotarArvore(table_global, table_local, backUp1);
            backUp1 = backUp1->brother;
        }

        backUp2 = atual->child;
        if (strcmp(backUp2->anotacao, "boolean")) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator ! cannot be applied to tipo %s\n", atual->linha, atual->coluna,
                   backUp2->anotacao);
        }

        atual->anotacao = "boolean";
    } else if (strcmp(atual->tipoNo, "Length") == 0) {
        backUp1 = atual->child;
        while (backUp1 != NULL) {
            anotarArvore(table_global, table_local, backUp1);
            backUp1 = backUp1->brother;
        }

        backUp2 = atual->child;
        if (strcmp(backUp2->anotacao, "String[]")) {
            errosSemantica = 1;
            printf("Line %d, col %d: Operator .length cannot be applied to tipo %s\n", atual->linha, atual->coluna,
                   backUp2->anotacao);
        }
        atual->anotacao = "int";
    } else if (strcmp(atual->tipoNo, "BoolLit") == 0) {
        atual->anotacao = "boolean";
    } else if (strcmp(atual->tipoNo, "DecLit") == 0) {
        long l = strtol(atual->valor, NULL, 10);
        if (l >= 0 && l <= INT_MAX) {
            atual->anotacao = "int";
        } else {
            errosSemantica = 1;
            printf("Line %d, col %d: Number %s out of bounds\n", atual->linha, atual->coluna, atual->valor);
        }

        atual->anotacao = "int";
    } else if (strcmp(atual->tipoNo, "RealLit") == 0) {
        char *valor = atual->valor;
        char *backUp = (char *) malloc(sizeof(char) * 1024);
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
                backUp[j] = valor[i];
                j++;
            }
            i++;
        }
        backUp[j] = '\0';

        if (!zeros) {
            double d = atof(backUp);
            if (isinf(d) || d == 0 || d > DBL_MAX) {
                errosSemantica = 1;
                printf("Line %d, col %d: Number %s out of bounds\n", atual->linha, atual->coluna, atual->valor);
            }
        }

        atual->anotacao = "double";

        free(backUp);
        backUp = NULL;
    } else if (strcmp(atual->tipoNo, "StrLit") == 0) {
        atual->anotacao = "String";
    }
}

int isExpressao(char *tipoNo) {
    if (strcmp(tipoNo, "Assign") == 0 || strcmp(tipoNo, "Or") == 0 || strcmp(tipoNo, "And") == 0
        || strcmp(tipoNo, "Eq") == 0 || strcmp(tipoNo, "Ne") == 0 || strcmp(tipoNo, "Lt") == 0
        || strcmp(tipoNo, "Ge") == 0 || strcmp(tipoNo, "Add") == 0 || strcmp(tipoNo, "Sub") == 0
        || strcmp(tipoNo, "Mul") == 0 || strcmp(tipoNo, "Div") == 0 || strcmp(tipoNo, "Mod") == 0
        || strcmp(tipoNo, "Not") == 0 || strcmp(tipoNo, "Minus") == 0 || strcmp(tipoNo, "Plus") == 0
        || strcmp(tipoNo, "Length") == 0 || strcmp(tipoNo, "Call") == 0 || strcmp(tipoNo, "ParseArgs") == 0
        || strcmp(tipoNo, "BoolLit") == 0 || strcmp(tipoNo, "DecLit") == 0 || strcmp(tipoNo, "Id") == 0
        || strcmp(tipoNo, "RealLit") == 0 || strcmp(tipoNo, "StrLit") == 0 || strcmp(tipoNo, "Gt") == 0
        || strcmp(tipoNo, "Le") == 0
        || strcmp(tipoNo, "Lshift") == 0 || strcmp(tipoNo, "Rshift") == 0 || strcmp(tipoNo, "Xor") == 0) {
        return 1;

    } else {
        return 0;
    }
}

void imprimirArvoreAnotada(node *current, int n) {
    int i;
    listaParametros *backUp;

    if (current == NULL) {
        return;
    }

    if (strcmp(current->tipoNo, "NULL") == 0) {
        imprimirArvoreAnotada(current->brother, n);
        return;
    } else {
        for (i = 0; i < n; i++) {
            printf("..");
        }

        if (current->valor != NULL) {
            if (current->numeroParametros >= 0 && isExpressao(current->tipoNo) == 1) {
                printf("%s(%s) - (", current->tipoNo, current->valor);
                backUp = current->params;
                while (backUp != NULL) {
                    printf("%s", backUp->tipo);
                    if (backUp->seguinte != NULL) {
                        printf(",");
                    }
                    backUp = backUp->seguinte;
                }
                printf(")");
            } else if (current->anotacao != NULL && isExpressao(current->tipoNo) == 1) {
                printf("%s(%s) - %s", current->tipoNo, current->valor, current->anotacao);
            } else {
                printf("%s(%s)", current->tipoNo, current->valor);
            }
        } else {
            if (current->anotacao != NULL && isExpressao(current->tipoNo) == 1) {
                printf("%s - %s", current->tipoNo, current->anotacao);
            } else {
                printf("%s", current->tipoNo);
            }
        }
        printf("\n");
    }

    imprimirArvoreAnotada(current->child, n + 1);
    imprimirArvoreAnotada(current->brother, n);
}

int contadorWhile = 1;
int contadorLogico = 1;
int return_encontrado = 0;
int contadorStr = 1;
int contadorComparador = 1;
int contadorConversoes = 1;
int contadorVarsG = 1;
int contadorVarsL = 1;
int contadorIf = 1;

strlit_list *vars_encontradas;
strlit_list *lista_global_stringlit;

strlit_list *criarStr(char *valor, char *tipo){
    strlit_list *new = (strlit_list*)malloc(sizeof(strlit_list));
    new->valor = (char*)strdup(valor);
    new->tipo = (char*)strdup(tipo);
    new->seguinte = NULL;
    return new;
}

void limpaLista(strlit_list *variavel){
    if(variavel == NULL){
        return;
    }

    if(variavel->valor != NULL){
        free(variavel->valor);
        variavel->valor = NULL;
    }
    if(variavel->tipo != NULL){
        free(variavel->tipo);
        variavel->tipo = NULL;
    }

    limpaLista(variavel->seguinte);

    free(variavel);
    variavel = NULL;
}

void add_strlit(strlit_list *strList, strlit_list *new){
    strlit_list *backUp = strList;

    if(backUp == NULL){
        strList = new;
        return;
    }

    while(backUp->seguinte != NULL){
        backUp = backUp->seguinte;
    }

    backUp->seguinte = new;
}

void print_stringlit(strlit_list *stringlit_List){
    strlit_list *backUp_stringList = stringlit_List;
    printf("\n");
    while(backUp_stringList != NULL){
        printf("%s", backUp_stringList->valor);
        backUp_stringList = backUp_stringList->seguinte;
    }
}

void gera_llvm(node *raiz){
    print_declaracao_var_func_global(raiz);
    gera_codigo_llvm(raiz);
    print_stringlit(lista_global_stringlit);
    limpaLista(lista_global_stringlit);
}

void print_declaracao_var_func_global(node *raiz){ //da print das variaveis globais e das funcoes declaradas
    listaVariaveis *backUp_vars = tabelaGlobal->vars;
    int isParametro = 0;
    while(backUp_vars != NULL){
        if(!backUp_vars->isFunction){
            if(strcmp(backUp_vars->tipo, "int") == 0){
                printf("@global.var.%s = common global i32 0, align 4\n", backUp_vars->nome);
            }
            if(strcmp(backUp_vars->tipo, "double") == 0){
                printf("@global.var.%s = common global double 0.000000e+00, align 4\n", backUp_vars->nome);
            }
            if(strcmp(backUp_vars->tipo, "boolean") == 0){
                printf("@global.var.%s = common global i1 0, align 4\n", backUp_vars->nome);
            }
            contadorVarsG++;
        } else {
            if(strcmp(backUp_vars->tipo, "void") == 0 && strcmp(backUp_vars->nome, "main") == 0){
                isParametro = 1;
            }
        }

        backUp_vars = backUp_vars->seguinte;
    }

    printf("declare i32 @atoi(i8*)\n");
    printf("declare i32 @printf(i8*, ...)\n\n");
    printf("define i32 @main(i32 %%argc, i8** %%argv) {\n");
    if (isParametro == 1){
        printf("\tcall void @function.declaration.v.main.s.(i32 %%argc, i8** %%argv)\n");
    } 
    printf("\tret i32 0\n");
    printf("}\n\n");
}

int tamanhoStrlit;
char *stringStrlit;
char *stringDeclit;
char *stringReallit;
char *tipoFuncao;

void acertarStr(char *valor){
    valor++; //removes the first "
    valor[strlen(valor)-1] = 0; //removes the last "

    int i = 0, j = 0;

    tamanhoStrlit = 0;
    
    while (valor[i] != '\0') {
        if(valor[i] == '%'){
            tamanhoStrlit++;
            stringStrlit[j] = valor[i];
            j++;
            tamanhoStrlit++;
            stringStrlit[j] = valor[i];
            j++;
        }
        else if(valor[i] == '\\'){
            tamanhoStrlit++;
            i++;
            if(valor[i] == 'n'){
                stringStrlit[j] = '\\';
                j++;
                stringStrlit[j] = '0';
                j++;
                stringStrlit[j] = 'A';
                j++;
            }
            else if(valor[i] == 'f'){
                stringStrlit[j] = '\\';
                j++;
                stringStrlit[j] = '0';
                j++;
                stringStrlit[j] = 'C';
                j++;
            }
            else if(valor[i] == 'r'){
                stringStrlit[j] = '\\';
                j++;
                stringStrlit[j] = '0';
                j++;
                stringStrlit[j] = 'D';
                j++;
            }
            else if(valor[i] == '"'){
                stringStrlit[j] = '\\';
                j++;
                stringStrlit[j] = '2';
                j++;
                stringStrlit[j] = '2';
                j++;
            }
            else if(valor[i] == 't'){
                stringStrlit[j] = '\\';
                j++;
                stringStrlit[j] = '0';
                j++;
                stringStrlit[j] = '9';
                j++;
            }
            else if(valor[i] == '\\'){
                stringStrlit[j] = '\\';
                j++;
                stringStrlit[j] = '5';
                j++;
                stringStrlit[j] = 'C';
                j++;
            }
        }
        else{
            tamanhoStrlit++;
            stringStrlit[j] = valor[i];
            j++;
        }
        i++;
    }

    tamanhoStrlit++;
    stringStrlit[j] = '\\';
    stringStrlit[j+1] = '0';
    stringStrlit[j+2] = '0';
    stringStrlit[j+3] = '\0';
}

void gera_codigo_llvm(node *atual){
    node *backUp1;

    if(atual == NULL || strcmp(atual->tipoNo, "NULL") == 0){
        return;
    }

    if(strcmp(atual->tipoNo, "Program") == 0){
        backUp1 = atual->child;
        while(backUp1 != NULL){
            gera_codigo_llvm(backUp1);
            backUp1 = backUp1->brother;
        }
    }
    else if(strcmp(atual->tipoNo, "MethodDecl") == 0){
        stringStrlit = (char*)malloc(sizeof(char)*1024);
        stringDeclit = (char*)malloc(sizeof(char)*1024);
        stringReallit = (char*)malloc(sizeof(char)*1024);

        contadorVarsL = 1;
        contadorComparador = 1;
        contadorConversoes = 1;
        contadorIf = 1;
        contadorWhile = 1;
        contadorLogico = 1;
        tipoFuncao = NULL;
        return_encontrado = 0;
        vars_encontradas = NULL;

        backUp1 = atual->child;
        while(backUp1 != NULL){
            gera_codigo_llvm(backUp1);
            backUp1 = backUp1->brother;
        }

        limpaLista(vars_encontradas);
        vars_encontradas = NULL;
        free(stringStrlit);
        stringStrlit = NULL;
        free(stringDeclit);
        stringDeclit = NULL;
        free(stringReallit);
        stringReallit = NULL;
    }
    else if(strcmp(atual->tipoNo, "MethodHeader") == 0){
        criarHeaderInicial(atual);
    }
    else if(strcmp(atual->tipoNo, "MethodBody") == 0){
        backUp1 = atual->child;
        while(backUp1 != NULL){
            fazer_llvm_rec(backUp1);
            backUp1 = backUp1->brother;
        }

        if(tipoFuncao != NULL && strcmp(tipoFuncao, "Void") == 0){
            printf("\tret void\n");
        }
        else if(tipoFuncao != NULL){
            if(strcmp(tipoFuncao, "Int") == 0){
                printf("\tret i32 0\n");
            }
            else if(strcmp(tipoFuncao, "Double") == 0){
                printf("\tret double 0.000000e+00\n");
            }
            else{
                printf("\tret i1 1\n");
            }
        }

        printf("}\n");
    }
}

void criarHeaderInicial(node *atual){
    char *backUp_type, *backUp_name;
    int i, found_string = 0;
    node *backUp1, *backUp2, *backUp3, *backUp_node_params;

    backUp1 = atual->child; //FUNCTION TYPE
    backUp_type = backUp1->tipoNo;
    tipoFuncao = backUp1->tipoNo;

    backUp2 = backUp1->brother; //FUNCTION NAME
    backUp_name = backUp2->valor;
    backUp3 = backUp2->brother; //METHOD PARAMS

    char *backUp_name_f = (char*)malloc(1024*sizeof(char));
    char *backUp_params_f = (char*)malloc(1024*sizeof(char));
    char *backUp_main = (char*)strdup("i32 %argc, i8** %argv");
    int backUp_count_f, backUp_count_params_f = 0;

    backUp_node_params = backUp3->child;

    if(strcmp(backUp_type, "Void") == 0){
        sprintf(backUp_name_f, "function.declaration.%s.%s.", "v", backUp_name);
    }
    else if(strcmp(backUp_type, "Int") == 0){
        sprintf(backUp_name_f, "function.declaration.%s.%s.", "i", backUp_name);
    }
    else if(strcmp(backUp_type, "Double") == 0){
        sprintf(backUp_name_f, "function.declaration.%s.%s.", "d", backUp_name);
    }
    else{
        sprintf(backUp_name_f, "function.declaration.%s.%s.", "b", backUp_name);
    }

    backUp_count_f = strlen(backUp_name_f);

    while(backUp_node_params != NULL){
        
        node *brother = backUp_node_params->child;

        if(strcmp(backUp_node_params->tipoNo, "ParamDecl") == 0){
            if(vars_encontradas == NULL){
                vars_encontradas = criarStr(brother->brother->valor, brother->tipoNo);
            }
            else{
                add_strlit(vars_encontradas, criarStr(brother->brother->valor, brother->tipoNo));
            }
        }

        backUp_node_params = backUp_node_params->brother;
    }

    strlit_list *backUp_param_decl = vars_encontradas;

    while(backUp_param_decl != NULL){

        if(strcmp(backUp_param_decl->tipo, "StringArray") == 0){
            char *backUp = (char*)strdup("s.");
            i = 0;
            while(backUp[i] != '\0'){
                backUp_name_f[backUp_count_f] = backUp[i];
                backUp_count_f++;
                i++;
            }

            found_string = 1;

            free(backUp);
            backUp = NULL;

            break;
        }
        if(strcmp(backUp_param_decl->tipo, "Int") == 0){
            char *backUp;
            backUp = (char*)strdup("i.");
            i = 0;
            while(backUp[i] != '\0'){
                backUp_name_f[backUp_count_f] = backUp[i];
                backUp_count_f++;
                i++;
            }

            free(backUp);
            backUp = NULL;

            backUp = (char*)malloc(1024*sizeof(char));
            sprintf(backUp, "i32 %%%s_backUp", backUp_param_decl->valor);
            i = 0;
            while(backUp[i] != '\0'){
                backUp_params_f[backUp_count_params_f] = backUp[i];
                backUp_count_params_f++;
                i++;
            }

            free(backUp);
            backUp = NULL;
        }
        if(strcmp(backUp_param_decl->tipo, "Bool") == 0){

            char *backUp;
            backUp = (char*)strdup("b.");
            i = 0;
            while(backUp[i] != '\0'){
                backUp_name_f[backUp_count_f] = backUp[i];
                backUp_count_f++;
                i++;
            }

            free(backUp);
            backUp = NULL;

            backUp = (char*)malloc(1024*sizeof(char));
            sprintf(backUp, "i1 %%%s_backUp", backUp_param_decl->valor);
            i = 0;
            while(backUp[i] != '\0'){
                backUp_params_f[backUp_count_params_f] = backUp[i];
                backUp_count_params_f++;
                i++;
            }

            free(backUp);
            backUp = NULL;
        }
        if(strcmp(backUp_param_decl->tipo, "Double") == 0){
            char *backUp;
            backUp = (char*)strdup("d.");
            i = 0;
            while(backUp[i] != '\0'){
                backUp_name_f[backUp_count_f] = backUp[i];
                backUp_count_f++;
                i++;
            }

            free(backUp);
            backUp = NULL;

            backUp = (char*)malloc(1024*sizeof(char));
            sprintf(backUp, "double %%%s_backUp", backUp_param_decl->valor);
            i = 0;
            while(backUp[i] != '\0'){
                backUp_params_f[backUp_count_params_f] = backUp[i];
                backUp_count_params_f++;
                i++;
            }

            free(backUp);
            backUp = NULL;
        }

        if(backUp_param_decl->seguinte != NULL){
            backUp_params_f[backUp_count_params_f] = ',';
            backUp_count_params_f++;
            backUp_params_f[backUp_count_params_f] = ' ';
            backUp_count_params_f++;
        }

        backUp_param_decl = backUp_param_decl->seguinte;
    }

    backUp_name_f[backUp_count_f] = '\0';
    backUp_params_f[backUp_count_params_f] = '\0';

    if(strcmp(backUp_type, "Void") == 0){
        if(found_string == 0){
            printf("define void @%s(%s) {\n", backUp_name_f, backUp_params_f);
        }
        else{
            printf("define void @%s(%s) {\n", backUp_name_f, backUp_main);
        }
    }
    else if(strcmp(backUp_type, "Int") == 0){
        if(found_string == 0){
            printf("define i32 @%s(%s) {\n", backUp_name_f, backUp_params_f);
        }
        else{
            printf("define i32 @%s(%s) {\n", backUp_name_f, backUp_main);
        }
    }
    else if(strcmp(backUp_type, "Double") == 0){
        if(found_string == 0){
            printf("define double @%s(%s) {\n", backUp_name_f, backUp_params_f);
        }
        else{
            printf("define double @%s(%s) {\n", backUp_name_f, backUp_main);
        }
    }
    else if(strcmp(backUp_type, "Bool") == 0){
        if(found_string == 0){
            printf("define i1 @%s(%s) {\n", backUp_name_f, backUp_params_f);
        }
        else{
            printf("define i1 @%s(%s) {\n", backUp_name_f, backUp_main);
        }
    }

    if(found_string == 1){
        printf("\t%%argc_backUp = alloca i32, align 4\n");
        printf("\t%%argv_backUp = alloca i8**, align 8\n");
        printf("\tstore i32 %%argc, i32* %%argc_backUp, align 4\n");
        printf("\tstore i8** %%argv, i8*** %%argv_backUp, align 8\n");
        limpaLista(vars_encontradas);
        vars_encontradas = NULL;
    }
    else{
        strlit_list *atual = vars_encontradas;
        while(atual != NULL){
            if(strcmp(atual->tipo, "Int") == 0){
                printf("\t%%%s = alloca i32, align 4\n", atual->valor);
                printf("\tstore i32 %%%s_backUp, i32* %%%s, align 4\n", atual->valor, atual->valor);
            }
            else if(strcmp(atual->tipo, "Double") == 0){
                printf("\t%%%s = alloca double, align 8\n", atual->valor);
                printf("\tstore double %%%s_backUp, double* %%%s, align 8\n", atual->valor, atual->valor);
            }
            else if(strcmp(atual->tipo, "Bool") == 0){
                printf("\t%%%s = alloca i1\n", atual->valor);
                printf("\tstore i1 %%%s_backUp, i1* %%%s\n", atual->valor, atual->valor);
            }
            
            atual = atual->seguinte;
        }
    }

    free(backUp_name_f);
    backUp_name_f = NULL;
    free(backUp_params_f);
    backUp_params_f = NULL;
    free(backUp_main);
    backUp_main = NULL;
}

char *verify_its_global(char *nome){
    char *backUp = NULL;
    strlit_list *atual = vars_encontradas;
    while(atual != NULL){
        if(strcmp(atual->valor, nome) == 0){
            return nome;
        }
        atual = atual->seguinte;
    }

    return backUp;
}

void tratarVarDecl(char *tipo, char *nome){
    if(strcmp(tipo, "Int") == 0){
        printf("\t%%%s = alloca i32, align 4\n", nome);
    }
    if(strcmp(tipo, "Double") == 0){
        printf("\t%%%s = alloca double, align 8\n", nome);
    }
    if(strcmp(tipo, "Bool") == 0){
        printf("\t%%%s = alloca i1\n", nome);
    }

    if(vars_encontradas == NULL){
        vars_encontradas = criarStr(nome, tipo);
    }
    else{
        add_strlit(vars_encontradas, criarStr(nome, tipo));
    }
}

void tratarReal(node *atual){
    acertarReal(atual->valor);
    printf("\t%%%d = fadd double 0.000000e+00, %.16e\n", contadorVarsL, atof(stringReallit));
    contadorVarsL++;
}

void tratarDec(node *atual){
    acertarDec(atual->valor);
    printf("\t%%%d = add i32 0, %s\n", contadorVarsL, stringDeclit);
    contadorVarsL++;
}

void tratarBool(node *atual){
    if(strcmp(atual->valor, "true") == 0){
        printf("\t%%%d = add i1 0, 1\n", contadorVarsL);
    }
    else{
        printf("\t%%%d = add i1 0, 0\n", contadorVarsL);
    }
    contadorVarsL++;
}

void tratarLen(node *atual){
    printf("\t%%%d = load i32, i32* %%argc_backUp, align 4\n", contadorVarsL);
    contadorVarsL++;
    printf("\t%%%d = sub i32 %%%d, 1\n", contadorVarsL, contadorVarsL-1);
    contadorVarsL++;
}

void tratarPrint(node *atual){
    strlit_list *backUp_str;
    char *backUp = (char*)malloc(1024*sizeof(char));

    if(strcmp(atual->child->anotacao, "String") == 0){
        acertarStr(atual->child->valor);
        sprintf(backUp, "@.global.strlit.%d = private unnamed_addr constant [%d x i8] c\"%s\", align 1\n", contadorStr, tamanhoStrlit, stringStrlit);
        printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([%d x i8], [%d x i8]* @.global.strlit.%d, i32 0, i32 0))\n", contadorVarsL, tamanhoStrlit, tamanhoStrlit, contadorStr);
        contadorVarsL++;
    }
    else if(strcmp(atual->child->anotacao, "int") == 0){
        sprintf(backUp, "@.global.strlit.%d = private unnamed_addr constant [3 x i8] c\"%%d\\00\", align 1\n", contadorStr);
        printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.%d, i32 0, i32 0), i32 %%%d)\n", contadorVarsL, contadorStr, contadorVarsL-1);
        contadorVarsL++;
    }
    else if(strcmp(atual->child->anotacao, "double") == 0){                 
        sprintf(backUp, "@.global.strlit.%d = private unnamed_addr constant [6 x i8] c\"%%.16e\\00\", align 1\n", contadorStr);
        printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.%d, i32 0, i32 0), double %%%d)\n", contadorVarsL, contadorStr, contadorVarsL-1);
        contadorVarsL++;
    }
    else if(strcmp(atual->child->anotacao, "boolean") == 0){
        printf("\t%%compare.%d = icmp eq i1 %%%d, 1\n", contadorComparador, contadorVarsL-1);
        printf("\tbr i1 %%compare.%d, label %%compare.if.%d, label %%compare.else.%d\n", contadorComparador, contadorComparador, contadorComparador);
        printf("\tcompare.if.%d:\n", contadorComparador);
        sprintf(backUp, "@.global.strlit.%d = private unnamed_addr constant [5 x i8] c\"true\\00\", align 1\n", contadorStr);
        printf("\t\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.global.strlit.%d, i32 0, i32 0))\n", contadorVarsL, contadorStr);
        printf("\t\tbr label %%compare.end.%d\n", contadorComparador);
        contadorVarsL++;
        contadorStr++;
        
        //ADD TO LIST
        if(lista_global_stringlit == NULL){
            lista_global_stringlit = criarStr(backUp, atual->child->anotacao);
        }
        else{
            backUp_str = criarStr(backUp, atual->child->anotacao);
            add_strlit(lista_global_stringlit, backUp_str);
        }

        printf("\tcompare.else.%d:\n", contadorComparador);
        printf("\t\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.%d, i32 0, i32 0))\n", contadorVarsL, contadorStr);
        printf("\t\tbr label %%compare.end.%d\n", contadorComparador);
        sprintf(backUp, "@.global.strlit.%d = private unnamed_addr constant [6 x i8] c\"false\\00\", align 1\n", contadorStr);
        printf("\tcompare.end.%d:\n", contadorComparador);
        contadorComparador++;
        contadorVarsL++;
    }

    if(lista_global_stringlit == NULL){
        lista_global_stringlit = criarStr(backUp, atual->child->anotacao);
    }
    else{
        backUp_str = criarStr(backUp, atual->child->anotacao);
        add_strlit(lista_global_stringlit, backUp_str);
    }

    contadorStr++;

    free(backUp);
    backUp = NULL;
}

void tratarAtr(node *atual){
    node *backUp = atual->child;
    if(strcmp(backUp->anotacao, "int") == 0){
        if(verify_its_global(backUp->valor) != NULL){
            printf("\tstore i32 %%%d, i32* %%%s, align 4\n", contadorVarsL-1, backUp->valor);
        }
        else{
            printf("\tstore i32 %%%d, i32* @global.var.%s, align 4\n", contadorVarsL-1, backUp->valor);
        }
    }
    else if(strcmp(backUp->anotacao, "double") == 0){
        if(strcmp(backUp->brother->anotacao, "int") == 0){
            printf("\t%%convertion.%d = sitofp i32 %%%d to double\n", contadorConversoes, contadorVarsL-1);
            if(verify_its_global(backUp->valor) != NULL){
                printf("\tstore double %%convertion.%d, double* %%%s, align 8\n", contadorConversoes, backUp->valor);                  
            }
            else{
                printf("\tstore double %%convertion.%d, double* @global.var.%s, align 8\n", contadorConversoes, backUp->valor);                                     
            }
            contadorConversoes++;
        }
        else{
            if(verify_its_global(backUp->valor) != NULL){
                printf("\tstore double %%%d, double* %%%s, align 8\n", contadorVarsL-1, backUp->valor);                  
            }
            else{
                printf("\tstore double %%%d, double* @global.var.%s, align 8\n", contadorVarsL-1, backUp->valor);                                     
            }
        }
    }
    else if(strcmp(backUp->anotacao, "boolean") == 0){
        if(verify_its_global(backUp->valor) != NULL){
            printf("\tstore i1 %%%d, i1* %%%s\n", contadorVarsL-1, backUp->valor);                   
        }
        else{
            printf("\tstore i1 %%%d, i1* @global.var.%s\n", contadorVarsL-1, backUp->valor);
        }
    }
}

void tratarId(node *atual){
    if(strcmp(atual->anotacao, "String[]") == 0){
        //printf("\t%%%d = load i8**, i8*** %%argv_backUp, align 8\n", contadorVarsL);
        //contadorVarsL++;
        return;
    }
    else if(verify_its_global(atual->valor) != NULL){
        if(strcmp(atual->anotacao, "int") == 0){
            printf("\t%%%d = load i32, i32* %%%s, align 4\n", contadorVarsL, atual->valor);
        }
        else if(strcmp(atual->anotacao, "double") == 0){
            printf("\t%%%d = load double, double* %%%s, align 8\n", contadorVarsL, atual->valor);
        }
        else if(strcmp(atual->anotacao, "boolean") == 0){
            printf("\t%%%d = load i1, i1* %%%s\n", contadorVarsL, atual->valor);
        }
        contadorVarsL++;
    }
    else{
        if(strcmp(atual->anotacao, "int") == 0){
            printf("\t%%%d = load i32, i32* @global.var.%s, align 4\n", contadorVarsL, atual->valor);
        }
        else if(strcmp(atual->anotacao, "double") == 0){
            printf("\t%%%d = load double, double* @global.var.%s, align 8\n", contadorVarsL, atual->valor);
        }
        else if(strcmp(atual->anotacao, "boolean") == 0){
            printf("\t%%%d = load i1, i1* @global.var.%s\n", contadorVarsL, atual->valor);
        }
        contadorVarsL++;
    }
}

void tratarMenos(node *atual){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = sub nsw i32 0, %%%d\n", contadorVarsL, contadorVarsL-1);
        contadorVarsL++;
    }
    else{
        printf("\t%%%d = fsub double -0.000000e+00, %%%d\n", contadorVarsL, contadorVarsL-1);
        contadorVarsL++;
    }
}

void tratarParse(node *atual){
    printf("\t%%%d = add i32 %%%d, 1\n", contadorVarsL, contadorVarsL-1);
    contadorVarsL++;
    printf("\t%%%d = load i8**, i8*** %%argv_backUp, align 8\n", contadorVarsL);
    contadorVarsL++;
    printf("\t%%%d = getelementptr inbounds i8*, i8** %%%d, i32 %%%d\n", contadorVarsL, contadorVarsL-1, contadorVarsL-2);
    contadorVarsL++;
    printf("\t%%%d = load i8*, i8** %%%d, align 8\n", contadorVarsL, contadorVarsL-1);
    contadorVarsL++;
    printf("\t%%%d = call i32 @atoi(i8* %%%d)\n", contadorVarsL, contadorVarsL-1);
    contadorVarsL++;
}

void tratarAdd(node *atual, int var1, int var2){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = add i32 %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var1);
            var1 = contadorVarsL;
            contadorVarsL++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var2);
            var2 = contadorVarsL;
            contadorVarsL++;
        }
        printf("\t%%%d = fadd double %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
}

void tratarSub(node *atual, int var1, int var2){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = sub i32 %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var1);
            var1 = contadorVarsL;
            contadorVarsL++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var2);
            var2 = contadorVarsL;
            contadorVarsL++;
        }
        printf("\t%%%d = fsub double %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
}

void tratarMul(node *atual, int var1, int var2){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = mul i32 %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var1);
            var1 = contadorVarsL;
            contadorVarsL++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var2);
            var2 = contadorVarsL;
            contadorVarsL++;
        }
        printf("\t%%%d = fmul double %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
}

void tratarDiv(node *atual, int var1, int var2){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = sdiv i32 %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var1);
            var1 = contadorVarsL;
            contadorVarsL++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var2);
            var2 = contadorVarsL;
            contadorVarsL++;
        }
        printf("\t%%%d = fdiv double %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
}

void tratarMod(node *atual, int var1, int var2){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = srem i32 %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var1);
            var1 = contadorVarsL;
            contadorVarsL++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var2);
            var2 = contadorVarsL;
            contadorVarsL++;
        }
        printf("\t%%%d = frem double %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
}

void tratarNot(node *atual, int var1){
    printf("\t%%%d = zext i1 %%%d to i32\n", contadorVarsL, var1);
    contadorVarsL++;
    printf("\t%%%d = icmp eq i32 %%%d, 0\n", contadorVarsL, contadorVarsL-1);
    contadorVarsL++;
}

void tratarIgual(node *atual, int var1, int var2){
    if(strcmp(atual->child->anotacao, "int") == 0 && strcmp(atual->child->brother->anotacao, "int") == 0){
        printf("\t%%%d = icmp eq i32 %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
    else if(strcmp(atual->child->anotacao, "boolean") == 0 && strcmp(atual->child->brother->anotacao, "boolean") == 0){
        printf("\t%%%d = zext i1 %%%d to i32\n", contadorVarsL, var1);
        contadorVarsL++;
        printf("\t%%%d = zext i1 %%%d to i32\n", contadorVarsL, var2);
        contadorVarsL++;
        printf("\t%%%d = icmp eq i32 %%%d, %%%d\n", contadorVarsL, contadorVarsL-1, contadorVarsL-2);
        contadorVarsL++;
    }
    else{
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var1);
            var1 = contadorVarsL;
            contadorVarsL++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var2);
            var2 = contadorVarsL;
            contadorVarsL++;
        }
        printf("\t%%%d = fcmp oeq double %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
}

void tratarDif(node *atual, int var1, int var2){
    if(strcmp(atual->child->anotacao, "int") == 0 && strcmp(atual->child->brother->anotacao, "int") == 0){
        printf("\t%%%d = icmp ne i32 %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
    else if(strcmp(atual->child->anotacao, "boolean") == 0 && strcmp(atual->child->brother->anotacao, "boolean") == 0){
        printf("\t%%%d = zext i1 %%%d to i32\n", contadorVarsL, var1);
        contadorVarsL++;
        printf("\t%%%d = zext i1 %%%d to i32\n", contadorVarsL, var2);
        contadorVarsL++;
        printf("\t%%%d = icmp ne i32 %%%d, %%%d\n", contadorVarsL, contadorVarsL-1, contadorVarsL-2);
        contadorVarsL++;
    }
    else{ //tem um double
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var1);
            var1 = contadorVarsL;
            contadorVarsL++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var2);
            var2 = contadorVarsL;
            contadorVarsL++;
        }
        printf("\t%%%d = fcmp une double %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
}

void tratarMenor(node *atual, int var1, int var2){
    if(strcmp(atual->child->anotacao, "int") == 0 && strcmp(atual->child->brother->anotacao, "int") == 0){
        printf("\t%%%d = icmp slt i32 %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
    else{
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var1);
            var1 = contadorVarsL;
            contadorVarsL++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var2);
            var2 = contadorVarsL;
            contadorVarsL++;
        }
        printf("\t%%%d = fcmp olt double %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
}

void tratarMaior(node *atual, int var1, int var2){
    if(strcmp(atual->child->anotacao, "int") == 0 && strcmp(atual->child->brother->anotacao, "int") == 0){
        printf("\t%%%d = icmp sgt i32 %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
    else{ //tem um double
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var1);
            var1 = contadorVarsL;
            contadorVarsL++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var2);
            var2 = contadorVarsL;
            contadorVarsL++;
        }
        printf("\t%%%d = fcmp ogt double %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
}

void tratarMenorIgual(node *atual, int var1, int var2){
    if(strcmp(atual->child->anotacao, "int") == 0 && strcmp(atual->child->brother->anotacao, "int") == 0){
        printf("\t%%%d = icmp sle i32 %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
    else{
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var1);
            var1 = contadorVarsL;
            contadorVarsL++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var2);
            var2 = contadorVarsL;
            contadorVarsL++;
        }
        printf("\t%%%d = fcmp ole double %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
}

void tratarMaiorIgual(node *atual, int var1, int var2){
    if(strcmp(atual->child->anotacao, "int") == 0 && strcmp(atual->child->brother->anotacao, "int") == 0){
        printf("\t%%%d = icmp sge i32 %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
    else{
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var1);
            var1 = contadorVarsL;
            contadorVarsL++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var2);
            var2 = contadorVarsL;
            contadorVarsL++;
        }
        printf("\t%%%d = fcmp oge double %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
}

void tratarAnd(node *atual){
    node *first = atual->child->brother;
    while(strcmp(first->tipoNo, "NULL") == 0){
        first = first->brother;
    }

    int contador_backUp_logico = contadorLogico;
    contadorLogico++;
    printf("\tbr label %%label.entry%d\n", contador_backUp_logico);
    printf("label.entry%d:\n", contador_backUp_logico);
    printf("\t%%%d = icmp eq i1 %%%d, 1\n", contadorVarsL, contadorVarsL-1);
    printf("\tbr i1 %%%d, label %%label.transition%d, label %%label.end%d\n", contadorVarsL, contador_backUp_logico, contador_backUp_logico);
    printf("label.transition%d:\n", contador_backUp_logico);
    contadorVarsL++;
    fazer_llvm_rec(first);
    printf("\t%%%d = icmp eq i1 %%%d, 1\n", contadorVarsL, contadorVarsL-1);
    printf("\tbr label %%label.end%d\n", contador_backUp_logico);
    printf("label.end%d:\n", contador_backUp_logico);
    contadorVarsL++;
    if(contador_backUp_logico == contadorLogico-1){ //nao ha mais and
        printf("\t%%%d = phi i1 [ 0, %%label.entry%d ], [ %%%d, %%label.transition%d ]\n", contadorVarsL, contador_backUp_logico, contadorVarsL-1, contador_backUp_logico);
    }
    else{ //ainda ha mais and
        printf("\t%%%d = phi i1 [ 0, %%label.entry%d ], [ %%%d, %%label.end%d ]\n", contadorVarsL, contador_backUp_logico, contadorVarsL-1, contador_backUp_logico+1);
    }
    contadorVarsL++;
}

void function_xor(node *atual, int var1, int var2){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = xor i32 %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var1);
            var1 = contadorVarsL;
            contadorVarsL++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var2);
            var2 = contadorVarsL;
            contadorVarsL++;
        }
        printf("\t%%%d = fxor double %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
}

void tratarOr(node *atual){
    node *first = atual->child->brother;
    while(strcmp(first->tipoNo, "NULL") == 0){
        first = first->brother;
    }

    int contador_backUp_logico = contadorLogico;
    contadorLogico++;
    printf("\tbr label %%label.entry%d\n", contador_backUp_logico);
    printf("label.entry%d:\n", contador_backUp_logico);
    printf("\t%%%d = icmp eq i1 %%%d, 0\n", contadorVarsL, contadorVarsL-1);
    printf("\tbr i1 %%%d, label %%label.transition%d, label %%label.end%d\n", contadorVarsL, contador_backUp_logico, contador_backUp_logico);
    printf("label.transition%d:\n", contador_backUp_logico);
    contadorVarsL++;
    fazer_llvm_rec(first);
    printf("\t%%%d = icmp eq i1 %%%d, 1\n", contadorVarsL, contadorVarsL-1);
    printf("\tbr label %%label.end%d\n", contador_backUp_logico);
    printf("label.end%d:\n", contador_backUp_logico);
    contadorVarsL++;
    if(contador_backUp_logico == contadorLogico-1){
        printf("\t%%%d = phi i1 [ 1, %%label.entry%d ], [ %%%d, %%label.transition%d ]\n", contadorVarsL, contador_backUp_logico, contadorVarsL-1, contador_backUp_logico);
    }
    else{
        printf("\t%%%d = phi i1 [ 1, %%label.entry%d ], [ %%%d, %%label.end%d ]\n", contadorVarsL, contador_backUp_logico, contadorVarsL-1, contador_backUp_logico+1);
    }
    contadorVarsL++;
}

void function_lshift(node *atual, int var1, int var2){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = shl i32 %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var1);
            var1 = contadorVarsL;
            contadorVarsL++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var2);
            var2 = contadorVarsL;
            contadorVarsL++;
        }
        printf("\t%%%d = fshl double %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
}

void function_rshift(node *atual, int var1, int var2){
    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = ashr i32 %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        if(strcmp(atual->child->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var1);
            var1 = contadorVarsL;
            contadorVarsL++;
        }
        if(strcmp(atual->child->brother->anotacao, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, var2);
            var2 = contadorVarsL;
            contadorVarsL++;
        }
        printf("\t%%%d = fashr double %%%d, %%%d\n", contadorVarsL, var1, var2);
        contadorVarsL++;
    }
}


void tratarIf(node *atual){
    node *first = atual->child->brother;
    while(strcmp(first->tipoNo, "NULL") == 0){
        first = first->brother;
    }
    node *second = first->brother;

    while(strcmp(second->tipoNo, "NULL") == 0){
        second = second->brother;
    }

    int backUp_contadorIf = contadorIf;
    contadorIf++;

    printf("\tbr label %%label.entry.if%d\n", backUp_contadorIf);
    printf("label.entry.if%d:\n", backUp_contadorIf);
    printf("\t%%%d = icmp eq i1 %%%d, 1\n", contadorVarsL, contadorVarsL-1);
    printf("\tbr i1 %%%d, label %%label.then%d, label %%label.else%d\n", contadorVarsL, backUp_contadorIf, backUp_contadorIf);
    contadorVarsL++;

    printf("label.then%d:\n", backUp_contadorIf);
    fazer_llvm_rec(first);
    printf("br label %%label.finished.if%d\n", backUp_contadorIf);
    
    printf("label.else%d:\n", backUp_contadorIf);
    fazer_llvm_rec(second);
    printf("br label %%label.finished.if%d\n", backUp_contadorIf);
    
    printf("label.finished.if%d:\n", backUp_contadorIf);
    
}

void tratarWhile(node *atual){
    node *first = atual->child;
    while(strcmp(first->tipoNo, "NULL") == 0){
        first = first->brother;
    }
    node *second = first->brother;
    while(strcmp(second->tipoNo, "NULL") == 0){
        second = second->brother;
    }

    int backUp_contadorWhile = contadorWhile;
    contadorWhile++;

    printf("\tbr label %%label.entry.while%d\n", backUp_contadorWhile);
    printf("label.entry.while%d:\n", backUp_contadorWhile);
    fazer_llvm_rec(first);
    printf("\t%%%d = icmp eq i1 %%%d, 1\n", contadorVarsL, contadorVarsL-1);
    printf("\tbr i1 %%%d, label %%label.work.while%d, label %%label.finished.while%d\n", contadorVarsL, backUp_contadorWhile, backUp_contadorWhile);
    contadorVarsL++;
    
    printf("label.work.while%d:\n", backUp_contadorWhile);
    fazer_llvm_rec(second);
    printf("\tbr label %%label.entry.while%d\n", backUp_contadorWhile);
    
    printf("label.finished.while%d:\n", backUp_contadorWhile);
    
}


void tratarReturn(node *atual){
    if(atual->child == NULL){
        printf("\tret void\n");
        contadorVarsL++;
        return;
    }
    fazer_llvm_rec(atual->child);
    if(strcmp(atual->child->anotacao, "int") == 0){
        if(strcmp(tipoFuncao, "Double") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, contadorVarsL-1);
            contadorVarsL++;
            printf("\tret double %%%d\n", contadorVarsL-1);
        }
        else{
            printf("\tret i32 %%%d\n", contadorVarsL-1);
        }
    }
    else if(strcmp(atual->child->anotacao, "double") == 0){
        printf("\tret double %%%d\n", contadorVarsL-1);
    }
    else{
        printf("\tret i1 %%%d\n", contadorVarsL-1);
    }
    contadorVarsL++;
}

void tratarChamada(node *atual){
    int i;
    listaParametros *backUp_params;
    node *backUp_node_params;
    char *backUp_name_f = (char*)malloc(1024*sizeof(char));
    char *backUp_params_f = (char*)malloc(1024*sizeof(char));
    int backUp_count_f = 0, backUp_count_params_f = 0, numeroParametros;

    backUp_params = atual->child->params;
    numeroParametros = atual->child->numeroParametros;
    backUp_node_params = atual->child->brother;

    if(strcmp(atual->anotacao, "boolean") == 0){
        sprintf(backUp_name_f, "function.declaration.%s.%s.", "b", atual->child->valor);
    }
    else if(strcmp(atual->anotacao, "int") == 0){
        sprintf(backUp_name_f, "function.declaration.%s.%s.", "i", atual->child->valor);
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        sprintf(backUp_name_f, "function.declaration.%s.%s.", "d", atual->child->valor);
    }
    else{
        sprintf(backUp_name_f, "function.declaration.%s.%s.", "v", atual->child->valor);
    }

    backUp_count_f = strlen(backUp_name_f);

    while(backUp_params != NULL){
        if(strcmp(backUp_node_params->tipoNo, "NULL") == 0){
            backUp_node_params = backUp_node_params->brother;
        }

        if(strcmp(backUp_params->tipo, "String[]") == 0){
            fazer_llvm_rec(backUp_node_params);

            char *backUp;
            backUp = (char*)strdup("s.");
            i = 0;
            while(backUp[i] != '\0'){
                backUp_name_f[backUp_count_f] = backUp[i];
                backUp_count_f++;
                i++;
            }

            free(backUp);
            backUp = NULL;

            sprintf(backUp_params_f, "i%d %%argc, i8** %%argv", 32);
            backUp_count_params_f = strlen(backUp_params_f);

            break;
        }
        else if(strcmp(backUp_params->tipo, "int") == 0){
            fazer_llvm_rec(backUp_node_params);

            char *backUp;
            backUp = (char*)strdup("i.");
            i = 0;
            while(backUp[i] != '\0'){
                backUp_name_f[backUp_count_f] = backUp[i];
                backUp_count_f++;
                i++;
            }

            free(backUp);
            backUp = NULL;

            backUp = (char*)malloc(1024*sizeof(char));
            sprintf(backUp, "i32 %%%d", contadorVarsL-1);

            i = 0;
            while(backUp[i] != '\0'){
                backUp_params_f[backUp_count_params_f] = backUp[i];
                backUp_count_params_f++;
                i++;
            }

            free(backUp);
            backUp = NULL;
        }
        else if(strcmp(backUp_params->tipo, "boolean") == 0){
            fazer_llvm_rec(backUp_node_params);

            char *backUp;
            backUp = (char*)strdup("b.");
            i = 0;
            while(backUp[i] != '\0'){
                backUp_name_f[backUp_count_f] = backUp[i];
                backUp_count_f++;
                i++;
            }

            free(backUp);
            backUp = NULL;

            backUp = (char*)malloc(1024*sizeof(char));
            sprintf(backUp, "i1 %%%d", contadorVarsL-1);

            i = 0;
            while(backUp[i] != '\0'){
                backUp_params_f[backUp_count_params_f] = backUp[i];
                backUp_count_params_f++;
                i++;
            }

            free(backUp);
            backUp = NULL;
        }
        else if(strcmp(backUp_params->tipo, "double") == 0){
            if(strcmp(backUp_node_params->anotacao, "int") == 0){
                fazer_llvm_rec(backUp_node_params);
                printf("\t%%%d = sitofp i32 %%%d to double\n", contadorVarsL, contadorVarsL-1);
                contadorVarsL++;
            }
            else{
                fazer_llvm_rec(backUp_node_params);
            }

            char *backUp;
            backUp = (char*)strdup("d.");
            i = 0;
            while(backUp[i] != '\0'){
                backUp_name_f[backUp_count_f] = backUp[i];
                backUp_count_f++;
                i++;
            }

            free(backUp);
            backUp = NULL;

            backUp = (char*)malloc(1024*sizeof(char));
            sprintf(backUp, "double %%%d", contadorVarsL-1);

            i = 0;
            while(backUp[i] != '\0'){
                backUp_params_f[backUp_count_params_f] = backUp[i];
                backUp_count_params_f++;
                i++;
            }

            free(backUp);
            backUp = NULL;
        }

        if(backUp_params->seguinte != NULL){
            char *backUp;
            backUp = (char*)strdup(", ");

            i = 0;
            while(backUp[i] != '\0'){
                backUp_params_f[backUp_count_params_f] = backUp[i];
                backUp_count_params_f++;
                i++;
            }
            free(backUp);
            backUp = NULL;
        }

        numeroParametros--;
        backUp_params = backUp_params->seguinte;
        backUp_node_params = backUp_node_params->brother;
    }

    backUp_name_f[backUp_count_f] = '\0';
    backUp_params_f[backUp_count_params_f] = '\0';

    if(strcmp(atual->anotacao, "int") == 0){
        printf("\t%%%d = call i32 @%s(%s)\n", contadorVarsL, backUp_name_f, backUp_params_f);
        contadorVarsL++;
    }
    else if(strcmp(atual->anotacao, "double") == 0){
        printf("\t%%%d = call double @%s(%s)\n", contadorVarsL, backUp_name_f, backUp_params_f);
        contadorVarsL++;
    }
    else if(strcmp(atual->anotacao, "boolean") == 0){
        printf("\t%%%d = call i1 @%s(%s)\n", contadorVarsL, backUp_name_f, backUp_params_f);
        contadorVarsL++;
    }
    else{
        printf("\tcall void @%s(%s)\n", backUp_name_f, backUp_params_f);
    }
    
    free(backUp_name_f);
    backUp_name_f = NULL;
    free(backUp_params_f);
    backUp_params_f = NULL;
}

void acertarDec(char *valor){
    int i=0, j=0;

    while(valor[i] != '\0'){
        if(valor[i] != '_'){
            stringDeclit[j] = valor[i];
            j++;
        }
        i++;
    }

    stringDeclit[j] = '\0';
}

void acertarReal(char *valor){
    int i=0, j=0;

    while(valor[i] != '\0'){
        if(valor[i] != '_'){
            stringReallit[j] = valor[i];
            j++;
        }
        i++;
    }

    stringReallit[j] = '\0';
}

void fazer_llvm_rec(node *atual){
    node *backUp1;

    if(strcmp(atual->tipoNo, "VarDecl") == 0){
        tratarVarDecl(atual->child->tipoNo, atual->child->brother->valor);
    }
    else if(strcmp(atual->tipoNo, "Call") == 0){
        tratarChamada(atual);
    }
    else if(strcmp(atual->tipoNo, "Print") == 0){
        backUp1 = atual->child;
        while(backUp1 != NULL){
            fazer_llvm_rec(backUp1);
            backUp1 = backUp1->brother;
        }

        tratarPrint(atual);
    }
    else if(strcmp(atual->tipoNo, "RealLit") == 0){
        tratarReal(atual);
    }
    else if(strcmp(atual->tipoNo, "DecLit") == 0){
        tratarDec(atual);
    }
    else if(strcmp(atual->tipoNo, "BoolLit") == 0){
        tratarBool(atual);
    }
    else if(strcmp(atual->tipoNo, "Assign") == 0){
        backUp1 = atual->child;
        while(backUp1 != NULL){
            fazer_llvm_rec(backUp1);
            backUp1 = backUp1->brother;
        }
        tratarAtr(atual);
        tratarId(atual->child);
    }
    else if(strcmp(atual->tipoNo, "Id") == 0){
        tratarId(atual);
    }
    else if(strcmp(atual->tipoNo, "Plus") == 0){
        backUp1 = atual->child;
        while(backUp1 != NULL){
            fazer_llvm_rec(backUp1);
            backUp1 = backUp1->brother;
        }
    }
    else if(strcmp(atual->tipoNo, "Minus") == 0){
        backUp1 = atual->child;
        while(backUp1 != NULL){
            fazer_llvm_rec(backUp1);
            backUp1 = backUp1->brother;
        }
        tratarMenos(atual);
    }
    else if(strcmp(atual->tipoNo, "Length") == 0){
        tratarLen(atual);
    }
    else if(strcmp(atual->tipoNo, "ParseArgs") == 0){
        fazer_llvm_rec(atual->child->brother);
        tratarParse(atual);
    }
    else if(strcmp(atual->tipoNo, "Add") == 0){
        backUp1 = atual->child;
        fazer_llvm_rec(backUp1);
        int var1 = contadorVarsL-1;
        backUp1 = atual->child->brother;
        fazer_llvm_rec(backUp1);
        int var2 = contadorVarsL-1;

        tratarAdd(atual, var1, var2);
    }
    else if(strcmp(atual->tipoNo, "Sub") == 0){
        backUp1 = atual->child;
        fazer_llvm_rec(backUp1);
        int var1 = contadorVarsL-1;
        backUp1 = atual->child->brother;
        fazer_llvm_rec(backUp1);
        int var2 = contadorVarsL-1;

        tratarSub(atual, var1, var2);
    }
    else if(strcmp(atual->tipoNo, "Mul") == 0){
        backUp1 = atual->child;
        fazer_llvm_rec(backUp1);
        int var1 = contadorVarsL-1;
        backUp1 = atual->child->brother;
        fazer_llvm_rec(backUp1);
        int var2 = contadorVarsL-1;

        tratarMul(atual, var1, var2);
    }
    else if(strcmp(atual->tipoNo, "Div") == 0){
        backUp1 = atual->child;
        fazer_llvm_rec(backUp1);
        int var1 = contadorVarsL-1;
        backUp1 = atual->child->brother;
        fazer_llvm_rec(backUp1);
        int var2 = contadorVarsL-1;

        tratarDiv(atual, var1, var2);
    }
    else if(strcmp(atual->tipoNo, "Mod") == 0){
        backUp1 = atual->child;
        fazer_llvm_rec(backUp1);
        int var1 = contadorVarsL-1;
        backUp1 = atual->child->brother;
        fazer_llvm_rec(backUp1);
        int var2 = contadorVarsL-1;

        tratarMod(atual, var1, var2);
    }
    else if(strcmp(atual->tipoNo, "Not") == 0){
        backUp1 = atual->child;
        fazer_llvm_rec(backUp1);
        int var1 = contadorVarsL-1;

        tratarNot(atual, var1);
    }
    else if(strcmp(atual->tipoNo, "And") == 0){
        fazer_llvm_rec(atual->child);
        tratarAnd(atual);
    }
    else if(strcmp(atual->tipoNo, "Or") == 0){
        fazer_llvm_rec(atual->child);
        tratarOr(atual);
    }
    else if(strcmp(atual->tipoNo, "Xor") == 0){
        backUp1 = atual->child;
        fazer_llvm_rec(backUp1);
        int var1 = contadorVarsL-1;
        backUp1 = atual->child->brother;
        fazer_llvm_rec(backUp1);
        int var2 = contadorVarsL-1;
        function_xor(atual, var1, var2);
    }
    else if(strcmp(atual->tipoNo, "Lshift") == 0){
        backUp1 = atual->child;
        fazer_llvm_rec(backUp1);
        int var1 = contadorVarsL-1;
        backUp1 = atual->child->brother;
        fazer_llvm_rec(backUp1);
        int var2 = contadorVarsL-1;
        function_lshift(atual, var1, var2);
    }
    else if(strcmp(atual->tipoNo, "Rshift") == 0){
        backUp1 = atual->child;
        fazer_llvm_rec(backUp1);
        int var1 = contadorVarsL-1;
        backUp1 = atual->child->brother;
        fazer_llvm_rec(backUp1);
        int var2 = contadorVarsL-1;
        function_rshift(atual, var1, var2);
    }
    else if(strcmp(atual->tipoNo, "Eq") == 0){
        backUp1 = atual->child;
        fazer_llvm_rec(backUp1);
        int var1 = contadorVarsL-1;
        backUp1 = atual->child->brother;
        fazer_llvm_rec(backUp1);
        int var2 = contadorVarsL-1;

        tratarIgual(atual, var1, var2);
    }
    else if(strcmp(atual->tipoNo, "Ne") == 0){
        backUp1 = atual->child;
        fazer_llvm_rec(backUp1);
        int var1 = contadorVarsL-1;
        backUp1 = atual->child->brother;
        fazer_llvm_rec(backUp1);
        int var2 = contadorVarsL-1;

        tratarDif(atual, var1, var2);
    }
    else if(strcmp(atual->tipoNo, "Lt") == 0){
        backUp1 = atual->child;
        fazer_llvm_rec(backUp1);
        int var1 = contadorVarsL-1;
        backUp1 = atual->child->brother;
        fazer_llvm_rec(backUp1);
        int var2 = contadorVarsL-1;

        tratarMenor(atual, var1, var2);
    }
    else if(strcmp(atual->tipoNo, "Gt") == 0){
        backUp1 = atual->child;
        fazer_llvm_rec(backUp1);
        int var1 = contadorVarsL-1;
        backUp1 = atual->child->brother;
        fazer_llvm_rec(backUp1);
        int var2 = contadorVarsL-1;

        tratarMaior(atual, var1, var2);
    }
    else if(strcmp(atual->tipoNo, "Le") == 0){
        backUp1 = atual->child;
        fazer_llvm_rec(backUp1);
        int var1 = contadorVarsL-1;
        backUp1 = atual->child->brother;
        fazer_llvm_rec(backUp1);
        int var2 = contadorVarsL-1;

        tratarMenorIgual(atual, var1, var2);
    }
    else if(strcmp(atual->tipoNo, "Ge") == 0){
        backUp1 = atual->child;
        fazer_llvm_rec(backUp1);
        int var1 = contadorVarsL-1;
        backUp1 = atual->child->brother;
        fazer_llvm_rec(backUp1);
        int var2 = contadorVarsL-1;

        tratarMaiorIgual(atual, var1, var2);
    }
    else if(strcmp(atual->tipoNo, "Block") == 0){
        backUp1 = atual->child;
        while(backUp1 != NULL){
            fazer_llvm_rec(backUp1);
            backUp1 = backUp1->brother;
        }
    }
    else if(strcmp(atual->tipoNo, "If") == 0){
        fazer_llvm_rec(atual->child);
        tratarIf(atual);
    }
    else if(strcmp(atual->tipoNo, "While") == 0){
        tratarWhile(atual);
    }
    else if(strcmp(atual->tipoNo, "Return") == 0){
        return_encontrado = 1;
        tratarReturn(atual);
    }
}