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

void setupLeds(void) {
//Définir la led 0 en entrée
TRISD &= ~0x01;
}

void configPortA(void) {
//Définir le potentiomètre en sortie
TRISA |= 0x01;
//Définir comme entrée analogique
ANSELA |= 0x01;
//Désactiver toutes les résistances de pull-up faibles
OPTION_REG |= 0x80;
}

void configADCModule(void) {
//Définir le canal d'entrée, GO/!Done et activer ADC
ADCON0 = 0x03;
//Justifier à droite, Fosc/4, VDD et VSS
ADCON1 = 0xC0;

}

void configADCInterrup(void) {
//Activer le bit d'interruption périphérique et le bit d'interruption globale
INTCON |= 0xC0;
//Activer l'interruption ADC
PIE1 |= 0x40;
//Effacer le bit d'interruption ADC
PIR1 &= ~0x40;
}

//Attendre ~x millisecondes
void delai_approx(int milSec) {
for(int i=0; i<milSec; i++)
__delay_ms(1);
}

void resetInterrupt(void) {1
ADCON0 |= 0x02;
//Effacer le bit d'interruption ADC
PIR1 &= ~0x40;
}

void timer2() {
//Définir le diviseur à 16 et activer le timer et le postscaler 1, mais ce n'est pas utile pour PWM
T2CON |= 0x06;
//Définir l'interruption du timer 2
PIR1 &= ~0x02;
//Définir le PR2 du timer 2
PR2 = 255;
}

void setPWMLed0() {
//Définir la led pour PWM
RD0PPS = 0x0F;
//Activer le PWM
PWM4CON = 0x80;
//Définir la valeur à 0
PWM4DCH = 0;
PWM4DCL &= ~0xC0;
}

void __interrupt() isr (void) {
//Vérifier uniquement l'interruption ADC
if(PIR1 & 0x40) {
    //PR2 ne fait que 8 bits de longueur, donc nous devons ignorer les deux derniers bits pour l'adapter
    PWM4DCH = ((ADRESH & 0x03) << 6) + (ADRESL / 4);
        
        resetInterrupt();
    }
}

void main(void) {
setupLeds();
configPortA();
configADCModule();
configADCInterrup();
//Attendre 1 ms pour le temps d'acquisition
delai_approx(1);
resetInterrupt();
timer2();
setPWMLed0();
while(1) {}
}
