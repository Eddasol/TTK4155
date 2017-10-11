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



volatile char *ADC_ptr = (char *) 0x1400;


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
		int y=read_y(ADC_ptr);
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
	DDRE |= (1 << PE1); // Setter PE høy med tanke på latchens virkemåte
	DDRB &= ~(1 << PB1); // skal sette PB1 som input. Knapp på joystick.

	//SRAM_test();
	
	volatile uint8_t *oled_command = 0x1000;
	
	volatile uint8_t *oled_data = 0x1200;
	
	/*for(int j = 0; j < 8; j++){
		*oled_command = 0xB0 + j;
		*oled_command = 0x00;
		*oled_command = 0x10;
		for (uint32_t i = 0; i < 8*128; i++) {
			*oled_data = 0xFF;
		}
	}
	*/
	//menu();		


	oled_reset();
	oled_bright();
	_delay_ms(1000);

	menu_funct();
	char* menu[]={"Meny      ","Edda      ","Arild     ","Robin     ","yo        ","h         ","e         ","i         "};
	int numb_alt=8;

	oled_reset();
	char* str="hei";
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

