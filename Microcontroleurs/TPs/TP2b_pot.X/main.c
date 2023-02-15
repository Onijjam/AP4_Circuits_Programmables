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

#define LED1    LATDbits.LATD0
#define LED2    LATDbits.LATD1
#define LED3    LATDbits.LATD2
#define LED4    LATDbits.LATD3
#define LED5    LATBbits.LATB0
#define LED6    LATBbits.LATB1
#define LED7    LATBbits.LATB2
#define LED8    LATBbits.LATB3

void setup(void) {
    // Configurer les broches des LEDs comme sorties
    TRISD &= 0xF0;
    TRISB &= 0xF0;
    
    // Configurer l'ADC
    ADCON0bits.ADON = 1;  // Activer l'ADC
    ADCON0bits.CHS = 0;   // Sélectionner AN0
    ADCON1bits.ADFM = 1;  // Justification à droite
    ADCON1bits.ADCS = 2;  // Temps de conversion Tad = 4 Tosc
    ADCON1bits.ADPREF = 0; // Tension de référence interne Vdd
}

uint16_t read_adc(void) {
    ADCON0bits.GO = 1;  // Démarrer la conversion
    while (ADCON0bits.GO); // Attendre la fin de la conversion
    return ((uint16_t)ADRESH << 8) + ADRESL;  // Retourner la valeur convertie
}

int main(void) {
    setup();
    while (1) {
        uint16_t adc_value = read_adc();  // Lire la valeur du potentiomètre
        uint16_t led_number = adc_value * 8 / 1023 + 1;  // Calculer le numéro de la LED à allumer
        
        LED1 = LED2 = LED3 = LED4 = LED5 = LED6 = LED7 = LED8 = 0;  // Éteindre toutes les LEDs
        
        switch (led_number) {  // Allumer la LED correspondante
            case 1: LED1 = 1; break;
            case 2: LED2 = 1; break;
            case 3: LED3 = 1; break;
            case 4: LED4 = 1; break;
            case 5: LED5 = 1; break;
            case 6: LED6 = 1; break;
            case 7: LED7 = 1; break;
            case 8: LED8 = 1; break;
        }
    }
}