/*
 * Sofia Inês Graça Paulino
 * 2020127408
 */

#ifndef TP_PARAGEM_H
#define TP_PARAGEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct paragem paragem, *pparagem;

struct paragem{
    char nome[100];
    char codigo[5]; //porque o último é \0
    int linhas;
};

pparagem menuParagens(pparagem p, int* totalParagens);

void getInfoParagem(pparagem p, int total);

pparagem registarParagem(pparagem p, int* totalParagens);

void visualizarParagens(pparagem p, int total);

pparagem eliminarParagem(pparagem p, int* totalParagens);

int existeParagem(pparagem p, int totalParagens, char* codigo);

void guardaParagens(pparagem p, int totalParagens);

#endif //TP_PARAGEM_H