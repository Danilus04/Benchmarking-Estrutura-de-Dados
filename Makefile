CC = gcc
CFLAGS = -O2 -Wall -Wextra
LDFLAGS = -lm

SRC = src\algoritmos.c src\main.c
TARGET = src\benchmarking.exe

DATA_DIR = data
OUTPUT_FILE = data\output.txt

.PHONY: all build run clean

all: build

build:
	@echo ======================================
	@echo Compilando projeto...
	@echo ======================================
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)
	@echo.
	@echo Compilacao concluida!
	@echo Executavel gerado em: $(TARGET)

run: build
	@echo.
	@echo ======================================
	@echo Executando programa...
	@echo ======================================
	@if not exist $(DATA_DIR) mkdir $(DATA_DIR)
	.\$(TARGET) > $(OUTPUT_FILE)
	@echo.
	@echo Execucao concluida!
	@echo Resultados salvos em: $(OUTPUT_FILE)

clean:
	@echo Removendo arquivos gerados...
	@if exist $(TARGET) del /Q $(TARGET)
	@if exist $(OUTPUT_FILE) del /Q $(OUTPUT_FILE)
	@echo Limpeza concluida.