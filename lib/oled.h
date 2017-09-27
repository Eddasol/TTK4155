/*
 * oled.h
 *
 * Created: 27.09.2017 17:22:20
 *  Author: eddas
 */ 


#ifndef OLED_H_
#define OLED_H_

void oled_init();
void oled_reset();
void oled_clear_line(uint8_t line);
void oled_write_c(uint8_t command);

#endif /* OLED_H_ */