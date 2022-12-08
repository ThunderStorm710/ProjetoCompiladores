#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdarg.h>
#include <float.h>
#include "semantic.h"

//correr com: valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes 

/* ------------------ TOKEN --------------- */

token* createToken(char *value, int line, int colunm){
    token *new = (token*)malloc(sizeof(token));
    if(value != NULL){
        new->value = (char*)strdup(value);
    }
    else{
        new->value = NULL;
    }
    new->line = line;
    new->colunm = colunm;
    return new;
}

void freeToken(token *aux){
    if(aux->value != NULL){
        free(aux->value);
        aux->value = NULL;
    }
    free(aux);
    aux = NULL;
}

/* ------------------- AST --------------- */

int itsTerminal(char *nodeType){
    if(strcmp(nodeType, "Bool") == 0 || strcmp(nodeType, "BoolLit") == 0 || strcmp(nodeType, "Double") == 0 
        || strcmp(nodeType, "DecLit") == 0 || strcmp(nodeType, "Id") == 0 || strcmp(nodeType, "Int") == 0 
        || strcmp(nodeType, "RealLit") == 0 || strcmp(nodeType, "StrLit") == 0 || strcmp(nodeType, "Void") == 0){
        return 1;
    }
    return 0;
}

node* createNode(char* nodeType, char *value, int line, int colunm){
    node* aux = (node*)malloc(sizeof(node));
    aux->nodeType = (char*)strdup(nodeType);
    if(value != NULL){
        aux->value = (char*)strdup(value);
    }
    else{
        aux->value = NULL;
    }

    aux->line = line;
    aux->colunm = colunm;
    aux->anoted = NULL;
    aux->params = NULL;
    aux->n_params = -1;
    aux->to_anote = 1;
    aux->children = NULL;
    aux->brother = NULL;
    return aux;
}

void insertBrother(node *bOld, node *bNew){
    if(bOld==NULL || bNew==NULL){
        return;
    }

    node *aux = bOld;
    while(aux->brother != NULL){
        aux = aux->brother;
    }
    
    aux->brother = bNew;
}

void insertChildren(node *f, node *s){
    if(f==NULL || s==NULL){
        return;
    }

    f->children = s;
}

void atributeType(node *type, node *varDecl){
    node *aux = varDecl;
    node *new = NULL;

    while(aux != NULL){
        new = createNode(type->nodeType, NULL, 0, 0);
        new->brother = aux->children;
        aux->children = new;
        aux = aux->brother;
    }
}

int countChildrens(node *n){
    int count = 0;
    node *aux;

    aux = n;
    while(aux->brother != NULL){
        count++;
        aux = aux->brother;
    }

    return count;
}

int addBlock(node *n) {
    int count = 0;
    if(n == NULL){
        return count;
    }

    if(n->brother != NULL){
        count = 1;
    }

    while(n->brother != NULL){        
        if (strcmp((n->brother)->nodeType, "NULL")!=0){
            count++;
        }
        n = n->brother;
    }

    return count;
}

void printNode(node *current){
    if(strcmp(current->nodeType, "Id") == 0 || strcmp(current->nodeType, "DecLit") == 0 || strcmp(current->nodeType, "RealLit") == 0 || strcmp(current->nodeType, "BoolLit") == 0){
        printf("%s(%s)\n",current->nodeType, current->value);
    }
    else{
        printf("%s\n",current->nodeType);
    }
}

void printAST(node *current, int n){
    int i;

    if(current == NULL){
        return;
    }

    if(strcmp(current->nodeType, "NULL") == 0){
        printAST(current->brother, n);
        return;
    }

    if(strcmp(current->nodeType, "NULL") != 0){
        for(i=0;i<n;i++){
            printf("..");
        }

        if(current->value != NULL){
            printf("%s(%s)\n",current->nodeType, current->value);
        }
        else{
            printf("%s\n",current->nodeType);
        }
    }
    
    printAST(current->children, n+1);
    printAST(current->brother, n);
}

void clearAST(node* atual){
    if(atual == NULL){
        return;
    }

    if(atual->nodeType != NULL){
        free(atual->nodeType);
        atual->nodeType = NULL;
    }
    if(atual->value != NULL){
        free(atual->value);
        atual->value = NULL;
    }

    clearAST(atual->children);
    atual->children = NULL;
    clearAST(atual->brother);
    atual->brother = NULL;

    free(atual);
    atual = NULL;
}

/* ------------------ SEMANTICS ---------------------- */

/* TABLES */

void clearParams(param_list *param){
    if(param == NULL){
        return;
    }

    if(param->type != NULL){
        free(param->type);
        param->type = NULL;
    }
    if(param->id != NULL){
        free(param->id);
        param->id = NULL;
    }

    clearParams(param->next);

    free(param);
    param = NULL;
}

void clearVars(var_list *var){
    if(var == NULL){
        return;
    }

    if(var->type != NULL){
        free(var->type);
        var->type = NULL;
    }
    if(var->name != NULL){
        free(var->name);
        var->name = NULL;
    }

    clearParams(var->paramTypes);
    clearVars(var->next);

    free(var);
    var = NULL;
}

void clearLocalTables(sym_table *local){
    if(local == NULL){
        return;
    }

    if(local->tableName != NULL){
        free(local->tableName);
        local->tableName = NULL;
    }
    if(local->tableType != NULL){
        free(local->tableType);
        local->tableType = NULL;
    }

    if(local->params != NULL){
        clearParams(local->params->next);
        if(local->params->type != NULL){
            free(local->params->type);
            local->params->type = NULL;
        }
        if(local->params->id != NULL){
            free(local->params->id);
            local->params->id = NULL;
        }
        free(local->params);
        local->params = NULL;
    }
    if(local->vars != NULL){
        clearVars(local->vars->next);
        if(local->vars->type != NULL){
            free(local->vars->type);
            local->vars->type = NULL;
        }
        if(local->vars->name != NULL){
            free(local->vars->name);
            local->vars->name = NULL;
        }
        free(local->vars);
        local->vars = NULL;
    }

    clearLocalTables(local->next);

    free(local);
    local = NULL;
}

void clearTables(sym_table *global, sym_table *local){
    if(global != NULL){
        if(global->tableName != NULL){
            free(global->tableName);
            global->tableName = NULL;
        }
        if(global->tableType != NULL){
            free(global->tableType);
            global->tableType = NULL;
        }

        clearVars(global->vars);

        free(global);
        global = NULL;
    }

    if(local != NULL){
        clearLocalTables(local);
    }
}

void print_table_global(sym_table *atual){
    var_list *auxV = atual->vars;
    param_list *auxP;

    printf("===== %s %s Symbol Table =====\n", atual->tableType, atual->tableName);
    while(auxV != NULL){
        if(auxV->function == 1){
            auxP = auxV->paramTypes;
            printf("%s\t(", auxV->name);
            while(auxP != NULL){
                printf("%s", auxP->type);
                if(auxP->next != NULL){
                    printf(",");
                }
                auxP = auxP->next;
            }
            printf(")\t%s", auxV->type);
        }
        else{
            printf("%s\t\t%s", auxV->name, auxV->type);
        }

        printf("\n");

        auxV = auxV->next;
    }
    printf("\n");
}

void print_tables_local(sym_table *atual){
    sym_table *aux = atual;
    var_list *auxV;
    param_list *auxP;

    while(aux != NULL){
        auxV = aux->vars;
        auxP = aux->params;
        if(auxP!=NULL){
            printf("===== %s %s(",  aux->tableType, aux->tableName);
            while(auxP != NULL){
                printf("%s", auxP->type);
                if(auxP->next !=NULL){
                    printf(",");
                }
                auxP = auxP->next;
            }
            printf(") Symbol Table =====\n");
        }
        else{
            printf("===== %s %s() Symbol Table =====\n", aux->tableType, aux->tableName);
        }
        while(auxV != NULL){
            if(auxV->flag == 2){
                //dont print, its repeated
            }
            else if(auxV->flag == 1){
                printf("%s\t\t%s\t%s\n", auxV->name, auxV->type, "param");
            }
            else{
                printf("%s\t\t%s\n", auxV->name, auxV->type);
            }

            auxV = auxV->next;
        }

        printf("\n");

        aux = aux->next;
    }
}

void add_to_local_table(sym_table *table, sym_table *element){
    sym_table *aux = table;

    if(aux == NULL){
        table = element;
        return;
    }

    while(aux->next != NULL){
        aux = aux->next;
    }

    aux->next = element;
}

param_list *create_param_type(char *type, char *id){
    param_list *new = (param_list*)malloc(sizeof(param_list));
    new->type = (char*)strdup(type);
    new->id = (char*)strdup(id);
    new->next = NULL;
    return new;
}

void add_param(param_list *paramList, param_list *new){
    param_list *aux = paramList;

    if(aux == NULL){
        paramList = new;
        return;
    }

    while(aux->next != NULL){
        aux = aux->next;
    }

    aux->next = new;
}

var_list *create_var(char *name, char *type){
    var_list *new = (var_list*)malloc(sizeof(var_list));
    new->name = (char*)strdup(name);
    new->type = (char*)strdup(type);
    new->function = 0;
    new->flag = 0;
    new->n_params = 0;
    new->paramTypes = NULL;
    new->next = NULL;
    return new;
}

void add_var(var_list *varList, var_list *new){
    var_list *aux = varList;

    if(aux == NULL){
        varList = new;
        return;
    }

    while(aux->next != NULL){
        aux = aux->next;
    }

    aux->next = new;
}

sym_table* create_table(char *name, char *type){
    sym_table* aux = (sym_table*)malloc(sizeof(sym_table));
    aux->tableName = (char*)strdup(name);
    aux->tableType = (char*)strdup(type);

    aux->vars = NULL;
    aux->params = NULL;
    aux->next = NULL;
    return aux;
}

char *changeType(char *nodeType){

    if(strcmp(nodeType, "Int") == 0){
        nodeType = "int";
        return nodeType;
    }

    if(strcmp(nodeType, "Double") == 0){
        nodeType = "double";
        return nodeType;
    }

    if(strcmp(nodeType, "Bool") == 0){
        nodeType = "boolean";
        return nodeType;
    }

    if(strcmp(nodeType, "Void") == 0){
        nodeType = "void";
        return nodeType;
    }

    if(strcmp(nodeType, "StringArray") == 0){
        nodeType = "String[]";
        return nodeType;
    }

    return nodeType;
}

void create_semantic_table(node *atual){
    char *aux;
    int error;
    sym_table *auxTable;
    var_list *auxVar, *auxVarLocal;
    param_list *auxParam, *auxParamPrint;
    node *aux1, *aux2, *aux3, *aux4, *aux5, *aux6, *auxProgram;
    int count_params;

    nErrorsSemantic = 0;

    if(atual == NULL){
        return;
    }

    if(strcmp(atual->nodeType, "Program")==0){ //Fazemos primeiro a tabela global toda
        aux1 = atual->children; //ID

        global_table = create_table(aux1->value, "Class");

        auxProgram = aux1->brother; //FieldDecl ou MethodDecl
        atual = aux1->brother; //FieldDecl ou MethodDecl

        while(atual != NULL){ //Fazemos primeiro a tabela global toda
            if(strcmp(atual->nodeType, "FieldDecl")==0){
                aux1 = atual->children; //TYPE
                aux2 = aux1->brother; //ID
                auxVar = create_var(aux2->value, changeType(aux1->nodeType));
                if(search_type_var(global_table, NULL, aux2->value) != NULL){
                    nErrorsSemantic = 1;
                    printf("Line %d, col %d: Symbol %s already defined\n", aux2->line, aux2->colunm, aux2->value);
                    clearVars(auxVar);
                }
                else{
                    if(global_table->vars == NULL){
                        global_table->vars = auxVar;
                    }
                    else{
                        add_var(global_table->vars, auxVar);
                    }
                }
            }
            if(strcmp(atual->nodeType, "MethodDecl")==0){
                aux1 = atual->children; //MethodHeader
                count_params = 0;
                while(aux1 != NULL){
                    if(strcmp(aux1->nodeType, "MethodHeader") == 0){
                        aux2 = aux1->children; //TYPE
                        aux3 = aux2->brother; //ID

                        auxVar = create_var(aux3->value, changeType(aux2->nodeType)); //ADD TO GLOBAL

                        aux4 = aux3->brother; //MethodParams
                        aux5 = aux4->children; //ParamDecl ou nada
                        while(aux5 != NULL){ //WHILE EXISTS ParamDecl's
                            if(strcmp(aux5->nodeType, "NULL")!=0){
                                count_params++;
                                //add to auxVar to global_table
                                auxParam = create_param_type(changeType(aux5->children->nodeType), (aux5->children)->brother->value);
                                
                                aux = search_var_exists(auxVar->paramTypes, (aux5->children)->brother->value);
                                if(aux != NULL){
                                    nErrorsSemantic = 1;
                                    printf("Line %d, col %d: Symbol %s already defined\n", (aux5->children)->brother->line, (aux5->children)->brother->colunm, (aux5->children)->brother->value);
                                }

                                if(auxVar->paramTypes == NULL){
                                    auxVar->paramTypes = auxParam;
                                }
                                else{
                                    add_param(auxVar->paramTypes, auxParam);
                                }
                            }
                            aux5 = aux5->brother;
                        }

                        auxVar->function = 1; //ITS FUNCTION
                        auxVar->n_params = count_params;
                        if(search_function_exists(global_table, auxVar->paramTypes, count_params, aux3->value) == 1){
                            nErrorsSemantic = 1;
                            printf("Line %d, col %d: Symbol %s(", aux3->line, aux3->colunm, aux3->value);
                            auxParamPrint = auxVar->paramTypes;
                            while(auxParamPrint != NULL){
                                printf("%s", auxParamPrint->type);
                                if(auxParamPrint->next != NULL){
                                    printf(",");
                                }
                                auxParamPrint = auxParamPrint->next;
                            }
                            printf(") already defined\n");
                            aux3->to_anote = 0;
                            clearVars(auxVar);
                        }
                        else{
                            if(global_table->vars == NULL){
                                global_table->vars = auxVar;
                            }
                            else{
                                add_var(global_table->vars, auxVar);
                            }
                        }
                    }

                    aux1 = aux1->brother; //MethodHeader ou MethodBody
                }
            }

            atual = atual->brother;
        }

        atual = auxProgram;

        while(atual != NULL){ //Depois fazemos as tabelas locais
            if(strcmp(atual->nodeType, "MethodDecl")==0){
                error = 0;
                aux1 = atual->children; //MethodHeader
                while(aux1 != NULL){
                    if(strcmp(aux1->nodeType, "MethodHeader") == 0){
                        aux2 = aux1->children; //TYPE
                        aux3 = aux2->brother; //ID

                        if(aux3->to_anote == 0){
                            error = 1;
                            break;
                        }
                        
                        auxTable = create_table(aux3->value, "Method");

                        auxVar = create_var("return", changeType(aux2->nodeType)); //CREATE VAR TYPE
                        auxVar->flag = 0;
                        auxTable->vars = auxVar; //TO LOCAL TABLE

                        aux4 = aux3->brother; //MethodParams
                        aux5 = aux4->children; //ParamDecl ou nada
                        while(aux5 != NULL){ //WHILE EXISTS ParamDecl's
                            if(strcmp(aux5->nodeType, "NULL")!=0){
                                //add to auxVar to global_table
                                auxParam = create_param_type(changeType(aux5->children->nodeType), (aux5->children)->brother->value);
                                
                                aux = search_var_exists(auxVar->paramTypes, (aux5->children)->brother->value);

                                if(auxVar->paramTypes == NULL){
                                    auxVar->paramTypes = auxParam;
                                }
                                else{
                                    add_param(auxVar->paramTypes, auxParam);
                                }

                                //add to local_table
                                aux6 = (aux5->children)->brother; //ID OF ParamDecl
                                auxVarLocal = create_var(aux6->value, changeType(aux5->children->nodeType));
                                if(aux!=NULL){
                                    auxVarLocal->flag = 2; //DONT PRINT, ITS REPEATED
                                }
                                else{
                                    auxVarLocal->flag = 1; //ITS VAR
                                }
                                auxTable->params = auxVar->paramTypes;
                                add_var(auxTable->vars, auxVarLocal);
                            }
                            aux5 = aux5->brother;
                        }
                    }
                    if(strcmp(aux1->nodeType, "MethodBody") == 0){
                        aux2 = aux1->children;
                        while(aux2 != NULL){
                            if(strcmp(aux2->nodeType, "VarDecl") == 0){
                                aux3 = aux2->children;
                                aux4 = aux3->brother;
                                
                                if(search_type_var(NULL, auxTable, aux4->value) != NULL){
                                    nErrorsSemantic = 1;
                                    printf("Line %d, col %d: Symbol %s already defined\n", aux4->line, aux4->colunm, aux4->value);
                                }
                                else{
                                    auxVar = create_var(aux4->value, changeType(aux3->nodeType));
                                    auxVar->flag = 0;
                                    add_var(auxTable->vars, auxVar); //TO LOCAL TABLE
                                }
                            }
                            else{
                                if(!(strcmp(aux2->nodeType, "NULL") == 0)){
                                    anote_ast(global_table, auxTable, aux2);
                                }
                            }

                            aux2 = aux2->brother;
                        }
                    }

                    aux1 = aux1->brother; //MethodHeader ou MethodBody
                }

                if(error != 1){
                    if(local_table == NULL){
                        local_table = auxTable;
                    }
                    else{
                        add_to_local_table(local_table, auxTable); //ADD TO LOCAL TABLE
                    }  
                }
            }

            atual = atual->brother;
        }
    }
}

/* ANOTED AST */

char *search_var_exists(param_list *params, char *var_name){
    if(params == NULL){
        return NULL;
    }

    param_list *auxP = params;

    while(auxP != NULL){
        if(strcmp(auxP->id, var_name) == 0){
            return auxP->type;
        }
        auxP = auxP->next;
    }

    return NULL;
}

int search_function_exists(sym_table *table_global, param_list *aux_paramTypes, int count_params, char *name){
    var_list *aux_vars;
    param_list *aux_params1, *aux_params2;
    int count_equals = 0;

    aux_vars = table_global->vars;
    while(aux_vars != NULL){
        if(aux_vars->function == 1 && aux_vars->n_params == count_params && strcmp(aux_vars->name, name) == 0){
            count_equals = 0;
            aux_params1 = aux_vars->paramTypes;
            aux_params2 = aux_paramTypes;
            while(aux_params1 != NULL){
                if(strcmp(aux_params1->type, aux_params2->type)==0){
                    count_equals++;
                }
                aux_params1 = aux_params1->next;
                aux_params2 = aux_params2->next;
            }
            if(count_equals == count_params){
                return 1;
            }
        }
        aux_vars = aux_vars->next;
    }

    return 0;   
}

char *search_type_var_in_table(sym_table *table, char *var_name){
    if(table == NULL){
        return NULL;
    }

    var_list *auxV = table->vars;

    while(auxV != NULL){
        if(strcmp(auxV->name, var_name) == 0 && auxV->function != 1){
            return auxV->type;
        }
        auxV = auxV->next;
    }

    return NULL;
}

char *search_type_var(sym_table *table_global, sym_table *table_local, char *var_name){
    char *aux = search_type_var_in_table(table_local, var_name);
    if(aux != NULL){
        return aux;
    }
    aux = search_type_var_in_table(table_global, var_name);
    if(aux != NULL){
        return aux;
    }
    return NULL;
}

void anote_ast(sym_table *table_global, sym_table *table_local, node *atual){
    char *aux;
    param_list *aux_params, *final_params;
    var_list *aux_vars;
    int count_params, count_equals, count_all_equals, find_function;
    node *aux1, *aux2, *aux3, *ant;

    if(atual == NULL){
        return;
    }

    if(strcmp(atual->nodeType, "NULL") == 0){
        return;
    }
    else if(strcmp(atual->nodeType, "Id") == 0){
        aux = search_type_var(table_global, table_local, atual->value);
        if(aux != NULL){
            atual->anoted = aux;
        }
        else{
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Cannot find symbol %s\n", atual->line, atual->colunm, atual->value);
            atual->anoted = "undef";
        }
    }
    else if(strcmp(atual->nodeType, "If") == 0){
        aux1 = atual->children;
        anote_ast(table_global, table_local, aux1);
        aux1 = aux1->brother;
        
        aux2 = atual->children;
        if(strcmp(aux2->anoted, "boolean")){
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Incompatible type %s in if statement\n", aux2->line, aux2->colunm, aux2->anoted);
        }

        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
    }
    else if(strcmp(atual->nodeType, "Block") == 0){
        aux1 = atual->children;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
    }
    else if(strcmp(atual->nodeType, "While") == 0){
        //dentro do while() só pode estar um boolit, gt, eq, get, leq, lt, neq
        aux1 = atual->children;
        anote_ast(table_global, table_local, aux1);
        aux1 = aux1->brother;

        aux2 = atual->children;
        if(strcmp(aux2->anoted, "boolean")){
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Incompatible type %s in while statement\n", aux2->line, aux2->colunm, aux2->anoted);
            atual->anoted = "undef";
        }
        else{
            atual->anoted = "boolean";
        }

        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }
    }
    else if(strcmp(atual->nodeType, "DoWhile") == 0){
        aux1 = atual->children;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            if(strcmp(aux1->nodeType, "NULL")){
                ant = aux1;
            }
            aux1 = aux1->brother;
        }

        aux2 = ant;
        if(strcmp(aux2->anoted, "boolean")){
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Incompatible type %s in do statement\n", aux2->line, aux2->colunm, aux2->anoted);
            atual->anoted = "undef";
        }
        else{
            atual->anoted = "boolean";
        }
    }
    else if(strcmp(atual->nodeType, "Print") == 0){
        aux1 = atual->children;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->children;
        if(strcmp(aux2->anoted, "undef") == 0 || strcmp(aux2->anoted, "String[]") == 0 || strcmp(aux2->anoted, "void") == 0){
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Incompatible type %s in System.out.println statement\n", aux2->line, aux2->colunm, aux2->anoted);
        }
    }
    else if(strcmp(atual->nodeType, "Return") == 0){
        aux1 = atual->children;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->children;
        if(aux2 != NULL){
            if(strcmp(table_local->vars->type, "void") == 0){
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Incompatible type %s in return statement\n",  aux2->line, aux2->colunm, aux2->anoted);
            }
            else if(strcmp(table_local->vars->type, aux2->anoted) == 0){
                return;
            }
            else if(strcmp(table_local->vars->type, "double") == 0){
                if((strcmp(aux2->anoted, "int") && strcmp(aux2->anoted, "double"))){
                    nErrorsSemantic = 1;
                    printf("Line %d, col %d: Incompatible type %s in return statement\n",  aux2->line, aux2->colunm, aux2->anoted);
                }
            }
            else{
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Incompatible type %s in return statement\n",  aux2->line, aux2->colunm, aux2->anoted);
            }
        }
        else{
            if(strcmp(table_local->vars->type, "void")){
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Incompatible type void in return statement\n",  atual->line, atual->colunm);
            }
        }
    }
    else if(strcmp(atual->nodeType, "Assign") == 0){
        aux1 = atual->children;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        //aux2 = atual->children;
        //atual->anoted = aux2->anoted;
        aux2 = atual->children;
        aux3 = aux2->brother;

        atual->anoted = aux2->anoted;

        if(strcmp(aux2->anoted, aux3->anoted) == 0 && strcmp(aux2->anoted, "undef") && strcmp(aux2->anoted, "String[]")){
            return;
        }
        else if(strcmp(aux2->anoted, "double") == 0 && strcmp(aux3->anoted, "int") == 0){
            return;            
        }
        else{
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator = cannot be applied to types %s, %s\n", atual->line, atual->colunm, aux2->anoted, aux3->anoted);
        }
    }
    else if(strcmp(atual->nodeType, "Call") == 0){
        count_params = 0;
        count_equals = 0;
        count_all_equals = 0;
        find_function = 0;
        aux1 = (atual->children)->brother;
        while(aux1 != NULL){
            if(strcmp(aux1->nodeType, "NULL")){
                count_params++;
            }
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux_vars = table_global->vars;
        while(aux_vars != NULL){
            count_equals = 0;
            count_all_equals = 0;
            if(aux_vars->function == 1 && aux_vars->n_params == count_params && strcmp(aux_vars->name, atual->children->value) == 0){
                aux_params = aux_vars->paramTypes;
                aux1 = (atual->children)->brother;
                while(aux1 != NULL){
                    if(strcmp(aux1->nodeType, "NULL")){
                        if(strcmp(aux_params->type, aux1->anoted)==0){
                            count_all_equals++;
                            count_equals++;
                        }
                        else if(strcmp(aux1->anoted, "int") == 0 && strcmp(aux_params->type, "double")==0){
                            count_equals++;
                        }
                        else{
                            break;
                        }
                        aux_params = aux_params->next;
                    }
                    aux1 = aux1->brother;
                }
                if(count_all_equals == count_params){
                    find_function = 1;
                    aux = aux_vars->type;
                    final_params = aux_vars->paramTypes;
                    break;
                }
                else if(count_equals == count_params){
                    aux = aux_vars->type;
                    final_params = aux_vars->paramTypes;
                    find_function++;
                }
            }
            aux_vars = aux_vars->next;
        }

        if(find_function == 1){
            atual->children->n_params = count_params;
            if(final_params == NULL){
                atual->children->params = NULL;
            }
            else{
                atual->children->params = final_params;
            }
            atual->anoted = aux;
        }
        else if(find_function > 1){
            nErrorsSemantic = 1;
            
            printf("Line %d, col %d: Reference to method %s(", atual->children->line, atual->children->colunm, atual->children->value);     
            aux1 = (atual->children)->brother;
            while(aux1 != NULL){
                if(strcmp(aux1->nodeType, "NULL")){
                    printf("%s", aux1->anoted);
                    if(aux1->brother != NULL){
                        printf(",");
                    }
                }
                aux1 = aux1->brother;
            }
            printf(") is ambiguous\n");
            atual->anoted = "undef";
            atual->children->anoted = "undef";
        }
        else{
            atual->children->anoted = "undef";
            atual->children->params = NULL;
            atual->anoted = "undef";

            nErrorsSemantic = 1;
            
            printf("Line %d, col %d: Cannot find symbol %s(", atual->children->line, atual->children->colunm, atual->children->value);     
            aux1 = (atual->children)->brother;
            while(aux1 != NULL){
                if(strcmp(aux1->nodeType, "NULL")){
                    printf("%s", aux1->anoted);
                    if(count_params != 1){
                        printf(",");
                    }
                    count_params--;
                }
                aux1 = aux1->brother;
            }
            printf(")\n");
        }
    }
    else if(strcmp(atual->nodeType, "ParseArgs") == 0){
        aux1 = atual->children;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->children;
        aux3 = aux2->brother;
        if(strcmp(aux2->anoted, "String[]")){
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator Integer.parseInt cannot be applied to types %s, %s\n", atual->line, atual->colunm, aux2->anoted, aux3->anoted);
        }
        else if(strcmp(aux3->anoted, "int")){
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator Integer.parseInt cannot be applied to types %s, %s\n", atual->line, atual->colunm, aux2->anoted, aux3->anoted);
        }

        atual->anoted = "int";
    }
    else if(strcmp(atual->nodeType, "And") == 0 || strcmp(atual->nodeType, "Or") == 0){
        aux1 = atual->children;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->children;
        aux3 = aux2->brother;
        if(strcmp(aux2->anoted, "boolean") && strcmp(atual->nodeType, "And") == 0){
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator && cannot be applied to types %s, %s\n", atual->line, atual->colunm, aux2->anoted, aux3->anoted);
        }
        else if(strcmp(aux2->anoted, "boolean") && strcmp(atual->nodeType, "Or") == 0){
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator || cannot be applied to types %s, %s\n", atual->line, atual->colunm, aux2->anoted, aux3->anoted);
        }
        else if(strcmp(aux3->anoted, "boolean") && strcmp(atual->nodeType, "And") == 0){
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator && cannot be applied to types %s, %s\n", atual->line, atual->colunm, aux2->anoted, aux3->anoted);
        }
        else if(strcmp(aux3->anoted, "boolean") && strcmp(atual->nodeType, "Or") == 0){
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator || cannot be applied to types %s, %s\n", atual->line, atual->colunm, aux2->anoted, aux3->anoted);
        }

        atual->anoted = "boolean";
    }
    else if(strcmp(atual->nodeType, "Eq") == 0 || strcmp(atual->nodeType, "Gt") == 0 || strcmp(atual->nodeType, "Geq") == 0
        || strcmp(atual->nodeType, "Leq") == 0 || strcmp(atual->nodeType, "Lt") == 0 || strcmp(atual->nodeType, "Neq") == 0){
        
        aux1 = atual->children;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->children;
        aux3 = aux2->brother;

        atual->anoted = "boolean";

        if(strcmp(atual->nodeType, "Eq") == 0){
            aux = "==";
        }
        else if(strcmp(atual->nodeType, "Gt") == 0){
            aux = ">";
        }
        else if(strcmp(atual->nodeType, "Geq") == 0){
            aux = ">=";
        }
        else if(strcmp(atual->nodeType, "Leq") == 0){
            aux = "<=";
        }
        else if(strcmp(atual->nodeType, "Lt") == 0){
            aux = "<";
        }
        else if(strcmp(atual->nodeType, "Neq") == 0){
            aux = "!=";
        }

        if(strcmp(atual->nodeType, "Eq") == 0 || strcmp(atual->nodeType, "Neq") == 0){
            if(strcmp(aux2->anoted, "boolean") == 0 && strcmp(aux3->anoted, "boolean") == 0){
                return;
            }
        }

        if(strcmp(aux2->anoted, "int") && strcmp(aux2->anoted, "double")){
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->colunm, aux, aux2->anoted, aux3->anoted);
        }
        else if(strcmp(aux3->anoted, "double") && strcmp(aux3->anoted, "int")){
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->colunm, aux, aux2->anoted, aux3->anoted);
        }
    }
    else if(strcmp(atual->nodeType, "Add") == 0 || strcmp(atual->nodeType, "Sub") == 0 || strcmp(atual->nodeType, "Mul") == 0
        || strcmp(atual->nodeType, "Div") == 0 || strcmp(atual->nodeType, "Mod") == 0){

        aux1 = atual->children;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->children;
        aux3 = aux2->brother;

        if(strcmp(atual->nodeType, "Add") == 0){
            aux = "+";
        }
        else if(strcmp(atual->nodeType, "Sub") == 0){
            aux = "-";
        }
        else if(strcmp(atual->nodeType, "Mul") == 0){
            aux = "*";
        }
        else if(strcmp(atual->nodeType, "Div") == 0){
            aux = "/";
        }
        else{
            aux = "%";
        }

        if(strcmp(aux2->anoted, "int")==0){
            if(strcmp(aux3->anoted, "int")==0){
                atual->anoted = "int";
            }
            else if(strcmp(aux3->anoted, "double")==0){
                atual->anoted = "double";
            }
            else{
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->colunm, aux, aux2->anoted, aux3->anoted);
                atual->anoted = "undef";
            }
        }
        else if(strcmp(aux2->anoted, "double")==0){
            if(strcmp(aux3->anoted, "int") && strcmp(aux3->anoted, "double")){
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->colunm, aux, aux2->anoted, aux3->anoted);
                atual->anoted = "undef";
            }
            else{
                atual->anoted = "double";
            }
        }
        else{
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", atual->line, atual->colunm, aux, aux2->anoted, aux3->anoted);
            atual->anoted = "undef";
        }
    }
    else if(strcmp(atual->nodeType, "Plus") == 0 || strcmp(atual->nodeType, "Minus") == 0){
        aux1 = atual->children;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->children;
        atual->anoted = aux2->anoted;
        if(strcmp(aux2->anoted, "int") == 0 || strcmp(aux2->anoted, "double") == 0){
            atual->anoted = aux2->anoted;
        }
        else{
            atual->anoted = "undef";
            if(strcmp(atual->nodeType, "Plus") == 0){
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Operator + cannot be applied to type %s\n", atual->line, atual->colunm, aux2->anoted);
            }
            else{
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Operator - cannot be applied to type %s\n", atual->line, atual->colunm, aux2->anoted);
            }
        }
    }
    else if(strcmp(atual->nodeType, "Not") == 0){
        aux1 = atual->children;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->children;
        if(strcmp(aux2->anoted, "boolean")){
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator ! cannot be applied to type %s\n", atual->line, atual->colunm, aux2->anoted);
        }

        atual->anoted = "boolean";
    }
    else if(strcmp(atual->nodeType, "Length") == 0){
        aux1 = atual->children;
        while(aux1 != NULL){
            anote_ast(table_global, table_local, aux1);
            aux1 = aux1->brother;
        }

        aux2 = atual->children;
        if(strcmp(aux2->anoted, "String[]")){
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Operator .length cannot be applied to type %s\n", atual->line, atual->colunm, aux2->anoted);
        }
        atual->anoted = "int";
    }
    else if(strcmp(atual->nodeType, "BoolLit") == 0){
        atual->anoted = "boolean";
    }
    else if(strcmp(atual->nodeType, "DecLit") == 0){
        /*char *aux2 = (char*)strdup(atual->value);
        char *pr, *pw;

        pr = atual->value;
        pw = atual->value;
        while (*pr) {
            *pw = *pr++;
            pw += (*pw != '_');
        }
        *pw = '\0';*/

        long l = strtol(atual->value,NULL,10);
        if(l>=0 && l<=INT_MAX){
            atual->anoted = "int";
        }
        else{
            nErrorsSemantic = 1;
            printf("Line %d, col %d: Number %s out of bounds\n", atual->line, atual->colunm, atual->value);
        }

        atual->anoted = "int";
        
        /*free(atual->value);
        atual->value = NULL;
        atual->value = aux2;*/
    }
    else if(strcmp(atual->nodeType, "RealLit") == 0){
        char *value = atual->value;
        char *aux = (char*)malloc(sizeof(char)*1024);
        int found = 0, zeros = 1, i = 0, j = 0;

        while (value[i] != '\0') {
            if((value[i] >= '0' && value[i] <= '9') || value[i] == 'e' || value[i] == 'E' || value[i] == '.' || value[i] == '-'){
                if(value[i] == 'e' || value[i] == 'E'){
                    found = 1;
                }
                if(value[i] != '.' && value[i] != '0' && !found){
                    zeros = 0;
                }
                aux[j] = value[i];
                j++;
            }
            i++;
        }
        aux[j] = '\0';
        
        if(!zeros){
            double d = atof(aux);
            if(isinf(d) || d == 0 || d > DBL_MAX){
                nErrorsSemantic = 1;
                printf("Line %d, col %d: Number %s out of bounds\n", atual->line, atual->colunm, atual->value);
            }
        }

        atual->anoted = "double";

        free(aux);
        aux = NULL;
    }
    else if(strcmp(atual->nodeType, "StrLit") == 0){
        atual->anoted = "String";
    }
}

int itsExpression(char *nodeType){
    if(strcmp(nodeType, "Assign") == 0 || strcmp(nodeType, "Or") == 0 || strcmp(nodeType, "And") == 0
        || strcmp(nodeType, "Eq") == 0 || strcmp(nodeType, "Neq") == 0 || strcmp(nodeType, "Lt") == 0
        || strcmp(nodeType, "Geq") == 0 || strcmp(nodeType, "Add") == 0 || strcmp(nodeType, "Sub") == 0
        || strcmp(nodeType, "Mul") == 0 || strcmp(nodeType, "Div") == 0 || strcmp(nodeType, "Mod") == 0
        || strcmp(nodeType, "Not") == 0 || strcmp(nodeType, "Minus") == 0 || strcmp(nodeType, "Plus") == 0
        || strcmp(nodeType, "Length") == 0 || strcmp(nodeType, "Call") == 0 || strcmp(nodeType, "ParseArgs") == 0
        || strcmp(nodeType, "BoolLit") == 0 || strcmp(nodeType, "DecLit") == 0 || strcmp(nodeType, "Id") == 0 
        || strcmp(nodeType, "RealLit") == 0 || strcmp(nodeType, "StrLit") == 0 || strcmp(nodeType, "Gt") == 0
        || strcmp(nodeType, "Leq") == 0){
        return 1;
    }
    else{
        return 0;
    }
}

void printAnotedAST(node *current, int n){
    int i;
    param_list *aux;

    if(current == NULL){
        return;
    }

    if(strcmp(current->nodeType, "NULL") == 0){
        printAnotedAST(current->brother, n);
        return;
    }
    else{
        for(i=0;i<n;i++){
            printf("..");
        }

        if(current->value != NULL){
            if(current->n_params >=0 && itsExpression(current->nodeType) == 1){
                printf("%s(%s) - (",current->nodeType, current->value);
                aux = current->params;
                while(aux != NULL){
                    printf("%s", aux->type);
                    if(aux->next != NULL){
                        printf(",");
                    }
                    aux = aux->next;
                }
                printf(")");
            }
            else if(current->anoted != NULL && itsExpression(current->nodeType) == 1){
                printf("%s(%s) - %s",current->nodeType, current->value, current->anoted);
            }
            else{
                printf("%s(%s)",current->nodeType, current->value);
            }
        }
        else{
            if(current->anoted != NULL && itsExpression(current->nodeType) == 1){
                printf("%s - %s",current->nodeType, current->anoted);
            }
            else{
                printf("%s",current->nodeType);
            }
        }

        //printf(" %d %d", current->line, current->colunm);

        printf("\n");
    }
    
    printAnotedAST(current->children, n+1);
    printAnotedAST(current->brother, n);
}


/* ------------------ PROGRAMS (Meta 4) ---------------------- */

//Variáveis globais têm o nome de: global.var.n (sendo n o número da var)
//Declarações de funções: function.declaration.n (sendo n o nome da function)
//Variavéis da função: function.var.n (sendo n o número da var)
//StrLit's globais: global.strlit.n (sendo o n o número da str)

int count_strlit = 1;
int count_global_vars = 1;
int count_temp_vars = 1;
int count_compares_label = 1;
int count_convertions = 1;
int count_label_if = 1;
int count_label_while = 1;
int count_label_dowhile = 1;
int count_label_and_or = 1;
int founded_return = 0;

strlit_list *list_global_strlit;
strlit_list *found_vars;

strlit_list *create_strlit(char *value, char *type){
    strlit_list *new = (strlit_list*)malloc(sizeof(strlit_list));
    new->value = (char*)strdup(value);
    new->type = (char*)strdup(type);
    new->next = NULL;
    return new;
}

void clearList(strlit_list *var){
    if(var == NULL){
        return;
    }

    if(var->value != NULL){
        free(var->value);
        var->value = NULL;
    }
    if(var->type != NULL){
        free(var->type);
        var->type = NULL;
    }

    clearList(var->next);

    free(var);
    var = NULL;
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

void print_strlit(strlit_list *strList){
    strlit_list *aux = strList;
    printf("\n");
    while(aux != NULL){
        printf("%s", aux->value);
        aux = aux->next;
    }
}

void create_llvm(node *root){
    print_global_declarations(root);
    generate_llvm(root);
    print_strlit(list_global_strlit);
    clearList(list_global_strlit);
}

void print_global_declarations(node *root){
    //Print first the global variables and functions declarations
    var_list *aux_vars = global_table->vars;
    
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

            count_global_vars++;
        }

        aux_vars = aux_vars->next;
    }

    printf("declare i32 @atoi(i8*)\n");
    printf("declare i32 @printf(i8*, ...)\n\n");
    printf("define i32 @main(i32 %%argc, i8** %%argv) {\n");
    printf("\tcall void @function.declaration.v.main.s.(i32 %%argc, i8** %%argv)\n");
    printf("\tret i32 0\n");
    printf("}\n\n");
}

int aux_length_strlit;
char *aux_change_strlit;
char *aux_change_declit;
char *aux_change_reallit;
char *global_function_type;

void change_strlit(char *value){
    value++; //removes the first "
    value[strlen(value)-1] = 0; //removes the last "

    int i = 0, j = 0;

    aux_length_strlit = 0;

    while (value[i] != '\0') {
        if(value[i] == '%'){
            aux_length_strlit++;
            aux_change_strlit[j] = value[i];
            j++;
            aux_length_strlit++;
            aux_change_strlit[j] = value[i];
            j++;
        }
        else if(value[i] == '\\'){
            aux_length_strlit++;
            i++;
            if(value[i] == 'n'){
                aux_change_strlit[j] = '\\';
                j++;
                aux_change_strlit[j] = '0';
                j++;
                aux_change_strlit[j] = 'A';
                j++;
            }
            else if(value[i] == 'f'){
                aux_change_strlit[j] = '\\';
                j++;
                aux_change_strlit[j] = '0';
                j++;
                aux_change_strlit[j] = 'C';
                j++;
            }
            else if(value[i] == 'r'){
                aux_change_strlit[j] = '\\';
                j++;
                aux_change_strlit[j] = '0';
                j++;
                aux_change_strlit[j] = 'D';
                j++;
            }
            else if(value[i] == '"'){
                aux_change_strlit[j] = '\\';
                j++;
                aux_change_strlit[j] = '2';
                j++;
                aux_change_strlit[j] = '2';
                j++;
            }
            else if(value[i] == 't'){
                aux_change_strlit[j] = '\\';
                j++;
                aux_change_strlit[j] = '0';
                j++;
                aux_change_strlit[j] = '9';
                j++;
            }
            else if(value[i] == '\\'){
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
            aux_change_strlit[j] = value[i];
            j++;
        }
        i++;
    }

    aux_length_strlit++;
    aux_change_strlit[j] = '\\';
    aux_change_strlit[j+1] = '0';
    aux_change_strlit[j+2] = 'A';

    aux_length_strlit++;
    aux_change_strlit[j+3] = '\\';
    aux_change_strlit[j+4] = '0';
    aux_change_strlit[j+5] = '0';

    aux_change_strlit[j+6] = '\0';
}

void generate_llvm(node *atual){
    node *aux1;

    if(atual == NULL || strcmp(atual->nodeType, "NULL") == 0){
        return;
    }

    if(strcmp(atual->nodeType, "Program") == 0){
        aux1 = atual->children;
        while(aux1 != NULL){
            generate_llvm(aux1);
            aux1 = aux1->brother;
        }
    }
    else if(strcmp(atual->nodeType, "MethodDecl") == 0){
        aux_change_strlit = (char*)malloc(sizeof(char)*1024);
        aux_change_declit = (char*)malloc(sizeof(char)*1024);
        aux_change_reallit = (char*)malloc(sizeof(char)*1024);

        count_temp_vars = 1;
        count_compares_label = 1;
        count_convertions = 1;
        count_label_if = 1;
        count_label_while = 1;
        count_label_dowhile = 1;
        count_label_and_or = 1;
        global_function_type = NULL;
        founded_return = 0;
        found_vars = NULL;

        aux1 = atual->children;
        while(aux1 != NULL){
            generate_llvm(aux1);
            aux1 = aux1->brother;
        }

        clearList(found_vars);
        found_vars = NULL;
        free(aux_change_strlit);
        aux_change_strlit = NULL;
        free(aux_change_declit);
        aux_change_declit = NULL;
        free(aux_change_reallit);
        aux_change_reallit = NULL;
    }
    else if(strcmp(atual->nodeType, "MethodHeader") == 0){
        create_header(atual);
    }
    else if(strcmp(atual->nodeType, "MethodBody") == 0){
        aux1 = atual->children;
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

    aux1 = atual->children; //FUNCTION TYPE
    aux_type = aux1->nodeType;
    global_function_type = aux1->nodeType;

    aux2 = aux1->brother; //FUNCTION NAME
    aux_name = aux2->value;
    aux3 = aux2->brother; //METHOD PARAMS

    char *aux_name_f = (char*)malloc(1024*sizeof(char));
    char *aux_params_f = (char*)malloc(1024*sizeof(char));
    char *aux_main = (char*)strdup("i32 %argc, i8** %argv");
    int aux_count_f, aux_count_params_f = 0;

    aux_node_params = aux3->children;

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
        
        node *brother = aux_node_params->children;

        if(strcmp(aux_node_params->nodeType, "ParamDecl") == 0){
            if(found_vars == NULL){
                found_vars = create_strlit(brother->brother->value, brother->nodeType);
            }
            else{
                add_strlit(found_vars, create_strlit(brother->brother->value, brother->nodeType));
            }
        }

        aux_node_params = aux_node_params->brother;
    }

    strlit_list *aux_param_decl = found_vars;

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
            sprintf(aux, "i32 %%%s_aux", aux_param_decl->value);
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
            sprintf(aux, "i1 %%%s_aux", aux_param_decl->value);
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
            sprintf(aux, "double %%%s_aux", aux_param_decl->value);
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
        clearList(found_vars);
        found_vars = NULL;
    }
    else{
        strlit_list *atual = found_vars;
        while(atual != NULL){
            if(strcmp(atual->type, "Int") == 0){
                printf("\t%%%s = alloca i32, align 4\n", atual->value);
                printf("\tstore i32 %%%s_aux, i32* %%%s, align 4\n", atual->value, atual->value);
            }
            else if(strcmp(atual->type, "Double") == 0){
                printf("\t%%%s = alloca double, align 8\n", atual->value);
                printf("\tstore double %%%s_aux, double* %%%s, align 8\n", atual->value, atual->value);
            }
            else if(strcmp(atual->type, "Bool") == 0){
                printf("\t%%%s = alloca i1\n", atual->value);
                printf("\tstore i1 %%%s_aux, i1* %%%s\n", atual->value, atual->value);
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
    strlit_list *atual = found_vars;
    while(atual != NULL){
        if(strcmp(atual->value, name) == 0){
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

    if(found_vars == NULL){
        found_vars = create_strlit(name, type);
    }
    else{
        add_strlit(found_vars, create_strlit(name, type));
    }
}

void function_realLit(node *atual){
    /*printf("\t%%%d = alloca double, align 8\n", count_temp_vars);
    change_reallit(atual->value);
    printf("\tstore double %.16E, double* %%%d, align 8\n", atof(aux_change_reallit), count_temp_vars);                  
    count_temp_vars++;*/
    change_reallit(atual->value);
    printf("\t%%%d = fadd double 0.000000e+00, %.16E\n", count_temp_vars, atof(aux_change_reallit));
    count_temp_vars++;
}

void function_decLit(node *atual){
    /*printf("\t%%%d = alloca i32, align 4\n", count_temp_vars);
    change_declit(atual->value);
    printf("\tstore i32 %d, i32* %%%d, align 4\n", atoi(aux_change_declit), count_temp_vars);                  
    count_temp_vars++;*/
    change_declit(atual->value);
    printf("\t%%%d = add i32 0, %s\n", count_temp_vars, aux_change_declit);
    count_temp_vars++;
}

void function_boolLit(node *atual){
    /*printf("\t%%%d = alloca i1\n", count_temp_vars);
    printf("\tstore i1 %s, i1* %%%d\n", atual->value, count_temp_vars);                  
    count_temp_vars++;
    printf("\t%%%d = load i1, i1* %%%d\n", count_temp_vars, count_temp_vars-1);*/
    if(strcmp(atual->value, "true") == 0){
        printf("\t%%%d = add i1 0, 1\n", count_temp_vars);
    }
    else{
        printf("\t%%%d = add i1 0, 0\n", count_temp_vars);
    }
    count_temp_vars++;
}

void function_length(node *atual){
    printf("\t%%%d = load i32, i32* %%argc_aux, align 4\n", count_temp_vars);
    count_temp_vars++;
    printf("\t%%%d = sub i32 %%%d, 1\n", count_temp_vars, count_temp_vars-1);
    count_temp_vars++;
}

void function_print(node *atual){
    strlit_list *aux_str;
    char *aux = (char*)malloc(1024*sizeof(char));

    if(strcmp(atual->children->anoted, "String") == 0){
        change_strlit(atual->children->value);
        sprintf(aux, "@.global.strlit.%d = private unnamed_addr constant [%d x i8] c\"%s\", align 1\n", count_strlit, aux_length_strlit, aux_change_strlit);
        printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([%d x i8], [%d x i8]* @.global.strlit.%d, i32 0, i32 0))\n", count_temp_vars, aux_length_strlit, aux_length_strlit, count_strlit);
        count_temp_vars++;
    }
    else if(strcmp(atual->children->anoted, "int") == 0){
        sprintf(aux, "@.global.strlit.%d = private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\", align 1\n", count_strlit);
        printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.global.strlit.%d, i32 0, i32 0), i32 %%%d)\n", count_temp_vars, count_strlit, count_temp_vars-1);
        count_temp_vars++;
    }
    else if(strcmp(atual->children->anoted, "double") == 0){                 
        sprintf(aux, "@.global.strlit.%d = private unnamed_addr constant [7 x i8] c\"%%.16E\\0A\\00\", align 1\n", count_strlit);
        printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.global.strlit.%d, i32 0, i32 0), double %%%d)\n", count_temp_vars, count_strlit, count_temp_vars-1);
        count_temp_vars++;
    }
    else if(strcmp(atual->children->anoted, "boolean") == 0){
        printf("\t%%compare.%d = icmp eq i1 %%%d, 1\n", count_compares_label, count_temp_vars-1);
        printf("\tbr i1 %%compare.%d, label %%compare.if.%d, label %%compare.else.%d\n", count_compares_label, count_compares_label, count_compares_label);
        printf("\tcompare.if.%d:\n", count_compares_label);
        sprintf(aux, "@.global.strlit.%d = private unnamed_addr constant [6 x i8] c\"true\\0A\\00\", align 1\n", count_strlit);
        printf("\t\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.%d, i32 0, i32 0))\n", count_temp_vars, count_strlit);
        printf("\t\tbr label %%compare.end.%d\n", count_compares_label);
        count_temp_vars++;
        count_strlit++;
        
        //ADD TO LIST
        if(list_global_strlit == NULL){
            list_global_strlit = create_strlit(aux, atual->children->anoted);
        }
        else{
            aux_str = create_strlit(aux, atual->children->anoted);
            add_strlit(list_global_strlit, aux_str);
        }

        printf("\tcompare.else.%d:\n", count_compares_label);
        printf("\t\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.global.strlit.%d, i32 0, i32 0))\n", count_temp_vars, count_strlit);
        printf("\t\tbr label %%compare.end.%d\n", count_compares_label);
        sprintf(aux, "@.global.strlit.%d = private unnamed_addr constant [7 x i8] c\"false\\0A\\00\", align 1\n", count_strlit);
        printf("\tcompare.end.%d:\n", count_compares_label);
        count_compares_label++;
        count_temp_vars++;
    }

    if(list_global_strlit == NULL){
        list_global_strlit = create_strlit(aux, atual->children->anoted);
    }
    else{
        aux_str = create_strlit(aux, atual->children->anoted);
        add_strlit(list_global_strlit, aux_str);
    }

    count_strlit++;

    free(aux);
    aux = NULL;
}

void function_assign(node *atual){
    node *aux = atual->children;
    if(strcmp(aux->anoted, "int") == 0){
        if(verify_its_global(aux->value) != NULL){
            printf("\tstore i32 %%%d, i32* %%%s, align 4\n", count_temp_vars-1, aux->value);
        }
        else{
            printf("\tstore i32 %%%d, i32* @global.var.%s, align 4\n", count_temp_vars-1, aux->value);
        }
    }
    else if(strcmp(aux->anoted, "double") == 0){
        if(strcmp(aux->brother->anoted, "int") == 0){
            printf("\t%%convertion.%d = sitofp i32 %%%d to double\n", count_convertions, count_temp_vars-1);
            if(verify_its_global(aux->value) != NULL){
                printf("\tstore double %%convertion.%d, double* %%%s, align 8\n", count_convertions, aux->value);                  
            }
            else{
                printf("\tstore double %%convertion.%d, double* @global.var.%s, align 8\n", count_convertions, aux->value);                                     
            }
            count_convertions++;
        }
        else{
            if(verify_its_global(aux->value) != NULL){
                printf("\tstore double %%%d, double* %%%s, align 8\n", count_temp_vars-1, aux->value);                  
            }
            else{
                printf("\tstore double %%%d, double* @global.var.%s, align 8\n", count_temp_vars-1, aux->value);                                     
            }
        }
    }
    else if(strcmp(aux->anoted, "boolean") == 0){
        if(verify_its_global(aux->value) != NULL){
            printf("\tstore i1 %%%d, i1* %%%s\n", count_temp_vars-1, aux->value);                   
        }
        else{
            printf("\tstore i1 %%%d, i1* @global.var.%s\n", count_temp_vars-1, aux->value);
        }
    }
}

void function_id(node *atual){
    if(strcmp(atual->anoted, "String[]") == 0){
        //printf("\t%%%d = load i8**, i8*** %%argv_aux, align 8\n", count_temp_vars);
        //count_temp_vars++;
        return;
    }
    else if(verify_its_global(atual->value) != NULL){
        if(strcmp(atual->anoted, "int") == 0){
            printf("\t%%%d = load i32, i32* %%%s, align 4\n", count_temp_vars, atual->value);
        }
        else if(strcmp(atual->anoted, "double") == 0){
            printf("\t%%%d = load double, double* %%%s, align 8\n", count_temp_vars, atual->value);
        }
        else if(strcmp(atual->anoted, "boolean") == 0){
            printf("\t%%%d = load i1, i1* %%%s\n", count_temp_vars, atual->value);
        }
        count_temp_vars++;
    }
    else{
        if(strcmp(atual->anoted, "int") == 0){
            printf("\t%%%d = load i32, i32* @global.var.%s, align 4\n", count_temp_vars, atual->value);
        }
        else if(strcmp(atual->anoted, "double") == 0){
            printf("\t%%%d = load double, double* @global.var.%s, align 8\n", count_temp_vars, atual->value);
        }
        else if(strcmp(atual->anoted, "boolean") == 0){
            printf("\t%%%d = load i1, i1* @global.var.%s\n", count_temp_vars, atual->value);
        }
        count_temp_vars++;
    }
}

void function_minus(node *atual){
    if(strcmp(atual->anoted, "int") == 0){
        printf("\t%%%d = sub nsw i32 0, %%%d\n", count_temp_vars, count_temp_vars-1);
        count_temp_vars++;
    }
    else{
        printf("\t%%%d = fsub double -0.000000e+00, %%%d\n", count_temp_vars, count_temp_vars-1);
        count_temp_vars++;
    }
}

void function_parseArgs(node *atual){
    printf("\t%%%d = add i32 %%%d, 1\n", count_temp_vars, count_temp_vars-1);
    count_temp_vars++;
    printf("\t%%%d = load i8**, i8*** %%argv_aux, align 8\n", count_temp_vars);
    count_temp_vars++;
    printf("\t%%%d = getelementptr inbounds i8*, i8** %%%d, i32 %%%d\n", count_temp_vars, count_temp_vars-1, count_temp_vars-2);
    count_temp_vars++;
    printf("\t%%%d = load i8*, i8** %%%d, align 8\n", count_temp_vars, count_temp_vars-1);
    count_temp_vars++;
    printf("\t%%%d = call i32 @atoi(i8* %%%d)\n", count_temp_vars, count_temp_vars-1);
    count_temp_vars++;
}

void function_add(node *atual, int var1, int var2){
    if(strcmp(atual->anoted, "int") == 0){
        printf("\t%%%d = add i32 %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
    else if(strcmp(atual->anoted, "double") == 0){
        if(strcmp(atual->children->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var1);
            var1 = count_temp_vars;
            count_temp_vars++;
        }
        if(strcmp(atual->children->brother->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var2);
            var2 = count_temp_vars;
            count_temp_vars++;
        }
        printf("\t%%%d = fadd double %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
}

void function_sub(node *atual, int var1, int var2){
    if(strcmp(atual->anoted, "int") == 0){
        printf("\t%%%d = sub i32 %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
    else if(strcmp(atual->anoted, "double") == 0){
        if(strcmp(atual->children->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var1);
            var1 = count_temp_vars;
            count_temp_vars++;
        }
        if(strcmp(atual->children->brother->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var2);
            var2 = count_temp_vars;
            count_temp_vars++;
        }
        printf("\t%%%d = fsub double %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
}

void function_mul(node *atual, int var1, int var2){
    if(strcmp(atual->anoted, "int") == 0){
        printf("\t%%%d = mul i32 %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
    else if(strcmp(atual->anoted, "double") == 0){
        if(strcmp(atual->children->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var1);
            var1 = count_temp_vars;
            count_temp_vars++;
        }
        if(strcmp(atual->children->brother->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var2);
            var2 = count_temp_vars;
            count_temp_vars++;
        }
        printf("\t%%%d = fmul double %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
}

void function_div(node *atual, int var1, int var2){
    if(strcmp(atual->anoted, "int") == 0){
        printf("\t%%%d = sdiv i32 %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
    else if(strcmp(atual->anoted, "double") == 0){
        if(strcmp(atual->children->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var1);
            var1 = count_temp_vars;
            count_temp_vars++;
        }
        if(strcmp(atual->children->brother->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var2);
            var2 = count_temp_vars;
            count_temp_vars++;
        }
        printf("\t%%%d = fdiv double %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
}

void function_mod(node *atual, int var1, int var2){
    if(strcmp(atual->anoted, "int") == 0){
        printf("\t%%%d = srem i32 %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
    else if(strcmp(atual->anoted, "double") == 0){
        if(strcmp(atual->children->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var1);
            var1 = count_temp_vars;
            count_temp_vars++;
        }
        if(strcmp(atual->children->brother->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var2);
            var2 = count_temp_vars;
            count_temp_vars++;
        }
        printf("\t%%%d = frem double %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
}

void function_not(node *atual, int var1){
    printf("\t%%%d = zext i1 %%%d to i32\n", count_temp_vars, var1);
    count_temp_vars++;
    printf("\t%%%d = icmp eq i32 %%%d, 0\n", count_temp_vars, count_temp_vars-1);
    count_temp_vars++;
}

void function_eq(node *atual, int var1, int var2){
    if(strcmp(atual->children->anoted, "int") == 0 && strcmp(atual->children->brother->anoted, "int") == 0){
        printf("\t%%%d = icmp eq i32 %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
    else if(strcmp(atual->children->anoted, "boolean") == 0 && strcmp(atual->children->brother->anoted, "boolean") == 0){
        printf("\t%%%d = zext i1 %%%d to i32\n", count_temp_vars, var1);
        count_temp_vars++;
        printf("\t%%%d = zext i1 %%%d to i32\n", count_temp_vars, var2);
        count_temp_vars++;
        printf("\t%%%d = icmp eq i32 %%%d, %%%d\n", count_temp_vars, count_temp_vars-1, count_temp_vars-2);
        count_temp_vars++;
    }
    else{
        if(strcmp(atual->children->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var1);
            var1 = count_temp_vars;
            count_temp_vars++;
        }
        if(strcmp(atual->children->brother->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var2);
            var2 = count_temp_vars;
            count_temp_vars++;
        }
        printf("\t%%%d = fcmp oeq double %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
}

void function_neq(node *atual, int var1, int var2){
    if(strcmp(atual->children->anoted, "int") == 0 && strcmp(atual->children->brother->anoted, "int") == 0){
        printf("\t%%%d = icmp ne i32 %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
    else if(strcmp(atual->children->anoted, "boolean") == 0 && strcmp(atual->children->brother->anoted, "boolean") == 0){
        printf("\t%%%d = zext i1 %%%d to i32\n", count_temp_vars, var1);
        count_temp_vars++;
        printf("\t%%%d = zext i1 %%%d to i32\n", count_temp_vars, var2);
        count_temp_vars++;
        printf("\t%%%d = icmp ne i32 %%%d, %%%d\n", count_temp_vars, count_temp_vars-1, count_temp_vars-2);
        count_temp_vars++;
    }
    else{ //tem um double
        if(strcmp(atual->children->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var1);
            var1 = count_temp_vars;
            count_temp_vars++;
        }
        if(strcmp(atual->children->brother->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var2);
            var2 = count_temp_vars;
            count_temp_vars++;
        }
        printf("\t%%%d = fcmp une double %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
}

void function_lt(node *atual, int var1, int var2){
    if(strcmp(atual->children->anoted, "int") == 0 && strcmp(atual->children->brother->anoted, "int") == 0){
        printf("\t%%%d = icmp slt i32 %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
    else{
        if(strcmp(atual->children->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var1);
            var1 = count_temp_vars;
            count_temp_vars++;
        }
        if(strcmp(atual->children->brother->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var2);
            var2 = count_temp_vars;
            count_temp_vars++;
        }
        printf("\t%%%d = fcmp olt double %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
}

void function_gt(node *atual, int var1, int var2){
    if(strcmp(atual->children->anoted, "int") == 0 && strcmp(atual->children->brother->anoted, "int") == 0){
        printf("\t%%%d = icmp sgt i32 %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
    else{ //tem um double
        if(strcmp(atual->children->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var1);
            var1 = count_temp_vars;
            count_temp_vars++;
        }
        if(strcmp(atual->children->brother->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var2);
            var2 = count_temp_vars;
            count_temp_vars++;
        }
        printf("\t%%%d = fcmp ogt double %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
}

void function_leq(node *atual, int var1, int var2){
    if(strcmp(atual->children->anoted, "int") == 0 && strcmp(atual->children->brother->anoted, "int") == 0){
        printf("\t%%%d = icmp sle i32 %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
    else{
        if(strcmp(atual->children->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var1);
            var1 = count_temp_vars;
            count_temp_vars++;
        }
        if(strcmp(atual->children->brother->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var2);
            var2 = count_temp_vars;
            count_temp_vars++;
        }
        printf("\t%%%d = fcmp ole double %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
}

void function_geq(node *atual, int var1, int var2){
    if(strcmp(atual->children->anoted, "int") == 0 && strcmp(atual->children->brother->anoted, "int") == 0){
        printf("\t%%%d = icmp sge i32 %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
    else{
        if(strcmp(atual->children->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var1);
            var1 = count_temp_vars;
            count_temp_vars++;
        }
        if(strcmp(atual->children->brother->anoted, "int") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, var2);
            var2 = count_temp_vars;
            count_temp_vars++;
        }
        printf("\t%%%d = fcmp oge double %%%d, %%%d\n", count_temp_vars, var1, var2);
        count_temp_vars++;
    }
}

void function_and(node *atual){
    node *first = atual->children->brother;
    while(strcmp(first->nodeType, "NULL") == 0){
        first = first->brother;
    }

    int aux_count_and_or = count_label_and_or;
    count_label_and_or++;
    printf("\tbr label %%label.entry%d\n", aux_count_and_or);
    printf("label.entry%d:        ;it's an and\n", aux_count_and_or);
    printf("\t%%%d = icmp eq i1 %%%d, 1\n", count_temp_vars, count_temp_vars-1);
    printf("\tbr i1 %%%d, label %%label.transition%d, label %%label.end%d\n", count_temp_vars, aux_count_and_or, aux_count_and_or);
    printf("label.transition%d:       ;transition of an and\n", aux_count_and_or);
    count_temp_vars++;
    code_llvm(first);
    printf("\t%%%d = icmp eq i1 %%%d, 1\n", count_temp_vars, count_temp_vars-1);
    printf("\tbr label %%label.end%d\n", aux_count_and_or);
    printf("label.end%d:      ; it's the end of an and\n", aux_count_and_or);
    count_temp_vars++;
    if(aux_count_and_or == count_label_and_or-1){ //não existiu mais nenhum and
        printf("\t%%%d = phi i1 [ 0, %%label.entry%d ], [ %%%d, %%label.transition%d ]\n", count_temp_vars, aux_count_and_or, count_temp_vars-1, aux_count_and_or);
    }
    else{ //existiu mais um and
        printf("\t%%%d = phi i1 [ 0, %%label.entry%d ], [ %%%d, %%label.end%d ]\n", count_temp_vars, aux_count_and_or, count_temp_vars-1, aux_count_and_or+1);
    }
    count_temp_vars++;
}

void function_or(node *atual){
    node *first = atual->children->brother;
    while(strcmp(first->nodeType, "NULL") == 0){
        first = first->brother;
    }

    int aux_count_and_or = count_label_and_or;
    count_label_and_or++;
    printf("\tbr label %%label.entry%d\n", aux_count_and_or);
    printf("label.entry%d:        ;it's an or\n", aux_count_and_or);
    printf("\t%%%d = icmp eq i1 %%%d, 0\n", count_temp_vars, count_temp_vars-1);
    printf("\tbr i1 %%%d, label %%label.transition%d, label %%label.end%d\n", count_temp_vars, aux_count_and_or, aux_count_and_or);
    printf("label.transition%d:       ;transition of an or\n", aux_count_and_or);
    count_temp_vars++;
    code_llvm(first);
    printf("\t%%%d = icmp eq i1 %%%d, 1\n", count_temp_vars, count_temp_vars-1);
    printf("\tbr label %%label.end%d\n", aux_count_and_or);
    printf("label.end%d:      ; it's the end of an or\n", aux_count_and_or);
    count_temp_vars++;
    if(aux_count_and_or == count_label_and_or-1){
        printf("\t%%%d = phi i1 [ 1, %%label.entry%d ], [ %%%d, %%label.transition%d ]\n", count_temp_vars, aux_count_and_or, count_temp_vars-1, aux_count_and_or);
    }
    else{
        printf("\t%%%d = phi i1 [ 1, %%label.entry%d ], [ %%%d, %%label.end%d ]\n", count_temp_vars, aux_count_and_or, count_temp_vars-1, aux_count_and_or+1);
    }
    count_temp_vars++;
}

void function_if(node *atual){
    node *first = atual->children->brother;
    while(strcmp(first->nodeType, "NULL") == 0){
        first = first->brother;
    }
    node *second = first->brother;
    while(strcmp(second->nodeType, "NULL") == 0){
        second = second->brother;
    }

    int aux_count_label_if = count_label_if;
    count_label_if++;

    printf("\tbr label %%label.entry.if%d\n", aux_count_label_if);
    printf("label.entry.if%d:       ;it's if \n", aux_count_label_if);
    printf("\t%%%d = icmp eq i1 %%%d, 1\n", count_temp_vars, count_temp_vars-1);
    printf("\tbr i1 %%%d, label %%label.then%d, label %%label.else%d\n", count_temp_vars, aux_count_label_if, aux_count_label_if);
    count_temp_vars++;

    printf("label.then%d:       ;it's if \n", aux_count_label_if);
    code_llvm(first);
    printf("br label %%label.finished.if%d\n", aux_count_label_if);
    
    printf("label.else%d:       ;it's else \n", aux_count_label_if);
    code_llvm(second);
    printf("br label %%label.finished.if%d\n", aux_count_label_if);
    
    printf("label.finished.if%d:\n", aux_count_label_if);
    
}

void function_while(node *atual){
    node *first = atual->children;
    while(strcmp(first->nodeType, "NULL") == 0){
        first = first->brother;
    }
    node *second = first->brother;
    while(strcmp(second->nodeType, "NULL") == 0){
        second = second->brother;
    }

    int aux_count_label_while = count_label_while;
    count_label_while++;

    printf("\tbr label %%label.entry.while%d\n", aux_count_label_while);
    printf("label.entry.while%d:       ;it's while \n", aux_count_label_while);
    code_llvm(first);
    printf("\t%%%d = icmp eq i1 %%%d, 1\n", count_temp_vars, count_temp_vars-1);
    printf("\tbr i1 %%%d, label %%label.work.while%d, label %%label.finished.while%d\n", count_temp_vars, aux_count_label_while, aux_count_label_while);
    count_temp_vars++;
    
    printf("label.work.while%d:       ;it's while \n", aux_count_label_while);
    code_llvm(second);
    printf("\tbr label %%label.entry.while%d\n", aux_count_label_while);
    
    printf("label.finished.while%d:\n", aux_count_label_while);
    
}

void function_dowhile(node *atual){
    node *first = atual->children;
    while(strcmp(first->nodeType, "NULL") == 0){
        first = first->brother;
    }
    node *second = first->brother;
    while(strcmp(second->nodeType, "NULL") == 0){
        second = second->brother;
    }

    int aux_count_label_dowhile = count_label_dowhile;
    count_label_dowhile++;

    printf("\tbr label %%label.work.dowhile%d\n", aux_count_label_dowhile);
    printf("label.entry.dowhile%d:       ;it's dowhile \n", aux_count_label_dowhile);
    code_llvm(second);
    printf("\t%%%d = icmp eq i1 %%%d, 1\n", count_temp_vars, count_temp_vars-1);
    printf("\tbr i1 %%%d, label %%label.work.dowhile%d, label %%label.finished.dowhile%d\n", count_temp_vars, aux_count_label_dowhile, aux_count_label_dowhile);
    count_temp_vars++;
    
    printf("label.work.dowhile%d:       ;it's dowhile\n", aux_count_label_dowhile);
    code_llvm(first);
    printf("\tbr label %%label.entry.dowhile%d\n", aux_count_label_dowhile);
    
    printf("label.finished.dowhile%d:\n", aux_count_label_dowhile);
    
}

void function_return(node *atual){
    if(atual->children == NULL){
        printf("\tret void\n");
        count_temp_vars++;
        return;
    }
    code_llvm(atual->children);
    if(strcmp(atual->children->anoted, "int") == 0){
        if(strcmp(global_function_type, "Double") == 0){
            printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, count_temp_vars-1);
            count_temp_vars++;
            printf("\tret double %%%d\n", count_temp_vars-1);
        }
        else{
            printf("\tret i32 %%%d\n", count_temp_vars-1);
        }
    }
    else if(strcmp(atual->children->anoted, "double") == 0){
        printf("\tret double %%%d\n", count_temp_vars-1);
    }
    else{
        printf("\tret i1 %%%d\n", count_temp_vars-1);
    }
    count_temp_vars++;
}

void function_call(node *atual){
    int i;
    param_list *aux_params;
    node *aux_node_params;
    char *aux_name_f = (char*)malloc(1024*sizeof(char));
    char *aux_params_f = (char*)malloc(1024*sizeof(char));
    int aux_count_f = 0, aux_count_params_f = 0, n_params;

    aux_params = atual->children->params;
    n_params = atual->children->n_params;
    aux_node_params = atual->children->brother;

    if(strcmp(atual->anoted, "boolean") == 0){
        sprintf(aux_name_f, "function.declaration.%s.%s.", "b", atual->children->value);
    }
    else if(strcmp(atual->anoted, "int") == 0){
        sprintf(aux_name_f, "function.declaration.%s.%s.", "i", atual->children->value);
    }
    else if(strcmp(atual->anoted, "double") == 0){
        sprintf(aux_name_f, "function.declaration.%s.%s.", "d", atual->children->value);
    }
    else{
        sprintf(aux_name_f, "function.declaration.%s.%s.", "v", atual->children->value);
    }

    aux_count_f = strlen(aux_name_f);

    while(aux_params != NULL){
        if(strcmp(aux_node_params->nodeType, "NULL") == 0){
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
            sprintf(aux, "i32 %%%d", count_temp_vars-1);

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
            sprintf(aux, "i1 %%%d", count_temp_vars-1);

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
            if(strcmp(aux_node_params->anoted, "int") == 0){
                code_llvm(aux_node_params);
                printf("\t%%%d = sitofp i32 %%%d to double\n", count_temp_vars, count_temp_vars-1);
                count_temp_vars++;
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
            sprintf(aux, "double %%%d", count_temp_vars-1);

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

        n_params--;
        aux_params = aux_params->next;
        aux_node_params = aux_node_params->brother;
    }

    aux_name_f[aux_count_f] = '\0';
    aux_params_f[aux_count_params_f] = '\0';

    if(strcmp(atual->anoted, "int") == 0){
        printf("\t%%%d = call i32 @%s(%s)\n", count_temp_vars, aux_name_f, aux_params_f);
        count_temp_vars++;
    }
    else if(strcmp(atual->anoted, "double") == 0){
        printf("\t%%%d = call double @%s(%s)\n", count_temp_vars, aux_name_f, aux_params_f);
        count_temp_vars++;
    }
    else if(strcmp(atual->anoted, "boolean") == 0){
        printf("\t%%%d = call i1 @%s(%s)\n", count_temp_vars, aux_name_f, aux_params_f);
        count_temp_vars++;
    }
    else{
        printf("\tcall void @%s(%s)\n", aux_name_f, aux_params_f);
    }
    
    free(aux_name_f);
    aux_name_f = NULL;
    free(aux_params_f);
    aux_params_f = NULL;
}

void change_declit(char *value){
    int i=0, j=0;

    while(value[i] != '\0'){
        if(value[i] != '_'){
            aux_change_declit[j] = value[i];
            j++;
        }
        i++;
    }

    aux_change_declit[j] = '\0';
}

void change_reallit(char *value){
    int i=0, j=0;

    while(value[i] != '\0'){
        if(value[i] != '_'){
            aux_change_reallit[j] = value[i];
            j++;
        }
        i++;
    }

    aux_change_reallit[j] = '\0';
}

void code_llvm(node *atual){
    node *aux1;

    if(strcmp(atual->nodeType, "VarDecl") == 0){
        function_varDecl(atual->children->nodeType, atual->children->brother->value);
    }
    else if(strcmp(atual->nodeType, "Call") == 0){
        function_call(atual);
    }
    else if(strcmp(atual->nodeType, "Print") == 0){
        aux1 = atual->children;
        while(aux1 != NULL){
            code_llvm(aux1);
            aux1 = aux1->brother;
        }

        function_print(atual);
    }
    else if(strcmp(atual->nodeType, "RealLit") == 0){
        function_realLit(atual);
    }
    else if(strcmp(atual->nodeType, "DecLit") == 0){
        function_decLit(atual);
    }
    else if(strcmp(atual->nodeType, "BoolLit") == 0){
        function_boolLit(atual);
    }
    else if(strcmp(atual->nodeType, "Assign") == 0){
        aux1 = atual->children;
        while(aux1 != NULL){
            code_llvm(aux1);
            aux1 = aux1->brother;
        }
        function_assign(atual);
        function_id(atual->children);
    }
    else if(strcmp(atual->nodeType, "Id") == 0){
        function_id(atual);
    }
    else if(strcmp(atual->nodeType, "Plus") == 0){
        aux1 = atual->children;
        while(aux1 != NULL){
            code_llvm(aux1);
            aux1 = aux1->brother;
        }
    }
    else if(strcmp(atual->nodeType, "Minus") == 0){
        aux1 = atual->children;
        while(aux1 != NULL){
            code_llvm(aux1);
            aux1 = aux1->brother;
        }
        function_minus(atual);
    }
    else if(strcmp(atual->nodeType, "Length") == 0){
        function_length(atual);
    }
    else if(strcmp(atual->nodeType, "ParseArgs") == 0){
        code_llvm(atual->children->brother);
        function_parseArgs(atual);
    }
    else if(strcmp(atual->nodeType, "Add") == 0){
        aux1 = atual->children;
        code_llvm(aux1);
        int var1 = count_temp_vars-1;
        aux1 = atual->children->brother;
        code_llvm(aux1);
        int var2 = count_temp_vars-1;

        function_add(atual, var1, var2);
    }
    else if(strcmp(atual->nodeType, "Sub") == 0){
        aux1 = atual->children;
        code_llvm(aux1);
        int var1 = count_temp_vars-1;
        aux1 = atual->children->brother;
        code_llvm(aux1);
        int var2 = count_temp_vars-1;

        function_sub(atual, var1, var2);
    }
    else if(strcmp(atual->nodeType, "Mul") == 0){
        aux1 = atual->children;
        code_llvm(aux1);
        int var1 = count_temp_vars-1;
        aux1 = atual->children->brother;
        code_llvm(aux1);
        int var2 = count_temp_vars-1;

        function_mul(atual, var1, var2);
    }
    else if(strcmp(atual->nodeType, "Div") == 0){
        aux1 = atual->children;
        code_llvm(aux1);
        int var1 = count_temp_vars-1;
        aux1 = atual->children->brother;
        code_llvm(aux1);
        int var2 = count_temp_vars-1;

        function_div(atual, var1, var2);
    }
    else if(strcmp(atual->nodeType, "Mod") == 0){
        aux1 = atual->children;
        code_llvm(aux1);
        int var1 = count_temp_vars-1;
        aux1 = atual->children->brother;
        code_llvm(aux1);
        int var2 = count_temp_vars-1;

        function_mod(atual, var1, var2);
    }
    else if(strcmp(atual->nodeType, "Not") == 0){
        aux1 = atual->children;
        code_llvm(aux1);
        int var1 = count_temp_vars-1;

        function_not(atual, var1);
    }
    else if(strcmp(atual->nodeType, "And") == 0){
        code_llvm(atual->children);
        function_and(atual);
    }
    else if(strcmp(atual->nodeType, "Or") == 0){
        code_llvm(atual->children);
        function_or(atual);
    }
    else if(strcmp(atual->nodeType, "Eq") == 0){
        aux1 = atual->children;
        code_llvm(aux1);
        int var1 = count_temp_vars-1;
        aux1 = atual->children->brother;
        code_llvm(aux1);
        int var2 = count_temp_vars-1;

        function_eq(atual, var1, var2);
    }
    else if(strcmp(atual->nodeType, "Neq") == 0){
        aux1 = atual->children;
        code_llvm(aux1);
        int var1 = count_temp_vars-1;
        aux1 = atual->children->brother;
        code_llvm(aux1);
        int var2 = count_temp_vars-1;

        function_neq(atual, var1, var2);
    }
    else if(strcmp(atual->nodeType, "Lt") == 0){
        aux1 = atual->children;
        code_llvm(aux1);
        int var1 = count_temp_vars-1;
        aux1 = atual->children->brother;
        code_llvm(aux1);
        int var2 = count_temp_vars-1;

        function_lt(atual, var1, var2);
    }
    else if(strcmp(atual->nodeType, "Gt") == 0){
        aux1 = atual->children;
        code_llvm(aux1);
        int var1 = count_temp_vars-1;
        aux1 = atual->children->brother;
        code_llvm(aux1);
        int var2 = count_temp_vars-1;

        function_gt(atual, var1, var2);
    }
    else if(strcmp(atual->nodeType, "Leq") == 0){
        aux1 = atual->children;
        code_llvm(aux1);
        int var1 = count_temp_vars-1;
        aux1 = atual->children->brother;
        code_llvm(aux1);
        int var2 = count_temp_vars-1;

        function_leq(atual, var1, var2);
    }
    else if(strcmp(atual->nodeType, "Geq") == 0){
        aux1 = atual->children;
        code_llvm(aux1);
        int var1 = count_temp_vars-1;
        aux1 = atual->children->brother;
        code_llvm(aux1);
        int var2 = count_temp_vars-1;

        function_geq(atual, var1, var2);
    }
    else if(strcmp(atual->nodeType, "Block") == 0){
        aux1 = atual->children;
        while(aux1 != NULL){
            code_llvm(aux1);
            aux1 = aux1->brother;
        }
    }
    else if(strcmp(atual->nodeType, "If") == 0){
        code_llvm(atual->children);
        function_if(atual);
    }
    else if(strcmp(atual->nodeType, "While") == 0){
        function_while(atual);
    }
    else if(strcmp(atual->nodeType, "DoWhile") == 0){
        function_dowhile(atual);
    }
    else if(strcmp(atual->nodeType, "Return") == 0){
        founded_return = 1;
        function_return(atual);
    }
}