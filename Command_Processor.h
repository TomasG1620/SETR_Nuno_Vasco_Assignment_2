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
 char CalculateChecksum(char cmd, char data);
 void UART_ReceiveChar(char c);
 void ProcessCommand(char start_frame, char cmd, char data, char checksum, char end_frame);
 
 #endif /* COMMAND_PROCESSOR_H */

