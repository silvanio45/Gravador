#include <8051.h>

#define MAX_SIZE 100 // Tamanho máximo da string de dados a ser gravada
#define MAX_SIZE2 100 // Tamanho máximo da segunda string de dados a ser gravada

char buffer[MAX_SIZE]; // Buffer para armazenar a string de dados
char buffer2[MAX_SIZE2]; //Buffer 2 para armazenar a string de dados

int X = 0; // Índice do próximo caractere a ser gravado no buffer
int Y = 0; // Índice do próximo caractere a ser gravado no buffer 2

void main()
{
    
    TMOD = 0x20; // Configura o modo 2, com timer 1 como modulador de baud rate
    TH1 = 0xFD; // Configura o baud rate para 9600
    SCON = 0x50; // Configura o modo 1 da porta serial, com recepção habilitada
    TR1 = 1; // Inicia o timer 1
    
    SPCTL = 0x50; // Configura modo 3 para a comunicação SPI
    SPIDIV = 0x01; // Configura baud rate para a metade da taxa de clock
    SPICON = 1; // Habilita a comunicação SPI

    while (1) {
        if (RI) { // Se um dado foi recebido na porta serial
            buffer[X] = SBUF; // Armazena o dado no buffer
            P0 = 0b1111101; // Ativa o led sinalizador verde
            RI = 0; // Limpa a flag de recepção
            X++; // Avança o índice do buffer
            
            if (X == MAX_SIZE) {

                P0 = 0b1111110;  // Ativa o led sinalizador vermelho
                X = 0; // Reinicia o índice do buffer

                }
            } 
            SPIBUF = 0xAA; // Envia um byte para o dispositivo SPI
            while (!SPI); // Espera o fim da transmissão
            buffer2[Y] = SPIBUF; // Armazena os dados recebidos
            P0 = 0b1111101; // Ativa o led sinalizador verde
            Y++;

            if (Y == MAX_SIZE2){
            
            P0 = 0b1111110; // Ativa o led sinalizador vermelho
            Y = 0; // Reinicia o índice do buffer 2

                }
            }
        }
    }
}
