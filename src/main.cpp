/// Author:        Andrew Enriquez & Rachael Seedenburg & Zahra Sadeq, Sahachel Flores 
// Net ID:         andrewenriquez, zahrasadeq,rtseeden, sflores1
// Date:           11/24/2018
// Assignment:     Final Project
//------------------------------------------------------------------//

#include <Arduino.h>
#include "timer.h"
#include "updownPWM.h"
#include "leftrightPWM.h"
#include "adc.h"
#include <math.h>
#include<Wire.h>

// MCP9808 I2C address is 0x18(24)
#define Addr 0x18

//change pin is used to switch from the pin we taking measument from and c stands for count
volatile int changePin = 0, c = 0, solarPin = 4; 
//these veriables will store the voltage values
volatile float v0 = 0, v1 = 0, v2 = 0, v3 = 0, solarVoltage;

volatile float vTop = 0, vBottom = 0, vLeft = 0, vRight = 0; 

typedef enum i2c_internal_state_enum{
  wait, moveUp, moveDown, moveLeft, moveRight,
} internal_move_state;

int main (){
  //initialize devices
  sei();
  initPWMTimer3();
  initPWMTimer4();
  initTimer0();
  initTimer1();
  initADC();
  Serial.begin(9600);

  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(9600);
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select configuration register
  Wire.write(0x01);
  // Continuous conversion mode, Power-up default
  Wire.write(0x00);
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select resolution rgister
  Wire.write(0x08);
  // Resolution = +0.0625 / C
  Wire.write(0x03);
  // Stop I2C Transmission
  Wire.endTransmission();

  //initializing into the first state
  internal_move_state move_state = wait;

  //default state for the left and right moving servo
  int leftRightDef = 90;
  int leftRightNew = leftRightDef;  
  //default state for the up and down moving servo
  int upDownDef = 40;
  int upDownNew = upDownDef;

  //threshold voltage for the photoresitors
  float threshVol = 0.75;

  //moving servos into default states
  setServoDegreeLR(leftRightDef);
  setServoDegreeUD(upDownDef);

  while(1){

      delayMs(10);

      unsigned int data[2];

      // Starts I2C communication
      Wire.beginTransmission(Addr);
      // Select data register
      Wire.write(0x05);
      // Stop I2C transmission
      Wire.endTransmission();
      
      // Request 2 bytes of data
      Wire.requestFrom(Addr, 2);
      
      // Read 2 bytes of data
      // temp MSB, temp LSB
      if(Wire.available() == 2)
      {
        data[0] = Wire.read();
        data[1] = Wire.read();
      }
      
      // Convert the data to 13-bits
      int temp = ((data[0] & 0x1F) * 256 + data[1]);
      if(temp > 4095)
      {
        temp -= 8192;
      }
      
      float cTemp = temp * 0.0625;
      float fTemp = cTemp * 1.8 + 32;
      

    switch(move_state){
      
      case wait:
        delayMs(500);
        // Output data to screen
        Serial.print("Temperature in Celsius: ");
        Serial.print(cTemp);
        Serial.println(" C");
        Serial.print("Temperature in Fahrenheit: ");
        Serial.print(fTemp);
        Serial.println(" F");
        Serial.print("result for solar voltate: ");
        Serial.print(solarVoltage);
        Serial.println(" V");

        // If statements in order to determind which state to move to
        if (vTop > vBottom && fabs(vTop - vBottom) > threshVol) {
          move_state = moveUp;
        }
        else if (vTop < vBottom && fabs(vTop - vBottom) > threshVol) {
          move_state = moveDown;
        }

        else if (vLeft > vRight && fabs(vLeft - vRight) > threshVol) {
          move_state = moveLeft;
        }

        else if (vLeft < vRight && fabs(vLeft - vRight) > threshVol) {
          move_state = moveRight;
        }

        else {
          move_state = wait;
        }


        break;

      //moving up state
      case moveUp:

        delayMs(10);
        Serial.println("Move up state");
        moveToUD(upDownDef, upDownNew);
        upDownDef = upDownNew;
        upDownNew = upDownNew + 2;
        if (vTop > vBottom && fabs(vTop - vBottom) > threshVol) {
          move_state = moveUp;
        }
        else {
          move_state = wait;
        }

        break;

      //moving down state
      case moveDown:
        delayMs(10);
        Serial.println("Move down state");
        moveToUD(upDownDef, upDownNew);
        upDownDef = upDownNew;
        upDownNew = upDownNew - 2;
        if (vTop < vBottom && fabs(vTop - vBottom) > threshVol) {
          move_state = moveDown;
        }
        else {
          move_state = wait;
        }
        break;

      //moving down state
      case moveLeft:
        delayMs(10);
        Serial.println("move left state");
        moveToLR(leftRightDef, leftRightNew);
        leftRightDef = leftRightNew;
        leftRightNew = leftRightNew - 2;
        if (vLeft > vRight && fabs(vLeft - vRight) > 1.0) {
          move_state = moveLeft;
        }
        else {
          move_state = wait;
        }
        break;

      //moving right state
      case moveRight:
        delayMs(10);
        Serial.println("move Right state");
        moveToLR(leftRightDef, leftRightNew);
        leftRightDef = leftRightNew;
        leftRightNew = leftRightNew + 2;
        if (vLeft < vRight && fabs(vLeft - vRight) > 1.0) {
          move_state = moveRight;
        }
        else {
          move_state = wait;
        }
        break;
  }
  }

return 0;
}

//ISR is used to take adc measurements are different intervals depending on the codition of c in the if 
//statement
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
         //Serial.println("Taking Samples");

         //here we are taking all 4 samples at the same time

        //we are at piin 0
         if(changePin == 0){
            v0 = sampleADC(changePin);
            //Serial.println("result for V0");
            //Serial.println(v0);
            //transition to next pin
            changePin = 1;
          }
        // we are at pin 1
        if(changePin == 1){

            v1 = sampleADC(changePin);
            //Serial.println("result for V1");
            //Serial.println(v1);
            //transiton to next pin ...and so on
            changePin = 2;
            
          }

          if(changePin == 2){

            v2 = sampleADC(changePin);
            //Serial.println("result for V2");
            //Serial.println(v2);
            changePin = 3;
          }

          if(changePin == 3){

            v3 = sampleADC(changePin);
            //Serial.println("result for V3");
            //Serial.println(v3);
            changePin = 0;
            //Serial.println("\n");
          }  
          if(solarPin == 4){
            solarVoltage = sampleADC(solarPin);
            //Serial.println("result for solar voltate");
            //Serial.println(solarVoltage);

          }
          
          vTop = v0 + v1;
          vBottom = v2 + v3;
          vLeft = v0 + v2;
          vRight = v1 + v3;

          //Serial.println("result for vTop");
          //Serial.println(vTop);
      }
}
