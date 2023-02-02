#include <8051.h>

#define MAX_SIZE 100 // Tamanho máximo da string de dados a ser gravada

char buffer[MAX_SIZE]; // Buffer para armazenar a string de dados

int X = 0; // Índice do próximo caractere a ser gravado no buffer

P3_4 = 0; 
P3_5 = 1; 
P3_6 = 0; 
P3_7 = 0; 

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
        
        P3_6 = 1; // Põe o MOSI em alto
        
        for (int i = 0; i < 8; i++)
        {
            P3_4 = 0; // Põe o SCK em baixo
            if (EM & 0x80)
                P3_6 = 1; // Põe o MOSI em alto
            else
                P3_6 = 0; // Põe o MOSI em baixo
            EM = EM << 1;
            P3_4 = 1; // Põe o SCK em alto
        }

        // Envia os dados
        for (int i = 0; i < 8; i++)
        {
            P3_4 = 0; // Põe o SCK em baixo
            if (dado & 0x80)
                P3_6 = 1; // Põe o MOSI em alto
            else
                P3_6 = 0; // Põe o MOSI em baixo
            dado = dado << 1;
            P3_4 = 1; // Põe o SCK em alto
        }

        P3_6 = 0; // Põe o MOSI em baixo
        for (int i = 0; i < 8; i++)
        {
            P3_4 = 0; // Põe o SCK em baixo
            P3_4 = 1; // Põe o SCK em alto
        }

                }
            }
        }
    }
}
