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


int main(){
	uart_init(UBRR);
	fdevopen(&uart_transmit, &uart_receive);
	
	SFIOR |= (1 << XMM2);
	MCUCR |= (1 << SRE);
	oled_init();
	interrupt_init();
	DDRE |= (1 << PE1); // Setter PE høy med tanke på latchens virkemåte.
	DDRB &= ~(1 << PB1); // Knapp på joystick som input.
	
	
	SPI_MasterInit();
	mcp2515_Init();		//SPI_MasterInit kjøres inne i mcp2515_Init().
	can_Init();
	//mcp2515_BitModify(MCP_CANCTRL, 0xE0, MODE_CONFIG); //Should set the CAN-controller in LoopBack Mode. 0x0f is the address of CANCTRL register, 0x40 is the Loopback register value.
	mcp2515_BitModify(MCP_CANCTRL, 0xE0, MODE_LOOPBACK);
	//mcp2515_Write(MCP_CANCTRL, MODE_LOOPBACK);		//Kan brukes på samme måte som BitModify for å sjekke hvilken mode can-controlleren er i.

	volatile uint8_t *oled_command = 0x1000;
	volatile uint8_t *oled_data = 0x1200;
	_delay_ms(150);
	while (1){
		mcp2515_PrintMode();
	}
	//menu();
	
	can_message_t* msg;
	msg->data[0] = 0xed;
	msg->data[1] = 0xa1;
	msg->id = 0x1234;
	msg->length = 2;
	while(1){
		can_messageSend(msg,MCP_TXB0CTRL);
	}
	

	oled_reset();
	oled_bright();
	_delay_ms(1000);

	//menu_funct();		//Denne funksjonen er ikke helt ferdig implementert.
	char* menu[]={"Meny      ","Edda      ","Arild     ","Robin     ","yo        ","h         ","e         ","i         "};
	int numb_alt=8;

	oled_reset();
	char* str = "hei";
	for (int i=0; i< numb_alt;i++){
		oled_write_from_start_on_line(i);
		oled_write_string(menu[i],10,0);
	}
	oled_write_from_start_on_line(1);
	oled_write_string(menu[1],10,1);
	
	int index=0;
	while(1){
		

		
		index=menustep(menu,numb_alt);
		if(button_pressed()){
			printf("%s\n",menu[index]);
			_delay_ms(200);
		}
		_delay_ms(100);		

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