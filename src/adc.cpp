<<<<<<< HEAD
/// Author:        Andrew Enriquez & Rachael Seedenburg & Zahra Sadeq, Sahachel Flores 
// Net ID:         andrewenriquez, zahrasadeq,rtseeden, sflores1
// Date:           11/24/2018
// Assignment:     Final Project
//------------------------------------------------------------------//
=======

>>>>>>> 4e813584e9ab304c2264d2106ed77fafe33b1d34

#include "adc.h"
#include <avr/io.h>
#include <Arduino.h>
//#include "timer.h"

void initADC(){
	// set voltage references to be AVCC
	  ADMUX |= (1 << REFS0);
	  ADMUX &= ~(1 << REFS1);
      
	// ADLAR = 0 (RIGHT JUSTIFIED)
	  ADMUX &= ~(1 << ADLAR);
	
    // Set A0
	  ADMUX &= ~((1 << MUX0) | (1 << MUX1) | (1 << MUX2) | (1 << MUX3) | (1 << MUX4));
	  ADCSRB &= ~(1 << MUX5);

	//enable ADC
	  ADCSRA |= (1 << ADEN);
	//disable auto trigger, do single conversions and wait 	//until conversion is complete
	  ADCSRA &= ~(1 << ADATE);
	
	  // set the pre-scaler ADC clock to 128
	  // ADC clock frequency is 16 Mhz divided by pre-scaler = 125KHz
	  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
	  // disable ADC0 pin digital input - pin A0 on board
	   DIDR0 |= (1 << ADC3D) | (1 << ADC2D) | (1 << ADC1D) | (1 << ADC0D);
}

<<<<<<< HEAD
=======

//thi function will be used to take samples from the 4 different 4 pins.
//selectPin determine the pin we are taking measument from and return the values in voltage form

float sampleADC(int selectPin){
  
    if(selectPin == 0)
    {
        //pin A0
        ADMUX &= ~(1 << MUX0 | 1 << MUX1 | 1 << MUX2 | 1 << MUX3 | 1 << MUX4 | 1 << MUX5);
    }
    else if(selectPin == 1)
    {
        //pint A1
        ADMUX |= (1 << MUX0);
        ADMUX &= ~(1 << MUX1 | 1 << MUX2 | 1 << MUX3 | 1 << MUX4 | 1 << MUX5);
    }
    else if(selectPin == 2)
    {
        //pin A2
        ADMUX |= (1 << MUX1);
        ADMUX &= ~(1 << MUX0 | 1 << MUX2 | 1 << MUX3 | 1 << MUX4 | 1 << MUX5);
    }
    else if(selectPin == 3)
    {
        //pin A3
        ADMUX |= (1 << MUX0) | (1 << MUX1);
        ADMUX &= ~(1 << MUX2 | 1 << MUX3 | 1 << MUX4 | 1 << MUX5);
    }
>>>>>>> 4e813584e9ab304c2264d2106ed77fafe33b1d34

//thi function will be used to take samples from the 4 different 4 pins.
//selectPin determine the pin we are taking measument from and return the values in voltage form

<<<<<<< HEAD
float sampleADC(int selectPin){
  
    if(selectPin == 0)
    {
        //pin A0
        ADMUX &= ~(1 << MUX0 | 1 << MUX1 | 1 << MUX2 | 1 << MUX3 | 1 << MUX4 | 1 << MUX5);
    }
    else if(selectPin == 1)
    {
        //pint A1
        ADMUX |= (1 << MUX0);
        ADMUX &= ~(1 << MUX1 | 1 << MUX2 | 1 << MUX3 | 1 << MUX4 | 1 << MUX5);
    }
    else if(selectPin == 2)
    {
        //pin A2
        ADMUX |= (1 << MUX1);
        ADMUX &= ~(1 << MUX0 | 1 << MUX2 | 1 << MUX3 | 1 << MUX4 | 1 << MUX5);
    }
    else if(selectPin == 3)
    {
        //pin A3
        ADMUX |= (1 << MUX0) | (1 << MUX1);
        ADMUX &= ~(1 << MUX2 | 1 << MUX3 | 1 << MUX4 | 1 << MUX5);
    }
    else if(selectPin == 4)
    {
        ADMUX |= (1 << MUX2);
        ADMUX &= ~(1 << MUX0 | 1 << MUX1 | 1 << MUX3 | 1 << MUX4 | 1 << MUX5);

    }


 // start the first conversion
  ADCSRA |= (1 << ADSC);

//wait for conversion to finish, this  way you  dont use interrupt  
  while(ADCSRA & (1 << ADSC)){}


  //we are returning the value in voltage form
  unsigned int result = ADCL;
  result +=((unsigned int)ADCH) << 8;
  return (float)result/1024*5;

}
=======
 // start the first conversion
  ADCSRA |= (1 << ADSC);

//wait for conversion to finish, this  way you  dont use interrupt  
  while(ADCSRA & (1 << ADSC)){}


  //we are returning the value in voltage form
  unsigned int result = ADCL;
  result +=((unsigned int)ADCH) << 8;
  return (float)result/1024*5;

}



>>>>>>> 4e813584e9ab304c2264d2106ed77fafe33b1d34
