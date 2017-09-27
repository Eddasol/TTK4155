/*
 * adc.h
 *
 * Created: 27.09.2017 17:20:53
 *  Author: eddas
 */ 

#include <avr/io.h>

#ifndef ADC_H_
#define ADC_H_

void interrupt_init();
int read_x(char *ADC_ptr);
int read_y(char *ADC_ptr);
int read_left(char *ADC_ptr);
int read_right(char *ADC_ptr);

#endif /* ADC_H_ */