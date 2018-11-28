

#include "adc.h"
#include <avr/io.h>
#include <Arduino.h>

//#include "timer.h"

void initADC7(){
  // set voltage references to be AVCC
  ADMUX |= (1 << REFS0);
  ADMUX &= ~(1 << REFS1);

  // ADLAR = 0 (RIGHT JUSTIFIED)
  ADMUX &= ~(1 << ADLAR);

  // Set A0
  ADMUX &= ~(1 << MUX0 | 1 << MUX1 | 1 << MUX2 | 1 << MUX3 | 1 << MUX4 | 1 << MUX5);
  // set Auto Trigger Source Selection
  // set to free-running mode ADTS[2:0] = 0b000
  // 
  ADCSRB &= ~(1 << ADTS2 | 1 << ADTS1 | 1 << ADTS0);

  // enable auto-triggering and turn-on ADC
  ADCSRA |= (1 << ADATE) | (1 << ADEN);

  // set the pre-scaler to 128
  // Sampling frequency is 16 Mhz divided by pre-scaler = 125KHz
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  // disable ADC0 pin digital input - pin A0 on board
  DIDR0 |= (1 << ADC7D);

  // start the first conversion
  ADCSRA |= (1 << ADSC);
}

void Select(int S0)
{
    int change;
    if(S0 == 0)
    {
        ADMUX &= ~(1 << MUX0 | 1 << MUX1 | 1 << MUX2 | 1 << MUX3 | 1 << MUX4 | 1 << MUX5);
        //return change = 0;
    }
    else if(S0 == 1)
    {
        ADMUX |= (1 << MUX0);
        ADMUX &= ~(1 << MUX1 | 1 << MUX2 | 1 << MUX3 | 1 << MUX4 | 1 << MUX5);
        //return change = 1;
    }
    else if(S0 == 2)
    {
        ADMUX |= (1 << MUX1);
        ADMUX &= ~(1 << MUX0 | 1 << MUX2 | 1 << MUX3 | 1 << MUX4 | 1 << MUX5);
        //return change = 2;
    }
    else if(S0 == 3)
    {
        ADMUX |= (1 << MUX0) | (1 << MUX1);
        ADMUX &= ~(1 << MUX2 | 1 << MUX3 | 1 << MUX4 | 1 << MUX5);
        //return change = 3;
    }
    else{
        Serial.println("We are no entering in select");
    }
}

void IsEqual(int v1, int v2, int v3, int v4)
{ 
    if(v1 > (v2 + .1)) //v2 need to move to the light
    {
        //move servo by 1 degree the right
        //delay
        
    }
    if(v2 > (v1 + .2))
    {
        //move sevo by 1 degree to the left
    }
    if(v1 > (v3 + .2))
    {
        //move servo up
    }
    if(v3 > (v1 + .2))
    {
        //move servo down
    }
    if(v2 > (v4 + .2))
    {
        //move servo up
    }
    if(v4 > (v2 + .2))
    {
        //move servo up
    }
    if(v3 > (v4 + .2))
    {
        //move servo right
    }
    if(v4 > (v3 + .2))
    {
        //move servo to the left
    }
}
