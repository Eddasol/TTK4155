/*
 * init.c
 *
 * Created: 08.11.2017 10:25:11
 *  Author: Arild Stenset
 */ 

 #define F_CPU 16000000UL
 #define BAUD 9600
 #define MYUBRR (F_CPU/16/BAUD - 1)		//If this doesn't work, set MYUBRR to 103. Check Table 22-12.

 #include <avr/interrupt.h>

 #include "init.h"
 #include "uart.h"
 #include "spi.h"
 #include "MCP2515.h"
 #include "can.h"
 #include "pwm.h"
 #include "adc.h"
 
 void initialize(){
	uart_init(MYUBRR);
	SPI_MasterInit();
	mcp2515_Init();
	can_Init();
	mcp2515_BitModify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);			//Set mcp in normal mode
	pwm_Init();
	adc_init();
 }

 void init_interrupt(){
	 mcp2515_BitModify(MCP_CANINTE, MCP_RX0IE, MCP_RX0IE);			// Enables interrupt on received can messages.
	 EIMSK |= (1 << INT2);											// Enable interrupt on INT2
	 EICRA |= (1 << ISC21);											// Interrupts on falling edge for mcp
	 EICRA &= ~(1 >> ISC20);										// Interrupts on falling edge for mcp
	 sei();															// Set global interrupt flag
 }