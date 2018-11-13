#include <Arduino.h>
#include "timer.h"
#include "PWM.h"
#include <Servo.h>
Servo myservo;
int main (){
  initPWMTimer4();
   // initialize devices
  initTimer0();

  while(1){
    
// delay 10 ms
 for(int i=0;i<100;i++)delayMs(1);
    OCR4A += 10;
    OCR4B+=5; 
 if(OCR4A==200){
     OCR4A=0;
     OCR4B=0;
     for(int i=0;i<100;i++)delayMs(1);
 }
// OCR1A controls duty cycle.  Increment duty cycle and it will change pulse width.
  }

  return 0;
}
/*int main(){
    myservo.attach(7);
    myservo.write(90);
    delayMs(10);
    myservo.write(45);

}*/