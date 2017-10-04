/*
 * byggern.c
 *
 * Created: 27.09.2017 17:00:29
 *  Author: eddas, robbas og arras
 */ 

#define F_CPU 4915200UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>


#include "uart.h"
#include "adc.h"
#include "oled.h"
#include "sram.h"




volatile char *ADC_ptr = (char *) 0x1400;

int main(){
	uart_init(UBRR);
	fdevopen(&uart_transmit, &uart_receive);
	
	SFIOR |= (1 << XMM2);
	MCUCR |= (1 << SRE);
	oled_init();
	interrupt_init();
	DDRE |= (1 << PE1); // Setter PE høy med tanke på latchens virkemåte

	//SRAM_test();
	
	volatile uint8_t *oled_command = 0x1000;
	
	volatile uint8_t *oled_data = 0x1200;
	
	for(int j = 0; j < 8; j++){
		*oled_command = 0xB0 + j;
		*oled_command = 0x00;
		*oled_command = 0x10;
		for (uint32_t i = 0; i < 8*128; i++) {
			*oled_data = 0xFF;
		}
	}
	int j=0;
	printf("Done\r\n");
	oled_reset();
	while(1){
		oled_reset();

		char* str1 = "robiIN heio hie";
		char* str2 = "arild king of karsk";
		char* str3 = "Edda yoyoyo";
		 
		int size1=15;
		int size2=19;
		int size3=11;
		
		oled_write_from_start_on_line(0);
		oled_write_string(str1,size1,0);
		
		oled_write_from_start_on_line(1);
		oled_write_string(str2,size2,0);

		oled_write_from_start_on_line(2);
		oled_write_string(str3,size3,0);
		
		_delay_ms(1000);
		
		//oled_reset();
		
		//_delay_ms(1000);
		//oled_bright();
		//_delay_ms(1000);
		
/*
		_delay_ms(1000);
		volatile uint8_t *oled_data = 0x1200;
		for (uint32_t i = 0; i < 8*128; i++) {
			*oled_data = i;
		}
	*/
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

