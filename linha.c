/*
 * Sofia Inês Graça Paulino
 * 2020127408
 */

#include "linha.h"

plinha menuLinhas(plinha l, int totalParagens, pparagem p){
    int opcao;
    char ficheiro[100];
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
                printf("Nome do ficheiro:");
                scanf("%s", ficheiro);
                l = adicionarLinhasFicheiroTexto(l, totalParagens, p, ficheiro);
                break;
            case 3:
                visualizarLinhas(l);
                break;
            case 4:
                l = atualizarLinha(l, totalParagens, p);
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
    char* aux;
    char paragem[5];
    do{
        printf("Nome:");
        scanf(" %99[^\n]", linha->nome);
    }while(existeLinha(l, linha->nome));
    do{
        printf("Codigo Paragem: (FIM para sair)");
        scanf("%s", paragem);
        if(existeParagem(p, totalParagens, paragem)){
            aux = realloc(linha->paragens, (sizeof(char) * 5) * (linha->totalP + 1));
            if(aux == NULL){
                printf("ERRO na realocacao ao adicionar paragem a linha\n");
                return;
            }
            for(int i = 0; i < totalParagens; i++){
                if(strcmp(p[i].codigo, paragem) == 0){
                    p[i].linhas++;
                    break;
                }
            }
            linha->paragens = aux;
            for(int i = 0; i < 5; i++){
                linha->paragens[linha->totalP * 5 + i] = paragem[i];
            }
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
        return l;
    }
    novo->totalP = 0;
    novo->paragens = NULL;
    getInfoLinhas(l, novo, totalParagens, p);
    if(novo->totalP == 0){
        printf("Linha nao criada devido a nao ter paragens!\n");
        free(novo);
        return l;
    }
    novo->prox = l;
    if(l != NULL){
        l->ant = novo;
    }
    novo->ant = NULL;
    l = novo;
    return l;
}

plinha adicionarLinhasFicheiroTexto(plinha l, int totalParagens, pparagem p, char* nomeF){
    FILE* f;
    plinha lin;
    paragem par;
    char* aux = NULL, *parAux;
    int cont = 0, x;

    f = fopen(nomeF, "r");
    if(f == NULL){
        printf("Erro a aceder ao ficheiro\n");
        return l;
    }

    lin = malloc(sizeof(linha));
    if(lin == NULL){
        printf("ERRO a alocar memoria para a linha!\n");
        return l;
    }
    lin->totalP = 0;
    lin->paragens = NULL;
    lin->prox = NULL;

    fscanf(f," %99[^\n]", lin->nome);

    if(existeLinha(l, lin->nome)){
        printf("ERRO! Ja existe uma linha com esse nome!\n");
        return l;
    }

    while(fscanf(f, " %99[^#] #  %4[^\n]", par.nome, par.codigo) == 2){
        x = 0;
        for(int i = 0; i < 99 && par.nome[i] != '\0'; i++){
            x++;
        }
        par.nome[x - 1] = '\0';
        par.codigo[4] = '\0';
        parAux = getCodigo(par.nome, p, totalParagens);
        if(!existeParagem(p, totalParagens, par.codigo)){
            printf("%s", par.codigo);
            printf("A paragem %s nao existe, logo nao pode ser inserida nesta linha\n", par.codigo);
        }
        else if(parAux != NULL && strcmp(par.codigo, parAux) == 0){//existe e o nome e codigo pertencem à mesma paragem
            if(lin->paragens != NULL){
                for(int i = 0; i < lin->totalP * 5; i += 5){
                    for(int j = 0; j < 5; j++){
                        if(lin->paragens[i + j] == par.codigo[j])
                            cont ++;
                        else
                            cont = 0;
                    }
                    if(cont == 5)
                        break;
                }
            }

            if(cont == 5){
                printf("A paragem %s ja foi adicionada a linha\n", par.codigo);
            }
            else{
                aux = realloc(lin->paragens, (sizeof(char) * 5) * (lin->totalP + 1));
                if(aux == NULL){
                    printf("Erro na realocacao!\n");
                    return l;
                }
                for(int i = 0; i < totalParagens; i++){
                    if(strcmp(p[i].codigo, par.codigo) == 0){
                        p[i].linhas++;
                        break;
                    }
                }
                lin->paragens = aux;
                for(int i = 0; i < 5; i++){
                    lin->paragens[lin->totalP * 5 + i] = par.codigo[i];
                }
                lin->totalP++;
            }
        }
        else{
            printf("Codigo(%s) e Nome(%s) nao pertencem a mesma paragem!\n", par.codigo, par.nome);
        }
    }

    if(lin->totalP == 0){
        free(lin);
        return l;
    }

    lin->prox = l;

    if(l != NULL){
        l->ant = lin;
    }
    lin->ant = NULL;

    l = lin;
    return l;
}

void visualizarLinhas(plinha l){
    while(l != NULL){
        printf("Nome: %s\t", l->nome);
        for(int i = 0; i < l->totalP * 5; i++)
            putchar(l->paragens[i]);
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
    scanf(" %99[^\n]", nome);
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
                if(l == NULL){
                    opcao = 3;
                }
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
    if(aux == NULL)
        return l;
    char paragem[5];
    char* paragemAux;
    printf("Codigo da paragem a adicionar:");
    scanf("%s", paragem);
    if(existeParagem(p, totalParagens, paragem)){
        paragemAux = realloc(aux->paragens, aux->totalP + 1);
        if(paragemAux == NULL){
            printf("Erro a adicionar paragem\n");
            return l;
        }
        aux->paragens = paragemAux;
        for(int i = 0; i < 5; i++){
            aux->paragens[i + (aux->totalP * 5)] = paragem[i];
        }
        aux->totalP++;
        for(int i = 0; i < totalParagens; i++){
            if(strcmp(p[i].codigo, paragem) == 0){
                p[i].linhas++;
                break;
            }
        }
    }
    return l;
}

plinha removerParagem(char* nome, plinha l, int totalParagens, pparagem p){
    plinha aux = l, ant = NULL;
    while(aux != NULL && strcmp(aux->nome, nome) != 0){
        ant = aux;
        aux = aux->prox;
    }
    if(aux == NULL)
        return l;
    char paragem[5];
    char* paragemAux;
    char paragemARemover[5];
    int iguais;
    printf("Codigo da paragem a remover:");
    scanf("%s", paragem);
    for(int j = 0; j < aux->totalP; j++){
        iguais = 1;
        for(int z = 0; z < 5; z++){
            if(aux->paragens[(j * 5) + z] != paragem[z])
                iguais = 0;
        }
        if(iguais == 1){
            if(aux->totalP == 1){
                free(aux->paragens);
                if(ant == NULL){
                    l = aux->prox;
                    free(aux);
                }
                else{
                    ant->prox = aux->prox;
                    free(aux);
                }
                for(int i = 0; i < totalParagens; i++){
                    if(strcmp(p[i].codigo, paragem) == 0){
                        p[i].linhas--;
                        break;
                    }
                }
                return l;
            }

            strcpy(paragemARemover, paragem);
            for(int k = j; k < aux->totalP; k++){
                for(int z = 0; z < 5; z++){
                    aux->paragens[(k * 5) + z] = aux->paragens[(k * 5) + z + 5];
                }
            }
            paragemAux = realloc(aux->paragens, aux->totalP - 1);
            if(paragemAux == NULL){
                printf("Erro a remover paragem\n");
                for(int k = aux->totalP - 1; k > j; k--){
                    for(int z = 4; z >= 0; z--){
                        aux->paragens[(k * 5) + z] = aux->paragens[(k * 5) + z - 5];
                    }
                }
                for(int z = 0; z < 5; z++){
                    aux->paragens[(j * 5) + z] = paragemARemover[z];
                }
                return l;
            }
            aux->paragens = paragemAux;
            aux->totalP--;
            for(int i = 0; i < totalParagens; i++){
                if(strcmp(p[i].codigo, paragem) == 0){
                    p[i].linhas--;
                    break;
                }
            }
            break;
        }
    }
    return l;
}

void libertarLinhas(plinha l){
    plinha aux;
    while(l != NULL){
        aux = l;
        l = l->prox;
        free(aux->paragens);
        free(aux);
    }
}

void guardaLinhas(plinha l){
    FILE* f;
    f = fopen("linhas.dat", "wb");
    if(f == NULL){
        return;
    }
    printf("A guardar linhas em ficheiro\n");
    while(l != NULL){
        fwrite(l, sizeof(linha), 1, f);
        fwrite(l->paragens, sizeof(char) * 5, l->totalP, f);
        l = l->prox;
    }
    fclose(f);
}

plinha recuperaLinhas(){
    plinha novo, p = NULL;
    char* aux;
    linha lin;
    FILE* f;
    f = fopen("linhas.dat", "rb");
    if(f == NULL){
        printf("Ficheiro de linhas nao existe ou erro a aceder-lhe!\n");
        return NULL;
    }
    while(fread(&lin, sizeof(linha), 1, f) == 1){
        novo = malloc(sizeof(linha));
        aux = malloc(sizeof(char) * 5 * lin.totalP);
        if(novo == NULL){
            printf("Erro a alocar memoria\n");
            fclose(f);
            return p;
        }
        if(aux == NULL){
            printf("Erro a alocar memoria\n");
            free(novo);
            fclose(f);
            return p;
        }
        fread(aux, sizeof(char) * 5, lin.totalP, f); //TODO: verificar se todas as paragens existem
        lin.paragens = aux;
        *novo = lin;
        novo->prox = NULL; //porque não vai ficar no mesmo lugar de memória que ficou da última vez
        p = insereNoFinal(p, novo);
    }
    fclose(f);
    return p;
}

plinha insereNoFinal(plinha p, plinha novo){
    plinha aux = p;
    if(aux == NULL){
        p = novo;
        return p;
    }
    while(aux->prox != NULL)
        aux = aux->prox;
    aux->prox = novo;
    return p;
}

void calcularPercursoUmaLinha(plinha l, pparagem p, int totalParagens, char *codOrigem[5], char *codDestino[5]) {
    int posDes, posOr, iguaisOr, iguaisDes, aux;

    //possivel ir da origem ao destino na mesma linha

    posDes = posOr = -1;
    for(int i = 0; i < l->totalP; i++){
        iguaisOr = iguaisDes = 1;
        for(int j = 0; j < 4; j++){
            if(l->paragens[i * 5 + j] != (*codOrigem)[j])
                iguaisOr = 0;

            if(l->paragens[i * 5 + j] != (*codDestino)[j])
                iguaisDes = 0;
        }
        if(iguaisDes == 1)
            posDes = i;
        if(iguaisOr == 1)
            posOr = i;
    }
    printf("\nLinha: %s\nParagens:\n", l->nome);
    if(posDes == posOr){
        printf("Origem e Destino coincidem!\n");
        return;
    }
    if(posDes > posOr){
        for(int i = posOr; i <= posDes; i++){
            for(int j = 0; j < totalParagens; j++){
                int iguais = 1;
                for(int k = 0; k < 5; k++){
                    if(p[j].codigo[k] != l->paragens[i * 5 + k]){
                        iguais = 0;
                    }
                }
                if(iguais == 1)
                    printf("- %s %s\n", p[j].nome, p[j].codigo);
            }
        }
    }
    else{
        for(int i = posOr; i >= posDes; i--){
            for(int j = 0; j < totalParagens; j++){
                int iguais = 1;
                for(int k = 0; k < 5; k++){
                    if(p[j].codigo[k] != l->paragens[i * 5 + k]){
                        iguais = 0;
                    }
                }
                if(iguais == 1)
                    printf("%s %s\n", p[j].nome, p[j].codigo);
            }
        }
    }
}

int verificaOrigemDestino(plinha l, const char* codOrigem, const char* codDestino){
    int or, des, existeOr = 0, existeDes = 0;
    for(int i = 0; i < l->totalP; i++){
        or = des = 1;
        for(int j = 0; j < 5; j++){
            if(codOrigem[j] != l->paragens[i * 5 + j]){
                or = 0;
            }
            if(codDestino[j] != l->paragens[i * 5 + j]){
                des = 0;
            }
        }
        if(or)
            existeOr = 1;
        if(des)
            existeDes = 1;
        if(existeOr && existeDes)
            return 1;
    }
    return 0;
}

int verificaOrigem(plinha l, const char* codOrigem){
    int or;
    for(int i = 0; i < l->totalP; i++){
        or = 1;
        for(int j = 0; j < 5; j++)
            if(codOrigem[j] != l->paragens[i * 5 + j])
                or = 0;

        if(or)
            return 1;
    }
    return 0;
}

void getInfoPercurso(char** codOrigem, char** codDestino, pparagem p, int totalParagens){
    char origem[100], destino[100];

    printf("\nOrigem:");
    scanf(" %99[^\n]", origem);

    *codOrigem = getCodigo(origem, p, totalParagens);
    if(codOrigem == NULL){
        printf("Paragem nao existe!\n");
        return;
    }

    printf("\nDestino:");
    scanf(" %99[^\n]", destino);

    *codDestino = getCodigo(destino, p, totalParagens);
    if(codDestino == NULL){
        printf("Paragem nao existe!\n");
        return;
    }
}

void calcularPercursos(plinha l, pparagem p, int totalParagens){
    char *codOrigem[5], *codDestino[5];
    plinha aux = l;

    getInfoPercurso(codOrigem, codDestino, p, totalParagens);
    if(*codDestino == NULL || *codOrigem == NULL)
        return;

    while(aux != NULL){
        /*if(verificaOrigemDestino(aux, *codOrigem, *codDestino) == 1)
            calcularPercursoUmaLinha(aux, p, totalParagens, codOrigem, codDestino);*/
        if(verificaOrigem(aux, *codOrigem) == 1)
            calculaPercursoDuasLinhas(aux, p, totalParagens, codOrigem, codDestino);
        aux = aux->prox;
    }
}

void calculaPercursoDuasLinhas(plinha l, pparagem p, int totalParagens, char* codOrigem[5], char* codDestino[5]){
    plinha aux;
    int or, dest;
    char* codTemp[5];
    for(int i = 0; i < l->totalP; i++){
        or = dest = 1;
        for(int j = 0; j < 5; j++){
            if((*codOrigem)[j] != l->paragens[i * 5 + j]){
                or = 0;
            }
            if((*codDestino[j]) != l->paragens[i * 5 + j]){
                dest = 0;
            }
        }

        if(!dest && !or){
            for(int j = 0; j < 5; j++)
                *(codTemp + j) = &l->paragens[i * 5 + j];

            //percorrer linhas prox
            aux = l->prox;
            while(aux != NULL){
                if(verificaOrigemDestino(aux, *codTemp, *codDestino) == 1){
                    calcularPercursoUmaLinha(l, p, totalParagens, codOrigem, codTemp);
                    if(strcmp(*codTemp, *codDestino) != 0)
                        calcularPercursoUmaLinha(aux, p, totalParagens, codTemp, codDestino);
                }
                putchar('\n');
                aux = aux->prox;
            }

            //percorrer linhas ant
            aux = l->ant;
            while(aux != NULL){
                if(verificaOrigemDestino(aux, *codTemp, *codDestino) == 1){
                    if(strcmp(*codTemp, *codDestino) != 0){
                        calcularPercursoUmaLinha(l, p, totalParagens, codOrigem, codTemp);
                        calcularPercursoUmaLinha(aux, p, totalParagens, codTemp, codDestino);
                    }
                }
                putchar('\n');
                aux = aux->ant;
            }
        }
    }

}