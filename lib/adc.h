/*
 * adc.h
 *
 * Created: 27.09.2017 17:20:53
 *  Author: eddas
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef ADC_H_
#define ADC_H_

ISR(INT2_vect);
void interrupt_init();
int button_pressed();
int read_x();
int read_y();
int read_left();
int read_right();

#endif /* ADC_H_ */