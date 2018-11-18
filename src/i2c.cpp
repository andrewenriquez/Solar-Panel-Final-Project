


#include "i2c.h"
#include "Arduino.h"
#include <avr/io.h>

 

typedef enum i2c_internal_state_enum{
  start, i2c_address,i2c_addressW, i2c_addressR, data0, stop, i2c_reg, 
} i2c_internal_state;

volatile unsigned int count = 0;
 
void initI2CMaster(){
  //Make the baud rate as low as possible
  TWSR |= (1 << TWPS0) | (1 << TWPS1);
  TWBR = 255;

  // enable TWI
  TWCR |= (1 << TWINT | 1 << TWEN);
}
void sendData(unsigned char address, unsigned char data){

  i2c_internal_state i2c_state = start;

  unsigned char twi_status;

 

  while(i2c_state != stop){

    twi_status = TWSR & 0xF8;

    switch(i2c_state){

      case start:

        TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

        i2c_state = i2c_address;

        break;

      case i2c_address:

        // start or repeated start

        if(twi_status != 0x10 && twi_status != 0x08){

          i2c_state = start;

        }

        else{
         // TWDR = address; //changed this for SLA+W or SLA+R input
          TWDR = (address << 1);

          TWCR = (1 << TWINT) | (1 << TWEN);

          i2c_state = data0;

        }

        break;

      case data0:

        if(twi_status == 0x20){ // SLA_W sent and NOT ACK Received

          i2c_state = start;

        }

        else{
          //Serial.println(TWDR);
          TWDR = data;
          //Serial.println(TWDR);
          TWCR = (1 << TWINT) | (1 << TWEN);

          i2c_state = stop;

        }

        break;

      case stop:

        if(twi_status == 0x30){ // data sent and NOT ACK Received

          i2c_state = start;

        }

        else{

          TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

        }

        break;

    }

    if(i2c_state != stop){

      while (!(TWCR & (1 << TWINT)));

      if(twi_status == 0x38 || twi_status == 0x00){ // Arbitration loss

        // Serial.println("Arbitration loss or invalid state");

        i2c_state = start;

      }

    }

  }

}
 
/** This code interfaces with the ADXL 345 that was in our sunfounder kit. The data sheet
 * specifies that in order to read data, we first need to start-> SLA+W -> regAddr ->stop/start->
 * SLA+R->Stop
 * 
 * **/
/* void ADXL_I2C(unsigned char addressW, unsigned char addressR, unsigned char regAddress){
  i2c_internal_state i2c_state = start;

  unsigned char twi_status;
  
  while(i2c_state != stop){
    twi_status = TWSR & 0xF8;
    //int count = 0;
    switch(i2c_state){
      case start:
        Serial.println("Case: Start");
        Serial.println(twi_status);
        TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
        Serial.println(count);
        if (count > 0) {
           Serial.println("It's being read");
           i2c_state = i2c_addressR;
           count = 0;
        }
        else {
          i2c_state = i2c_addressW;
        }
        break;

      case i2c_addressW:
        Serial.println("Case: i2c_addressW");
        //Serial.println(twi_status);
        // start or repeated start
        if(count == 0){
           Serial.println("count == 0");
          count = 1;
        }

        if(twi_status != 0x10 && twi_status != 0x08){
          Serial.println("write: 0x10 or 0x08");
          i2c_state = start;
        }
        else{
          //TWDR = (address << 1);
          TWDR = addressW;
          //TWDR |= 0x01;
          TWCR = (1 << TWINT) | (1 << TWEN);
          Serial.println("going to case i2c_reg");
          i2c_state = i2c_reg;
        }
        break;
    case i2c_reg:
        Serial.println("Case: i2c_reg");
        Serial.println(twi_status);
        // start or repeated start
       
        //if(twi_status != 0x10 && twi_status != 0x08){ //original
        if (twi_status != 0x18) { // Not (SLA+W has been transmitted; ACK has been received)
          Serial.println("reg: back to start");
          i2c_state = start;
        }
        else{
          //TWDR = (address << 1);
          TWDR = regAddress;
          //TWDR |= 0x01;
          TWCR = (1 << TWINT) | (1 << TWEN);
          i2c_state = start;
        }
        break;
    case i2c_addressR:
        Serial.println("Case: i2c_addressR");
        //Serial.println(twi_status);
        // start or repeated start
        if(twi_status != 0x10 && twi_status != 0x08){
          i2c_state = start;
        }
        else{
          //TWDR = (address << 1);
          TWDR = addressR;
          Serial.println("set R");
          TWCR = (1 << TWINT) | (1 << TWEN)| (1 << TWEA);
          i2c_state = data0;
        }
        break;

      case data0:
        Serial.println("Case: data0");
        Serial.println(twi_status);
        if(twi_status == 0x48){ // SLA_W sent and NOT ACK Received
          Serial.println("0x48");
          i2c_state = start;
          //Serial.println()
        }
        else{
          //TWDR = data;
          //if (twi_status)
          unsigned int inputData = TWDR;
          Serial.println(inputData);
          TWCR = (1 << TWINT) | (1 << TWEN);
          //Serial.println("i2c_address");
          //Serial.println(TWDR);
          i2c_state = stop;
        }
        break;

      case stop:
      Serial.println("Case: stop");
        Serial.println(twi_status);

        if(twi_status == 0x58){ // data sent and NOT ACK Received
          i2c_state = start;
        }
        else{
          TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
        }
        break;
    }
    if(i2c_state != stop) {
     Serial.println("if statement: ");
     // count += 1;
     Serial.println("twi_status: ");
     Serial.println(twi_status);
     Serial.println("TWCR: ");
     Serial.println(TWCR);
     //Serial.println("TWINT: ");
     //Serial.println(TWINT);
      while (!(TWCR & (1 << TWINT)));
       Serial.println("TWCR: ");
       Serial.println(TWCR);

      if(twi_status == 0x38 || twi_status == 0x00){ // Arbitration loss
        Serial.println("Arbitration loss or invalid state: Going back to Start");
         //count += 1;
        i2c_state = start;
      }
       Serial.println("Getting past the delay while");
    }
  }
} */
/*
#include <Arduino.h>
#include "i2c.h"
#include <avr/io.h>

typedef enum i2c_internal_state_enum {
    start, i2c_address, data0, stop
} i2c_internal_state;

void initI2CMaster() {
    //Baud rate as low as possible
    TWSR |= (1 << TWPS0) | (1 << TWPS1);
    TWBR = 255;

    //enable TWI
    TWCR |= (1 << TWINT | 1 << TWEN);
}
void sendData(unsigned char address, unsigned char data) {

    i2c_internal_state i2c_state = start;
    unsigned char twi_status;

    while (i2c_state != stop) {
        twi_status = TWSR & 0xF8;
        switch(i2c_state) {
            case start:
                
                Serial.println("start");
                TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
                i2c_state = i2c_address;
                Serial.println(twi_status);
                break;
            case i2c_address:
                Serial.println("address");
                if (twi_status != 0x10 && twi_status != 0x08) {
                    //Serial.println(twi_status);
                    i2c_state = start;
                    //i2c_state = stop;
                }
                else {
                    Serial.println("else");
                    TWDR = (address << 1);
                    TWDR |= 0b00000001;
                    TWCR = (1 << TWINT) | (TWEN);
                    i2c_state = data0;
                }
                break;
            case data0:
                Serial.println("data0");
                
                TWDR = data;
                TWCR = (1 << TWINT) | (1 << TWEN);
                
                Serial.println("TWDR");
                i2c_state = stop;
                break;
            case stop:
                Serial.println("stop");
                TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

                break;


            //Serial.println("test");
        
        }
            if (i2c_state != stop) {
                Serial.println("if");
            while(!(TWCR & (1 << TWINT)));
            if (twi_status == 0x38 || twi_status == 0x00) {
                Serial.println("Arbitration loss or invalid state");
                i2c_state = start;

            }
        }
        
    }
           
}*/


