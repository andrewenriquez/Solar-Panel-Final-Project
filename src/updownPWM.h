/// Author:        Andrew Enriquez & Rachael Seedenburg & Zahra Sadeq, Sahachel Flores 
// Net ID:         andrewenriquez, zahrasadeq,rtseeden, sflores1
// Date:           11/24/2018
// Assignment:     Final Project
//------------------------------------------------------------------//

#ifndef UPDOWNPWM_H
#define UPDOWNPWM_H

#include <avr/io.h>
#include <math.h>
//void initPWMTimer1();

void initPWMTimer4();

void turnOFF();

void turnON();

void PWMChangeFrequency();
void setServoDegreeUD(unsigned int degree);
//void delayUs(unsigned int delay);
void moveToUD(int originalposition, int newposition);
#endif