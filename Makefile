# Makefile with variables
P = main
OBJECTS = main.o Command_Processor.o 
CFLAGS = -g -Wall -O3
LDLIBS = 
CC = gcc

# Compilação dos arquivos
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos compilados 
clean:
	rm *.o $(P)

# Regra para formatar o código (usando clang-format)
#format:
#	clang-format -i *.c *.h

# Regra para verificar a formatação
#check-format:
#	clang-format --dry-run --Werror *.c *.h

# Phony targets (não geram ficheiros com estes nomes)
#.PHONY: all test clean format check-format

