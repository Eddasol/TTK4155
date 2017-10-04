/*
 * oled.h
 *
 * Created: 27.09.2017 17:22:20
 *  Author: eddas
 */ 

#include <avr/io.h>

#ifndef OLED_H_
#define OLED_H_



void oled_init();
void oled_write_char(char* str);
void oled_write_string(char* str, int size, int inv);
void oled_write_from_start_on_line(int line);
void oled_reset();
void oled_bright();
void oled_clear_line(uint8_t line);
void oled_write_c(uint8_t command);

#endif /* OLED_H_ */