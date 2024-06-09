#ifndef CIDADES_H
#define CIDADES_H

typedef struct {
    char Nome[256];    // Nome da cidade
    int Posicao;       // Posição da cidade
} Cidade;

typedef struct {
    int T;    // Comprimento total da estrada
    int N;    // Número de cidades
    Cidade* C; // Vetor de cidades
} Estrada;

Estrada* getEstrada(const char* nomeArquivo); // Inicializa cidades no TAD indicado acima.
double calcularVizinhanca(const Cidade* cidade, const Estrada* estrada); // Retorna a nova vizinhanca.
char* CidadeMenorVizinhanca(const char* nomeArquivo); // Retorna a cidade que tem menor vizinhanca.

#endif
