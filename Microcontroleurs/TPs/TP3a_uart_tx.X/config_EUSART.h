/* 
 * File:   config_EUSART.h
 * Author: gautm
 *
 * Created on 15 février 2023, 15:34
 */
#ifndef CONFIG_EUSART_H
#define	CONFIG_EUSART_H
#define _XTAL_FREQ 8000000

#include <xc.h>

void registerConfig(void);
void inputOutput(void);
void configTerminal(void);
void activateUART(void);
void setup(void);
char read(void);
void write(char);
void writeString(const char*);
void delai_approx(int);

#endif
