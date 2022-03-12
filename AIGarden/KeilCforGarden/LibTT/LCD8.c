#include <REGX52.H>

#include "port.h"
#include"..\libTT\delay.h"
#include"..\libTT\LCD8.h"

unsigned char swap_Byte(unsigned char b)
{
	b = (b&0xF0) >> 4 | (b&0x0F) << 4;
	b = (b&0xCC) >> 2 | (b&0x33) << 2;
	b = (b&0xAA) >> 1 | (b&0x55) << 1;
	return b;
}

void Lcd_Cmd(unsigned char cmd)
{
	LCD_RS = 0;
	LCD_DATA = swap_Byte(cmd);
	LCD_EN = 0;
	LCD_EN = 1;

	if(cmd<=0x02)
	{
	 	delay(2);
	}
	else
	{
	 	delay(1);
	}
}

void Lcd_Chr_Cp(char c)		// Current Position
{
 	LCD_RS = 1;
	LCD_DATA = swap_Byte(c);
	LCD_EN = 0;
	LCD_EN = 1;
	delay(1);
}

// Xuat ra man hinh LCD 1 ky tu, ngay tai vi tri dong row, cot col
void Lcd_Chr(unsigned char row, unsigned char col, char c)
{
	unsigned char cmd;

	// Di chuyen co tro den vi tri can thiet
	cmd = (row==1?0x80:0xC0) + col - 1;
	Lcd_Cmd(cmd);

	// Xuat ky tu
	Lcd_Chr_Cp(c);
}	

void Lcd_Out_Cp(char *str)
{
 	unsigned char i = 0;
	while(str[i]!=0)
	{
	 	Lcd_Chr_Cp(str[i]);
		i++;
	}
}

void Lcd_Out(unsigned char row, unsigned char col, char *str)
{
 	unsigned char cmd;

	// Di chuyen co tro den vi tri can thiet
	cmd = (row==1?0x80:0xC0) + col - 1;
	Lcd_Cmd(cmd);

	Lcd_Out_Cp(str);
}

void Lcd_Init()
{
 	Lcd_Cmd(0x30);
	delay(5);
	Lcd_Cmd(0x30);
	delay(1);
	Lcd_Cmd(0x30);

	Lcd_Cmd(0x38); 		// So dong hien thi la 2, font 5x8

	Lcd_Cmd(0x01);		// Xoa noi dung hien thi
	Lcd_Cmd(0x0C);	  	// Bat hien thi va tat con tro
}