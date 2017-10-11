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

volatile char *ADCptr = (char *) 0x1400;

/*char* menu_control(struct menu current_menu);
struct menu set_options(int index,char* str, int size, struct menu name);
struct menu init(int numb_opt,char* stringOptions[], int stringSizes[], struct menu nextMenus[], struct menu name);
struct menu make_menu();
int menustep(char* menu[], int size);
*/
const int length=10;
int line_to_invert=1;


struct menu
{
	int numb_options;
	char* options[10];
	struct menu* next[10];
};




struct menu set_options(int index,char* str, int size, struct menu name){
	char str1[10];
	for (int i=0;i<size;i++){
		str1[i]=str[i];
	}
	for (int i=size; i<10;i++){
		str1[i]=' ';
	}
	name.options[index]=str1;
	return name;
}

struct menu init(int numb_opt,char* stringOptions[], int stringSizes[], struct menu *nextMenus[], struct menu name){
	name.numb_options=numb_opt;
	for (int i=0;i<numb_opt;i++){
		set_options(i,stringOptions[i],stringSizes[i],name);
		name.next[i]=nextMenus[i];
	}
	return name;
}


struct menu first;
struct menu Edda;
struct menu Arild;
struct menu Robin;
struct menu empty;
struct menu e;
struct menu d;

struct menu make_menu(){

	struct menu fnext[]={empty,Edda,Robin,Arild};
	char* fstr[]={"Hovedmeny","Edda","Robin","Arild"};
	int fsize[]={9,4,5,5};
	first = init(4,fstr,fsize,&fnext,first);
	
	struct menu Anext[]={empty};
	char* Astr[]={"Arild"};
	int Asize[]={5};
	Arild = init(1,Astr,Asize,&Anext,Arild);
	
	char* Rstr[]={"Robin"};
	Robin = init(1,Rstr,Asize,&Anext,Robin);
	
	struct menu Enext[]={empty,e,d};
	char* Estr[]={"Edda","e","d"};
	int Esize[]={4,1,1};
	Edda = init(3,Estr,Esize,&Enext,Edda);
	
	char* estr[]={"e"};
	int esize[]={1};
	e=init(1,estr,esize,&Anext,e);
	
	char* dstr[]={"d"};
	d=init(1,dstr,esize,&Anext,d);
	return first;
}
	


char* menu_control(struct menu current_menu){
	oled_reset();
	if(current_menu.numb_options==1){
		printf ("return");
		return current_menu.options[0];
	}
	
	for (int i=0; i< current_menu.numb_options;i++){
		printf("%s\n",current_menu.options[i]);
		_delay_ms(10);
		oled_write_from_start_on_line(i);
		oled_write_string(current_menu.options[i],length,0);
	}
	oled_write_from_start_on_line(1);
	oled_write_string(current_menu.options[1],length,1);
	
	int index;
	
	while(1){
		index = menustep(current_menu.options, current_menu.numb_options);
		if (button_pressed()){
			_delay_ms(10);
			printf("Button pressed");
			_delay_ms(500);
			return menu_control(*current_menu.next[index]);
		}
		_delay_ms(200);
	}
}

void menu_funct(){
	printf(menu_control(first));
}

int menustep(char* menu[], int size){
	int direction = 0;
	int joystick_Position = read_y(ADCptr);

	if(joystick_Position > 20){
		direction = 1;
	}
	
	if(joystick_Position < -20){
		direction = -1;
	}
	if(direction){
	oled_write_from_start_on_line(line_to_invert);
	oled_write_string(menu[line_to_invert],length,0);
	line_to_invert = (line_to_invert-direction+size-1-1)%(size-1)+1;
	oled_write_from_start_on_line(line_to_invert);
	oled_write_string(menu[line_to_invert],length,1);
	
	}
	/*for(int line = 0; line < menu_items; line++){
		int current_line_length = get_string_size(page,line);
		oled_write_from_start_on_line(line);
		(line == line_to_invert) ? oled_write_string(menu_options[0][line],current_line_length,1) : oled_write_string(menu_options[0][line],current_line_length,0);
	}*/
	
	return line_to_invert;
}

