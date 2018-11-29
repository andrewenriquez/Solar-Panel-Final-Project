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

/**Had to implement an ISR for the 1ms sample rating using timer1.
 * Couldn't figure out how to do it otherwise.
 **/
ISR(ADC_vect){
  
  //result=ADCL;
   //result+=((unsigned int)ADCH) << 8;
  ADCSRA |= (1 << ADSC);
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
    */
}
