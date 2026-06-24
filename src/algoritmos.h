#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// Estrutura para contabilizar as métricas do algoritmo
typedef struct {
    unsigned long long comparacoes;
    unsigned long long trocas;
    double tempo_segundos;
} Metricas;

// Funções de geração de dados
void gerarVetorAleatorio(int *v, int n);
void gerarVetorOrdenado(int *v, int n);
void gerarVetorInverso(int *v, int n);
void gerarVetorQuaseOrdenado(int *v, int n);
int* copiarVetor(int *v, int n);

// Algoritmos de ordenação - Problema 1
void bubbleSort(int *vetor, int n, Metricas *m);
void insertionSort(int *vetor, int n, Metricas *m);
void selectionSort(int *vetor, int n, Metricas *m);

// Algoritmos de ordenação - Problema 2
void quickSort(int *vetor, int n, Metricas *m);
void heapSort(int *vetor, int n, Metricas *m);

// Algoritmo de ordenação - Problema 3
void shellSort(int *vetor, int n, Metricas *m);

// Funções auxiliares
void exibirVetor(int *v, int n);
int estaOrdenado(int *v, int n);

#endif
