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

/*Permet de répéter une action pour simuler une attente (peu précis mais universel)*/
void delai_approx(void) {
    /*Doit faire 125 cycle pour avoir 0.5s car il en faut 250 pour faire une 1s avec 32 de prescaler*/
    for(int i=0; i<125; i++){
        /*On met bien TMR2IF à 0*/
        PIR1 &= ~0x02;
        /*On lit le bit de TMR2IF pour savoir quand il a fait un cyle (doit être à 1)*/
        while(!(PIR1 & 0x02)){
            
        }
    }
}

void main(void) {
    /* Code d'initialisation */
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
    
    int count = 1;
    char verif = 'd';
    
    while(1){
        /* Code a executer dans une boucle infinie */
        /*On met un delai pour attendre les 0,125 secondes*/
        delai_approx();
        
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
                count++;
            }
            else{
                LATD |= (1 << count);
                if(count == 1){
                    LATD &= ~1;
                }
                else{
                    LATD &= ~(1 << (count-1));
                }
                count++;
            }
        }
        
        if (verif == 'b'){
            if(count == 0){
                LATD = 0;
                LATB |= 1;
                count++;
            }
            else{
                LATB |= (1 << count);
                if(count == 1){
                    LATB &= ~1;
                }
                else{
                    LATB &= ~(1 << (count-1));
                }
                count++;
            }
        }
        
        
        
        
    }
}