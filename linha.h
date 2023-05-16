/*
 * Sofia Inês Graça Paulino
 * 2020127408
 */

#ifndef TP_LINHA_H
#define TP_LINHA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "paragem.h"

typedef struct linha linha, *plinha;

struct linha{
    char nome[100];
    char *paragens;
    int totalP; //quantas paragens que há nesta linha
    plinha prox;
    plinha ant;
};

plinha menuLinhas(plinha l, int totalParagens, pparagem p);

int existeLinha(plinha l, char* nome);

void getInfoLinhas(plinha l, plinha linha, int totalParagens, pparagem p);

plinha adicionarLinhaManualmente(plinha l, int totalParagens, pparagem p);

void visualizarLinhas(plinha l);

plinha atualizarLinha(plinha l, int totalParagens, pparagem p);

plinha adicionarParagem(char* nome, plinha l, int totalParagens, pparagem p);

plinha removerParagem(char* nome, plinha l, int totalParagens, pparagem p);

void libertarLinhas(plinha l);

#endif //TP_LINHA_H