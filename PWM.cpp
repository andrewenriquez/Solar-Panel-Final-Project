/// Author:        Andrew Enriquez & Rachael Seedenburg, 
// Net ID:         andrewenriquez, 
// Date:           10/24/2018
// Assignment:     Lab 4
//------------------------------------------------------------------//
#include "PWM.h"

#include <avr/io.h>
#include "timer.h"
void initPWMTimer4(){
  DDRH |= (1 << DDH3); // output to pin 6
TCCR4A |= (1 << COM4A1)|(1 << WGM41)|(1 << WGM40);
TCCR4B |= (1 << WGM42)|(1<<CS40);
OCR4A = 0;
OCR4B=0;

}
void turnOFF(){
OCR4A=0;//Need to adjust this I am not quite sure what frequencies are too low to hear
OCR4B=0;//Needs to be half of OCR4A for 50 percent duty cycle
}

void turnON(){
//TCCR4A |= (1 << COM4A1)|(1 << COM4B1)|(1 << WGM41)|(1<<WGM40);
  //TCCR4B |= (1 << WGM43)|(1 << WGM42)|(1<<CS40);
TCCR4A |= (1 << COM4A1)|(1 << WGM41)|(1 << WGM40);
TCCR4B |= (1 << WGM42)|(1<<CS40);

 /* // Timer 1: Set Fast PWM 10-bit mode, non-inverting
  TCC1A |= (1 << COM1A1)|(1 << WGM11)|(1 << WGM10);
  TCCR1B |= (1 << WGM12)|(1 << CS10);
*/
  // duty cycle  = 25%
  OCR1A = 255;
}

//OCR4A=8000;//Need to adjust this I am not quite sure what frequencies are too low to hear
//OCR4B=4000;
//}
void PWMChangeFrequency(){
    delayMs(10);
    OCR4A += 10000; 
    OCR4B += 10000/2;
  
}