#include "rtc.h"

uint8_t current_hours;       //24hour format
uint8_t current_minutes;
uint8_t current_seconds;
uint8_t current_year;
uint8_t current_month;
uint8_t current_date;
uint8_t dummy_day;

char date_arr[20];
char time_arr[20];

void rtc_init(uint8_t i_seconds,uint8_t i_minutes,uint8_t i_hours,uint8_t i_date,uint8_t i_month,uint8_t i_year)  //initialising RTC with some initial time
{
  i2c_start();
  i2c_write(RTC_W);
  i2c_write(START_ADDRESS);
  i2c_write(dec2bcd(i_seconds));   //00H
  i2c_write(dec2bcd(i_minutes));   //01H
  i2c_write(dec2bcd(i_hours));     //02H
  i2c_write('0');                  //day is not needed so can be entered as zero, 03H
  i2c_write(dec2bcd(i_date));      //04H
  i2c_write(dec2bcd(i_month));     //05H
  i2c_write(dec2bcd(i_year));      //06H
  i2c_stop();
}

void getCurrentDateTime()    //reading RTC current date and time
{
  i2c_start();
  i2c_write(RTC_W);
  i2c_write(START_ADDRESS);
  i2c_repeatedStart();
  i2c_write(RTC_R);
  current_seconds = bcd2dec(i2c_read(1)); //ACK -> 1, NACK -> 0
  current_minutes = bcd2dec(i2c_read(1)); 
  current_hours = i2c_read(1); 
  dummy_day = bcd2dec(i2c_read(1)); 
  current_date = bcd2dec(i2c_read(1)); 
  current_month = bcd2dec(i2c_read(1)); 
  current_year = bcd2dec(i2c_read(0)); 
  i2c_stop();
}
uint8_t bcd2dec(uint8_t bcd)           //convert BCD to Decimal
{
  return (((bcd & 0xF0) >> 4) * 10 + (bcd & 0x0F));
}
uint8_t dec2bcd(uint8_t dec)           //convert Decimal to BCD
{
   return (((dec / 10) << 4) | (dec % 10));
}
void printTimeToSerial()
{
   sprintf(date_arr,"%02d-%02d-%02d",current_date,current_month,current_year);
   sprintf(time_arr,"%02d:%02d:%02d",bcd2dec((current_hours&0x3f)),current_minutes,current_seconds);
   /*Serial0_transmitString("Date is : ");     //used to display date and time in serial monitor
   Serial0_transmitString(date_arr);
   Serial0_transmitString("Time is : ");
   Serial0_transmitString(time_arr);*/
}
void printTimeToLcd()
{
   sprintf(date_arr,"DATE: %02d-%02d-%02d",current_date,current_month,current_year);
   sprintf(time_arr,"TIME: %02d:%02d:%02d",bcd2dec((current_hours&0x3f)),current_minutes,current_seconds);
   Lcd_sendCommand(0x80);
   Lcd_sendString(date_arr);
   Lcd_sendCommand(0xC0);
   Lcd_sendString(time_arr);
}