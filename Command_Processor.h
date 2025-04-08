/** 
 * @file Command_Processor_Test.h
 * @brief Interface do processador de comandos para testes.
 * 
 * @authors 
 *      - Tomás Gomes [98807]  
 *      - Vasco Pestana [88827]
 * @date 2025
 */

 #ifndef COMMAND_PROCESSOR_H
 #define COMMAND_PROCESSOR_H
 
 // Declare as funções UART que serão fornecidas por nós
 void UART_SendChar(char c);
 void UART_SendString(const char* str);
 
 // Funções do Command_Processor
 void CommandProcessorInit(void);

 /**
 * @brief Calcula o checksum com base no comando e no dado.
 * 
 * @param cmd  Comando recebido (ex: 'A', 'P'…)
 * @param data Dado associado ao comando (ex: 'T', 'H', 'C')
 * @return Checksum calculado (1 byte)
 */
 char CalculateChecksum(char cmd, char data);

 /**
 * @brief Recebe caracteres da UART um por um e reconstrói comandos completos.
 * 
 * @param c Caractere recebido da UART
 */
 void UART_ReceiveChar(char c);

/**
 * @brief Processa comandos válidos e executa ações conforme o tipo de comando.
 * 
 * @param start_frame Caractere inicial esperado ('#')
 * @param cmd Comando (ex: 'A', 'P', 'L', 'R')
 * @param data Dado complementar ao comando (ex: 'T' para temperatura)
 * @param checksum Checksum recebido
 * @param end_frame Caractere final esperado ('!')
 */
 void ProcessCommand(char start_frame, char cmd, char data, char checksum, char end_frame);
 
 #endif /* COMMAND_PROCESSOR_H */

