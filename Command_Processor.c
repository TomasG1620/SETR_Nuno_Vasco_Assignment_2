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
#include <stdio.h>
#include <string.h>

#define MAX_HISTORY 20

// Valores pré-determinados para sensores (amostras)
int temperature_values[MAX_HISTORY] = {22, 23, 21, 25, 24, 26, 22, 23, 21, 24, 25, 23, 26, 24, 21, 23, 24, 22, 26, 25};
int humidity_values[MAX_HISTORY] = {50, 52, 51, 49, 53, 54, 50, 55, 52, 50, 54, 53, 51, 50, 49, 52, 53, 54, 55, 50};
int co2_values[MAX_HISTORY] = {400, 450, 420, 430, 440, 460, 420, 410, 420, 440, 430, 450, 440, 430, 460, 410, 400, 450, 460, 420};

// Histórico de valores
int temp_history[MAX_HISTORY];
int hum_history[MAX_HISTORY];
int co2_history[MAX_HISTORY];

int temperature_index = 0;
int humidity_index = 0;
int co2_index = 0;

// Função para inicializar o processador de comandos
void CommandProcessorInit(void) {
    memset(temp_history, 0, sizeof(temp_history));
    memset(hum_history, 0, sizeof(hum_history));
    memset(co2_history, 0, sizeof(co2_history));
    printf("Command Processor initialized!\n");
}

// Função para calcular o checksum (CMD + DATA)
char CalculateChecksum(char cmd, char data) {
    return (char)((cmd + data) % 256);  // Limitar a soma a 8 bits (1 byte)
}

// Definição da função int_to_string
const char *int_to_string(int value) {
    static char buffer[10];           // Buffer para armazenar o valor convertido
    sprintf(buffer, "%d", value);     // Converte o número em string
    return buffer;                    // Retorna o ponteiro para o buffer
}

// Processar o comando, validando ASCII, checksum e estrutura correta
void ProcessCommand(char start_frame, char cmd, char data, char checksum, char end_frame) {

    // Validação de estrutura e checksum
    if (start_frame != '#' || end_frame != '!' || checksum != CalculateChecksum(cmd, data)) {
        printf("Error: Invalid command structure or incorrect checksum\n");
        return;
    }

    switch (cmd) {
        case 'A': // Obter todos os valores dos sensores em tempo real
            printf("Temperature: %d °C\n", temperature_values[temperature_index % MAX_HISTORY]);
            printf("Humidity: %d %%\n", humidity_values[humidity_index % MAX_HISTORY]);
            printf("CO2: %d ppm\n", co2_values[co2_index % MAX_HISTORY]);

            // Guardar no histórico
            temp_history[temperature_index % MAX_HISTORY] = temperature_values[temperature_index % MAX_HISTORY];
            hum_history[humidity_index % MAX_HISTORY] = humidity_values[humidity_index % MAX_HISTORY];
            co2_history[co2_index % MAX_HISTORY] = co2_values[co2_index % MAX_HISTORY];
            temperature_index++;
            humidity_index++;
            co2_index++;
            break;

        case 'P': // Obter valor de um sensor específico
            if (data == 'T') {
                printf("Temperature: %d °C\n", temperature_values[(temperature_index) % MAX_HISTORY]);
                temp_history[temperature_index % MAX_HISTORY] = temperature_values[temperature_index % MAX_HISTORY];
                temperature_index++;
            } else if (data == 'H') {
                printf("Humidity: %d %%\n", humidity_values[(humidity_index) % MAX_HISTORY]);
                hum_history[humidity_index % MAX_HISTORY] = humidity_values[humidity_index % MAX_HISTORY];
                humidity_index++;
            } else if (data == 'C') {
                printf("CO2: %d ppm\n", co2_values[(co2_index) % MAX_HISTORY]);
                co2_history[co2_index % MAX_HISTORY] = co2_values[co2_index % MAX_HISTORY];
                co2_index++;
            } else {
                printf("Invalid sensor\n");
            }
            break;

/*        case 'L': // Lista do histórico das amostras 
            printf("Last 20 samples:\n");
            for (int i = 0; i < MAX_HISTORY; i++) {
                printf("Sample %d -> Temp: %d °C, Hum: %d %%, CO2: %d ppm\n", i + 1, 
                    temp_history[i], hum_history[i], co2_history[i]);
            }
            break;
*/
case 'L': // Lista do histórico das amostras
    printf("Last 20 samples:\n");

    // Percorre até 20 amostras ou até o máximo de valores disponíveis
    for (int i = 0; i < MAX_HISTORY; i++) {
        // Obtenção dos valores corretos, com verificação do índice
        int temp_val = (i < temperature_index) ? temp_history[i] : -1;
        int hum_val = (i < humidity_index) ? hum_history[i] : -1;
        int co2_val = (i < co2_index) ? co2_history[i] : -1;

        // Conversão condicional dos valores para string ou "-"
        const char *temp_str = (temp_val != -1) ? int_to_string(temp_val) : "-";
        const char *hum_str = (hum_val != -1) ? int_to_string(hum_val) : "-";
        const char *co2_str = (co2_val != -1) ? int_to_string(co2_val) : "-";

        printf("Sample %d -> Temp: %s, Hum: %s, CO2: %s\n", i + 1, temp_str, hum_str, co2_str);
    }
    break;

        case 'R': // Dá um reset no histórico 
            printf("Reseting the values...\n");
            memset(temp_history, 0, sizeof(temp_history));
            memset(hum_history, 0, sizeof(hum_history));
            memset(co2_history, 0, sizeof(co2_history));
            temperature_index = 0;
            humidity_index = 0;
            co2_index = 0;
            break;

        default:
            printf("Invalid command\n");
            break;
    }
}
