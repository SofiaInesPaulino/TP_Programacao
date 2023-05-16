/*
 * Sofia Inês Graça Paulino
 * 2020127408
 */
#include <stdio.h>
#include <stdlib.h>

#include "linha.h"
#include "paragem.h"

int main() {
    pparagem p = NULL; //array dinamico
    plinha l = NULL; //lista ligada
    int totalParagens = 0;
    int opcao;
    do{
        printf("\n ***** MENU ***** \n");
        printf("1 - Operacoes sobre paragens\n");
        printf("2 - Operacoes sobre linhas\n");
        printf("3 - Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                p = menuParagens(p, &totalParagens);
                break;
            case 2:
                l = menuLinhas(l, totalParagens, p);
                break;
            case 3:
                libertarLinhas(l);
                free(p);
                p = NULL;
                break;
            default:
                break;
        }
    }while(opcao != 3);
    return 0;
}