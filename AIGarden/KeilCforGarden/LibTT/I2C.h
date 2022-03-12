#ifndef	_SOFT_I2C_H_
#define _SOFT_I2C_H_

void I2c_Init();
			  
void I2c_Start();


void I2c_Write(unsigned char dat);

void I2c_Ack();

void I2c_Nak();

unsigned char I2c_Read();

void I2c_Stop();

#endif