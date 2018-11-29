


#include "i2c.h"
#include "Arduino.h"
#include <avr/io.h>
#include "Wire.h"

 

typedef enum i2c_internal_state_enum{
  start, i2c_address,i2c_addressW, i2c_addressR, data0, stop, i2c_reg, 
} i2c_internal_state;

volatile unsigned int count = 0;

// MCP9808 I2C address is 0x18(24)
#define Addr 0x18

void i2cInit(){   
  // Initialise I2C communication as MASTER  
  Wire.begin();  
  // Initialise Serial Communication, set baud rate = 9600  
 // Serial.begin(9600);    
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
  // Select resolution register  
  Wire.write(0x08);  
  // Resolution = +0.0625 / C  
  Wire.write(0x03);  
  // Stop I2C Transmission  
  Wire.endTransmission();
}

int getTemp(){  
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
  if(Wire.available() == 2) {    
    data[0] = Wire.read();    
    data[1] = Wire.read();  
  }    
  // Convert the data to 13-bits  
  unsigned int temp = ((data[0] & 0x1F) * 256 + data[1]);  
  if(temp > 4095) {    
    temp -= 8192;  
  }  
  return temp;
}

float convertC(int ffTemp){
  float cTemp = ffTemp * 0.0625;
  // Output data to screen  
 return cTemp;
}
float convertF(int cTemp){
  float ffTemp = cTemp * 1.8 + 32;    
  // Output data to screen  
  return ffTemp;
 
}


