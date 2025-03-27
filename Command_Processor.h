/*  Assignment 2 - Sistemas Embutidos e de Tempo Real
---------------------------------------------------------------------------------------------
Autores: Tomás Gomes   [98807]
         Vasco Pestana [88827]

Descrição:
        -> Implementação de um módulo em C que processa comandos que são recebidos em UART 
        (um caratér de cada vez). O módulo faz parte de um sensor inteligente, capaz de medir
        temperatura(-50ºC ... 60ºC), humidade(0 ... 100%) e CO2 (400 ... 20000 ppm).
*/

#ifndef COMMAND_PROCESSOR_H  
#define COMMAND_PROCESSOR_H 

// Funções declaradas (prototypes)
void CommandProcessorInit(void);  
char CalculateChecksum(char cmd, char data);
void ProcessCommand(char start_frame, char cmd, char data, char checksum, char end_frame);
  // Declaração da função para evitar erro de declaração implícita
const char *int_to_string(int value);

#endif
