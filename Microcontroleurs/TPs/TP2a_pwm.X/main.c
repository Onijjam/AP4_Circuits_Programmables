#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

#define _XTAL_FREQ 8000000

/*LEDs :
 * D1 <=> PORTD0
 * D2 <=> PORTD1
 * D3 <=> PORTD2
 * D4 <=> PORTD3
 * D5 <=> PORTB0
 * D6 <=> PORTB1
 * D7 <=> PORTB2
 * D8 <=> PORTB3
 * 
 * Buttons : 
 * S2 <=> RA5
 */

void main(void) {
    /* Code d'initialisation */
    /*Mise en Output des LEDS*/
    TRISA |= 0x20;
    ANSELA &= ~(0x20);
    TRISD &= 0xF0;
    TRISB &= 0xF0;
    /*On allume de D1 à D4 de manière individuel et on éteins de D5 à D8 | On initialise le cas zero*/
    LATD = 0;
    LATB = 0;
    
    while(1){
        if(!(PORTA & 0x20)){
            while(!(PORTA & 0x20)){
                
            }
            LATD ^= 0x0A;
        }
    }
}