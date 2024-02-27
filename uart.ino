#include <Arduino.h>
#include "uart.h"

void Serial0_init(uint16_t baud_rate)
{
    uint16_t ubrr_value;
    ubrr_value = 103;          //calculated UBRR value for 9600 baud rate ((CLOCK_SPEED/(16*baud_rate)) - 1)
    UBRR0H = (uint8_t)(ubrr_value>>8);
    UBRR0L = (uint8_t)ubrr_value;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);              //enabling receiver and transmitter
    UCSR0C = 0x06;                               //one stop bit and 8 bit frame
}
void Serial0_transmitChar(uint8_t a)
{
     while (!( UCSR0A & (1<<UDRE0)));   //wait until transmit buffer is empty
     UDR0 = a;
     while (!( UCSR0A & (1<<TXC0)));    //wait until data get transmitted
}
void Serial0_transmitString(char *ptr)
{
     while(*ptr!='\0')
     {
        Serial0_transmitChar(*ptr);
        ptr++;
     }
}
