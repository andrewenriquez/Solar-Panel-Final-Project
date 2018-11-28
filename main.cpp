#include <Arduino.h>
#include "timer.h"
#include "updownPWM.h"
#include "leftrightPWM.h"
#include "adc.h"
#include <math.h>
int main (){
  initPWMTimer1();
  initPWMTimer2();
   // initialize devices
  initTimer0();
initADC7();
  Serial.begin(9600);
  unsigned int result1 = 0, result2 = 0, result3 = 0, result4 = 0;
  int changeResult = 0;
  unsigned int A0,A1,A2,A3;
  /*while(1){
    moveTo(0,72);
    moveTo2(0,180);
  }*/


  while(1){
     
    if(changeResult == 3)
  {
    result4 = ADCL;
    result4 += ((unsigned int)ADCH) << 8;
    A3=(float)result4/1024.00 *5.0;
    Serial.println((float)result3/1024.00 *5.00);
    Serial.println("result for A3");
    changeResult = 0;
      if((fabs(A0-A1)>=1.5)&&changeResult==0){
   moveTo(0,45);
}
  }


  else if(changeResult == 2)
  {
    result3 = ADCL;
    result3 += ((unsigned int)ADCH) << 8;
    A2=(float)result3/1024.00 *5.0;
    Serial.println((float)result2/1024.00 *5.00);
    Serial.println("result for A2");
    changeResult = 3;
  }
 
  else if(changeResult == 1)
  {
    result2 = ADCL;
    result2 += ((unsigned int)ADCH) << 8;
    A1=(float)result2/1024.00 *5.0;
    Serial.println((float)result1/1024.00 *5.00);
    Serial.println("result for A1");
    changeResult = 2;
  }

  else if (changeResult == 0)
  {
    result1 = ADCL;
    result1 += ((unsigned int)ADCH) << 8;
    
    A0=(float)result1/1024.00 *5.0;
    Serial.println((float)result1/1024.00 *5.00);
    Serial.println("result for A0");
    changeResult = 1;

  }

  Select(changeResult);
  //IsEqual(result1, result2, result3, result4);

  // if((fabs(A0-A1)>=1.5)&&changeResult==0){
  //moveTo(0,45);


  }


return 0;
}
