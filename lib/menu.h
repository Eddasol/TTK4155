/*
 * menu.h
 *
 * Created: 04.10.2017 16:39:22
 *  Author: eddas
 */ 

#include <stdlib.h>
#include <avr/io.h>


#ifndef MENU_H_
#define MENU_H_



int menustep(char* menu[], int size);
struct menu make_menu();

char* menu_control(struct menu current_menu);
void menu_funct();
void test();

#endif /* MENU_H_ */