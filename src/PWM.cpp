/// Author:        Andrew Enriquez & Rachael Seedenburg, 
// Net ID:         andrewenriquez, 
// Date:           10/24/2018
// Assignment:     Lab 4
//------------------------------------------------------------------//
#include "PWM.h"

#include <avr/io.h>
#include "timer.h"
void initPWMTimer4(){
  DDRH |= (1 << DDH4); // output to pin 7
  OCR4A=0;


}
void turnOFF(){
OCR4A=0;//Need to adjust this I am not quite sure what frequencies are too low to hear
OCR4B=0;//Needs to be half of OCR4A for 50 percent duty cycle
}
void turnON(){
TCCR4A |= (1 << COM4A1)|(1 << COM4B1)|(1 << WGM41)|(1<<WGM40);
  TCCR4B |= (1 << WGM43)|(1 << WGM42)|(1<<CS40);
OCR4A=8000;//Need to adjust this I am not quite sure what frequencies are too low to hear
OCR4B=4000;
}
void PWMChangeFrequency(){
    delayMs(10);
    OCR4A += 10000; 
    OCR4B =OCR4A/2; 
  
}