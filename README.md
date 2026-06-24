# Benchmarking e Análise Empírica de Algoritmos de Ordenação

## Descrição

Este projeto implementa e analisa empiricamente seis algoritmos clássicos de ordenação em C:
- **Bubblesort** (melhorado)
- **Insertionsort**
- **Selectionsort**
- **Shellsort**
- **Quicksort**
- **Heapsort**

Cada algoritmo é instrumentado para medir:
- Número de comparações
- Número de trocas/deslocamentos
- Tempo de execução

## Estrutura do Projeto

```
.
├── src/
│   ├── algoritmos.h         # Header com declarações
│   ├── algoritmos.c         # Implementação dos 6 algoritmos
│   ├── main.c               # Programa principal com os 3 problemas
│   └── benchmarking         # Executável (gerado após compilação)
├── data/
│   ├── problema1_resultados.csv    # Resultados do Problema 1
│   ├── problema2_resultados.csv    # Resultados do Problema 2
│   └── problema3_resultados.csv    # Resultados do Problema 3
├── build.sh                 # Script de compilação
├── run.sh                   # Script de execução
└── README.md                # Este arquivo

```

## Compilação

### No Linux/macOS com WSL ou Git Bash (Windows)

```bash
# Dar permissão de execução aos scripts (primeira vez apenas)
chmod +x build.sh run.sh

# Compilar
./build.sh
```

Ou compile manualmente:

```bash
cd src/
gcc -O2 -Wall -Wextra -lm algoritmos.c main.c -o benchmarking
```

## Execução

### No Linux/macOS com WSL ou Git Bash (Windows)

```bash
# Executar (vai compilar e rodar automaticamente)
./run.sh
```

Ou execute manualmente:

```bash
cd src/
./benchmarking
```

## Problemas Resolvidos

### Problema 1: Custo de Operações Teóricas vs. Tempo Real
- **Algoritmos:** Bubblesort, Insertionsort, Selectionsort
- **Tamanho:** 30.000 elementos
- **Cenários:** Aleatório, Ordenado (melhor caso), Inverso (pior caso)
- **Saída:** Tabela com tempo, comparações e trocas para cada combinação

### Problema 2: O Desafio do Quicksort Clássico
- **Algoritmos:** Quicksort (pivô no final), Heapsort
- **Tamanho:** 5.000 elementos
- **Cenário:** Vetor já ordenado em crescente
- **Método:** 10 execuções para calcular média e desvio padrão
- **Saída:** Tabela com tempos, gráfico de comparação

### Problema 3: Dados Quase-Ordenados e Shellsort
- **Algoritmos:** Insertionsort, Shellsort
- **Tamanho:** 50.000 elementos
- **Cenário:** Vetor quase-ordenado (0,5% elementos perturbados)
- **Saída:** Comparação de desempenho

## Resultados dos Testes

Os resultados são salvos em arquivos CSV em `data/`:

### Problema 1: `problema1_resultados.csv`
```
Algoritmo,Cenario,Tempo(s),Comparacoes,Trocas
Bubble,Aleatorio,X.XXXXXX,XXXXXXXXX,XXXXXXXXX
Insertion,Aleatorio,X.XXXXXX,XXXXXXXXX,XXXXXXXXX
...
```

### Problema 2: `problema2_resultados.csv`
```
Execucao,QuickSort_Tempo(s),HeapSort_Tempo(s)
1,X.XXXXXX,X.XXXXXX
2,X.XXXXXX,X.XXXXXX
...
```

### Problema 3: `problema3_resultados.csv`
```
Algoritmo,Tempo(s),Comparacoes,Trocas
Insertion,X.XXXXXX,XXXXXXXXX,XXXXXXXXX
Shell,X.XXXXXX,XXXXXXXXX,XXXXXXXXX
```

## Observações Importantes

1. **Stack Overflow no Quicksort:** Quando executado em um vetor já ordenado, o Quicksort clássico com pivô no final pode causar Stack Overflow. O script `run.sh` aumenta automaticamente o limite com `ulimit -s unlimited`.

2. **Instrumentação Correta:**
   - Cada comparação lógica é contada em `m->comparacoes`
   - Cada escrita/troca é contada em `m->trocas`
   - O tempo é medido com `clock_gettime(CLOCK_MONOTONIC, ...)`

3. **Semente Aleatória:** Usa `srand(42)` para garantir que todos os testes usem os mesmos dados aleatórios.

## Requisitos do Sistema

- Compilador GCC (ou compatível)
- Linux, macOS ou Windows 11 com WSL 2 / Git Bash
- ~100 MB de espaço em disco
- A execução completa leva ~1-5 minutos dependendo do hardware

## Autor(es)

[Seu nome e do colega de dupla aqui]

## Data

[Data da entrega]

---

**Nota:** Este projeto foi desenvolvido como trabalho prático da disciplina de Estrutura de Dados.
