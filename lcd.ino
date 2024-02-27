#include <Arduino.h>
#include "lcd.h"
#include "i2c.h"

void Lcd_init()
{
   Lcd_sendCommand(0x02);
   Lcd_sendCommand(44);     //for 4 line interface
   Lcd_sendCommand(12);
}
void Lcd_sendString(char *ptr)   //string always should be at char* and not at uint8_t*
{
   while(*ptr!='\0'){
     Lcd_sendData(*ptr);
     ptr++;
   }
}
void Lcd_sendData(uint8_t d) //D7 D6 D5 D4 LED+ EN RW RS   
{
   uint8_t upper = d&0xf0;
   uint8_t lower = (d<<4)&0xf0;
   i2c_send(upper|0x0D);
   delay(1);
   i2c_send(upper|0x09);
   delay(1);
   i2c_send(lower|0x0D);
   delay(1);
   i2c_send(lower|0x09);
   delay(1);
}
void Lcd_sendCommand(uint8_t a)
{
   uint8_t upper = a&0xf0;
   uint8_t lower = (a<<4)&0xf0;
   i2c_send(upper|0x0C);
   delay(1);
   i2c_send(upper|0x08);
   delay(1);
   i2c_send(lower|0x0C);
   delay(1);
   i2c_send(lower|0x08);
   delay(1);
}