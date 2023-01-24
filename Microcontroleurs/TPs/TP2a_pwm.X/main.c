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

void init_timer2(void){
    //On active l'interrupteur sur le timer2
    PIE1 |= 0x02; 
    /*On paramètre le prescaler à 1 et postcaler à 16*/
    T2CON &= ~(0x7F);
    T2CON |= 0x7C;
    PR2 = 124;
}

void init_PWM4(void){
    //PWM4 enable
    PWM4CON |= 0x80;
    //0% = 0; 25% = 125; 50%=250; 75%=375; 100%=500
    PWM4DCL = 0;
    PWM4DCH = 0;
    
}

void init_PPS(void){
    RD0PPS |= 0x0F;
    
    
}

int PMW_change(int count){
    if(count == 0){
        PWM4DCL = 0;
        PWM4DCH = 0;
        count = count+1;
        return count;
    }
    else if (count == 1){
        PWM4DCL = 0x40; // 0001 1111 01
        PWM4DCH = 0x1F; //PWM4DCL + PWMDCH = 125
        count = count+1;
        return count;
    }
    else if (count == 2){
        PWM4DCL = 0x80; // 0011 1110 10
        PWM4DCH = 0x3E; //PWM4DCL + PWMDCH = 250
        count = count+1;
        return count;
    }
    else if (count == 3){
        PWM4DCL = 0x40; // 0101 1101 01
        PWM4DCH = 0x5D; //PWM4DCL + PWMDCH = 375
        count = count+1;
        return count;
    }
    else if (count == 4){
        PWM4DCL = 0x80; // 0111 1100 10
        PWM4DCH = 0x7C; //PWM4DCL + PWMDCH = 500
        count = 0;
        return count;
    }
}

void main(void) {
    /* Code d'initialisation */
    /*Mise en Output des LEDS*/
    TRISA |= 0x20;
    ANSELA &= ~(0x20);
    TRISD &= 0xF0;
    TRISB &= 0xF0;
    
    init_timer2();
    
    init_PWM4();
    
    init_PPS();
    
    
    LATD = 0x01;
    LATB = 0;
    
    int count = 1;
    
    while(1){
        if(!(PORTA & 0x20)){
            while(!(PORTA & 0x20)){
                
            }
            //ici
            count = PMW_change(count);
        }
    }
}