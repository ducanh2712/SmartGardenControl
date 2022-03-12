#ifndef _LCD8_H
#define  _LCD8_H_

unsigned char swap_Byte(unsigned char cmd);
void Lcd_Cmd(unsigned char cmd);
void Lcd_Chr_Cp (char c);
void Lcd_Chr(unsigned char row,unsigned char col, char c);
void Lcd_Out_Cp (char *str);
void Lcd_Out (unsigned char row,unsigned char col, char *str);
void Lcd_Init();
void write_CGRAM ( unsigned char hex  [],int);


#endif

