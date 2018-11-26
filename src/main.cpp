/// Date:
// Assignment:
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
// Requirements:
//----------------------------------------------------------------------//

#include <avr/io.h>
#include <Arduino.h>
//#include "timer.h" 
//#include "i2c.h"


int main() {
   Serial.begin(9600);
    // Initialise Serial Communication, set baud rate = 9600 
    /*int temp0;
    float cTemp;
    float fahTemp;
    */
   
    Serial.println("initlization"); 
    //delayMs(500);
   /* initTimer1();
    Serial.println("Getting past timer1"); 
    initTimer0();
    Serial.println("Getting past timer0"); 
    i2cInit(); 
    Serial.println("Getting past i2cInit"); 
    Serial.println("Getting past initlization"); 

    while(1) {
        //delay(500);
        temp0 = getTemp();
        Serial.println("Getting past getTemp "); 
        //delay(500);

        cTemp = convertC(temp0);
        Serial.println("Temperature in Celsius : ");  
        Serial.println(cTemp);  
        Serial.println(" C");   
        //delay(500);

        fahTemp = convertF(temp0);
        Serial.println("Temperature in Fahrenheit : ");  
        Serial.println(fahTemp);  
        Serial.println(" F");  
        //delay(500);
    }
    return 0;
    */
}
