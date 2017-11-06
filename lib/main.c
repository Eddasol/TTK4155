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
#include "menu.h"
#include "MCP2515.h"
#include "spi.h"
#include "can.h"
#include "joystick.h"

int main(){
	uart_init(UBRR);
	fdevopen(&uart_transmit, &uart_receive);
	
	SFIOR |= (1 << XMM2);		// This has to be set in order to use the programming pins for JTAG as normal, which means that a 64kbit address space cannot be reached.
	MCUCR |= (1 << SRE);		// Enable External SRAM
	DDRE |= (1 << PE1);			// Setter PE høy med tanke på latchens virkemåte.
	DDRB &= ~(1 << PB1);		// Sets joystick pushbutton as input
	
	oled_init();
	interrupt_init();
	SPI_MasterInit();
	mcp2515_Init();
	can_Init();

	mcp2515_BitModify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);		//Set mcp in normal mode
	//mcp2515_Write(MCP_CANCTRL, MODE_LOOPBACK);				//The mcp Write function can be used in the same way as the bitmodify in order to set the mode of the mcp. Here used for test purposes.

	menu_funct();	
	//mcp2515_PrintMode();
	while(1){
		/*
		can_message_t* msg;
		msg->data[0] = 0x00;	// 0b 1110 1101 =			DECIMAL 237
		msg->data[1] = 0x33;	// 0b 1010 0001 =			DECIMAL 161
		msg->id = 0x0082;		// 0b 0001 0010 0011 0100 = DECIMAL 4660
		msg->length = 0x2;		// 0b 0010 =				DECIMAL 2
		can_sendMessage(*msg);
		can_print(can_read());
		*/
		joystickDriver();
		//_delay_ms(100);
		if(get_can_message_received()){
			can_print(can_read());
		}
		_delay_ms(100);
	}

	return 0;
}

ISR(INT0_vect){
	set_can_message_received();
	//printf("interrupt\t");
}