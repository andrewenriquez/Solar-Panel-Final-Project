/// Author:        Andrew Enriquez & Rachael Seedenburg & Zahra Sadeq, Sahachel Flores 
// Net ID:         andrewenriquez, zahrasadeq,rtseeden, sflores1
// Date:           11/24/2018
// Assignment:     Final Project
//------------------------------------------------------------------//
#include <Arduino.h>
#include "updownPWM.h"
#include <avr/io.h>
#include "timer.h"
void initPWMTimer4() {
    DDRH |= (1 << DDH3); //pin 6 on dev board

    // set Fast PWM 10-bit mode, non-inverting
    TCCR4A |= (1 << COM4A1) | (1 << WGM41) | (1 << WGM40);
    TCCR4B |= (1 << WGM42) | (1 << CS41) | (1 << CS40);
}

void setServoDegreeUD(unsigned int degree) {
    if (degree > 72) {//With how the top servo is built if it rotates past this degree it will hit the structure
        degree = 72;
    }
    else if (degree < 4) {
        degree = 2;//make sure that it is not negative
    }
    OCR4A = ceil((2.83 * degree) + 100);//set OCRnA to the appropriate value given the degree
  
}
void moveToUD(int originalposition, int newposition){//same as the function in left right PWM if move the servo from one position to another
if(newposition>originalposition){
    for(unsigned int j=originalposition;j<=newposition;j++){
    setServoDegreeUD(j);

        for(unsigned int i=0;i<25000;i++){
            delayMs(1);
        }
    }
}
else{
     for(unsigned int j=originalposition;j>=newposition;j--){
    setServoDegreeUD(j);

        for(unsigned int i=0;i<25000;i++){
            delayMs(1);
        }
    }
}
}