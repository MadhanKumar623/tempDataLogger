#ifndef I2C_H_
#define I2C_H_

#define RTC_R 0xd1     //slave address is 0x68 for RTC
#define RTC_W 0xd0
#define LCD_R 0x4f     //slave address is 0x27 for LCD
#define LCD_W 0x4e

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(uint8_t);
uint8_t i2c_read(uint8_t);
void i2c_send(uint8_t);
void i2c_repeatedStart(void);

#endif