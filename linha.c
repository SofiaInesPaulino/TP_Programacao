/*
 * Sofia Inês Graça Paulino
 * 2020127408
 */

#include "linha.h"

plinha menuLinhas(plinha l, int totalParagens, pparagem p){
    int opcao;
    do{
        printf("\n ***** MENU LINHAS ***** \n");
        printf("1 - Adicionar Linha Manualmente\n");
        printf("2 - Adicionar Linha Por Ficheiro\n");
        printf("3 - Visualizar Linhas\n");
        printf("4 - Atualizar Linha\n");
        printf("5 - Voltar\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                l = adicionarLinhaManualmente(l, totalParagens, p);
                break;
            case 2:
                printf("Funcao por implementar");
                break;
            case 3:
                visualizarLinhas(l);
                break;
            case 4:
                atualizarLinha(l, totalParagens, p);
                break;
            default:
                break;
        }
    }while(opcao != 5);
    return l;
}

int existeLinha(plinha l, char* nome){
    while(l != NULL){
        if(strcmp(l->nome, nome) == 0){
            return 1;
        }
        l = l->prox;
    }
    return 0;
}

void getInfoLinhas(plinha l, plinha linha, int totalParagens, pparagem p){
    char paragem[5];
    char** aux;
    do{
        printf("Nome:");
        scanf("%s", linha->nome); //TODO: alterar para getLine
    }while(existeLinha(l, linha->nome));
    do{
        printf("Codigo Paragem: (FIM para sair)");
        scanf("%s", paragem);
        if(existeParagem(p, totalParagens, paragem)){
            aux = realloc(linha->paragens, linha->totalP + 1);
            if(aux == NULL){
                printf("ERRO na realocacao ao adicionar paragem a linha\n");//TODO
                return;
            }
            for(int i = 0; i < totalParagens; i++){
                if(strcmp(p[i].codigo, paragem) == 0){
                    p[i].linhas++;
                    printf("ADD: %d\n", p[i].linhas);
                    break;
                }
            }
            linha->paragens = aux;
            strcpy(linha->paragens[linha->totalP], paragem);
            linha->totalP++;
        }
    }while(strcmp(paragem, "FIM") != 0);
}

plinha adicionarLinhaManualmente(plinha l, int totalParagens, pparagem p){
    if(totalParagens == 0){
        printf("Impossivel adicionar linhas! Crie primeiro paragens!\n");
        return NULL;
    }
    plinha novo = malloc(sizeof(linha));
    if(novo == NULL){
        printf("ERRO a adicionar linha\n");
        printf("HERE");
        return l;
    }
    novo->totalP = 0;
    novo->paragens = NULL;
    getInfoLinhas(l, novo, totalParagens, p);
    novo->prox = l;
    if(l != NULL){
        l->ant = novo;
    }
    novo->ant = NULL;
    l = novo;
    return l;
}

void visualizarLinhas(plinha l){
    while(l != NULL){
        printf("Nome: %s\t", l->nome);
        for(int i = 0; i < l->totalP; i++){
            for(int j = 0; j < 4; j++) {
                printf("%c", l->paragens[i][j]);
            }
            putchar('\t');
        }
        putchar('\n');
        l = l->prox;
    }
}

plinha atualizarLinha(plinha l, int totalParagens, pparagem p){
    if(l == NULL){
        printf("Nao ha linhas para atualizar!\n");
        return l;
    }
    char nome[100];
    printf("Nome da Linha a atualizar:");
    scanf("%s", nome);
    if(!existeLinha(l, nome)){
        printf("A linha nao existe!");
        return l;
    }
    int opcao;
    do{
        printf("1 - Adicionar Paragem\n");
        printf("2 - Remover Paragem\n");
        printf("3 - Voltar\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                l = adicionarParagem(nome, l, totalParagens, p);
                break;
            case 2:
                l = removerParagem(nome, l, totalParagens, p);
                break;
            default:
                break;
        }
    }while(opcao != 3);
    return l;
}

plinha adicionarParagem(char* nome, plinha l, int totalParagens, pparagem p){
    plinha aux = l;
    while(aux != NULL && strcmp(aux->nome, nome) != 0){
        aux = aux->prox;
    }
    char paragem[5];
    char** paragemAux;
    printf("Codigo da paragem a adicionar:");
    scanf("%s", paragem);
    if(existeParagem(p, totalParagens, paragem)){
        paragemAux = realloc(aux->paragens, aux->totalP + 1);
        if(paragemAux == NULL){
            printf("Erro a adicionar paragem\n");
            return l;
        }
        aux->paragens = paragemAux;
        strcpy(aux->paragens[aux->totalP], paragem);
        aux->totalP++;
        for(int i = 0; i < totalParagens; i++){
            if(strcmp(p[i].codigo, paragem) == 0){
                printf("ANTES UPDATE: %d\n", p[i].linhas);
                p[i].linhas++;
                printf("UPDATE: %d\n", p[i].linhas);
                break;
            }
        }
    }
    return l;
}

plinha removerParagem(char* nome, plinha l, int totalParagens, pparagem p){
    printf("HERE");
    plinha aux = l;
    while(aux != NULL && strcmp(aux->nome, nome) == 0){
        aux = aux->prox;
    }
    char paragem[5];
    char** paragemAux;
    char paragemARemover[5];
    printf("Codigo da paragem a remover:");
    scanf("%s", paragem);
    for(int j = 0; j < aux->totalP; j++){
        if(strcmp(aux->paragens[j], paragem) == 0){
            strcpy(paragemARemover, paragem);
            for(int k = j; k < aux->totalP; k++){
                strcpy(aux->paragens[k], aux->paragens[k + 1]);
            }
            paragemAux = realloc(aux->paragens, aux->totalP - 1);
            if(paragemAux == NULL){
                printf("Erro a remover paragem\n");
                for(int k = aux->totalP - 1; k > j; k--){
                    strcpy(aux->paragens[k], aux->paragens[k - 1]);
                }
                strcpy(aux->paragens[j], paragemARemover);
                return l;
            }
            aux->paragens = paragemAux;
            aux->totalP--;
            for(int i = 0; i < totalParagens; i++){
                if(strcmp(p[i].codigo, paragem) == 0){ //TODO
                    p[i].linhas--;
                    printf("P[i]-linhas: %d", p[i].linhas);
                    break;
                }
            }
            break;
        }
    }
    return l;
}