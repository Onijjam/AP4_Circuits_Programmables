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

/*Permet de r�p�ter une action pour simuler une attente (peu pr�cis mais universel)*/
void delai_approx(void) {
    for(int i=0; i<1000; i++){
        for(int i=0; i<50; i++){
        
        }
    }
}

void main(void) {
    /* Code d'initialisation */
    /*Mise en Output des LEDS*/
    TRISD &= 0xF0;
    TRISB &= 0xF0;
    /*On allume de D1 � D4 de mani�re individuel et on �teins de D5 � D8 | On initialise le cas zero*/
    LATD |= (1 << 3) + (1 << 2) + (1 << 1) + 1;
    LATB &= ~((1 << 3) + (1 << 2) + (1 << 1) + 1);
    
    while(1){
        /* Code a executer dans une boucle infinie */
        /*On met un delai pour attendre les 0,5 secondes*/
        delai_approx();
        /*On inverse l'�tat des deux set de LED pour donner l'effet de blink*/
        LATD ^= (1 << 3) + (1 << 2) + (1 << 1) + 1;
        LATB ^= (1 << 3) + (1 << 2) + (1 << 1) + 1;
    }
}

