


#ifndef I2C_C
#define I2C_H

void initI2CMaster();
void sendData(unsigned char address, unsigned char data);
//void recieveData(unsigned char address, unsigned char data);
void ADXL_I2C(unsigned char addressW, unsigned char addressR, unsigned char regAddress);

void i2cInit();
int getTemp();

float convertC(int ffTemp);
float convertF(int cTemp);


#endif