#ifndef PWM_H
#define PWM_H

#include <avr/io.h>

//void initPWMTimer1();

void initPWMTimer4();

void turnOFF();

void turnON();

void PWMChangeFrequency();

void initPWMTimer1();
void setServoDegree(unsigned int degree);
void initPWMTimer5();
void setServoDegree5(unsigned int degree);
//void delayUs(unsigned int delay);

#endif