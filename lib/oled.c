/*
 * oled.c
 *
 * Created: 27.09.2017 17:22:07
 *  Author: eddas, robbas og arras
 */ 

#include "oled.h"
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

volatile char *OLEDC_ptr = (uint8_t *) 0x1000; // Command char* before
volatile char *OLEDD_ptr = (uint8_t *) 0x1200; // Data char* before

/*
static unsigned int LCD_SegTable[] PROGMEM =
{
    0xEAA8,     // '*'
    0x2A80,     // '+'
    0x4000,     // ','
    0x0A00,     // '-'
    0x0A51,     // '.' Degree sign
    0x4008,     // '/'
}*/

const unsigned char PROGMEM font[95][5];


void oled_init(){
	oled_write_c(0xae);        //  display  off
	oled_write_c(0xa1);        //segment  remap
	oled_write_c(0xda);        //common  pads  hardware:  alternative
	oled_write_c(0x12);
	oled_write_c(0xc8);        //common output scan direction:com63~com0
	oled_write_c(0xa8);        //multiplex  ration  mode:63
	oled_write_c(0x3f);
	oled_write_c(0xd5);        //display divide ratio/osc. freq. mode
	oled_write_c(0x80);
	oled_write_c(0x81);        //contrast  control
	oled_write_c(0x50);
	oled_write_c(0xd9);        //set  pre-charge  period
	oled_write_c(0x21);
	oled_write_c(0x20);        //Set  Memory  Addressing  Mode
	oled_write_c(0x02);
	oled_write_c(0xdb);        //VCOM  deselect  level  mode
	oled_write_c(0x30);
	oled_write_c(0xad);        //master  configuration
	oled_write_c(0x00);
	oled_write_c(0xa4);        //out  follows  RAM  content
	oled_write_c(0xa6);        //set  normal  display
	oled_write_c(0xaf);        //  display  on
	oled_reset();
}

void oled_reset(){
	for(int line = 0; line < 8; line++){
		oled_clear_line(line);
	}
}

void oled_clear_line(uint8_t line){
	oled_write_c(0xb0 + line); // Selecting row/page
	for(int byte = 0; byte < 128; byte++){
		OLEDD_ptr[0] = 0x00; // Clear current column
	}
}

void oled_bright(){
	for(int line = 0; line < 8; line++){
		oled_write_c(0xb0+line);
		for(int byte = 0; byte < 128; byte++){
			OLEDD_ptr[0] = 0xff;
		}
	}
}

void oled_write_c(uint8_t command){
	OLEDC_ptr[0] = command;
}

void oled_write_char(char* str){
	uint8_t FONT_SIZE=5;
	for(uint8_t _col; _col < FONT_SIZE; _col++){
			*OLEDD_ptr = (pgm_read_byte(&(font[*str-32][_col])));
	}
}

void oled_write_char_inv(char* str){
	uint8_t FONT_SIZE=5;
	for(uint8_t _col; _col < FONT_SIZE; _col++){
		*OLEDD_ptr = ~(pgm_read_byte(&(font[*str-32][_col])));
	}
}


void oled_write_string(char* str, int size, int inv){
	if (!inv){
		for (int i = 0; i < size; i++){
			oled_write_char(str+i);
		}
	}
	else{
		for (int i = 0; i < size; i++){
			oled_write_char_inv(str+i);
		}
	}
	
	
}

void oled_write_from_start_on_line(int line){
		*OLEDC_ptr = 0xB0 + line;
		*OLEDC_ptr = 0x00;
		*OLEDC_ptr = 0x10;
}

const unsigned char PROGMEM font[95][5] = {
	{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, //   
	{0b00000000,0b00000000,0b01011110,0b00000000,0b00000000}, // ! 
	{0b00000000,0b00001110,0b00000000,0b00001110,0b00000000}, // " 
	{0b00101000,0b01111100,0b00101000,0b01111100,0b00101000}, // # 
	{0b00001000,0b01010100,0b01111100,0b01010100,0b00100000}, // $ 
	{0b00100110,0b00010000,0b00001000,0b01100100,0b00000000}, // % 
	{0b00101000,0b01010100,0b00101000,0b01000000,0b00000000}, // & 
	{0b00000000,0b00000000,0b00001110,0b00000000,0b00000000}, // ' 
	{0b00000000,0b00111100,0b01000010,0b00000000,0b00000000}, // ( 
	{0b00000000,0b01000010,0b00111100,0b00000000,0b00000000}, // ) 
	{0b00000000,0b01010100,0b00111000,0b01010100,0b00000000}, // * 
	{0b00010000,0b00010000,0b01111100,0b00010000,0b00010000}, // + 
	{0b00000000,0b10000000,0b01100000,0b00100000,0b00000000}, // , 
	{0b00010000,0b00010000,0b00010000,0b00010000,0b00000000}, // - 
	{0b00000000,0b01100000,0b01100000,0b00000000,0b00000000}, // . 
	{0b00100000,0b00010000,0b00001000,0b00000100,0b00000000}, // / 
	{0b00000000,0b00111100,0b01000010,0b00111100,0b00000000}, // 0 
	{0b00000000,0b01000100,0b01111110,0b01000000,0b00000000}, // 1 
	{0b01000100,0b01100010,0b01010010,0b01001100,0b00000000}, // 2 
	{0b00100010,0b01001010,0b01001010,0b00110110,0b00000000}, // 3 
	{0b00011000,0b00010100,0b01111110,0b00010000,0b00000000}, // 4 
	{0b00101110,0b01001010,0b01001010,0b00110010,0b00000000}, // 5 
	{0b00111100,0b01001010,0b01001010,0b00110000,0b00000000}, // 6 
	{0b00000010,0b01100010,0b00011010,0b00000110,0b00000000}, // 7 
	{0b00110100,0b01001010,0b01001010,0b00110100,0b00000000}, // 8 
	{0b00001100,0b01010010,0b01010010,0b00111100,0b00000000}, // 9 
	{0b00000000,0b01101100,0b01101100,0b00000000,0b00000000}, // : 
	{0b10000000,0b01101100,0b00101100,0b00000000,0b00000000}, // ; 
	{0b00000000,0b00010000,0b00101000,0b01000100,0b00000000}, // < 
	{0b00101000,0b00101000,0b00101000,0b00101000,0b00000000}, // = 
	{0b00000000,0b01000100,0b00101000,0b00010000,0b00000000}, // > 
	{0b00000000,0b00000100,0b01010010,0b00001100,0b00000000}, // ? 
	{0b00111100,0b01000010,0b01011010,0b00011100,0b00000000}, // @ 
	{0b01111100,0b00010010,0b00010010,0b01111100,0b00000000}, // A 
	{0b01111110,0b01001010,0b01001010,0b00110100,0b00000000}, // B 
	{0b00111100,0b01000010,0b01000010,0b00100100,0b00000000}, // C 
	{0b01111110,0b01000010,0b01000010,0b00111100,0b00000000}, // D 
	{0b01111110,0b01001010,0b01001010,0b01000010,0b00000000}, // E 
	{0b01111110,0b00001010,0b00001010,0b00000010,0b00000000}, // F 
	{0b00111100,0b01000010,0b01010010,0b01110100,0b00000000}, // G 
	{0b01111110,0b00001000,0b00001000,0b01111110,0b00000000}, // H 
	{0b00000000,0b01000010,0b01111110,0b01000010,0b00000000}, // I 
	{0b00100000,0b01000000,0b01000000,0b00111110,0b00000000}, // J 
	{0b01111110,0b00011000,0b00100100,0b01000010,0b00000000}, // K 
	{0b01111110,0b01000000,0b01000000,0b01000000,0b00000000}, // L 
	{0b01111110,0b00001100,0b00001100,0b01111110,0b00000000}, // M 
	{0b01111110,0b00001100,0b00110000,0b01111110,0b00000000}, // N 
	{0b00111100,0b01000010,0b01000010,0b00111100,0b00000000}, // O 
	{0b01111110,0b00010010,0b00010010,0b00001100,0b00000000}, // P 
	{0b00111100,0b01100010,0b01000010,0b10111100,0b00000000}, // Q 
	{0b01111110,0b00010010,0b00110010,0b01001100,0b00000000}, // R 
	{0b00100100,0b01001010,0b01010010,0b00100100,0b00000000}, // S 
	{0b00000000,0b00000010,0b01111110,0b00000010,0b00000000}, // T 
	{0b00111110,0b01000000,0b01000000,0b00111110,0b00000000}, // U 
	{0b00011110,0b01100000,0b01100000,0b00011110,0b00000000}, // V 
	{0b01111110,0b00110000,0b00110000,0b01111110,0b00000000}, // W 
	{0b01100110,0b00011000,0b00011000,0b01100110,0b00000000}, // X 
	{0b00000000,0b00001110,0b01110000,0b00001110,0b00000000}, // Y 
	{0b01100010,0b01010010,0b01001010,0b01000110,0b00000000}, // Z 
	{0b00000000,0b01111110,0b01000010,0b01000010,0b00000000}, // [ 
	{0b00000100,0b00001000,0b00010000,0b00100000,0b00000000}, // "\" 
	{0b00000000,0b01000010,0b01000010,0b01111110,0b00000000}, // ] 
	{0b00000000,0b00000100,0b00000010,0b00000100,0b00000000}, // ^ 
	{0b01000000,0b01000000,0b01000000,0b01000000,0b00000000}, // _ 
	{0b00000000,0b00000010,0b00000100,0b00000000,0b00000000}, // ` 
	{0b00110000,0b01001000,0b00101000,0b01111000,0b00000000}, // a 
	{0b01111110,0b01001000,0b01001000,0b00110000,0b00000000}, // b 
	{0b00110000,0b01001000,0b01001000,0b00000000,0b00000000}, // c 
	{0b00110000,0b01001000,0b01001000,0b01111110,0b00000000}, // d 
	{0b00110000,0b01101000,0b01011000,0b00010000,0b00000000}, // e 
	{0b00010000,0b01111100,0b00010010,0b00000100,0b00000000}, // f 
	{0b01010000,0b10101000,0b10101000,0b10011000,0b00000000}, // g 
	{0b01111110,0b00001000,0b00001000,0b01110000,0b00000000}, // h 
	{0b00000000,0b01001000,0b01111010,0b01000000,0b00000000}, // i 
	{0b00000000,0b01000000,0b10000000,0b01111010,0b00000000}, // j 
	{0b01111110,0b00010000,0b00101000,0b01000000,0b00000000}, // k 
	{0b00000000,0b01000010,0b01111110,0b01000000,0b00000000}, // l 
	{0b01111000,0b00010000,0b00011000,0b01110000,0b00000000}, // m 
	{0b01111000,0b00001000,0b00001000,0b01110000,0b00000000}, // n 
	{0b00110000,0b01001000,0b01001000,0b00110000,0b00000000}, // o 
	{0b11111000,0b01001000,0b01001000,0b00110000,0b00000000}, // p 
	{0b00110000,0b01001000,0b01001000,0b11111000,0b00000000}, // q 
	{0b01111000,0b00001000,0b00001000,0b00010000,0b00000000}, // r 
	{0b01010000,0b01011000,0b01101000,0b00101000,0b00000000}, // s 
	{0b00001000,0b00111110,0b01001000,0b01000000,0b00000000}, // t 
	{0b00111000,0b01000000,0b01000000,0b01111000,0b00000000}, // u 
	{0b00000000,0b00111000,0b01000000,0b00111000,0b00000000}, // v 
	{0b01111000,0b01100000,0b01100000,0b01111000,0b00000000}, // w 
	{0b01001000,0b00110000,0b00110000,0b01001000,0b00000000}, // x 
	{0b00011000,0b10100000,0b01000000,0b00111000,0b00000000}, // y 
	{0b01001000,0b01101000,0b01011000,0b01001000,0b00000000}, // z 
	{0b00000000,0b00001000,0b00111100,0b01000010,0b00000000}, // 
	{0b00000000,0b00000000,0b01111110,0b00000000,0b00000000}, // | 
	{0b00000000,0b01000010,0b00111100,0b00001000,0b00000000}, // 
	{0b00000100,0b00000010,0b00000100,0b00000010,0b00000000}, // ~ 
};