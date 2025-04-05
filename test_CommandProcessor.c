/*  Assignment 2 - Sistemas Embutidos e de Tempo Real
---------------------------------------------------------------------------------------------
Autores: Tomás Gomes   [98807]
         Vasco Pestana [88827]

Descrição:
        -> Testes unitários para o módulo de processamento de comandos UART.
*/

/** 
 * @file test_CommandProcessor.c
 * @brief Testes unitários para o processador de comandos de sensores inteligentes.
 * 
 * Este arquivo contém testes unitários usando o framework Unity para validar
 * o comportamento do processador de comandos.
 * 
 * @authors 
 *      - Tomás Gomes [98807]  
 *      - Vasco Pestana [88827]
 * @date 2025
 */

 #include "Unity/src/unity.h"
 #include "Command_Processor.h"
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 // Buffer para capturar a saída da UART
 #define MAX_BUFFER_SIZE 2048
 char output_buffer[MAX_BUFFER_SIZE];
 int buffer_position = 0;
 
 // Função para limpar o buffer antes de cada teste
 void resetBuffer() {
     memset(output_buffer, 0, sizeof(output_buffer));
     buffer_position = 0;
 }
 
 // Mock da função UART_SendChar para capturar a saída
 void UART_SendChar(char c) {
     if (buffer_position < MAX_BUFFER_SIZE - 1) {
         output_buffer[buffer_position++] = c;
         output_buffer[buffer_position] = '\0';  // Sempre terminar com null
     }
 }
 
 // Mock da função UART_SendString que usa nossa versão mockada de UART_SendChar
 void UART_SendString(const char* str) {
     while (*str) {
         UART_SendChar(*str++);
     }
 }
 
 // Setup e Teardown para os testes
 void setUp(void) {
     resetBuffer();
     CommandProcessorInit();
 }
 
 void tearDown(void) {
     // Nada a limpar após os testes
 }
 
 // Função auxiliar para enviar um comando completo
 void sendCommand(char cmd, char data) {
     char checksum = CalculateChecksum(cmd, data);
     char command[] = {'#', cmd, data, checksum, '!'};
     
     for (int i = 0; i < 5; i++) {
         UART_ReceiveChar(command[i]);
     }
 }
 
 // Testes unitários
 
 // Teste 1: Comando 'A' - Todos os sensores
 void test_CommandA_AllSensors(void) {
     // Enviar comando A
     sendCommand('A', 'T');
     
     // Verificar se a saída contém as informações esperadas
     TEST_ASSERT_TRUE(strstr(output_buffer, "Temperature:") != NULL);
     TEST_ASSERT_TRUE(strstr(output_buffer, "°C") != NULL);
     TEST_ASSERT_TRUE(strstr(output_buffer, "Humidity:") != NULL);
     TEST_ASSERT_TRUE(strstr(output_buffer, "%") != NULL);
     TEST_ASSERT_TRUE(strstr(output_buffer, "CO2:") != NULL);
     TEST_ASSERT_TRUE(strstr(output_buffer, "ppm") != NULL);
 }
 
 // Teste 2: Comando 'P T' - Temperatura
 void test_CommandP_Temperature(void) {
     // Enviar comando P com parâmetro T
     sendCommand('P', 'T');
     
     // Verificar se a saída contém apenas informações de temperatura
     TEST_ASSERT_TRUE(strstr(output_buffer, "Temperature:") != NULL);
     TEST_ASSERT_TRUE(strstr(output_buffer, "°C") != NULL);
     TEST_ASSERT_FALSE(strstr(output_buffer, "Humidity:") != NULL);
     TEST_ASSERT_FALSE(strstr(output_buffer, "CO2:") != NULL);
 }
 
 // Teste 3: Comando 'P H' - Humidade
 void test_CommandP_Humidity(void) {
     // Enviar comando P com parâmetro H
     sendCommand('P', 'H');
     
     // Verificar se a saída contém apenas informações de humidade
     TEST_ASSERT_FALSE(strstr(output_buffer, "Temperature:") != NULL);
     TEST_ASSERT_TRUE(strstr(output_buffer, "Humidity:") != NULL);
     TEST_ASSERT_TRUE(strstr(output_buffer, "%") != NULL);
     TEST_ASSERT_FALSE(strstr(output_buffer, "CO2:") != NULL);
 }
 
 // Teste 4: Comando 'P C' - CO2
 void test_CommandP_CO2(void) {
     // Enviar comando P com parâmetro C
     sendCommand('P', 'C');
     
     // Verificar se a saída contém apenas informações de CO2
     TEST_ASSERT_FALSE(strstr(output_buffer, "Temperature:") != NULL);
     TEST_ASSERT_FALSE(strstr(output_buffer, "Humidity:") != NULL);
     TEST_ASSERT_TRUE(strstr(output_buffer, "CO2:") != NULL);
     TEST_ASSERT_TRUE(strstr(output_buffer, "ppm") != NULL);
 }
 
 // Teste 5: Comando 'L' - Listar histórico
 void test_CommandL_ListHistory(void) {
     // Adicionar algumas amostras primeiro
     sendCommand('A', 'X');
     resetBuffer();  // Limpar o buffer para o teste atual
     
     // Enviar comando L
     sendCommand('L', 'X');
     
     // Verificar se a saída contém o histórico
     TEST_ASSERT_TRUE(strstr(output_buffer, "Last 20 samples:") != NULL);
     TEST_ASSERT_TRUE(strstr(output_buffer, "Sample 1") != NULL);
 }
 
 // Teste 6: Comando 'R' - Reset
 void test_CommandR_Reset(void) {
     // Adicionar algumas amostras primeiro
     sendCommand('A', 'X');
     resetBuffer();
     
     // Enviar comando R
     sendCommand('R', 'X');
     
     // Verificar se a mensagem de reset foi exibida
     TEST_ASSERT_TRUE(strstr(output_buffer, "Reseting the values...") != NULL);
     
     // Verificar se o histórico foi limpo
     resetBuffer();
     sendCommand('L', 'X');
     TEST_ASSERT_TRUE(strstr(output_buffer, "Sample 1 -> Temp: -, Hum: -, CO2: -") != NULL);
 }
 
 // Teste 7: Comando inválido (checksum errado)
 void test_InvalidChecksum(void) {
     // Enviar comando com checksum incorreto
     char command[] = {'#', 'P', 'T', 0x00, '!'};
     
     for (int i = 0; i < 5; i++) {
         UART_ReceiveChar(command[i]);
     }
     
     // Verificar se a mensagem de erro foi exibida
     TEST_ASSERT_TRUE(strstr(output_buffer, "Error: Invalid command") != NULL);
 }
 
 // Teste 8: Comando com formato inválido (sem # no início)
 void test_InvalidFormat_NoStartFrame(void) {
     // Enviar comando sem # no início
     char command[] = {'X', 'P', 'T', 'X', '!'};
     
     for (int i = 0; i < 5; i++) {
         UART_ReceiveChar(command[i]);
     }
     
     // Verificar que nenhuma saída foi gerada (comando não reconhecido)
     TEST_ASSERT_EQUAL_STRING("", output_buffer);
 }
 
 // Teste 9: Comando com formato inválido (sem ! no final)
 void test_InvalidFormat_NoEndFrame(void) {
     char cmd = 'A';
     char data = 'X';
     char checksum = CalculateChecksum(cmd, data);
     char command[] = {'#', cmd, data, checksum, 'X'};
     
     for (int i = 0; i < 5; i++) {
         UART_ReceiveChar(command[i]);
     }
     
     // Verificar que mensagem de erro foi exibida
     TEST_ASSERT_TRUE(strstr(output_buffer, "Error: Invalid command") != NULL);
 }
 
 // Teste 10: Comando com código de comando inválido
 void test_InvalidCommandCode(void) {
     // Enviar comando com código inexistente
     sendCommand('Z', 'X');
     
     // Verificar se a mensagem de erro foi exibida
     TEST_ASSERT_TRUE(strstr(output_buffer, "Invalid command") != NULL);
 }
 
 // Teste 11: Verificar valores dos sensores
 void test_SensorValues(void) {
     // Testar vários comandos P para ver se os valores dos sensores estão sendo incrementados
     
     // Primeiro sensor - Temperatura
     sendCommand('P', 'T');
     char* temp1 = strstr(output_buffer, "Temperature: ");
     TEST_ASSERT_NOT_NULL(temp1);
     int value1 = atoi(temp1 + 13);  // Extrair o valor numérico
     
     resetBuffer();
     
     // Segunda leitura do mesmo sensor
     sendCommand('P', 'T');
     char* temp2 = strstr(output_buffer, "Temperature: ");
     TEST_ASSERT_NOT_NULL(temp2);
     int value2 = atoi(temp2 + 13);  // Extrair o valor numérico
     
     // Os valores devem ser diferentes pois o índice incrementa
     TEST_ASSERT_NOT_EQUAL(value1, value2);
 }
 
 // Programa principal que executa os testes
 int main(void) {
     UNITY_BEGIN();
     
     RUN_TEST(test_CommandA_AllSensors);
     RUN_TEST(test_CommandP_Temperature);
     RUN_TEST(test_CommandP_Humidity);
     RUN_TEST(test_CommandP_CO2);
     RUN_TEST(test_CommandL_ListHistory);
     RUN_TEST(test_CommandR_Reset);
     RUN_TEST(test_InvalidChecksum);
     RUN_TEST(test_InvalidFormat_NoStartFrame);
     RUN_TEST(test_InvalidFormat_NoEndFrame);
     RUN_TEST(test_InvalidCommandCode);
     RUN_TEST(test_SensorValues);
     
     return UNITY_END();
 }

