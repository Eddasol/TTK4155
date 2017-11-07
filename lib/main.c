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
	initialization();
	fdevopen(&uart_transmit, &uart_receive);
	
	//menu_funct();	
	
	while(1){
		/*
		can_message_t* msg;
		msg->data[0] = 0x00;	// 0b 1110 1101 =			DECIMAL 237
		msg->data[1] = 0x33;	// 0b 1010 0001 =			DECIMAL 161
		msg->id = 0x0082;		// 0b 0001 0010 0011 0100 = DECIMAL 4660
		msg->length = 0x2;		// 0b 0010 =				DECIMAL 2
		can_sendMessage(*msg);
		*/
		
		joystickDriver();
		//_delay_ms(100);
		
		/*
		if(get_can_message_received()){				//Update 07.11.17: vi tok feil angående interruptsa, de funker ikke.
			can_print(can_read());
		}
		*/
		
		//joystick_Print_Values();
		
		can_print(can_read());			
		_delay_ms(100);
	}

	return 0;
}

ISR(INT0_vect){						//Not working as intended
	set_can_message_received();
	printf("interrupt\t");
}