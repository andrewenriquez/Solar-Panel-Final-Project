#ifndef UPDOWNPWM_H
#define UPDOWNPWM_H

#include <avr/io.h>
#include <math.h>
//void initPWMTimer1();

void initPWMTimer4();

void turnOFF();

void turnON();

void PWMChangeFrequency();
void setServoDegree(unsigned int degree);
//void delayUs(unsigned int delay);
void moveTo(int originalposition, int newposition);
#endif