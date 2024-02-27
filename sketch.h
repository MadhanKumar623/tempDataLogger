#ifndef SKETCH_H
#define SKETCH_H

#include <stdint.h>
#include <string.h>
#include <SD.h>
#include <SPI.h>
#include "i2c.h"
#include "rtc.h"
#include "lcd.h"
#include "uart.h"
#include "adc.h"

File myFile;

#define CLOCK_SPEED 16000000UL    //atmega2560 runs at 16MHz frequency
#define BAUD 9600UL

const float BETA = 3950;         //temperature coefficient of NTC
int pinCS = 53;                //CS pin is 53rd pin in arduino mega

//below are initial data to set during rtc_init()
uint8_t initial_hours = 23;       //24hour format
uint8_t initial_minutes = 59;     //initial date = 31-12-23
uint8_t initial_seconds = 50;     //initial time = 23:59:50
uint8_t initial_year = 23;
uint8_t initial_month = 12;
uint8_t initial_date = 31;

float tempResult;
char str[20];
extern uint8_t current_seconds;
extern char date_arr[20], time_arr[20];

#endif