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
        /*On met une valeur de départ à TMRO*/
        TMR0 = 6;
        /*On met bien TMR0IF à 0*/
        INTCON &= ~0x04;
        /*On lit le bit de TMR0IF pour savoir quand il a fait un cyle (doit être à 1)*/
        while(!(INTCON & 0x04)){
            
        }
    }
}

void main(void) {
    /* Code d'initialisation */
    /*On paramètre le prescaler à 32*/
    OPTION_REG &= ~(0x2F);
    OPTION_REG |= 0x04;
    
    /*Mise en Output des LEDS*/
    TRISD &= 0xF0;
    TRISB &= 0xF0;
    /*On allume de D1 à D4 de manière individuel et on éteins de D5 à D8 | On initialise le cas zero*/
    LATD |= (1 << 3) + (1 << 2) + (1 << 1) + 1;
    LATB &= ~((1 << 3) + (1 << 2) + (1 << 1) + 1);
    
    while(1){
        /* Code a executer dans une boucle infinie */
        /*On met un delai pour attendre les 0,5 secondes*/
        delai_approx();
        /*On inverse l'état des deux set de LED pour donner l'effet de blink*/
        LATD ^= (1 << 3) + (1 << 2) + (1 << 1) + 1;
        LATB ^= (1 << 3) + (1 << 2) + (1 << 1) + 1;
    }
}