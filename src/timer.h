/// Author:        Andrew Enriquez & Rachael Seedenburg & Zahra Sadeq, Sahachel Flores 
// Net ID:         andrewenriquez, zahrasadeq,rtseeden, sflores1
// Date:           11/24/2018
// Assignment:     Final Project
//------------------------------------------------------------------//

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void initTimer1();
//void delayUs(unsigned int delay); //doesnt seem to work.

void initTimer0();
void delayMs(unsigned int delay);

#endif