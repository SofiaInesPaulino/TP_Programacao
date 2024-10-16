/*
 * Sofia Inês Graça Paulino
 * 2020127408
 */

#include "paragem.h"

pparagem menuParagens(pparagem p, int* totalParagens, int *id){
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
                p = registarParagem(p, totalParagens, id);
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

void getInfoParagem(pparagem p, int total, int id){
    char codigo[5] = "P";
    char numero[3];
    int aux = 2;
    do{
        printf("\nNome:");
        scanf(" %99[^\n]", p[total].nome);
    }while(getCodigo(p[total].nome, p, total) != NULL);
    while(id % 10 > 9){
        aux--;
        id = id % 10;
    }
    for(int i = 0; i < aux; i++){
        strcat(codigo, "0");
    }
    itoa(id, numero, 10);
    codigo[4] = '\0';
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

pparagem registarParagem(pparagem p, int* totalParagens, int* id){
    paragem* aux = realloc(p, sizeof(paragem)*((*totalParagens) + 1));
    if(aux == NULL){
        printf("ERRO na alocacao de memoria\n");
        return p;
    }
    p = aux;
    getInfoParagem(p, *totalParagens, *id);
    (*id)++;
    (*totalParagens)++;
    return p;
}

pparagem eliminarParagem(pparagem p, int* totalParagens){
    if(p == NULL){
        printf("Nao ha paragens para eliminar!\n");
        return p;
    }
    char codigo[5];
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
            aux = realloc(p, (*totalParagens - 1) * sizeof(paragem));
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
            return p;
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

void guardaParagens(pparagem p, int totalParagens){
    FILE* f;

    f = fopen("paragens.dat", "wb");
    if(f == NULL){
        printf("Erro a aceder ao ficheiro!\n");
        return;
    }
    printf("A guardar paragens em ficheiro\n");
    fwrite(&totalParagens, sizeof(int), 1, f);
    fwrite(p, sizeof(paragem), totalParagens, f);
    fclose(f);
}

pparagem recuperaParagens(int * totalParagens){
    FILE* f;
    pparagem p = NULL;

    *totalParagens = 0;
    f = fopen("paragens.dat", "rb");
    if(f == NULL){
        printf("Ficheiro de paragens nao existe ou erro a aceder-lhe!\n");
        return NULL;
    }
    fread(totalParagens, sizeof(int), 1, f);
    p = malloc(sizeof(paragem) * (*totalParagens));
    if(p == NULL){
        printf("Erro a alocar memoria\n");
        fclose(f);
        *totalParagens = 0;
        return NULL;
    }
    fread(p, sizeof(paragem), *totalParagens, f);
    fclose(f);
    return p;
}

char* getCodigo(char* nomeParagem, pparagem p, int totalParagens){
    for(int i = 0; i < totalParagens; i++){
        if(strcmp(p[i].nome, nomeParagem) == 0){
            return p[i].codigo;
        }
    }
    return NULL;
}