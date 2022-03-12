#ifndef _PORT_H_
#define _PORT_H_

// khai bao ket noi LCD
sbit LCD_RS	= P0^6;
sbit LCD_EN	= P0^7;
sbit LCD_D4	= P2^7;
sbit LCD_D5 = P2^6;
sbit LCD_D6 = P2^5;
sbit LCD_D7 = P2^4;

// Khai bao ket noi I2C
sbit SOFT_I2C_SCL	= P0^3;
sbit SOFT_I2C_SDA	= P0^4; 

// Ket noi nut nhan 
sbit BTN = P1^0;

#endif