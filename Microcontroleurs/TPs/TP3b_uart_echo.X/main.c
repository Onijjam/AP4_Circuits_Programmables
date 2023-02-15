#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC
#include "config_EUSART.h"

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

void config_Interruption(void) {
    INTCON |= 0xC0;
    PIE1 |= 0x20;  
    PIR1 &= ~0x20;
}

void __interrupt() isr (void) {
    if(PIR1 & 0x20){
        write(RC1REG);
        PIR1 &= ~0x20;
    }
}

void main(void) {
    setup();
    config_Interruption();
    writeString("Démarrage\n\r");
    while(1) {
    
    }
}

