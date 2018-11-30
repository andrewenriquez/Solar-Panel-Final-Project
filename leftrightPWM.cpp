
/// Author:        Andrew Enriquez & Rachael Seedenburg, 
// Net ID:         andrewenriquez, 
// Date:           10/24/2018
// Assignment:     Lab 4
//------------------------------------------------------------------//
#include <Arduino.h>
#include "leftrightPWM.h"
#include <avr/io.h>
#include "timer.h"
void initPWMTimer3() {
    DDRE |= (1 << DDE3); //pin 5 on dev board

    // set Fast PWM 10-bit mode, non-inverting
    TCCR3A |= (1 << COM3A1) | (1 << WGM31) | (1 << WGM30);
    TCCR3B |= (1 << WGM32) | (1 << CS31) | (1 << CS30);
}

void setServoDegree2(unsigned int degree) {
    if (degree > 175) {
        degree = 180;
    }
    else if (degree < 0) {
        degree = 0;
    }
    OCR3A = ceil((2.83 * degree) + 100);//To set the degree that we want to move to the appropiate OCRnA value
    
}
void moveTo2(int originalposition, int newposition){// to move the servo from one position to another
if(newposition>originalposition){// determining which way the servo has to move counter clockwise or clockwise
    for(unsigned int j=originalposition;j<=newposition;j++){
    setServoDegree2(j);

        for(unsigned int i=0;i<25000;i++){
            delayMs(1);// have to give a delay for the servo to move properly This is the delay that I found to be the smoothest moving
        }
    }
}
else{//to move in the clockwise direction
     for(unsigned int j=originalposition;j>=newposition;j--){
    setServoDegree2(j);

        for(unsigned int i=0;i<25000;i++){
            delayMs(1);
        }
    }
}
}

