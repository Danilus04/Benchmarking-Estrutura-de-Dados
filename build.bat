@echo off
REM Script de compilação para Windows CMD/PowerShell
REM Alternativa para usuários que não têm bash

echo.
echo ======================================
echo Compilando projeto...
echo ======================================
echo.

cd /d "%~dp0src"

if not exist "%.c" (
    echo Erro: arquivos .c nao encontrados
    pause
    exit /b 1
)

REM Compilar com GCC
gcc -O2 -Wall -Wextra -lm algoritmos.c main.c -o benchmarking.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Compilacao bem-sucedida!
    echo Executavel gerado: benchmarking.exe
    echo.
    echo Para executar, use: benchmarking.exe
    echo.
    pause
) else (
    echo.
    echo ERRO na compilacao!
    echo.
    pause
    exit /b 1
)
