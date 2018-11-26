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
#include "PWM.h"
#include "timer.h" 
#include "adc.h"
#include "i2c.h"
//#include "switch.h"

/*
 * Define a set of states that can be used in the state machine using an enum
 */

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

  

Serial.begin(9600);

sei();
  
  
  while (1) {
    //delayMs(1000);f
   //ADXL_I2C(0x18, 0x18, 0x02);
   sendData(0x18, 0x02);
   delayMs(1000);
  
  
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
int main() {
    // Initialise Serial Communication, set baud rate = 9600 
     
    Serial.begin(9600); 
    i2cInit();
    int temp0;
    float celTemp;
    float fahTemp;
    
    while(1) {
        delay(500);
        temp0 = i2cTemp();
        delay(500);
        celTemp = convertTempC(temp0);
        delay(500);
        fahTemp = convertTempF(temp0);
        delay(500);
        Serial.print("Temperature in Celsius : ");  
        Serial.println(celTemp);  
        Serial.println(" C");  
        Serial.print("Temperature in Fahrenheit : ");  
        Serial.println(fahTemp);  
        Serial.println(" F");

        delay(500);
        

    }
    return 0;
}
*/