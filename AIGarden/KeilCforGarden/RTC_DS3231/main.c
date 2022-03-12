#include <REGX52.H>
#include "stdio.h"
#include "..\libTT\I2C.h"
#include "..\libTT\delay.h"
#include "..\libTT\RTC_DS3231.h"
#include "..\libTT\LCD8.h"
#include"port.h"

unsigned char Hour, Minute, Second, Mode, Day, Date, Month, Year, old_second, gio, phut, giay;
	
void Lcd_Time()
{
	Lcd_Chr(1,2,Hour/10+0x30);
	Lcd_Chr_Cp(Hour%10+0x30);
	Lcd_Chr_Cp(':');
	Lcd_Chr_Cp(Minute/10+0x30);
	Lcd_Chr_Cp(Minute%10+0x30);
	Lcd_Chr_Cp(':');
	Lcd_Chr_Cp(Second/10+0x30);
	Lcd_Chr_Cp(Second%10+0x30);
}

void Lcd_Day()
{
	Lcd_Chr(2,2,Date/10+0x30);
	Lcd_Chr_Cp(Date%10+0x30);
	Lcd_Chr_Cp('/');
	Lcd_Chr_Cp(Month/10+0x30);
	Lcd_Chr_Cp(Month%10+0x30);
	Lcd_Out_Cp("/20");
	Lcd_Chr_Cp(Year/10+0x30);
	Lcd_Chr_Cp(Year%10+0x30);
}

void SetTime(mode)
{
	if(UP == 0)
	{
		if(mode	== 1) { gio++;if(gio>23)gio=0;}
		if(mode	== 2) { phut++;if(phut>59)phut=0;}
		if(mode	== 3) { giay=0;}
		Ds3231_Write_Time(gio,phut,giay,24,0);
	}
	if(DOWN == 0)
	{
		if(mode	== 1) { gio--;if(gio<23)gio=23;}
		if(mode	== 2) { phut--;if(phut<0)phut=59;}
		if(mode	== 3) { giay=0;}
		Ds3231_Write_Time(gio,phut,giay,24,0);
	}
}
void main()
{
//	int mode=0;
	int i=0;
 	Lcd_Init();	
	I2c_Init();
	Ds3231_Init();
	Ds3231_Write_Time(20,42,0,24,0);
	Ds3231_Write_Date(2,30,8,20);

	while(1)
	{
		gio = Hour;
		phut = Minute;
		giay = Second;
		if(BUT == 0) {mode++;mode=mode%4;}
		if(mode == 1)
		{
			for(;mode==1;)
			{
				Ds3231_Read_Time(&Hour, &Minute, &Second, &Mode);
				if(BUT == 0) {mode++;mode=mode%4;}
				for(i=0;i<500;i++)
				{
					Lcd_Time();
					Lcd_Day();
					SetTime(1);
					delay(1);
				}
				for(i=0;i<500;i++)
				{
					Lcd_Out(1,8,"  ");
					SetTime(1);
					delay(1);
				}
			}
		}
		else if(mode == 2)
		{
			for(;mode==2;)
			{
				Ds3231_Read_Time(&Hour, &Minute, &Second, &Mode);
				if(BUT == 0) {mode++;mode=mode%4;}
for(i=0;i<500;i++)
				{
					Lcd_Time();
					Lcd_Day();
					SetTime(1);
					delay(1);
				}
				for(i=0;i<500;i++)
				{
					Lcd_Out(1,5,"  ");
					SetTime(1);
					delay(1);
				}
			}
		}
		else if(mode == 3)
		{
			for(;mode==3;)
			{
				Ds3231_Read_Time(&Hour, &Minute, &Second, &Mode);
				if(BUT == 0) {mode++;mode=mode%4;}
				for(i=0;i<500;i++)
				{
					Lcd_Time();
					Lcd_Day();
					SetTime(1);
					delay(1);
				}
				for(i=0;i<500;i++)
				{
					Lcd_Out(1,2,"  ");
					SetTime(1);
					delay(1);
				}
			}
		}
		else
		{	
			Ds3231_Read_Time(&Hour, &Minute, &Second, &Mode);
			Ds3231_Read_Date(&Day, &Date, &Month, &Year);
			if(BUT == 0) {mode++;mode=mode%4;}			 	 	
			Lcd_Time();
			Lcd_Day();
		}
	}
}