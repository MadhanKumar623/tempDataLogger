#include "sketch.h"

void delay1(int a) //a = 400 ---> 1 second (approximately) 
{
   volatile long i; 
   while(a)
   {
     for(i = 1;i<=1000;i++);
     a--;
   }
}

void setup()
{
  i2c_init();         
  Lcd_init();
  Adc_init();
  rtc_init(initial_seconds,initial_minutes,initial_hours,initial_date,initial_month,initial_year);  
  Serial0_init(BAUD);      //initialising serial monitor through UART0 communication
  SD.begin();              //initialising SD card
}

void loop()                 //runs continuosly
{
   getCurrentDateTime();
   printTimeToLcd();
   printTimeToSerial();       
   tempResult = convertToCelcius(readAnalog0());
   sprintf(str,"Temperature: %02d C",(uint16_t)tempResult);  //converting temperature result to string
   if(current_seconds%10 == 0||current_seconds%10 == 1||current_seconds%10 == 9)               //storing and displaying the temperature data for 10|9|11 seconds once
   {
      writeToSDcard(date_arr,time_arr,str);   //writing to SD card along with time stamp
      Lcd_sendCommand(0x94);
      Lcd_sendString(str);
   }
   delay1(400);        //1 sec delay
   //readFromSDcard();  //used to read stored data from SD card
}
