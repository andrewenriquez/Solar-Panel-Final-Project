/// Author:        Andrew Enriquez, Rachel, Zahra, Sahchel
// Net ID:         andrewenriquez, 
// Date:           10/24/2018
// Assignment:     Final Project
//----------------------------------------------------------------------//


#ifndef ADC_H
#define ADC_H


#include <avr/io.h>

void initADC();
float sampleADC(int selectPin);

#endif
