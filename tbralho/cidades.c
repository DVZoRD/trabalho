#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

Estrada* getEstrada(const char* nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    Estrada* estrada = (Estrada*) malloc(sizeof(Estrada));
    fscanf(file, "%d", &(estrada->T));
    fscanf(file, "%d", &(estrada->N));
    estrada->C = (Cidade*) malloc(estrada->N * sizeof(Cidade));

    for (int i = 0; i < estrada->N; i++) {
        fscanf(file, "%d %s", &(estrada->C[i].Posicao), estrada->C[i].Nome);
    }

    fclose(file);
    return estrada;
}

double calcularVizinhanca(const Cidade* cidade, const Estrada* estrada) {
    double vizinhanca = estrada->T;
    for (int i = 0; i < estrada->N; i++) {
        if (strcmp(cidade->Nome, estrada->C[i].Nome) != 0) {
            double dist = abs(cidade->Posicao - estrada->C[i].Posicao) / 2.0;
            if (dist < vizinhanca) {
                vizinhanca = dist;
            }
        }
    }
    return vizinhanca;
}

char* CidadeMenorVizinhanca(const char* nomeArquivo) {
    Estrada* estrada = getEstrada(nomeArquivo);
    if (!estrada) {
        return NULL;
    }

    double menorVizinhanca = estrada->T;
    char* cidadeMenorVizinhanca = (char*) malloc(256 * sizeof(char));

    for (int i = 0; i < estrada->N; i++) {
        double vizinhanca = calcularVizinhanca(&estrada->C[i], estrada);
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            strcpy(cidadeMenorVizinhanca, estrada->C[i].Nome);
        }
    }

    free(estrada->C);
    free(estrada);

    return cidadeMenorVizinhanca;
}

int main() {
    const char* nomeArquivo = "teste01.txt";
    Estrada* estrada = getEstrada(nomeArquivo);

    if (estrada) {
        printf("Comprimento da estrada: %d\n", estrada->T);
        printf("Numero de cidades: %d\n", estrada->N);
        for (int i = 0; i < estrada->N; i++) {
            printf("Cidade: %s, Posicao: %d\n", estrada->C[i].Nome, estrada->C[i].Posicao);
        }

        char* menorVizinhanca = CidadeMenorVizinhanca(nomeArquivo);
        if (menorVizinhanca) {
            printf("Cidade com a menor vizinhanca: %s\n", menorVizinhanca);
            free(menorVizinhanca);
        }

        free(estrada->C);
        free(estrada);
    } else {
        printf("Erro ao carregar a estrada.\n");
    }

    return 0;
}
