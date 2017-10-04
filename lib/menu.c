/*
 * menu.c
 *
 * Created: 04.10.2017 16:39:11
 *  Author: eddas
 */ 

#include "adc.h"
#include "oled.h"
#include "menu.h"

#define number_of_pages 1
#define menu_items 3
const int length=10;
volatile char* menu_options[4] = {"Meny 1             ","arild king of karsk", "Edda er her        ", "Robin er der       "};
int line_to_invert=1;

/*
void menu_funct(){
	printf(menu_control(make_menu()));
}
struct menu make_menu(){
	menu empty = {1, 0, {" "," "," "," "," "," "," "," "," "," "}};
	menu first{0, 4, {"Hovedmeny ","Edda      ","Robin     ","Arild     "," "," "," "," "," "," "}, {empty,Edda,empty,empty,empty,empty,empty,empty,empty,empty}};
	
	menu Edda = {1, 0, {" "," "," "," "," "," "," "," "," "," "}, {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty}};
	menu Edda = {0, 3, {"Eddas alder","22","21"," "," "," "," "," "," "," "}, {empty,empty,first,empty,empty,empty,empty,empty,empty,empty}};
		/*
	struct menu Robin{
		.empt=0;
		.numb_options=3;
		.menu_options={"Robin alder","22","21"," "," "," "," "," "," "," "};
		.next_element={empty,E_22,E_21,empty,empty,empty,empty,empty,empty,empty}
	}
	struct menu Arild{
		.empt=1;
		.numb_options=3;
		.menu_options={"King of karsk"," "," "," "," "," "," "," "," "," "};
		.next_element={empty,empty,empty,empty,empty,empty,empty,empty,empty,empty}
	}
	struct menu E_22{
		.empt=1;
		.numb_options=0;
		.menu_options={"FEIL"," "," "," "," "," "," "," "," "," "};
		.next_element={empty,empty,empty,empty,empty,empty,empty,empty,empty,empty}
	}
	struct menu E_21{
		.empt=1;
		.numb_options=0;
		.menu_options={"RIKTIG"," "," "," "," "," "," "," "," "," "};
		.next_element={empty,empty,empty,empty,empty,empty,empty,empty,empty,empty}
	}
	return first;
}
*/
char* menu_control(menu current_menu){
	if(current_menu.empt){
		return current_menu.menu_options[0]
	}
	for (int i=0; i< current_menu.menu_options;i++){
		oled_write_from_start_on_line(i);
		oled_write_string(current_menu.menu_options[i],length,0);
	}
	oled_write_from_start_on_line(1);
	oled_write_string(current_menu.menu_options[i],length,1);
	
	int index;
	
	while{
		index = menustep(current_menu.menu_options, current_menu.numb_options);
		if (button_pressed()){
			menu_control(current_menu.next_element[index]);
		}
		_delay_ms(200);
	}
}
*/

int menustep(char* menu[], int size){
	int direction = 0;
	int joystick_Position = read_y(ADC_ptr);

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