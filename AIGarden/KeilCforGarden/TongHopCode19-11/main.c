#include <REGX52.H>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "../libTT/LCD8.h"
#include "../libTT/delay.h"
#include "port.h"



unsigned int mode=0;
int I_RH,D_RH,I_Temp,D_Temp,CheckSum;
int i=0;


void timer_delay20ms()		/* Timer0 delay function */
{
	TMOD = 0x01;
	TH0 = 0xB8;		/* Load higher 8-bit in TH0 */
	TL0 = 0x0C;		/* Load lower 8-bit in TL0 */
	TR0 = 1;		/* Start timer0 */
	while(TF0 == 0);	/* Wait until timer0 flag set */
	TR0 = 0;		/* Stop timer0 */
	TF0 = 0;		/* Clear timer0 flag */
}

void timer_delay30us()		/* Timer0 delay function */
{
	TMOD = 0x01;		/* Timer0 mode1 (16-bit timer mode) */
	TH0 = 0xFF;		/* Load higher 8-bit in TH0 */
	TL0 = 0xF1;		/* Load lower 8-bit in TL0 */
	TR0 = 1;		/* Start timer0 */
	while(TF0 == 0);	/* Wait until timer0 flag set */
	TR0 = 0;		/* Stop timer0 */
	TF0 = 0;		/* Clear timer0 flag */
}

void Request()			/* Microcontroller send request */
{
	DHT11 = 0;		/* set to low pin */
	timer_delay20ms();	/* wait for 20ms */
	DHT11 = 1;		/* set to high pin */
}

void Response()			/* Receive response from DHT11 */
{
	while(DHT11==1);
	while(DHT11==0);
	while(DHT11==1);
}

int Receive_data()		/* Receive data */
{
	int q,c=0;	
	for (q=0; q<8; q++)
	{
		while(DHT11==0);/* check received bit 0 or 1 */
		timer_delay30us();
		if(DHT11 == 1)	/* If high pulse is greater than 30ms */
		c = (c<<1)|(0x01);/* Then its logic HIGH */
		else		/* otherwise its logic LOW */
		c = (c<<1);
		while(DHT11==1);
	}
	return c;
}

void main()
{	unsigned char dat[20];
	Lcd_Init();		/* initialize LCD */;
//	Lcd_Out (1,1,"Devzone");
	while(1)
	{			
		Request();	/* send start pulse */
		Response();	/* receive response */
				
		I_RH=Receive_data();	/* store first eight bit in I_RH */
		D_RH=Receive_data();	/* X`store next eight bit in D_RH */
		I_Temp=Receive_data();	/* store next eight bit in I_Temp */
		D_Temp=Receive_data();	/* store next eight bit in D_Temp */
		CheckSum=Receive_data();/* store next eight bit in CheckSum */

		if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
		{
			Lcd_Out(1,1,"Error");
		}	 
		
		else
		{
			sprintf(dat,"Hum = %d.%d",I_RH,D_RH);
			Lcd_Out(1,1,dat);
			sprintf(dat,"Tem = %d.%d",I_Temp,D_Temp);   
			Lcd_Out(2,1,dat);
			Lcd_Chr_Cp(0xDF);	
			memset(dat,0,20);
  			sprintf(dat,"%d   ",CheckSum);
  			Lcd_Out(1,13,dat);
		//	delay(100);   
		}		
		delay(100);
	}	
}