#include "config_EUSART.h"

void registerConfig(void) {
    // Connecter RC6 à TX/CK
    RC6PPS = 0x14;
    // Connecter RC7 à RX
    RXPPS = 0x17;
}

void inputOutput(void) {
    // Sortie RC6
    TRISC &= ~0x40;
    // Entrée numérique RC7
    TRISC |= 0x80;
    ANSELC &= ~0x80;
}

void configTerminal(void) {
    // Mode asynchrone et set BRGH à 0
    TX1STA &= ~0x14;
    TX1STA |= 0x20;
    // Définir le taux de bits à 16
    BAUD1CON = 0x08;
    // Définir SP1BR à 119 pour 18.432 MHz
    SP1BRGH = 0;
    SP1BRGL = 51;
}

void activateUART(void) {
    // Activer le port série et activer le récepteur
    RC1STA |= 0x90;
    // Bit d'activation de transmission
    TX1STA |= 0x20;
}

void write(char data) {
    TX1REG = data;
}

void writeString(const char* string) {
    int i = 0;
    while(string[i] != '\0') {
        write(string[i]);
        delai_approx(3); // Attendre 3 ms
        i++;
    }
}

char read(void) {
    return RC1REG;
}

void delai_approx(int milSec) {
    for(int i=0; i<milSec; i++)
    __delay_ms(1);
}


void setup(void) {
    registerConfig();
    inputOutput();
    configTerminal();
    activateUART();
}