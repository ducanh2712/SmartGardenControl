
 
sbit SCL=P0^0;      //SCL Connected to P0.0
sbit SDA=P0^1;      //SDA Connected to P0.1
 
 
void delay_us(unsigned int us_count)
 {  
    while(us_count!=0)
      {
         us_count--;
       }
   }
 
void i2c_Clock(void)
{
    delay_us(50);
    SCL = 1;        
 
    delay_us(50);        
    SCL = 0;        
}
 
  
void i2c_Start()
{
    SCL = 0;        // pull SCL low
 
    SDA = 1;        // pull SDA High
    delay_us(50);
 
    SCL = 1;        //pull SCL high
    delay_us(50);
 
    SDA = 0;        //Now pull SDA LOW, to generate the Start Condition
    delay_us(50);
 
    SCL = 0;        //Finally Clear the SCL to complete the cycle
}

 
void i2c_Stop(void)
{
    SCL = 0;            // pull SCL low
    delay_us(50);
 
    SDA = 0;            // pull SDA  low
    delay_us(50);
 
    SCL = 1;            // pull SCL High
    delay_us(50);
 
    SDA = 1;            // Now pull SDA High, to generate the Stop Condition
}

void i2c_Write(unsigned char dat)
{
    unsigned char i;
 
    for(i=0;i<8;i++)         
     {
        SDA = dat & 0x80;    
        i2c_Clock();         
        dat = dat<<1;
      }
        SDA = 1;                 
}

unsigned char i2c_Read(void)
{
    unsigned char i, dat=0x00;
 
       SDA=1;               
    for(i=0;i<8;i++)       
     {
       delay_us(50);
        SCL = 1;           
        delay_us(50);
 
        dat = dat<<1;       
        dat = dat | SDA;    
 
        SCL = 0;            
       }
   return dat;             
}

void i2c_Ack()
{
    SDA = 0;        
    i2c_Clock();    
    SDA = 1;        
}

void i2c_NoAck()
{
    SDA = 1;        
   i2c_Clock();     
    SCL = 1;     
}

 
#define dataport P2       // LCD dataport connected to PORT1
 
sbit rs= dataport^0;      // Register select pin connected to P1.0
sbit rw= dataport^1;      // Read Write pin connected to P1.1
sbit en= dataport^2;      // Enable pin connected to P1.2
 
 
 
/* 16x2 lcd Specification */
#define LCDMaxLines 2
#define LCDMaxChars 16
#define LineOne 0x80
#define LineTwo 0xc0
 
#define BlankSpace ' '
 
 
 
 
 
 
 
//LCD initilization
void LCD_Init()
{
    delay_us(5000);
   lcd_WriteCmd(0x02);  //initilize the LCD in 4bit Mode
   lcd_WriteCmd(0x28);
   lcd_WriteCmd(0x0C);  // display ON cursor ON
   lcd_WriteCmd(0x01);  // clear the LCD
   lcd_WriteCmd(0x80);  // move the Cursor to First line First Position
 
}
 
 
// lcd Write command function
void lcd_WriteCmd( char a)
{
 
   dataport=(a & 0xf0);        
   rs=0;                      
   rw=0;                 
 	 en=1;                 
   delay_us(1);
   en=0;
   delay_us(1);                  
   dataport=((a<<4) & 0xf0);   
   rs=0;                    
   rw=0;                    
   en=1;                      
   delay_us(1);
   en=0;
   delay_us(1);
}
 
 
 // lcd writedata function
void lcd_Writedata( char a)
{
 
 
   dataport=(a & 0xf0);        
     rs=1;                      
     rw=0;                      
     en=1;                      
    delay_us(1);
     en=0;
 
   delay_us(1);                
 
   dataport=((a <<4) & 0xf0);  
     rs=1;                    
     rw=0;                     
     en=1;                      
    delay_us(1);
     en=0;
 
   delay_us(1);
 
}

 
 //lcd gotolinetwo fuction
void lcd_GoToLineTwo()
{
   lcd_WriteCmd(LineTwo);   // move the Cursor to Second line First Position
}
 
 
 
//lcd go to X(first row), Y(second row) line
void lcd_GoToXY(char row, char col)
{
   char pos;
 
    if(row<LCDMaxLines)
      {
         pos= LineOne | (row << 6);
                                    
 
        if(col<LCDMaxChars)
           pos= pos+col;            
                                    
 
         lcd_WriteCmd(pos);        
       }
}
 

//lcd display string function
void lcd_DisplayString(char *string_ptr)
{
   while(*string_ptr)
    lcd_Writedata(*string_ptr++);
    }
 
 
//lcd display rtc time function
void lcd_DisplayRtcTime(char hour,char min,char sec)
{
    lcd_Writedata(((hour>>4) & 0x0f) + 0x30);
    lcd_Writedata((hour & 0x0f) + 0x30);
    lcd_Writedata(':');
 
    lcd_Writedata(((min>>4) & 0x0f) + 0x30);
    lcd_Writedata((min & 0x0f) + 0x30);
    lcd_Writedata(':');
 
    lcd_Writedata(((sec>>4) & 0x0f) + 0x30);
    lcd_Writedata((sec & 0x0f) + 0x30);
 
 }
 
 
 // lcd display rtc date function
void lcd_DisplayRtcDate(char day,char month,char year)
 {
     lcd_Writedata(((day>>4) & 0x0f) + 0x30);
     lcd_Writedata((day & 0x0f) + 0x30);
     lcd_Writedata('/');
 
     lcd_Writedata(((month>>4) & 0x0f) + 0x30);
     lcd_Writedata((month & 0x0f) + 0x30);
     lcd_Writedata('/');
 
     lcd_Writedata(((year>>4) & 0x0f) + 0x30);
     lcd_Writedata((year & 0x0f) + 0x30);
 
 }

 Skip to content
Why GitHub? 
Team
Enterprise
Explore 
Marketplace
Pricing 
Search

Sign in
Sign up
Embedotronics
/
8051-microcontroller-interfacing-with-DS1307-Real-Time-Clock
000
Code
Issues
Pull requests
Actions
Projects
Security
Insights
Join GitHub today
GitHub is home to over 50 million developers working together to host and review code, manage projects, and build software together.

8051-microcontroller-interfacing-with-DS1307-Real-Time-Clock/ds1307.c
@Embedotronics
Embedotronics Add files via upload
Latest commit d32b034 on 2 Apr
 History
 1 contributor
118 lines (76 sloc)  2.79 KB
  

#include<reg51.h> 
#include "ds1307.h"
#include "i2c.h"
#include "delay.h"
 
 
 
/* Below given values are fixed and should not be changed.
    Refer Ds1307 DataSheet for more info*/
 
#define DS1307_ID 0xD0     // ds1307 ID
 
#define SEC_ADDRESS   0x00 // address to access ds1307 SEC register
#define DATE_ADDRESS  0x04 // address to access ds1307 DATE register
#define control       0x07 // address to access ds1307 CONTROL register
 
 
 
 
 
 
//ds1307 initilization
void ds1307_Init()
{
    i2c_Start();            // Start i2c communication
 
    ds1307_Write(DS1307_ID);   
   ds1307_Write(control);    
 
    ds1307_Write(0x00);        
 
    i2c_Stop();             
 
 }
 

void ds1307_Write(unsigned char dat)
{
    i2c_Write(dat);   
    i2c_Clock();
 }
 

unsigned char ds1307_Read()
{
    unsigned char dat;
    dat = i2c_Read();   
    return(dat);
 }

void ds1307_SetTime(unsigned char hh, unsigned char mm, unsigned char ss)
{
    i2c_Start();            // Start i2c communication
 
    ds1307_Write(DS1307_ID);    
    ds1307_Write(SEC_ADDRESS);
    ds1307_Write(ss);           
    ds1307_Write(mm);           
    ds1307_Write(hh);           
 
    i2c_Stop();             // Stop i2c communication after Setting the Time
}

void ds1307_SetDate(unsigned char dd, unsigned char mm, unsigned char yy)
{
    i2c_Start();            // Start i2c communication
 
    ds1307_Write(DS1307_ID);    
    ds1307_Write(DATE_ADDRESS);     
 
    ds1307_Write(dd);           
    ds1307_Write(mm);           
    ds1307_Write(yy);           
 
    i2c_Stop();             // Stop i2c communication after Setting the Date
}

void ds1307_GetTime(unsigned char *h_ptr,unsigned char *m_ptr,unsigned char *s_ptr)
{
     i2c_Start();           // Start i2c communication
 
    ds1307_Write(DS1307_ID);    
    ds1307_Write(SEC_ADDRESS);          
 
     i2c_Stop();            
 
    i2c_Start();               
    ds1307_Write(0xD1);         
                               
 
  *s_ptr = ds1307_Read();  i2c_Ack();     
  *m_ptr = ds1307_Read();  i2c_Ack();     
  *h_ptr = ds1307_Read();  i2c_NoAck();   
 
  i2c_Stop();               // stop i2c communication after reading the Time
 }
 
void ds1307_GetDate(unsigned char *d_ptr,unsigned char *m_ptr,unsigned char *y_ptr)
{
    i2c_Start();            // start i2c communication
 
    ds1307_Write(DS1307_ID);    
    ds1307_Write(DATE_ADDRESS);     
 
    i2c_Stop();             
 
 
   i2c_Start();             
   ds1307_Write(0xD1);          
                            
 
  *d_ptr = ds1307_Read(); i2c_Ack();     
  *m_ptr = ds1307_Read(); i2c_Ack();     
  *y_ptr = ds1307_Read(); i2c_NoAck();   
 
  i2c_Stop();         // stop i2c communication after reading the Time
 }
#include <reg51.h> 
#include "lcd.h"  	 
#include "ds1307.h" 
#include "i2c.h"
#include "delay.h"
 
/* main program */
void main() 
{
   unsigned char sec,min,hour,day,month,year;
 
  /* Initilize the lcd */
    lcd_Init();
 
  /* Initilize the RTC(ds1307)*/
    ds1307_Init();
 
 
  /*set the time and Date only once */
  ds1307_SetTime(0x23,0x59,0x30);  //  
  ds1307_SetDate(0x31,0x12,0x19);  //  
 
  /* Display "time" on first line*/
  lcd_DisplayString("Time: ");
 
   /* Display "date" on Second line*/
  lcd_GoToLineTwo();
  lcd_DisplayString("Date: ");
 
   /* Display the time and date continously */ 
   while(1)
    {
	   /* Read the Time from RTC(ds1307) */ 
        ds1307_GetTime(&hour,&min,&sec);        
 
		/* Display the time on firstline 7th position*/
 
         lcd_GoToXY(0,6); 		 
         lcd_DisplayRtcTime(hour,min,sec);
 
 
	    /* Read the Date from RTC(ds1307) */ 
        ds1307_GetDate(&day,&month,&year);        
 
		/* Display the Date on secondline 7th position*/
         lcd_GoToXY(1,6); 		 
         lcd_DisplayRtcDate(day,month,year);
     }
}