#include <Arduino.h>
#include "i2c.h"

void i2c_send(uint8_t m)
{
  i2c_start();
  i2c_write(LCD_W);
  i2c_write(m);
  i2c_stop();  
}
void i2c_init()
{
   TWBR = 72;       //SCL 10KHz frequency
   TWSR = 0x00;     //prescaler as 1
}
void i2c_start()
{
   TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); 
   while(!(TWCR & (1<<TWINT)));    //wait until the TWINT bit set by hardware
}
void i2c_repeatedStart()
{
   TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); 
   while(!(TWCR & (1<<TWINT))); 
}
void i2c_stop()
{
   TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
   while(!(TWCR & (1<<TWINT)));  //wait until the TWINT bit set by hardware
}
void i2c_write(uint8_t a)
{
  TWDR = a;
  TWCR = (1<<TWINT) | (1<<TWEN);   //clearing the TWINT bit(by writing logic one)
  while (!(TWCR & (1<<TWINT)));  //wait until the TWINT bit set by hardware
}
uint8_t i2c_read(uint8_t flag)
{
   if(flag==1)
   {
      TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);    //enabling ACK mode
   }
   else if(flag==0)
   {
      TWCR = (1 << TWINT) | (1 << TWEN); 
   }
   while (!(TWCR & (1<<TWINT))); 
   return TWDR;
}