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

int main(void){

	uart_init(MYUBRR);
	fdevopen(&uart_transmit, &uart_receive);
	SPI_MasterInit();
	mcp2515_Init();
	//pwmDriver();
	can_Init();		//CanInit funker pr 01.11.2017 ikke på Atmega2560'n
	_delay_ms(100);
	//mcp2515_BitModify(MCP_CANCTRL, 0xE0, MODE_CONFIG);		//Set mcp in config mode
	//mcp2515_BitModify(MCP_CANCTRL, 0xE0, MODE_NORMAL);		//Set mcp in normal mode
	mcp2515_BitModify(MCP_CANCTRL, 0xE0, MODE_LOOPBACK);		//Set mcp in loopback mode
	_delay_ms(100);
	//mcp2515_Write(MCP_CANCTRL, MODE_LOOPBACK);		//Kan brukes på samme måte som BitModify for å sjekke hvilken mode can-controlleren er i.
	
	/*
	while (1){
		mcp2515_PrintMode();
		_delay_ms(200);
	}
	*/
	
	while(1){
		can_message_t* msg;
		msg->data[0] = 0xEd;	// 0b 1110 1101				= DECIMAL 237
		msg->data[1] = 0xA1;	// 0b 1010 0001				= DECIMAL 161
		msg->id = 0x0044;		// 0b 0001 0010 0011 0100	= DECIMAL 4660
		msg->length = 0x2;		// 0b 0010					= DECIMAL 2
		can_sendMessage(*msg);
		can_print(can_read());
		_delay_ms(100);
	}
	

	while(1);
    return 0;
}

