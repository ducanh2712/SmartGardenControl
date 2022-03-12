#include"Main.h"
#include"port.h"
#include"I2C.h"
#include"RTC_DS3231.h"
#include "..\libTT\delay.h"

#define DS3231_WriteMode 0xD0  
#define DS3231_ReadMode 0xD1
          
#define SEC_ADD   0x00
#define DATE_ADD  0x04 
#define CONTROL 0x07       

void Ds3231_Init()	  
{
	I2c_Init();
	I2c_Start();

	I2c_Write(DS3231_WriteMode);
	I2c_Write(CONTROL);

	I2c_Write(SEC_ADD);
							
	I2c_Stop();
}

void Ds3231_Write(unsigned char dat)
{
	I2c_Write(dat);
	delay(1);
	I2C_SCL = 1;
	delay(1);
	I2C_SCL = 0;
}

unsigned char Ds3231_Read()
{
    unsigned char dat;
    dat = I2c_Read();   
    return(dat);
}

void Ds3231_Set_Time(unsigned char hh, unsigned char mm, unsigned char ss)
{
	ss = ((ss/10)<<4)|(ss%10);
	mm = ((mm/10)<<4)|(mm%10);
	hh   = ((hh  /10)<<4)|(hh  %10);

	I2c_Start();
	Ds3231_Write(DS3231_WriteMode);
	Ds3231_Write(SEC_ADD);

	Ds3231_Write(ss);
	Ds3231_Write(mm);
	Ds3231_Write(hh);

	I2c_Stop();
}

void Ds3231_Set_Date(unsigned char yy, unsigned char mm, unsigned char dd)
{
	dd	= ((dd/10)<<4)  | (dd%10);
	mm 	= ((mm/10)<<4) | (mm%10);
	yy	= ((yy/10)<<4)  | (yy%10);

	I2c_Start();
	Ds3231_Write(DS3231_WriteMode);
	Ds3231_Write(DATE_ADD);

	Ds3231_Write(dd);
	Ds3231_Write(mm);
	Ds3231_Write(yy);

	I2c_Stop();
}

void Ds3231_Read_Time(unsigned char * hour, unsigned char * minute, unsigned char * second)
{
	//unsigned char h_tmp, m_tmp, s_tmp;	

	I2c_Start();

	I2c_Write(DS3231_WriteMode);
	I2c_Write(SEC_ADD);

	I2c_Stop();

	I2c_Start();

	I2c_Write(DS3231_ReadMode);
	*second = I2c_Read(); I2c_Ack();
	*minute = I2c_Read();	I2c_Ack();
	*hour = I2c_Read();	I2c_Nak();

	I2c_Stop();

//	s_tmp &= 0x7F;
//	*second = (s_tmp>>4)*10+(s_tmp&0x0F);
//	m_tmp &= 0x7F;
//	*minute = (m_tmp>>4)*10+(m_tmp&0x0F);
//	h_tmp &= 0x3F;
//	*hour = (h_tmp>>4)*10+(h_tmp&0x0F);
				
}


void Ds3231_Read_Date(unsigned char * date,unsigned char * month, unsigned char * year)
{
	I2c_Start();

	I2c_Write(DS3231_WriteMode); 
	I2c_Write(DATE_ADD);
	
	I2c_Stop();

	I2c_Start(); 

	I2c_Write(DS3231_ReadMode); 
	*date = I2c_Read();	I2c_Ack();
	*month= I2c_Read();	I2c_Ack();
	*year = I2c_Read();	I2c_Nak();

	I2c_Stop();
//	*date &= 0x3F;
//	*date = (*date>>4)*10 + (*date & 0x0F);
//	*month &= 0x1F;
//	*month = (*month>>4)*10 + (*month & 0x0F);
//	*year = (*year>>4)*10 + (*year & 0x0F);	
}

