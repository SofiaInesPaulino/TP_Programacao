/*
 * Sofia Inês Graça Paulino
 * 2020127408
 */

#include "paragem.h"

pparagem menuParagens(pparagem p, int* totalParagens){
    int opcao;
    do{
        printf("\n ***** MENU PARAGENS ***** \n");
        printf("1 - Registar Paragem\n");
        printf("2 - Visualizar Paragens\n");
        printf("3 - Eliminar Paragem\n");
        printf("4 - Voltar\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                p = registarParagem(p, totalParagens);
                break;
            case 2:
                visualizarParagens(p, *totalParagens);
                break;
            case 3:
                p = eliminarParagem(p, totalParagens);
                break;
            default:
                break;
        }
    }while(opcao != 4);
    return p;
}

void getInfoParagem(pparagem p, int total){
    char codigo[4] = "P";
    char numero[3];
    int aux = 2;
    printf("\nNome:");
    scanf(" %99[^\n]", p[total].nome);
    while(total % 10 > 9){
        aux--;
        total = total % 10;
    }
    for(int i = 0; i < aux; i++){
        strcat(codigo, "0");
    }
    itoa(total, numero, 10);
    strcpy(p[total].codigo, strcat(codigo, numero));
    strcat(p[total].codigo, "\0");
    p[total].linhas = 0;
}

void visualizarParagens(pparagem p, int total){
    for(int i = 0; i < total; i++){
        printf("\n Nome:%s\tCodigo:%s", p[i].nome, p[i].codigo);
    }
    putchar('\n');
}

pparagem registarParagem(pparagem p, int* totalParagens){
    paragem* aux = realloc(p, sizeof(paragem)*((*totalParagens) + 1));
    if(aux == NULL){
        printf("ERRO na alocacao de memoria\n");
        return p;
    }
    p = aux;
    getInfoParagem(p, *totalParagens);
    (*totalParagens)++;
    return p;
}

pparagem eliminarParagem(pparagem p, int* totalParagens){
    if(p == NULL){
        printf("Nao ha paragens para eliminar!\n");
    }
    char codigo[4];
    paragem par;
    pparagem aux;
    printf("\nCodigo da paragem a eliminar:");
    scanf("%s", codigo);
    for(int i = 0; i < *totalParagens; i++){
        if(strcmp(p[i].codigo, codigo) == 0){
            if(*totalParagens == 1){ //se encontrar e for a unica paragem
                if(p[i].linhas == 0){ //nao esta associada a nenhuma linha
                    free(p);
                    *totalParagens = 0;
                    return NULL;
                }
                else{
                    printf("Impossivel eliminar paragem!\n");
                    return p;
                }
            }
            par = p[i];
            for(int j = i; j < *totalParagens - 1; j++){
                p[j] = p[j + 1];
            }
            aux = realloc(p, *totalParagens - 1);
            if(aux == NULL){
                for(int j = *totalParagens - 1; j > i; j--){
                    p[j] = p[j - 1];
                }
                p[i] = par;
                return p;
            }
            else{
                (*totalParagens)--;
                p = aux;
                if(*totalParagens == 0){
                    return NULL;
                }
            }

        }
    }
    return p;
}

int existeParagem(pparagem p, int totalParagens, char* codigo){
    for(int i = 0; i < totalParagens; i++){
        if(strcmp(p[i].codigo, codigo) == 0){
            return 1;
        }
    }
    return 0;
}