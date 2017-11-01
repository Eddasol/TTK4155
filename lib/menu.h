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



typedef struct menu menu;

struct menu{

	menu *parent;

	menu *children[10];

	int numb_children;

	char name[20];

};

void menu_funct();

void make_menu(menu* newmenu, menu *_parent,menu **_children,int _numb_children,char* _name);
void make_menu_only_name(menu* newmenu,char* _name);
void addChildParent(menu* _parent, menu* _child);
void addParentAsLastChild(menu* _menu);

char* menu_control(menu* current_menu);
int menustep(menu* _menu);
menu* createAllMenu();

#endif /* MENU_H_ */