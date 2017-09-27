/*
 * byggern.c
 *
 * Created: 27.09.2017 17:00:29
 *  Author: eddas, robbas og arras
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>

#include "uart.h"
#include "adc.h"
#include "oled.h"
#include "sram.h"

#define F_CPU 4915200UL
#define BAUD 9600
#define UBRR 31

volatile char *OLEDC_ptr = (uint8_t *) 0x1000; // Command char* before
volatile char *OLEDD_ptr = (uint8_t *) 0x1200; // Data char* before
volatile char *ADC_ptr = (char *) 0x1400;
volatile char *SRAM_ptr = (char *) 0x1800;



int main(){
	uart_init(UBRR);
	fdevopen(&uart_transmit, &uart_receive);
	
	SFIOR |= (1 << XMM2);
	MCUCR |= (1 << SRE);
	//oled_init();
	//interrupt_init();
	//DDRE |= (1 << PE1); // Setter PE høy med tanke på latchens virkemåte
					
	//printf("Reboot\r\n");
	
//	_delay_ms(10);
	//volatile char *foo = (char *) 0x1801; // Start address for the SRAM

	while(1){
		
		//_delay_us(1);	

		//OLEDC_ptr[0]=0;
		//_delay_ms(1000);
		//OLEDD_ptr[0]=0;
		//oled_reset();
		//_delay_ms(100);
		
		//SRAM_test();
		/*
		printf("x: %d\t", read_x(ADC_ptr));
		printf("y: %d\t",read_y(ADC_ptr));
		//_delay_ms(100);
		printf("left: %d\t",read_left(ADC_ptr));
		//_delay_us(1);
		printf("right: %d\t",read_right(ADC_ptr));
		*/
		//	printf("s\n");
		
		_delay_ms(1000);
		//printf("OLEDC\n");
		OLEDC_ptr[0]=1;
		
		_delay_ms(1000);
		//printf("OLEDD\n");
		OLEDD_ptr[0]=1;
		
		_delay_ms(1000);
		//printf("SRAM\n");
		SRAM_ptr[0]=1;
		
		_delay_ms(1000);
		//printf("ADC\n");
		ADC_ptr[0]=1;
		
		/*
		uart_transmit('H');
		uart_transmit('e');
		uart_transmit('i');
		uart_transmit('\r');
		uart_transmit('\n');
		
		//fdevopen(uart_transmit, uart_receive);
		//printf("UART REC = %c\n",uart_receive());
		PORTA |= (1 << PA0);
		_delay_ms(100);
		PORTA |= (1 << PA1);
		_delay_ms(100);
		PORTA |= (1 << PA2);
		_delay_ms(100);
		PORTA &= !(1 << PA0);
		_delay_ms(100);
		PORTA &= !(1 << PA1);
		_delay_ms(100);
		PORTA &= !(1 << PA2);
		_delay_ms(100);
		*/	
		/*
		//
		//PORTC &= ~(1 << PC3);
		//PORTC &= ~(1 << PC2);
		//PORTC &= ~(1 << PC1);		//Setter de tre bit'ene til 0 ved initialisering, output til OLED command LAV.
		//_delay_ms(1000);
		//PORTC |= (1 << PC1);		//OUTPUT til OLED data LAV.
		//_delay_ms(1000);
		//PORTC &= ~(1 << PC1);		
		//PORTC |= (1 << PC2);
		//_delay_ms(100);
		//PORTC &= ~(1 << PC2);
		//PORTC |= (1 << PC3);
		//_delay_ms(10);
		//PORTC &= ~(1 << PC3);
		*/
		
	}	
	return 0;
}

ISR(INT2_vect){

	interrupt_triggered = 1;
}