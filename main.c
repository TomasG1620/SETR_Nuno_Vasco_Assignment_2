/*  Assignment 2 - Sistemas Embutidos e de Tempo Real
---------------------------------------------------------------------------------------------
Autores: Tomás Gomes   [98807]
         Vasco Pestana [88827]

Descrição:
        -> Implementação de um módulo em C que processa comandos que são recebidos em UART 
        (um caratér de cada vez). O módulo faz parte de um sensor inteligente, capaz de medir
        temperatura(-50ºC ... 60ºC), humidade(0 ... 100%) e CO2 (400 ... 20000 ppm).
*/

#include "Command_Processor.h" 

int main() {
    CommandProcessorInit();  // Inicializar o processador

    // Exemplo de comandos válidos com CMD, DATA e CHECKSUM em ASCII
    ProcessCommand('#', 'A', 0, (char)('A' + 0), '!');   // CMD = 'A', DATA = 0

    ProcessCommand('#', 'P', 'T', (char)('P' + 'T'), '!'); // CMD = 'P', DATA = 'T'
    ProcessCommand('#', 'P', 'T', (char)('P' + 'T'), '!'); // CMD = 'P', DATA = 'T'
	ProcessCommand('#', 'P', 'T', (char)('P' + 'T'), '!'); // CMD = 'P', DATA = 'T'
    
    ProcessCommand('#', 'A', 0, (char)('A' + 0), '!');   // CMD = 'A', DATA = 0
    ProcessCommand('#', 'A', 0, (char)('A' + 0), '!');   // CMD = 'A', DATA = 0

    ProcessCommand('#', 'P', 'T', (char)('P' + 'T'), '!'); // CMD = 'P', DATA = 'T'
    ProcessCommand('#', 'P', 'T', (char)('P' + 'T'), '!'); // CMD = 'P', DATA = 'T'
	ProcessCommand('#', 'P', 'T', (char)('P' + 'T'), '!'); // CMD = 'P', DATA = 'T'

    ProcessCommand('#', 'L', 0, (char)('L' + 0), '!');   // CMD = 'L', DATA = 0
    ProcessCommand('#', 'R', 0, (char)('R' + 0), '!');   // CMD = 'R', DATA = 0
    ProcessCommand('#', 'L', 0, (char)('L' + 0), '!');   // CMD = 'L', DATA = 0

    return 0;
}
