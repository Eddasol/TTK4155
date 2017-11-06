/*
 * menu.c
 *
 * Created: 04.10.2017 16:39:11
 *  Author: eddas
 */ 

#include "adc.h"
#include "oled.h"
#include "menu.h"
#include <util/delay.h>

#define number_of_pages 1
#define menu_items 3

const int length=20;
char back[20]="back                ";
int line_to_invert=1;

#include <stdio.h>


void menu_funct(){
	printf(menu_control(createAllMenu()));
}

void make_menu(menu* newmenu, menu *_parent,menu **_children,int _numb_children,char* _name){
	newmenu->parent=_parent;
	for (int i = 0; i<_numb_children;i++){
		newmenu->children[i]=_children[i];
	}
	newmenu->numb_children=_numb_children;
	int i=0;
	while(_name[i]!='.'){
		newmenu->name[i]=_name[i];
		i+=1;
	}
	while(i<length){
		newmenu->name[i]=' ';
		i+=1;
	}
}

void make_menu_only_name(menu* newmenu,char* _name){
	int i=0;
	while(_name[i]!='.'){
		newmenu->name[i]=_name[i];
		i+=1;
	}
	while(i<length){
		newmenu->name[i]=' ';
		i+=1;
	}
	newmenu->numb_children=0;
}

void addChildParent(menu* _parent, menu* _child){
	_parent->children[_parent->numb_children]=_child;
	_parent->numb_children+=1;
	_child->parent=_parent;
}

void addParentAsLastChild(menu* _menu){
	_menu->children[_menu->numb_children]=_menu;
	_menu->numb_children+=1;
}

char* menu_control(menu* current_menu){
	oled_reset();
	if(current_menu->numb_children==0){
		printf ("return");
		return current_menu->name;
	}
	
	oled_write_from_start_on_line(0);//Printer overskrift
	oled_write_string(current_menu->name,length,0);
	for (int i=0; i< current_menu->numb_children;i++){
		oled_write_from_start_on_line(i+1);
		oled_write_string(current_menu->children[i]->name,length,0);//Printer alternativ
	}
	if(current_menu->parent!=NULL){
		oled_write_from_start_on_line(current_menu->numb_children-1);
		oled_write_string(back,length,0);//Legger til back som alternativ
	}

	oled_write_from_start_on_line(1);
	oled_write_string(current_menu->children[0]->name,length,1);//Velger linje 1 som valgt ved start
	int index=0;
	while(1){
		index = menustep(current_menu);
		if (button_pressed()){
			
			printf("Button pressed");
			_delay_ms(500);
			return menu_control(current_menu->children[index]);
		}
		_delay_ms(200);
	}
}




int menustep(menu* _menu){
	int direction = 0;
	int joystick_Position = read_y()*0.784314-100;
	
	if(joystick_Position > 20){
		direction = 1;
	}

	if(joystick_Position < -20){
		direction = -1;
	}
	if(direction){
		oled_write_from_start_on_line(line_to_invert+1);
		if (_menu->parent==_menu->children[line_to_invert]){
			oled_write_string(back,length,0);	
		}
		else{
			oled_write_string(_menu->children[line_to_invert]->name,length,0);
		}
		
		line_to_invert = (line_to_invert-direction+_menu->numb_children)%(_menu->numb_children);
		oled_write_from_start_on_line(line_to_invert+1);
		if (_menu->parent==_menu->children[line_to_invert]){
			oled_write_string(back,length,1);
		}
		else{
			oled_write_string(_menu->children[line_to_invert]->name,length,1);
		}
	}
	return line_to_invert;
}


menu* createAllMenu(){
	menu *mainmenu=malloc(sizeof(menu));
	menu *menu1=malloc(sizeof(menu));
	menu *menu2=malloc(sizeof(menu));
	menu *menu3=malloc(sizeof(menu));
	menu *menu11=malloc(sizeof(menu));
	menu *menu12=malloc(sizeof(menu));
	make_menu_only_name(mainmenu,"mainmenu.");
	make_menu_only_name(menu1,"menu1.");
	make_menu_only_name(menu2,"menu2.");
	make_menu_only_name(menu3,"menu3.");
	make_menu_only_name(menu11,"menu11.");
	make_menu_only_name(menu12,"menu12.");
	addChildParent(mainmenu,menu1);
	addChildParent(mainmenu,menu2);
	addChildParent(mainmenu,menu3);
	addChildParent(menu1,menu11);
	addChildParent(menu1,menu12);
	addParentAsLastChild(menu1);
	return mainmenu;
}