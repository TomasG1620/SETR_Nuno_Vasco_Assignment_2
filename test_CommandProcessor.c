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

// Função chamada antes de cada teste
void setUp(void) { 
    CommandProcessorInit();
}

// Função chamada após cada teste
void tearDown(void) {}

// Teste para verificar se o checksum é calculado corretamente
void test_CalculateChecksum(void) {
    TEST_ASSERT_EQUAL_CHAR((char)(('A' + 0) % 256), CalculateChecksum('A', 0));
    TEST_ASSERT_EQUAL_CHAR((char)(('P' + 'T') % 256), CalculateChecksum('P', 'T'));
    TEST_ASSERT_EQUAL_CHAR((char)(('L' + 0) % 256), CalculateChecksum('L', 0));
}


// Teste para comandos válidos
void test_ProcessCommand_Valid(void) {
    ProcessCommand('#', 'A', 0, CalculateChecksum('A', 0), '!');
    ProcessCommand('#', 'P', 'T', CalculateChecksum('P', 'T'), '!');
    ProcessCommand('#', 'R', 0, CalculateChecksum('R', 0), '!');
}

// Teste para comandos inválidos (checksum errado)
void test_ProcessCommand_InvalidChecksum(void) {
    // Comando inválido pois o checksum não bate
    ProcessCommand('#', 'A', 0, 'X', '!');
}

// Teste para comando inválido (estrutura errada)
void test_ProcessCommand_InvalidStructure(void) {
    // Comando inválido pois falta um caractere válido
    ProcessCommand('*', 'A', 0, CalculateChecksum('A', 0), '!');
}

// Função principal de testes
int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_CalculateChecksum);
    RUN_TEST(test_ProcessCommand_Valid);
    RUN_TEST(test_ProcessCommand_InvalidChecksum);
    RUN_TEST(test_ProcessCommand_InvalidStructure);

    return UNITY_END();
}
