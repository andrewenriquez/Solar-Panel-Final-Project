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


<<<<<<< HEAD
/* typedef enum stateType_enum {
  wait_press, debounce_press, wait_release, debounce_release, count_sec
} stateType; */

//change pin is used to switch from the pin we taking measument from and c stands for count
volatile int changePin = 0, c = 0; 
//these veriables will store the valtage values
volatile float v0 = 0, v1 = 0, v2 = 0, v3 = 0;


int main() {

  initPWMTimer4();
  //initTimer1();
  //initTimer0();
  initADC();
  //initSwitchPB3();
  initI2CMaster();

  initPWMTimer5();

Serial.begin(9600);

sei();
  
  
  while (1) {
    //delayMs(1000);f
   //ADXL_I2C(0x18, 0x18, 0x02);
   //sendData(0x18, 0x02);
   delayMs(100);
   setServoDegree5(45);
   setServoDegree(90);
  
  }


  return 0;
}


ISR(TIMER1_COMPA_vect){
  
  //this is how we take the 1 seconds sample rate from the adc, we are basically calling the timer 100 times
  //change where the 100 is position to increase the sample rate
  //we can use the values of v0, v1, v2, and v3 to move the servos
    if(c  < 100){
      c++;
      }
    else{
         //after calling timer 100 times, we take our samples and reset the variable c
         c = 0;
         Serial.println("Taking Samples");

         //here we are taking all 4 samples at the same time

        //we are at piin 0
         if(changePin == 0){
            v0 = sampleADC(changePin);
            Serial.println("result for V0");
            Serial.println(v0);
            //transition to next pin
            changePin = 1;
          }
        // we are at pin 1
        if(changePin == 1){

            v1 = sampleADC(changePin);
            Serial.println("result for V1");
            Serial.println(v1);
            //transiton to next pin ...and so on
            changePin = 2;
            
          }

          if(changePin == 2){

            v2 = sampleADC(changePin);
            Serial.println("result for V2");
            Serial.println(v2);
            changePin = 3;
          }

          if(changePin == 3){

            v3 = sampleADC(changePin);
            Serial.println("result for V3");
            Serial.println(v3);
            changePin = 0;
            Serial.println("\n");
          }  
          
        
      }
}



/*
=======
>>>>>>> 386687adb1d0e8f6879e723b3594bfe5eb2a1fcd
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
   } 
    */

