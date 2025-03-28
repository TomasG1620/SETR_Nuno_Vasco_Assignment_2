/*  Assignment 2 - Sistemas Embutidos e de Tempo Real
---------------------------------------------------------------------------------------------
Autores: Tomás Gomes   [98807]
         Vasco Pestana [88827]

Descrição:
        -> Implementação de um módulo em C que processa comandos que são recebidos em UART 
        (um caratér de cada vez). O módulo faz parte de um sensor inteligente, capaz de medir
        temperatura(-50ºC ... 60ºC), humidade(0 ... 100%) e CO2 (400 ... 20000 ppm).
*/

/** 
 * @file Command_Processor.h
 * @brief Cabeçalho do processador de comandos para sensores inteligentes.
 * 
 * Este cabeçalho contém as definições de funções utilizadas para processar 
 * comandos recebidos via UART, validando comandos, verificando checksums e armazenando histórico.
 * 
 * @authors 
 *      - Tomás Gomes [98807]  
 *      - Vasco Pestana [88827]
 * @date 2025
 */

#ifndef COMMAND_PROCESSOR_H  
#define COMMAND_PROCESSOR_H 

/** 
 * @brief Inicializa o processador de comandos.
 * 
 * Esta função inicializa o histórico e define os valores iniciais dos sensores.
 */

void CommandProcessorInit(void); 

/**
 * @brief Calcula o checksum de um comando.
 * 
 * @param cmd Caractere representando o comando.
 * @param data Caractere representando os dados.
 * @return char Checksum calculado (1 byte).
 */

char CalculateChecksum(char cmd, char data);

/**
 * @brief Processa e valida um comando recebido.
 * 
 * Esta função processa um comando recebido, verificando a estrutura e o checksum.
 * Se o comando for válido, ele executa as funções apropriadas.
 * 
 * @param start_frame Caractere de início do comando (esperado '#').
 * @param cmd Caractere representando o comando.
 * @param data Dados do comando.
 * @param checksum Checksum do comando (para validação).
 * @param end_frame Caractere de fim do comando (esperado '!').
 */

void ProcessCommand(char start_frame, char cmd, char data, char checksum, char end_frame);

/**
 * @brief Converte um número inteiro em string.
 * 
 * @param value Valor inteiro a ser convertido.
 * @return const char* Ponteiro para a string resultante.
 */

const char *int_to_string(int value);

#endif
