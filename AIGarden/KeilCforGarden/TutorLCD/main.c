#include "main.h"
#include"..\libTT\delay.h"
#include"..\libTT\LCD8.h"
#include "port.h"


void main()		
{
	//LCD_EN = 1;
	Lcd_Init();
	Lcd_Out_Cp("DEvzONE2020");
	while(1)
	{
	}
}				
																									  

// Khai bao ket noi LCD
//#define LCD_DATA P3
//#define LCD_RS P2_0
//#define LCD_EN P2_1
//
//char customChar[] = {0x01,0x02,0x04,0x08,0x10,0x11,0x1F,0x00};							
//
//void main()
//{
//	// Khi su dung thi thong thuong xoa toan bo LCD di vi co the van luu lai noi dung cua chuong trinh cu
//	Lcd_Cmd(0x01);
//	//Khoi tao
//	Lcd_Init();
//	//Lcd_Chr_Cp('A');
//
//	write_CGRAM(customChar, 8);
//	delay(4);
//	Lcd_Cmd(0xC0);
//	Lcd_Chr_Cp(0x00);
//	Lcd_Chr_Cp(0x01);
//	P1_6=0;
//	P1_5=1;
//	P2_5=0;
//	while(1)
//	{
//	}
//
//}
//
//	// Khi su dung thi thong thuong xoa toan bo LCD di vi co the van luu lai noi dung cua chuong trinh cu
//	Lcd_Cmd(0x01);
//	//Khoi tao
//	Lcd_Init();
//	//Bat hien thi va bat con tro
//	//Lcd_Cmd(0x0E); 
//
//	//Bat hien thi va tat con tro
//	//Lcd_Cmd(0x0C); 
//
//	//Hien thi ki tu len man hinh
//	Lcd_Chr_Cp('A');
//
//	//In chuoi ki tu len man hinh
//	//Lcd_Out_Cp("Hello World");
//
//	//Dich chuyen den dong 2
//	Lcd_Cmd(0xC0);
//	Lcd_Out_Cp("Dong 2");
//
//	//Di chuyen con tro den dong 1, cot 5 va hien thi
//	//Lcd_Chr(5,1,'A');
//	//Lcd_Out(5,2,"Hello World");