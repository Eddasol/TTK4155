/*
 * adc.c
 *
 * Created: 27.09.2017 17:20:20
 *  Author: eddas, robbas og arras
 */ 
#include "adc.h"


enum dir{LEFT, RIGHT, UP, DOWN, NEUTRAL};

volatile int interrupt_triggered = 0;
ISR(INT2_vect){

	interrupt_triggered = 1;
}

void interrupt_init(){
	GICR |= (1<<INT2);
	EMCUCR &= ~(1 << ISC2); //Interrupt på stigende flanke
	sei();
}

int read_x(char *ADC_ptr){
	ADC_ptr[0]=0x05;
	
	while(interrupt_triggered==0){	}
	interrupt_triggered = 0;
	
	int x_value=ADC_ptr[0];
	int x_pro=x_value*0.784314-100;//0.784..=200/255, ble feil om ikke gjort på denne måten
	return (x_pro);
	
}

int read_y(char *ADC_ptr){
	ADC_ptr[0]=0x04;
	
	while(interrupt_triggered==0){	}
	interrupt_triggered = 0;
	
	int y_value=ADC_ptr[0];
	int y_pro=y_value*0.784314-100;
	return (y_pro);
}


int read_left(char *ADC_ptr){
	ADC_ptr[0]=0x06;
	
	while(interrupt_triggered==0){	}
	interrupt_triggered = 0;
	
	int l_value=ADC_ptr[0];
	int l_pro=l_value*100/255;
	return (l_pro);
}

int read_right(char *ADC_ptr){
	ADC_ptr[0]=0x07;
	
	while(interrupt_triggered==0){	}
	interrupt_triggered = 0;
	
	int r_value=ADC_ptr[0];
	int r_pro=r_value*100/255;
	return (r_pro);
}