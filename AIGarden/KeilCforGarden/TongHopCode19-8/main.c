#include <REGX52.H>
#include "stdio.h"
#include "string.h"
#include "port.h"
#include "..\libTT\delay.h"
#include "..\libTT\LCD8.h"
//#include "..\libTT\DHT11.h"
#include "..\libTT\I2C.h"
#include "..\libTT\RTC_DS3231.h"

//////Khai bao ket noi button de doi mode
////#define UP P1_1
////#define DOWN P1_2
////#define BUT P1_3 

//////Khai bao ket noi LCD
////#define LCD_RS  P0_7
////#define LCD_EN  P0_6
////#define LCD_DATA P2

//////Khai bao ket noi I2C
////#define I2C_SCL	 P3_2
////#define I2C_SDA	 P3_3 

////Khai bao ket noi DHT11
// #define DHT11  P0_5
// #define P1_4 OK

unsigned int set=0;
unsigned char Hour, Minute, Second, Mode, Day, Date, Month, Year, old_second, gio, phut, giay;
int I_RH,D_RH,I_Temp,D_Temp,CheckSum;
int i=0;
unsigned char dat[20];

//char Num_Pad()
//{
//	int i,key,key1,key2
//	key1 = checkPad();
//	key2 = checkPad();
//	if(key2 == OK) return key1;
//	else	key = key1*10 + key2;
//	return key;
//}



//void Write_Time_Onl( char Num_Pad())
//{
//	if(set==1)  Ds3231_Write_Time(Num_Pad(),Minute,Second,24,0);
//	else if(set==2)  Ds3231_Write_Time(Hour,Num_Pad(),Second,24,0);
//	else if(set==3)  Ds3231_Write_Date(Day,Num_Pad(),Month,Year);
//	else if(set==4)  Ds3231_Write_Date(Day,Date,Num_Pad(),Year);
//	else if(set==5)  Ds3231_Write_Date(Day,Date,Month,Num_Pad());
//}


//void Lcd_Time() //In man hinh gio/phut/giay
//{
//	Lcd_Chr(2,1,Hour/10+0x30);
//	Lcd_Chr_Cp(Hour%10+0x30);
//	Lcd_Chr_Cp(':');
//	Lcd_Chr_Cp(Minute/10+0x30);
//	Lcd_Chr_Cp(Minute%10+0x30);
//	Lcd_Chr_Cp(':');
//	Lcd_Chr_Cp(Second/10+0x30);
//	Lcd_Chr_Cp(Second%10+0x30);
//}

//void Lcd_Day() // In man hinh ngay/thang/nam
//{
//	Lcd_Chr(2,9,Date/10+0x30);
//	Lcd_Chr_Cp(Date%10+0x30);
//	Lcd_Chr_Cp('/');
//	Lcd_Chr_Cp(Month/10+0x30);
//	Lcd_Chr_Cp(Month%10+0x30);
//	Lcd_Out_Cp("/");
//	Lcd_Chr_Cp(Year/10+0x30);
//	Lcd_Chr_Cp(Year%10+0x30);
//}

//void SetTime() // Dieu chinh gio/phut/giay bang nut bam
//{
//	if(UP == 0)
//	{
//		if(set	== 1) { Hour++;if(Hour>=23)Hour=0;}
//		else if(set  == 2) { Minute++;if(Minute>=59)Minute=0;}
//		Ds3231_Write_Time(Hour,Minute,Second,24,0);
//	}
//	if(DOWN == 0)
//	{
//		if(set	== 1) { Hour--;if(Hour<=0)Hour=23;}
//		else if(set	== 2) { Minute--;if(Minute<=0)Minute=59;}
//		Ds3231_Write_Time(Hour,Minute,Second,24,0);
//	}
//}

void DHT11_LCD()
{
		Request();	
		Response();	
		
		I_RH=Receive_data();
		D_RH=Receive_data();	
		I_Temp=Receive_data();
		D_Temp=Receive_data();
		CheckSum=Receive_data();

		if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
		{
			Lcd_Out(0,0,"Error");
		}
		
		else
		{
			sprintf(dat,"H=%d.%d",I_RH,D_RH);
			Lcd_Out(1,1,dat);
			sprintf(dat," T=%d.%d",I_Temp,D_Temp);   
			Lcd_Out_Cp(dat);
			Lcd_Chr_Cp(0xDF);
			Lcd_Out_Cp("C");
			memset(dat,0,20);
			delay(500);
		}
}
void DS3231_LCD()
{
				Ds3231_Read_Time(&Hour, &Minute, &Second, &Mode);
			Ds3231_Read_Date(&Day, &Date, &Month, &Year);
			if(BUT == 0){set++;set%=4;}
			if(set==1)
			{
				Lcd_Out(2,1,"  ");
				for (i=0;i<50;i++)
				{
					if(BUT == 0){set++;set%=4;i=50;}
					SetTime();
					delay(10);
				}
			}
			else if (set==2)
			{
				Lcd_Out(2,4,"  ");
				for (i=0;i<50;i++)
				{
					if(BUT == 0){set++;set%=4;i=50;}
					SetTime();
					delay(10);
				}
			}
			else if (set==3)	
			{
				Lcd_Out(2,7	,"  ");
				for (i=0;i<50;i++)
				{
					if(BUT == 0){set++;set%=4;i=50;}
					SetTime();
					delay(10);
				}
			}
}

void main()
{

	Lcd_Cmd(0x01);
	Lcd_Init();
	//	I2c_Init();
	//	Ds3231_Init();
	//Ds3231_Write_Time(8,59,30,24,0);
	//Ds3231_Write_Date(2,4,8,20);	
	while(1)
	{	
			DHT11_LCD();
			DS3231_LCD();
//			SetTime();
//			Lcd_Time();
//			Lcd_Day();
//			for (i=0;i<50;i++)
//			{
//					if(BUT == 0){set++;set%=4;i=50;}
//					delay(10);
//			}			

	}
}