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

void main(void) {
    setup();
    writeString("Hello, World !\n\r");
    while(1) { 
        
    }
}