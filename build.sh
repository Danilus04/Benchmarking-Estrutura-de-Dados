#!/bin/bash

# Script de compilação para o projeto de Benchmarking de Algoritmos de Ordenação
# Este script compila todos os arquivos .c e gera o executável

echo "======================================"
echo "Compilando projeto..."
echo "======================================"

cd "$(dirname "$0")/src" || exit 1

# Compilar com opções de otimização
gcc -O2 -Wall -Wextra -lm algoritmos.c main.c -o benchmarking

if [ $? -eq 0 ]; then
    echo ""
    echo "✓ Compilação bem-sucedida!"
    echo "Executável gerado: ./benchmarking"
    echo ""
    echo "Para executar, use:"
    echo "  ./run.sh"
else
    echo ""
    echo "✗ Erro na compilação!"
    exit 1
fi
