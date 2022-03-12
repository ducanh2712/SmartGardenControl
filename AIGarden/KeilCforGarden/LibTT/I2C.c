#include"main.h"
#include"port.h"
#include"I2c.h"
#include "..\libTT\delay.h"

bit I2c_Get_Ack();
void I2c_Ack();
void I2c_Nak();

void I2c_Init()
{
 	I2C_SCL=1;
	I2C_SDA=1;
}

void I2c_Start()
{
	I2C_SCL = 1;     
	I2C_SDA = 1;     
	I2C_SDA = 0; 
	I2C_SCL = 0;            
}


void I2c_Write(unsigned char dat)
{
	unsigned char i;

	for(i=0;i<8;i++)                   
	{
		I2C_SDA = dat & 0x80;    
		
		I2C_SCL = 1;
		
		I2C_SCL = 0;                   
		dat = dat<<1;
	}                          
	I2C_SCL = 1;
	I2C_SCL = 0;
}

void I2c_Ack()
{
	I2C_SDA = 0;        
	
	I2C_SCL = 1;
	
	I2C_SCL = 0;    
	I2C_SDA = 1;      
}

void I2c_Nak()
{
	I2C_SDA = 1;         
	
	I2C_SCL = 1;
	
	I2C_SCL = 0; 
	I2C_SCL = 1;         
}

unsigned char I2c_Read()
{
	int i, dat=0x00;

	I2C_SDA=1;               
	for(i=0;i<8;i++)     
	{
		
		I2C_SCL = 1;       
		

		dat = dat<<1;    
		dat = dat | I2C_SDA;  

		I2C_SCL = 0;         
	}
	return dat;          
}

void I2c_Stop()
{ 	
	I2C_SCL = 1;         
	
	I2C_SDA = 0;        
	
	I2C_SCL = 1;         
	
	I2C_SDA = 1;          
}
