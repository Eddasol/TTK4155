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

/*int get_string_size(int page, int line){
	int length;
	for(int i = 0; menu_options[page][line][i] != '\0'; ++i){
		length = i;
	}
	return length;
}*/
/*
void menu(){
	oled_reset();
	
	char* string[3]={"alt1  ","alt2  ","Alt3  "};
	int lenght[3]={4,4,4};
	int size=3;
	for(int i =0;i<size;i++){
		oled_write_from_start_on_line(i+1);
		oled_write_string(string[i],lenght[i],0);
	}
	int invertedIndex=0;
	int direction;
	while(1){
		int y=read_y();
	if(y>10){
		oled_write_from_start_on_line(invertedIndex+1);
		oled_write_string(string[invertedIndex],lenght[invertedIndex],0);
		invertedIndex=(invertedIndex-1)%size;
		oled_write_from_start_on_line(invertedIndex+1);
		oled_write_string(string[invertedIndex],lenght[invertedIndex],1);
		direction=1;
	}
	else if(y<-10){
		oled_write_from_start_on_line(invertedIndex+1);
		oled_write_string(string[invertedIndex],lenght[invertedIndex],0);
		invertedIndex=(invertedIndex+1)%size;
		oled_write_from_start_on_line(invertedIndex+1);
		oled_write_string(string[invertedIndex],lenght[invertedIndex],1);
		direction=-1;
	}
		else{ direction=0;}
	int delay=direction*1000/y;
	_delay_ms(100);
	
	}
*/
int* calculateJoystickPosition(can_message_t message){
	int calculatedJoystickPositionData[2] = {-1000, -1000};
	// if x position is supposed to have a negative value, set it negative
	if(message.data[2] == 1){
		calculatedJoystickPositionData[0] = message.data[0] - 256;	
	}else{
		calculatedJoystickPositionData[0] = message.data[0];
	}
	// if y position is supposed to have a negative value, set it negative
	if(message.data[3] == 1){
		calculatedJoystickPositionData[1] = message.data[1] - 256;
	}else{
		calculatedJoystickPositionData[1] = message.data[1];
	}
	return calculatedJoystickPositionData;
}

void joystickDriver() {
	can_message_t* msgJoystickPosition;
	msgJoystickPosition->data[0] = read_x();	// 0b 1110 1101 =			DECIMAL 237
	msgJoystickPosition->data[1] = read_y();	// 0b 1010 0001 =			DECIMAL 161
	msgJoystickPosition->data[2] = (read_x() < 0) ? 1 : 0;
	msgJoystickPosition->data[3] = (read_y() < 0) ? 1 : 0;
	msgJoystickPosition->id = 0x0000;		// 0b 0001 0010 0011 0100 = DECIMAL 4660
	msgJoystickPosition->length = 0x2;		// 0b 0010 =				DECIMAL 2
	
	can_sendMessage(*msgJoystickPosition);
	//can_print(can_read());
	int* ls = calculateJoystickPosition(*msgJoystickPosition);
	printf("%i, %i\n", ls[0], ls[1]);
	//printf("%i\n", read_x());
	_delay_ms(300);
}

int main(){
	uart_init(UBRR);
	fdevopen(&uart_transmit, &uart_receive);
	
	SFIOR |= (1 << XMM2);		//This has to be set in order to use the programming pins for JTAG as normal, which means that a 64kbit adress space cannot be reached.
	MCUCR |= (1 << SRE);		
	oled_init();
	interrupt_init();
	DDRE |= (1 << PE1);			// Setter PE høy med tanke på latchens virkemåte.
	DDRB &= ~(1 << PB1);		// Sets joystick pushbutton as input
	
	
	SPI_MasterInit();
	mcp2515_Init();
	can_Init();
	//mcp2515_BitModify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
	mcp2515_BitModify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
	//mcp2515_Write(MCP_CANCTRL, MODE_LOOPBACK);				//The mcp Write function can be used in the same way as the bitmodify in order to set the mode of the mcp. Here used for test purposes.

	volatile uint8_t *oled_command = 0x1000;
	volatile uint8_t *oled_data = 0x1200;
	
	//while (1){
	//	mcp2515_PrintMode();
	//}
	//menu();

	while(1){
		can_message_t* msg;
		msg->data[0] = 0xEC;	// 0b 1110 1101 =			DECIMAL 237
		msg->data[1] = 0xA0;	// 0b 1010 0001 =			DECIMAL 161
		msg->id = 0x0032;		// 0b 0001 0010 0011 0100 = DECIMAL 4660
		msg->length = 0x2;		// 0b 0010 =				DECIMAL 2
		can_sendMessage(*msg);
		can_print(can_read());
		_delay_ms(100);
		
	}

	oled_reset();
	oled_bright();
	_delay_ms(1000);

	menu_funct();		//Denne funksjonen er ikke helt ferdig implementert.
	while(1){
			

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
	}	
	return 0;
}