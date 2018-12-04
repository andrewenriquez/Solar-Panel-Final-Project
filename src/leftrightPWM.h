/// Author:        Andrew Enriquez & Rachael Seedenburg & Zahra Sadeq, Sahachel Flores 
// Net ID:         andrewenriquez, zahrasadeq,rtseeden, sflores1
// Date:           11/24/2018
// Assignment:     Final Project
//------------------------------------------------------------------//

#ifndef LEFTRIGHTPWM_H
#define LEFTRIGHTPWM_H

#include <avr/io.h>
#include <math.h>
void initPWMTimer3();
void setServoDegree2(unsigned int degree);
void moveTo2(int originalposition, int newposition);
#endif