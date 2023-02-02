#include <8051.h>

#define MAX_SIZE 100 
char buffer[MAX_SIZE];
int X = 0; 

P3_4 = 0; 
P3_5 = 1; 
P3_6 = 0; 
P3_7 = 0; 

void main()
{
    
    TMOD = 0x20; 
    TH1 = 0xFD; 
    SCON = 0x50; 
    TR1 = 1; 
    
    SPCTL = 0x50; 
    SPIDIV = 0x01; 
    SPICON = 1; 

    while (1) {
        if (RI) { 
            buffer[X] = SBUF; 
            P0 = 0b1111101; 
            RI = 0; 
            X++; 
            
            if (X == MAX_SIZE) {

                P0 = 0b1111110;  
                X = 0; 

                }
            } 
        
        P3_6 = 1; 
        
        for (int i = 0; i < 8; i++)
        {
            P3_4 = 0; 
            if (EM & 0x80)
                P3_6 = 1;
            else
                P3_6 = 0; 
            EM = EM << 1;
            P3_4 = 1; 
        }

        
        for (int i = 0; i < 8; i++)
        {
            P3_4 = 0; 
            if (dado & 0x80)
                P3_6 = 1; 
            else
                P3_6 = 0; 
            dado = dado << 1;
            P3_4 = 1; 
        }

        P3_6 = 0;
        for (int i = 0; i < 8; i++)
        {
            
            P3_4 = 0;
            P3_4 = 1; 
            
                    }
                }
            }
        }
    }
}
