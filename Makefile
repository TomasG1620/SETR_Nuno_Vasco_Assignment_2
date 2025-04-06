# Makefile for Smart Sensor System
# Autores: Tomás Gomes [98807], Vasco Pestana [88827]

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Diretórios
UNITY_DIR = Unity/src
BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = .

# Lista de arquivos objeto
OBJS = $(OBJ_DIR)/Command_Processor.o
MAIN_OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/uart_mock.o
TEST_OBJS = $(OBJ_DIR)/test_CommandProcessor.o $(OBJ_DIR)/unity.o

# Alvos principais
all: directories main tests

# Criar diretórios necessários
directories:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

# Programa principal
main: $(BIN_DIR)/main

$(BIN_DIR)/main: $(MAIN_OBJ) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Testes unitários
tests: $(BIN_DIR)/test_CommandProcessor

$(BIN_DIR)/test_CommandProcessor: $(TEST_OBJS) $(OBJ_DIR)/Command_Processor.o
	$(CC) $(CFLAGS) -o $@ $^

# Regras de compilação para arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/unity.o: $(UNITY_DIR)/unity.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cabeçalhos
DEPS = Command_Processor.h $(UNITY_DIR)/unity.h

# Garantir que as dependências sejam verificadas
$(OBJS) $(MAIN_OBJ) $(TEST_OBJS): $(DEPS)

# Executar programa principal
run: $(BIN_DIR)/main
	./$(BIN_DIR)/main

# Executar testes
run-tests: $(BIN_DIR)/test_CommandProcessor
	./$(BIN_DIR)/test_CommandProcessor

# Limpar arquivos gerados
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

# Alvos fictícios (não correspondem a arquivos)
.PHONY: all clean run run-tests directories tests main

