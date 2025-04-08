/** 
 * @file uart_mock.c
 * @brief Implementação de mock das funções UART para compilação do programa principal
 * 
 * Este arquivo fornece implementações básicas de UART_SendChar e UART_SendString
 * para permitir que o programa principal seja compilado e executado.
 */

#include <stdio.h>

/**
 * @brief Simula o envio de um caractere pela UART.
 * 
 * Esta função simula o comportamento da UART imprimindo o caractere
 * fornecido na saída padrão.
 * 
 * @param c Caractere a ser enviado.
 */
void UART_SendChar(char c) {
    printf("%c", c);
}

/**
 * @brief Simula o envio de uma string pela UART.
 * 
 * Esta função simula o comportamento da UART imprimindo a string
 * fornecida na saída padrão.
 * 
 * @param str Ponteiro para a string a ser enviada.
 */
void UART_SendString(const char* str) {
    printf("%s", str);
}

