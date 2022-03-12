#ifndef	_RTC_DS3231_
#define _RTC_DS3231_

void Ds3231_Init();  

void Ds3231_Write(unsigned char dat);

unsigned char Ds3231_Read();

void Ds3231_Set_Time(unsigned char hh, unsigned char mm, unsigned char ss);

void Ds3231_Set_Date(unsigned char yy, unsigned char mm, unsigned char dd);

void Ds3231_Read_Time(unsigned char * hour, unsigned char * minute, unsigned char * second);

void Ds3231_Read_Date(unsigned char * date,unsigned char * month, unsigned char * year);

#endif