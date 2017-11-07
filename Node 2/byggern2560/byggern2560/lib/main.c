/*
 * byggern2560.c
 *
 * Created: 01.11.2017 13:06:58
 * Author : Arild Stenset
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>

#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD - 1)		//If this doesn't work, set MYUBRR to 103. Check Table 22-12.

#include "uart.h"
#include "spi.h"
#include "MCP2515.h"
#include "can.h"
#include "pwm.h"

volatile int can_message_received = 0;

void interrupt_Enable(){
	mcp2515_BitModify(MCP_CANINTE, MCP_RX0IE, MCP_RX0IE);		// Enables interrupt on received can messages.
	EIMSK |= (1 << INT2);				// Enable interrupt on INT2
	EICRA |= (1 << ISC21);				// Interrupts on falling edge for mcp
	EICRA &= ~(1 >> ISC20);				// Interrupts on falling edge for mcp
	sei();								// Set global interrupt flag
}

ISR(INT2_vect){
	can_message_received = 1;
	printf("triggered\n");
}

int main(void){
	
	uart_init(MYUBRR);
	fdevopen(&uart_transmit, &uart_receive);
	SPI_MasterInit();
	mcp2515_Init();
	can_Init();
	//interrupt_Enable();
	//mcp2515_BitModify(MCP_CANCTRL, MODE_MASK, MODE_CONFIG);		//Set mcp in config mode
	mcp2515_BitModify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);		//Set mcp in normal mode
	//mcp2515_BitModify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);		//Set mcp in loopback mode
	//mcp2515_Write(MCP_CANCTRL, MODE_LOOPBACK);		//Kan brukes på samme måte som BitModify for å sjekke hvilken mode can-controlleren er i.
	pwm_Init();
	/*
	while (1){
		mcp2515_PrintMode();
		_delay_ms(200);
	}
	*/

	while(1){
		can_message_t* msg;
		msg->data[0] = 0x29;	// 0b 1110 1101				= DECIMAL 237
		msg->data[1] = 0x12;	// 0b 1010 0001				= DECIMAL 161
		msg->id = 0x0069;		// 0b 0001 0010 0011 0100	= DECIMAL 4660
		msg->length = 0x2;		// 0b 0010					= DECIMAL 2
		can_sendMessage(*msg);
		
		/*
		if(can_message_received){
			printf("Interrupt\n");
			can_print(can_read());
			can_message_received = 0;
		}
		*/

		//pwm_test();
		pwm_setServo(can_read());
		//_delay_ms(20);
		//can_print(can_read());
	}
	

	while(1);
    return 0;
}

