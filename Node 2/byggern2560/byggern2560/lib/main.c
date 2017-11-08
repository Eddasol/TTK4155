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

#include "uart.h"
#include "spi.h"
#include "MCP2515.h"
#include "can.h"
#include "pwm.h"
#include "init.h"
#include "ir.h"
#include "game.h"
#include "adc.h"

volatile int can_message_received = 0;

int main(void){
	initialize();
	fdevopen(&uart_transmit, &uart_receive);
	
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

		//pwm_setServo(can_read());
		//can_print(can_read());
		uint8_t val = adc_read(IR_CHANNEL);
		printf("ADC-value: %d\n", val);
		_delay_ms(50);

	}
	

	while(1);
    return 0;
}

ISR(INT2_vect){
	can_message_received = 1;
	printf("triggered\n");
}
