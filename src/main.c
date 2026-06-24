#include "algoritmos.h"

// Executar Problema 1: Bubble, Insertion, Selection com 3 cenários
void problema1() {
    printf("\n========== PROBLEMA 1: Bubble, Insertion, Selection ==========\n");
    printf("Tamanho: 30.000 elementos\n\n");
    
    int N = 30000;
    FILE *fp = fopen("../data/problema1_resultados.csv", "w");
    if (fp == NULL) {
        perror("Erro ao abrir arquivo de dados");
        return;
    }
    
    // Cabeçalho CSV
    fprintf(fp, "Algoritmo,Cenario,Tempo(s),Comparacoes,Trocas\n");
    
    int *original = (int *)malloc(N * sizeof(int));
    int *vetor = (int *)malloc(N * sizeof(int));
    
    if (original == NULL || vetor == NULL) {
        fprintf(stderr, "Erro de alocação\n");
        return;
    }
    
    srand(42);
    
    // Cenários
    const char *cenarios[] = {"Aleatorio", "Ordenado", "Inverso"};
    
    for (int c = 0; c < 3; c++) {
        printf("Cenário: %s\n", cenarios[c]);
        
        // Gerar dados original
        if (c == 0) gerarVetorAleatorio(original, N);
        else if (c == 1) gerarVetorOrdenado(original, N);
        else gerarVetorInverso(original, N);
        
        // Bubblesort
        memcpy(vetor, original, N * sizeof(int));
        Metricas m;
        struct timespec inicio, fim;
        
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        bubbleSort(vetor, N, &m);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        m.tempo_segundos = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        
        printf("  Bubble: %.6f s, Comparacoes: %llu, Trocas: %llu\n", 
               m.tempo_segundos, m.comparacoes, m.trocas);
        fprintf(fp, "Bubble,%s,%.6f,%llu,%llu\n", 
                cenarios[c], m.tempo_segundos, m.comparacoes, m.trocas);
        
        // Insertionsort
        memcpy(vetor, original, N * sizeof(int));
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        insertionSort(vetor, N, &m);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        m.tempo_segundos = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        
        printf("  Insertion: %.6f s, Comparacoes: %llu, Trocas: %llu\n", 
               m.tempo_segundos, m.comparacoes, m.trocas);
        fprintf(fp, "Insertion,%s,%.6f,%llu,%llu\n", 
                cenarios[c], m.tempo_segundos, m.comparacoes, m.trocas);
        
        // Selectionsort
        memcpy(vetor, original, N * sizeof(int));
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        selectionSort(vetor, N, &m);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        m.tempo_segundos = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        
        printf("  Selection: %.6f s, Comparacoes: %llu, Trocas: %llu\n\n", 
               m.tempo_segundos, m.comparacoes, m.trocas);
        fprintf(fp, "Selection,%s,%.6f,%llu,%llu\n", 
                cenarios[c], m.tempo_segundos, m.comparacoes, m.trocas);
    }
    
    free(original);
    free(vetor);
    fclose(fp);
    printf("Resultados salvos em: ../data/problema1_resultados.csv\n");
}

// Executar Problema 2: Quicksort vs Heapsort com 10 execuções
void problema2() {
    printf("\n========== PROBLEMA 2: Quicksort vs Heapsort ==========\n");
    printf("Tamanho: 5.000 elementos (vetor já ordenado)\n");
    printf("Executando 10 vezes cada para calcular média e desvio padrão\n\n");
    
    int N = 5000;
    FILE *fp = fopen("../data/problema2_resultados.csv", "w");
    if (fp == NULL) {
        perror("Erro ao abrir arquivo de dados");
        return;
    }
    
    fprintf(fp, "Execucao,QuickSort_Tempo(s),HeapSort_Tempo(s)\n");
    
    int *original = (int *)malloc(N * sizeof(int));
    int *vetor = (int *)malloc(N * sizeof(int));
    
    // Gerar vetor ordenado
    gerarVetorOrdenado(original, N);
    
    double tempos_quick[10], tempos_heap[10];
    
    for (int exec = 0; exec < 10; exec++) {
        printf("Execução %d/10...\n", exec + 1);
        
        // Quicksort
        memcpy(vetor, original, N * sizeof(int));
        Metricas m;
        struct timespec inicio, fim;
        
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        quickSort(vetor, N, &m);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_quick[exec] = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        
        // Heapsort
        memcpy(vetor, original, N * sizeof(int));
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        heapSort(vetor, N, &m);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempos_heap[exec] = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        
        fprintf(fp, "%d,%.6f,%.6f\n", exec + 1, tempos_quick[exec], tempos_heap[exec]);
    }
    
    // Calcular média, desvio padrão, mínimo e máximo
    double media_quick = 0, media_heap = 0;
    for (int i = 0; i < 10; i++) {
        media_quick += tempos_quick[i];
        media_heap += tempos_heap[i];
    }
    media_quick /= 10;
    media_heap /= 10;
    
    double std_quick = 0, std_heap = 0;
    for (int i = 0; i < 10; i++) {
        std_quick += (tempos_quick[i] - media_quick) * (tempos_quick[i] - media_quick);
        std_heap += (tempos_heap[i] - media_heap) * (tempos_heap[i] - media_heap);
    }
    std_quick = sqrt(std_quick / 10);
    std_heap = sqrt(std_heap / 10);

    double min_quick = tempos_quick[0], max_quick = tempos_quick[0];
    double min_heap = tempos_heap[0], max_heap = tempos_heap[0];
    for (int i = 1; i < 10; i++) {
        if (tempos_quick[i] < min_quick) min_quick = tempos_quick[i];
        if (tempos_quick[i] > max_quick) max_quick = tempos_quick[i];
        if (tempos_heap[i] < min_heap) min_heap = tempos_heap[i];
        if (tempos_heap[i] > max_heap) max_heap = tempos_heap[i];
    }

    printf("\n--- RESUMO PROBLEMA 2 ---\n");
    printf("Quicksort: Média = %.6f s, Desvio = %.6f s, Min = %.6f s, Max = %.6f s\n", 
           media_quick, std_quick, min_quick, max_quick);
    printf("Heapsort:  Média = %.6f s, Desvio = %.6f s, Min = %.6f s, Max = %.6f s\n", 
           media_heap, std_heap, min_heap, max_heap);

    // Gravar resumo em arquivo
    FILE *fres = fopen("../data/RESUMO_RESULTADOS.txt", "w");
    if (fres != NULL) {
        fprintf(fres, "PROBLEMA 2 - Quicksort vs Heapsort (vetor ordenado)\n\n");
        fprintf(fres, "| Métrica | Quicksort | Heapsort |\n");
        fprintf(fres, "|---------|-----------|----------|\n");
        fprintf(fres, "| Média (s) | %.6f | %.6f |\n", media_quick, media_heap);
        fprintf(fres, "| Desvio Padrão (s) | %.6f | %.6f |\n", std_quick, std_heap);
        fprintf(fres, "| Mínimo (s) | %.6f | %.6f |\n", min_quick, min_heap);
        fprintf(fres, "| Máximo (s) | %.6f | %.6f |\n", max_quick, max_heap);
        fclose(fres);
        printf("Resumo salvo em: ../data/RESUMO_RESULTADOS.txt\n");
    } else {
        perror("Erro ao abrir arquivo de resumo");
    }
    
    free(original);
    free(vetor);
    fclose(fp);
    printf("Resultados salvos em: ../data/problema2_resultados.csv\n");
}

// Executar Problema 3: Insertion vs Shell com vetor quase-ordenado
void problema3() {
    printf("\n========== PROBLEMA 3: Insertion vs Shell (Quase-Ordenado) ==========\n");
    printf("Tamanho: 50.000 elementos (0.5%% perturbado)\n\n");
    
    int N = 50000;
    FILE *fp = fopen("../data/problema3_resultados.csv", "w");
    if (fp == NULL) {
        perror("Erro ao abrir arquivo de dados");
        return;
    }
    
    fprintf(fp, "Algoritmo,Tempo(s),Comparacoes,Trocas\n");
    
    int *original = (int *)malloc(N * sizeof(int));
    int *vetor = (int *)malloc(N * sizeof(int));
    
    // Gerar vetor quase-ordenado
    srand(42);
    gerarVetorQuaseOrdenado(original, N);
    
    Metricas m;
    struct timespec inicio, fim;
    
    // Insertionsort
    printf("Executando Insertionsort...\n");
    memcpy(vetor, original, N * sizeof(int));
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    insertionSort(vetor, N, &m);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo_insertion = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    
    printf("Insertion: %.6f s, Comparacoes: %llu, Trocas: %llu\n", 
           tempo_insertion, m.comparacoes, m.trocas);
    fprintf(fp, "Insertion,%.6f,%llu,%llu\n", tempo_insertion, m.comparacoes, m.trocas);
    
    // Shellsort
    printf("Executando Shellsort...\n");
    memcpy(vetor, original, N * sizeof(int));
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    shellSort(vetor, N, &m);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo_shell = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    
    printf("Shell: %.6f s, Comparacoes: %llu, Trocas: %llu\n", 
           tempo_shell, m.comparacoes, m.trocas);
    fprintf(fp, "Shell,%.6f,%llu,%llu\n", tempo_shell, m.comparacoes, m.trocas);
    
    printf("\nResultados salvos em: ../data/problema3_resultados.csv\n");
    
    free(original);
    free(vetor);
    fclose(fp);
}

int main() {
    printf("=========================================\n");
    printf("BENCHMARKING DE ALGORITMOS DE ORDENAÇÃO\n");
    printf("=========================================\n");
    
    // Executar os três problemas
    problema1();
    problema2();
    problema3();
    
    printf("\n=========================================\n");
    printf("EXECUÇÃO CONCLUÍDA!\n");
    printf("Verifique os arquivos CSV em ../data/\n");
    printf("=========================================\n");
    
    return 0;
}
