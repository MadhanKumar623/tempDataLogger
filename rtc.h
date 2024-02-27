#ifndef RTC_H
#define RTC_H

#define START_ADDRESS 0x00

void rtc_init(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);  
uint8_t dec2bcd(uint8_t);
uint8_t bcd2dec(uint8_t);
void getCurrentDateTime(void);
void printTimeToSerial(void);
void printTimeToLcd(void);

#endif