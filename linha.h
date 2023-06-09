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
    int totalP; //quantas paragens que há nesta linha
    char *paragens;
    plinha prox;
    plinha ant;
};

plinha menuLinhas(plinha l, int totalParagens, pparagem p);

int existeLinha(plinha l, char* nome);

void getInfoLinhas(plinha l, plinha linha, int totalParagens, pparagem p);

plinha adicionarLinhaManualmente(plinha l, int totalParagens, pparagem p);

plinha adicionarLinhasFicheiroTexto(plinha l, int totalParagens, pparagem p, char* nomeF);

void visualizarLinhas(plinha l);

plinha atualizarLinha(plinha l, int totalParagens, pparagem p);

plinha adicionarParagem(char* nome, plinha l, int totalParagens, pparagem p);

plinha removerParagem(char* nome, plinha l, int totalParagens, pparagem p);

void libertarLinhas(plinha l);

void guardaLinhas(plinha l);

plinha recuperaLinhas();

plinha insereNoFinal(plinha p, plinha novo);

void calcularPercursoUmaLinha(plinha l, pparagem p, int totalParagens, char *codOrigem[5], char *codDestino[5]);

int verificaOrigemDestino(plinha l, const char* codOrigem, const char* codDestino);

void getInfoPercurso(char** codOrigem, char** codDestino, pparagem p, int totalParagens);

void calcularPercursos(plinha l, pparagem p, int totalParagens);

#endif //TP_LINHA_H