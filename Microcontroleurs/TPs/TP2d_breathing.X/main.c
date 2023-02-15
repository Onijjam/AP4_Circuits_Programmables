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
int inc = 1;

void setupLeds(void) {
//Définir la led 0 en entrée
TRISD &= ~0x0F;
TRISB &= ~0x0F;
}

void configTimer2Interrup(void) {
//Activer le bit d'interruption périphérique et le bit d'interruption globale
INTCON |= 0xC0;
}

void delai_approx(int milSec) {
for(int i=0; i<milSec; i++)
__delay_ms(1);
}

void timer2() {
    //Définir timer2 pour déclencher une interruption après 1ms
    //Définir le diviseur à 16 et activer le timer et le postscaler 1
    T2CON |= 0x06;
    //Activer l'interruption du timer2
    PIE1 |= 0x02;
    //Définir l'interruption du timer 2
    PIR1 &= ~0x02;
    //Définir le PR2 du timer 2
    PR2 = 249;
}

void setPWMLed0() {
    //Définir la led pour PWM
    RD0PPS = 0x0F;
    RD1PPS = 0x0F;
    RD2PPS = 0x0F;
    RD3PPS = 0x0F;
    RB0PPS = 0x0F;
    RB1PPS = 0x0F;
    RB2PPS = 0x0F;
    RB3PPS = 0x0F;
    //Activer le PWM
    PWM4CON = 0x80;
    //Définir la valeur à 0
    PWM4DCH = 0;
    PWM4DCL &= ~0xC0;
}

void __interrupt() isr (void) {
    if(PIR1 & 0x02)
    {
        if(PWM4DCH == 250)
        inc = 0;
        if(PWM4DCH == 0 && PWM4DCL == 0)
        inc = 1;
         if(inc)
                if(PWM4DCL & 0x80)
                {
                    PWM4DCL &= ~0xC0;
                    PWM4DCH++;
                }
                else
                    PWM4DCL+=0x80;
            else
                if(PWM4DCL == 0)
                {
                    PWM4DCH--;
                    PWM4DCL |= 0x80;
                }
                else
                    PWM4DCL-=0x80;
            PIR1 &= ~0x02;
    }
}

void main(void) {
setupLeds();
configTimer2Interrup();
delai_approx(1);
timer2();
setPWMLed0();
while(1) {}
}
