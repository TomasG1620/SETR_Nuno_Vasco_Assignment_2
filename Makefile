# Nome do módulo
MODULE_NAME = CommandProcessor

# Paths
UNITY_ROOT = Unity
SRC_FOLDER = .
TEST_FOLDER = .

# Commands
CLEANUP = rm -f
MKDIR = mkdir -p

# Compiler
C_COMPILER = gcc
CFLAGS=-std=c99  
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition

# Executáveis
TEST_TARGET = test$(MODULE_NAME)
MAIN_TARGET = main$(MODULE_NAME)

# Ficheiros fonte
SRC_FILES=$(UNITY_ROOT)/src/unity.c $(SRC_FOLDER)/Command_Processor.c $(TEST_FOLDER)/test_$(MODULE_NAME).c
MAIN_FILES=$(SRC_FOLDER)/Command_Processor.c $(SRC_FOLDER)/main.c

# Includes
INC_DIRS=-I$(SRC_FOLDER) -I$(UNITY_ROOT)/src
SYMBOLS=

all: clean $(TEST_TARGET) $(MAIN_TARGET) run_tests run_main

# Compilar os testes
$(TEST_TARGET): $(SRC_FILES)
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES) -o $(TEST_TARGET)

# Compilar o programa principal
$(MAIN_TARGET): $(MAIN_FILES)
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(MAIN_FILES) -o $(MAIN_TARGET)

# Executar os testes
run_tests: $(TEST_TARGET)
	./$(TEST_TARGET)

# Executar o programa principal
run_main: $(MAIN_TARGET)
	./$(MAIN_TARGET)

# Limpeza dos arquivos gerados
clean:
	$(CLEANUP) $(TEST_TARGET) $(MAIN_TARGET)


