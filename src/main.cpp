#include <Arduino.h>
#include "timer.h"
#include "updownPWM.h"
#include "leftrightPWM.h"
#include "adc.h"
#include <math.h>

//change pin is used to switch from the pin we taking measument from and c stands for count
volatile int changePin = 0, c = 0, solarPin = 4; 
//these veriables will store the valtage values
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

  

  internal_move_state move_state = wait;


  int leftRightDef = 60;
  int leftRightNew = leftRightDef;  
  int upDownDef = 35;
  int upDownNew = upDownDef;
  float threshVol = 1.0;
  setServoDegree2(leftRightDef);
  setServoDegree(upDownDef);

  while(1){

    switch(move_state){
      
      case wait:
        delayMs(10);
        //Serial.println("wait state");
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

      case moveUp:

        delayMs(10);
        Serial.println("Move up state");
        moveTo(upDownDef, upDownNew);
        upDownDef = upDownNew;
        upDownNew = upDownNew + 2;
        if (vTop > vBottom && fabs(vTop - vBottom) > threshVol) {
          move_state = moveUp;
        }
        else {
          move_state = wait;
        }

        break;

      case moveDown:
        delayMs(10);
        Serial.println("Move down state");
        moveTo(upDownDef, upDownNew);
        upDownDef = upDownNew;
        upDownNew = upDownNew - 2;
        if (vTop < vBottom && fabs(vTop - vBottom) > threshVol) {
          move_state = moveDown;
        }
        else {
          move_state = wait;
        }
        break;

      case moveLeft:
        delayMs(10);
        Serial.println("move left state");
        //Serial.println("Move down state");
        moveTo2(leftRightDef, leftRightNew);
        leftRightDef = leftRightNew;
        leftRightNew = leftRightNew - 2;
        if (vLeft > vRight && fabs(vLeft - vRight) > 1.0) {
          move_state = moveLeft;
        }
        else {
          move_state = wait;
        }
        break;

      case moveRight:
        delayMs(10);
        Serial.println("move Right state");
        moveTo2(leftRightDef, leftRightNew);
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
          if(solarPin == 4){
            solarVoltage = sampleADC(solarPin);
            Serial.println("result for solar voltate");
            Serial.println(solarVoltage);

          }
          
          vTop = v0 + v1;
          vBottom = v2 + v3;
          vLeft = v0 + v2;
          vRight = v1 + v3;

          //Serial.println("result for vTop");
          //Serial.println(vTop);
      }
}
