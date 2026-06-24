#include "algoritmos.h"

// ========== GERAÇÃO DE DADOS ==========

void gerarVetorAleatorio(int *v, int n) {
    for (int i = 0; i < n; i++)
        v[i] = rand() % 100000;
}

void gerarVetorOrdenado(int *v, int n) {
    for (int i = 0; i < n; i++)
        v[i] = i;
}

void gerarVetorInverso(int *v, int n) {
    for (int i = 0; i < n; i++)
        v[i] = n - i;
}

void gerarVetorQuaseOrdenado(int *v, int n) {
    // Primeiro, criar vetor ordenado
    for (int i = 0; i < n; i++)
        v[i] = i;
    
    // Trocar 0.5% dos elementos com seus vizinhos
    int num_trocas = (int)(n * 0.005);
    for (int i = 0; i < num_trocas; i++) {
        int idx = rand() % (n - 1);
        int temp = v[idx];
        v[idx] = v[idx + 1];
        v[idx + 1] = temp;
    }
}

int* copiarVetor(int *v, int n) {
    int *copia = (int *)malloc(n * sizeof(int));
    if (copia == NULL) return NULL;
    memcpy(copia, v, n * sizeof(int));
    return copia;
}

// ========== PROBLEMA 1: BUBBLE SORT, INSERTION SORT, SELECTION SORT ==========

// Bubblesort melhorado: para quando não houver mais trocas
void bubbleSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    
    for (int i = 0; i < n - 1; i++) {
        int ultima_troca = -1;
        for (int j = 0; j < n - 1 - i; j++) {
            m->comparacoes++;
            if (vetor[j] > vetor[j + 1]) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                m->trocas++;
                ultima_troca = j;
            }
        }
        if (ultima_troca == -1) break; // Nenhuma troca, vetor está ordenado
    }
}

// Insertionsort com instrumentação correta
void insertionSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    
    for (int i = 1; i < n; i++) {
        int chave = vetor[i];
        int j = i - 1;
        
        while (j >= 0) {
            m->comparacoes++;
            if (vetor[j] > chave) {
                vetor[j + 1] = vetor[j];
                m->trocas++;
                j--;
            } else {
                break;
            }
        }
        vetor[j + 1] = chave;
    }
}

// Selectionsort com instrumentação
void selectionSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            m->comparacoes++;
            if (vetor[j] < vetor[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = vetor[i];
            vetor[i] = vetor[min_idx];
            vetor[min_idx] = temp;
            m->trocas++;
        }
    }
}

// ========== PROBLEMA 2: QUICKSORT E HEAPSORT ==========

// Quicksort com pivô no último elemento
void quickSortHelper(int *vetor, int inicio, int fim, Metricas *m) {
    if (inicio < fim) {
        int pi = inicio;
        int pivot = vetor[fim];
        
        for (int i = inicio; i < fim; i++) {
            m->comparacoes++;
            if (vetor[i] < pivot) {
                int temp = vetor[i];
                vetor[i] = vetor[pi];
                vetor[pi] = temp;
                m->trocas++;
                pi++;
            }
        }
        
        int temp = vetor[pi];
        vetor[pi] = vetor[fim];
        vetor[fim] = temp;
        m->trocas++;
        
        quickSortHelper(vetor, inicio, pi - 1, m);
        quickSortHelper(vetor, pi + 1, fim, m);
    }
}

void quickSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    if (n > 0)
        quickSortHelper(vetor, 0, n - 1, m);
}

// Heapsort com instrumentação
void heapifyDown(int *vetor, int n, int i, Metricas *m) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;
    
    if (esquerda < n) {
        m->comparacoes++;
        if (vetor[esquerda] > vetor[maior])
            maior = esquerda;
    }
    
    if (direita < n) {
        m->comparacoes++;
        if (vetor[direita] > vetor[maior])
            maior = direita;
    }
    
    if (maior != i) {
        int temp = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = temp;
        m->trocas++;
        heapifyDown(vetor, n, maior, m);
    }
}

void heapSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    
    // Construir max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyDown(vetor, n, i, m);
    
    // Extrair elementos do heap
    for (int i = n - 1; i > 0; i--) {
        int temp = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = temp;
        m->trocas++;
        
        heapifyDown(vetor, i, 0, m);
    }
}

// ========== PROBLEMA 3: SHELL SORT ==========

void shellSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    
    // Usar sequência de gap: N/2, N/4, ..., 1
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int chave = vetor[i];
            int j = i;
            
            while (j >= gap) {
                m->comparacoes++;
                if (vetor[j - gap] > chave) {
                    vetor[j] = vetor[j - gap];
                    m->trocas++;
                    j -= gap;
                } else {
                    break;
                }
            }
            vetor[j] = chave;
        }
    }
}

// ========== FUNÇÕES AUXILIARES ==========

void exibirVetor(int *v, int n) {
    for (int i = 0; i < n && i < 10; i++)
        printf("%d ", v[i]);
    if (n > 10) printf("...");
    printf("\n");
}

int estaOrdenado(int *v, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (v[i] > v[i + 1]) return 0;
    }
    return 1;
}
