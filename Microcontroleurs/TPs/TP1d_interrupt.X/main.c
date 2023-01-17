#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

/*LEDs :
 * D1 <=> PORTD0
 * D2 <=> PORTD1
 * D3 <=> PORTD2
 * D4 <=> PORTD3
 * D5 <=> PORTB0
 * D6 <=> PORTB1
 * D7 <=> PORTB2
 * D8 <=> PORTB3
 */

int time_ms = 0;

void __interrupt() isr (void){
    PIR1 &= ~(0x02);
    time_ms++;
    if(time_ms == 125){
        char b = (LATB & 0x0F);
        char d = (LATD & 0x0F);
        int count = 0;
        char verif = 'b';
        char choice = b;

        if(b == 0x00){
            verif = 'd';
            choice = d;
        }

        switch( choice )
        {
            case 0x01:
                    count=1;
                    break;
            case 0x02:
                    count=2;
                    break;
            case 0x04:
                    count=3;
                    break;
            case 0x08:
                    count=4;
                    break;
            default:
                    count=0;
                    break;
        }

        if(count == 4){
                if(verif == 'd'){
                    verif = 'b';
                }
                else if(verif == 'b'){
                    verif = 'd';
                }
                count = 0;
            }

        if (verif == 'd'){
            if(count == 0){
                LATB = 0;
                LATD |= 1;
            }
            else{
                LATD |= (1 << count);
                if(count == 1){
                    LATD &= ~1;
                }
                else{
                    LATD &= ~(1 << (count-1));
                }
            }      
        }
        
        if (verif == 'b'){
            if(count == 0){
                LATD = 0;
                LATB |= 1;
            }
            else{
                LATB |= (1 << count);
                if(count == 1){
                    LATB &= ~1;
                }
                else{
                    LATB &= ~(1 << (count-1));
                }
            }
        }
        time_ms=0;
    }     
}

void main(void) {
    /* Code d'initialisation */
    /*On acive le GEI et le PEIE*/
    INTCON |= 0xC0;
    /*On active l'interrupteur sur le timer2*/
    PIE1 |= 0x02; 
    /*On paramètre le prescaler à 1 et postcaler à 16*/
    T2CON &= ~(0x7F);
    T2CON |= 0x7C;
    PR2 = 124;
    /*Mise en Output des LEDS*/
    TRISD &= 0xF0;
    TRISB &= 0xF0;
    /*On allume de D1 à D4 de manière individuel et on éteins de D5 à D8 | On initialise le cas zero*/
    LATD = 0;
    LATB = 0;
    LATD |= 1; 
    
    while(1){
 
    }
}