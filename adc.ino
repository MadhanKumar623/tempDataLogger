#include <Arduino.h>
#include "adc.h"

AnalogResult TempSensor;

void Adc_init()
{
   ADMUX = 0x40;         //result will be right justified
   ADCSRB = 0b00000000;  //ADC at free running mode, 0x00
   ADCSRA = 0b10000111;  //0x87
   DIDR0 = 1<<ADC0D;     //disabling the digital buffer in Analog input (A0)
}
uint16_t readAnalog0()
{
   ADCSRA |= (1 << ADSC);
   while (ADCSRA & (1 << ADSC));
   TempSensor.AD8Read.lowByteData = ADCL;      //storing low byte
   TempSensor.AD8Read.highByteData = ADCH;     //storing high byte
   return TempSensor.AD16Read;                 //returning as 16 bit data
}
float convertToCelcius(uint16_t analogValue)
{
    float celsius = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;
    return celsius;
}