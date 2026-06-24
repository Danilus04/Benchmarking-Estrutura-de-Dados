#!/usr/bin/env python3
"""
Script para gerar gráficos e análises dos resultados de benchmarking
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os
from pathlib import Path

# Definir diretório de dados
data_dir = Path(__file__).parent / "data"
data_dir.mkdir(exist_ok=True)

# Configurar matplotlib para português
plt.rcParams['font.family'] = 'DejaVu Sans'

def gerar_graficos_problema1():
    """Gerar gráficos do Problema 1"""
    print("Gerando gráficos do Problema 1...")
    
    df = pd.read_csv(data_dir / "problema1_resultados.csv")
    
    # Gráfico 1: Tempo por algoritmo e cenário
    fig, axes = plt.subplots(1, 3, figsize=(15, 5))
    
    for idx, cenario in enumerate(['Aleatorio', 'Ordenado', 'Inverso']):
        dados = df[df['Cenario'] == cenario]
        axes[idx].bar(dados['Algoritmo'], dados['Tempo(s)'])
        axes[idx].set_title(f'Tempo - Cenário: {cenario}')
        axes[idx].set_ylabel('Tempo (s)')
        axes[idx].tick_params(axis='x', rotation=45)
        axes[idx].grid(axis='y', alpha=0.3)
    
    plt.tight_layout()
    plt.savefig(data_dir / 'problema1_tempo.png', dpi=300, bbox_inches='tight')
    print("  ✓ Salvo: problema1_tempo.png")
    plt.close()
    
    # Gráfico 2: Comparações
    fig, axes = plt.subplots(1, 3, figsize=(15, 5))
    
    for idx, cenario in enumerate(['Aleatorio', 'Ordenado', 'Inverso']):
        dados = df[df['Cenario'] == cenario]
        axes[idx].bar(dados['Algoritmo'], dados['Comparacoes'])
        axes[idx].set_title(f'Comparações - Cenário: {cenario}')
        axes[idx].set_ylabel('Número de Comparações')
        axes[idx].tick_params(axis='x', rotation=45)
        axes[idx].ticklabel_format(style='scientific', axis='y', scilimits=(0,0))
        axes[idx].grid(axis='y', alpha=0.3)
    
    plt.tight_layout()
    plt.savefig(data_dir / 'problema1_comparacoes.png', dpi=300, bbox_inches='tight')
    print("  ✓ Salvo: problema1_comparacoes.png")
    plt.close()
    
    # Gráfico 3: Trocas
    fig, axes = plt.subplots(1, 3, figsize=(15, 5))
    
    for idx, cenario in enumerate(['Aleatorio', 'Ordenado', 'Inverso']):
        dados = df[df['Cenario'] == cenario]
        axes[idx].bar(dados['Algoritmo'], dados['Trocas'])
        axes[idx].set_title(f'Trocas - Cenário: {cenario}')
        axes[idx].set_ylabel('Número de Trocas')
        axes[idx].tick_params(axis='x', rotation=45)
        axes[idx].ticklabel_format(style='scientific', axis='y', scilimits=(0,0))
        axes[idx].grid(axis='y', alpha=0.3)
    
    plt.tight_layout()
    plt.savefig(data_dir / 'problema1_trocas.png', dpi=300, bbox_inches='tight')
    print("  ✓ Salvo: problema1_trocas.png")
    plt.close()

def gerar_graficos_problema2():
    """Gerar gráficos do Problema 2"""
    print("Gerando gráficos do Problema 2...")
    
    df = pd.read_csv(data_dir / "problema2_resultados.csv")
    
    # Calcular estatísticas
    media_qs = df['QuickSort_Tempo(s)'].mean()
    std_qs = df['QuickSort_Tempo(s)'].std()
    media_hs = df['HeapSort_Tempo(s)'].mean()
    std_hs = df['HeapSort_Tempo(s)'].std()
    
    # Gráfico: Comparação com barras de erro
    fig, ax = plt.subplots(figsize=(10, 6))
    
    algoritmos = ['Quicksort', 'Heapsort']
    medias = [media_qs, media_hs]
    desvios = [std_qs, std_hs]
    
    x = np.arange(len(algoritmos))
    width = 0.5
    
    bars = ax.bar(x, medias, width, yerr=desvios, capsize=10, alpha=0.8, 
                  color=['#FF6B6B', '#4ECDC4'])
    
    ax.set_ylabel('Tempo (segundos)', fontsize=12)
    ax.set_title('Problema 2: Quicksort vs Heapsort\n(Vetor com 5000 elementos já ordenado)', 
                 fontsize=14, fontweight='bold')
    ax.set_xticks(x)
    ax.set_xticklabels(algoritmos, fontsize=12)
    ax.grid(axis='y', alpha=0.3)
    
    # Adicionar valores nas barras
    for i, (bar, media) in enumerate(zip(bars, medias)):
        height = bar.get_height()
        ax.text(bar.get_x() + bar.get_width()/2., height,
                f'{media:.6f}s\n±{desvios[i]:.6f}s',
                ha='center', va='bottom', fontsize=10, fontweight='bold')
    
    plt.tight_layout()
    plt.savefig(data_dir / 'problema2_comparacao.png', dpi=300, bbox_inches='tight')
    print("  ✓ Salvo: problema2_comparacao.png")
    plt.close()
    
    # Gráfico: Evolução dos tempos
    fig, ax = plt.subplots(figsize=(12, 6))
    
    ax.plot(df['Execucao'], df['QuickSort_Tempo(s)'], 'o-', label='Quicksort', linewidth=2)
    ax.plot(df['Execucao'], df['HeapSort_Tempo(s)'], 's-', label='Heapsort', linewidth=2)
    
    ax.axhline(y=media_qs, color='#FF6B6B', linestyle='--', alpha=0.5, label=f'Média QS: {media_qs:.6f}s')
    ax.axhline(y=media_hs, color='#4ECDC4', linestyle='--', alpha=0.5, label=f'Média HS: {media_hs:.6f}s')
    
    ax.set_xlabel('Execução', fontsize=12)
    ax.set_ylabel('Tempo (segundos)', fontsize=12)
    ax.set_title('Problema 2: Variação de Tempo entre Execuções', fontsize=14, fontweight='bold')
    ax.legend(fontsize=10)
    ax.grid(alpha=0.3)
    
    plt.tight_layout()
    plt.savefig(data_dir / 'problema2_evolucao.png', dpi=300, bbox_inches='tight')
    print("  ✓ Salvo: problema2_evolucao.png")
    plt.close()

def gerar_graficos_problema3():
    """Gerar gráficos do Problema 3"""
    print("Gerando gráficos do Problema 3...")
    
    df = pd.read_csv(data_dir / "problema3_resultados.csv")
    
    # Gráfico: Comparação de tempo
    fig, ax = plt.subplots(figsize=(10, 6))
    
    algoritmos = df['Algoritmo'].tolist()
    tempos = df['Tempo(s)'].tolist()
    cores = ['#95E1D3', '#F38181']
    
    bars = ax.bar(algoritmos, tempos, color=cores, alpha=0.8, edgecolor='black', linewidth=2)
    
    ax.set_ylabel('Tempo (segundos)', fontsize=12)
    ax.set_title('Problema 3: Insertionsort vs Shellsort\n(Vetor quase-ordenado com 50000 elementos)', 
                 fontsize=14, fontweight='bold')
    ax.grid(axis='y', alpha=0.3)
    
    # Adicionar valores nas barras
    for bar, tempo in zip(bars, tempos):
        height = bar.get_height()
        ax.text(bar.get_x() + bar.get_width()/2., height,
                f'{tempo:.6f}s',
                ha='center', va='bottom', fontsize=11, fontweight='bold')
    
    # Adicionar razão de speedup
    ratio = df[df['Algoritmo'] == 'Insertion']['Tempo(s)'].values[0] / \
            df[df['Algoritmo'] == 'Shell']['Tempo(s)'].values[0]
    ax.text(0.5, 0.95, f'Shellsort é {ratio:.2f}x mais lento que Insertionsort',
            transform=ax.transAxes, ha='center', va='top',
            bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.5),
            fontsize=11)
    
    plt.tight_layout()
    plt.savefig(data_dir / 'problema3_comparacao.png', dpi=300, bbox_inches='tight')
    print("  ✓ Salvo: problema3_comparacao.png")
    plt.close()
    
    # Gráfico: Comparações
    fig, ax = plt.subplots(figsize=(10, 6))
    
    bars = ax.bar(algoritmos, df['Comparacoes'], color=cores, alpha=0.8, edgecolor='black', linewidth=2)
    
    ax.set_ylabel('Número de Comparações', fontsize=12)
    ax.set_title('Problema 3: Comparações Realizadas', fontsize=14, fontweight='bold')
    ax.ticklabel_format(style='scientific', axis='y', scilimits=(0,0))
    ax.grid(axis='y', alpha=0.3)
    
    # Adicionar valores nas barras
    for bar, comp in zip(bars, df['Comparacoes']):
        height = bar.get_height()
        ax.text(bar.get_x() + bar.get_width()/2., height,
                f'{comp:.0f}',
                ha='center', va='bottom', fontsize=10)
    
    plt.tight_layout()
    plt.savefig(data_dir / 'problema3_comparacoes.png', dpi=300, bbox_inches='tight')
    print("  ✓ Salvo: problema3_comparacoes.png")
    plt.close()

def criar_resumo_texto():
    """Criar arquivo de resumo em texto"""
    print("Gerando resumo em texto...")
    
    with open(data_dir / 'RESUMO_RESULTADOS.txt', 'w', encoding='utf-8') as f:
        f.write("=" * 80 + "\n")
        f.write("RESUMO DOS RESULTADOS - BENCHMARKING DE ALGORITMOS DE ORDENAÇÃO\n")
        f.write("=" * 80 + "\n\n")
        
        # Problema 1
        f.write("PROBLEMA 1: Custo de Operações Teóricas vs. Tempo Real\n")
        f.write("-" * 80 + "\n")
        df1 = pd.read_csv(data_dir / "problema1_resultados.csv")
        f.write(df1.to_string(index=False))
        f.write("\n\n")
        
        # Problema 2
        f.write("PROBLEMA 2: O Desafio do Quicksort Clássico\n")
        f.write("-" * 80 + "\n")
        df2 = pd.read_csv(data_dir / "problema2_resultados.csv")
        f.write(df2.to_string(index=False))
        f.write("\n\n")
        
        # Estatísticas Problema 2
        f.write("Estatísticas Problema 2:\n")
        f.write(f"  Quicksort: Média = {df2['QuickSort_Tempo(s)'].mean():.6f}s, ")
        f.write(f"Desvio = {df2['QuickSort_Tempo(s)'].std():.6f}s\n")
        f.write(f"  Heapsort:  Média = {df2['HeapSort_Tempo(s)'].mean():.6f}s, ")
        f.write(f"Desvio = {df2['HeapSort_Tempo(s)'].std():.6f}s\n\n")
        
        # Problema 3
        f.write("PROBLEMA 3: Dados Quase-Ordenados e Shellsort\n")
        f.write("-" * 80 + "\n")
        df3 = pd.read_csv(data_dir / "problema3_resultados.csv")
        f.write(df3.to_string(index=False))
        f.write("\n\n")
    
    print("  ✓ Salvo: RESUMO_RESULTADOS.txt")

if __name__ == "__main__":
    print("=" * 80)
    print("Gerando gráficos e análises...")
    print("=" * 80)
    print()
    
    try:
        gerar_graficos_problema1()
        gerar_graficos_problema2()
        gerar_graficos_problema3()
        criar_resumo_texto()
        
        print()
        print("=" * 80)
        print("✓ Todos os gráficos foram gerados com sucesso!")
        print("=" * 80)
        print("\nArquivos gerados em 'data/':")
        print("  - problema1_tempo.png")
        print("  - problema1_comparacoes.png")
        print("  - problema1_trocas.png")
        print("  - problema2_comparacao.png")
        print("  - problema2_evolucao.png")
        print("  - problema3_comparacao.png")
        print("  - problema3_comparacoes.png")
        print("  - RESUMO_RESULTADOS.txt")
        
    except Exception as e:
        print(f"\n✗ Erro ao gerar gráficos: {e}")
        import traceback
        traceback.print_exc()
