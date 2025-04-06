/** 
 * @file uart_mock.c
 * @brief Implementação de mock das funções UART para compilação do programa principal
 * 
 * Este arquivo fornece implementações básicas de UART_SendChar e UART_SendString
 * para permitir que o programa principal seja compilado e executado.
 */

#include <stdio.h>

// Mock para UART_SendChar - imprime na saída padrão
void UART_SendChar(char c) {
    printf("%c", c);
}

// Mock para UART_SendString - imprime na saída padrão
void UART_SendString(const char* str) {
    printf("%s", str);
}

