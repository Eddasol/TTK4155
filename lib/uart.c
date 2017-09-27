/*
 * uart.c
 *
 * Created: 27.09.2017 17:21:39
 *  Author: eddas
 */ 
#include "uart.h"

void uart_init(unsigned int baud){
	
	//UBRR1 = (unsigned char)51;
	//Set baud-rate:
	//UBRR1H = (uint8_t)(((F_CPU/(BAUD*16UL))-1) >> 8);
	//UBRR1L = (uint8_t)((F_CPU/(BAUD*16UL))-1);
	
	UBRR0H = (unsigned char)(UBRR >> 8);
	UBRR0L = (unsigned char) UBRR;
	
	//Enable receiver and transmitter:
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	//Set frame format: 8 data, 2 stop bit:
	//UCSR1C = (1<<UMSEL0) | (1<<USBS1) | (1<<UCSZ00) | (1<<UCSZ01);
	
}

void uart_transmit(char c) {
	//Sjekk om det er klart for å sende, hvis ikke, vent til det er klart
	//Skriv riktig bokstav til riktig register
	
	//Wait for empty transmit buffer
	while(!(UCSR0A & (1<<UDRE0))){}
	//Put data into buffer;
	
	UDR0 = c;
}

unsigned char uart_receive(){
	while (!(UCSR0A & (1 << RXC0))) {}
	
	return UDR0;
}
