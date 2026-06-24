#!/bin/bash

# Script de execução para o projeto de Benchmarking de Algoritmos de Ordenação
# Este script executa o programa e aumenta o limite de pilha para evitar Stack Overflow no Quicksort

echo "======================================"
echo "Aumentando limite de pilha do sistema..."
echo "======================================"

# Aumentar limite de pilha (necessário para evitar Stack Overflow no Quicksort com dados já ordenados)
ulimit -s unlimited

if [ $? -eq 0 ]; then
    echo "✓ Limite de pilha ajustado com sucesso"
else
    echo "⚠ Não foi possível aumentar o limite de pilha"
    echo "  Isto pode causar problemas com o Quicksort em dados ordenados"
fi

echo ""
echo "======================================"
echo "Executando programa..."
echo "======================================"
echo ""

# Executar o programa
cd "$(dirname "$0")/src" || exit 1

if [ -f "./benchmarking" ]; then
    ./benchmarking
    
    if [ $? -eq 0 ]; then
        echo ""
        echo "======================================"
        echo "✓ Execução concluída com sucesso!"
        echo "======================================"
        echo ""
        echo "Arquivos de dados gerados:"
        echo "  - ../data/problema1_resultados.csv"
        echo "  - ../data/problema2_resultados.csv"
        echo "  - ../data/problema3_resultados.csv"
    else
        echo ""
        echo "✗ Erro durante a execução!"
        exit 1
    fi
else
    echo ""
    echo "✗ Executável não encontrado!"
    echo "  Execute primeiro: ./build.sh"
    exit 1
fi
