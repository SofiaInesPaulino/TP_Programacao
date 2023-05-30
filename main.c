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

    //ler informacao previamente gravada em ficheiro
    p = recuperaParagens(&totalParagens);
    l = recuperaLinhas();

    do{
        printf("\n ***** MENU ***** \n");
        printf("1 - Operacoes sobre paragens\n");
        printf("2 - Operacoes sobre linhas\n");
        printf("3 - Calcular percurso\n");
        printf("4 - Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                p = menuParagens(p, &totalParagens);
                break;
            case 2:
                l = menuLinhas(l, totalParagens, p);
                break;
            case 3:
                calcularPercurso(l, p, totalParagens);
                break;
            case 4:
                //guardar informacao em ficheiros
                guardaParagens(p, totalParagens);
                guardaLinhas(l);

                //libertar memoria alocada
                libertarLinhas(l);
                free(p);
                p = NULL;
                break;
            default:
                break;
        }
    }while(opcao != 4);
    return 0;
}