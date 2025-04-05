/*  Assignment 2 - Sistemas Embutidos e de Tempo Real
---------------------------------------------------------------------------------------------
Autores: Tomás Gomes   [98807]
         Vasco Pestana [88827]

Descrição:
        -> Implementação de um módulo em C que processa comandos que são recebidos em UART 
        (um caratér de cada vez). O módulo faz parte de um sensor inteligente, capaz de medir
        temperatura(-50ºC ... 60ºC), humidade(0 ... 100%) e CO2 (400 ... 20000 ppm).
*/

#include "Unity/src/unity.h"
#include "Command_Processor.h"
#include <string.h>

// Função para simular UART output
char uart_output[1024];
int uart_index = 0;

void UART_SendChar_Test(char c) {
    uart_output[uart_index++] = c;
    uart_output[uart_index] = '\0'; // garantir null-termination
}

void setUp(void) {
    uart_index = 0;
    uart_output[0] = '\0';
    CommandProcessorInit();
}

void tearDown(void) {
    // Nada a limpar por agora
}

void test_CalculateChecksum_should_return_correct_value(void) {
    TEST_ASSERT_EQUAL_CHAR((char)(( 'A' + 'T') % 256), CalculateChecksum('A', 'T'));
    TEST_ASSERT_EQUAL_CHAR((char)(( 'P' + 'H') % 256), CalculateChecksum('P', 'H'));
}

void test_ProcessCommand_valid_command_all(void) {
    char cmd[] = {'#', 'A', '0', CalculateChecksum('A', '0'), '!'};
    ProcessCommand(cmd[0], cmd[1], cmd[2], cmd[3], cmd[4]);

    TEST_ASSERT_NOT_EQUAL(0, strlen(uart_output));
    TEST_ASSERT_NOT_NULL(strstr(uart_output, "Temperature:"));
    TEST_ASSERT_NOT_NULL(strstr(uart_output, "Humidity:"));
    TEST_ASSERT_NOT_NULL(strstr(uart_output, "CO2:"));
}

void test_ProcessCommand_invalid_checksum(void) {
    char cmd[] = {'#', 'A', '0', 0x00 /* errado */, '!'};
    ProcessCommand(cmd[0], cmd[1], cmd[2], cmd[3], cmd[4]);

    TEST_ASSERT_NOT_NULL(strstr(uart_output, "Error: Invalid command structure"));
}

void test_UART_ReceiveChar_whole_command(void) {
    char full_command[] = {'#', 'A', '0', CalculateChecksum('A', '0'), '!'};
    for (int i = 0; i < 5; i++) {
        UART_ReceiveChar(full_command[i]);
    }

    TEST_ASSERT_NOT_EQUAL(0, strlen(uart_output));
    TEST_ASSERT_NOT_NULL(strstr(uart_output, "Temperature:"));
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_CalculateChecksum_should_return_correct_value);
    RUN_TEST(test_ProcessCommand_valid_command_all);
    RUN_TEST(test_ProcessCommand_invalid_checksum);
    RUN_TEST(test_UART_ReceiveChar_whole_command);

    return UNITY_END();
}
