#ifndef ADC_H
#define ADC_H

typedef struct
{
    uint8_t lowByteData;       //make data to be as RIGHT JUSTIFIED
    uint8_t highByteData;
}IndividualBytes;

typedef union{
    uint16_t AD16Read;
    IndividualBytes AD8Read;    
}AnalogResult;


void Adc_init(void);
uint16_t readAnalog0(void);
float convertToCelcius(uint16_t);

#endif