#ifndef LCD_H_
#define LCD_H_

void Lcd_init(void);
void Lcd_sendString(char*);
void Lcd_sendData(uint8_t);
void Lcd_sendCommand(uint8_t);

#endif