
/// Author:        Andrew Enriquez & Rachael Seedenburg, 
// Net ID:         andrewenriquez, 
// Date:           10/24/2018
// Assignment:     Lab 4
//------------------------------------------------------------------//
#include <Arduino.h>
#include "updownPWM.h"
#include <avr/io.h>
#include "timer.h"
void initPWMTimer1() {
    DDRB |= (1 << DDB5); //pin 11 on dev board

    // set Fast PWM 10-bit mode, non-inverting
    TCCR1A |= (1 << COM1A1) | (1 << WGM11) | (1 << WGM10);
    TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
}

void setServoDegree(unsigned int degree) {
    if (degree > 72) {//With how the top servo is built if it rotates past this degree it will hit the structure
        degree = 72;
    }
    else if (degree < 0) {
        degree = 0;//make sure that it is not negative
    }
    OCR1A = ceil((2.83 * degree) + 100);//set OCRnA to the appropriate value given the degree
  
}
void moveTo(int originalposition, int newposition){//same as the function in left right PWM if move the servo from one position to another
if(newposition>originalposition){
    for(unsigned int j=originalposition;j<=newposition;j++){
    setServoDegree(j);

        for(unsigned int i=0;i<25000;i++){
            delayMs(1);
        }
    }
}
else{
     for(unsigned int j=originalposition;j>=newposition;j--){
    setServoDegree(j);

        for(unsigned int i=0;i<25000;i++){
            delayMs(1);
        }
    }
}
}