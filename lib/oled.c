/*
 * oled.c
 *
 * Created: 27.09.2017 17:22:07
 *  Author: eddas, robbas og arras
 */ 

#include "oled.h"

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
	//oled_reset();
}

void oled_reset(){
	for(int line = 0; line < 8; line++){
		oled_clear_line(line);
	}
}

void oled_clear_line(uint8_t line){
	oled_write_c(0xb0 + line); // Selecting row/page
	for(int byte = 0; byte < 128; byte++){
		OLEDD_ptr[0] = 0xff; // Clear current column
	}
}

void oled_write_c(uint8_t command){
	OLEDC_ptr[0] = command;
}