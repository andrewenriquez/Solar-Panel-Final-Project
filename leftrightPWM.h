#ifndef LEFTRIGHTPWM_H
#define LEFTRIGHTPWM_H

#include <avr/io.h>
#include <math.h>
void initPWMTimer2();
void setServoDegree2(unsigned int degree);
void moveTo2(int originalposition, int newposition);
#endif