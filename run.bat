@echo off
REM Script de execução para Windows CMD/PowerShell
REM Alternativa para usuários que não têm bash

echo.
echo ======================================
echo Executando programa...
echo ======================================
echo.

cd /d "%~dp0src"

if not exist "benchmarking.exe" (
    echo Erro: benchmarking.exe nao encontrado
    echo Execute primeiro: build.bat
    pause
    exit /b 1
)

benchmarking.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ======================================
    echo Execucao concluida com sucesso!
    echo ======================================
    echo.
    echo Arquivos de dados gerados em: data\
    echo   - problema1_resultados.csv
    echo   - problema2_resultados.csv
    echo   - problema3_resultados.csv
    echo.
    echo Proximos passos:
    echo   1. Executar: python gerar_graficos.py
    echo   2. Preencher o TEMPLATE_RELATORIO.md
    echo   3. Converter para PDF
    echo.
    pause
) else (
    echo.
    echo ERRO durante a execucao!
    echo.
    pause
    exit /b 1
)
