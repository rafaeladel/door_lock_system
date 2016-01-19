/*
 * KEYPAD.c
 *
 * Created: 12/31/2015 9:35:40 PM
 *  Author: Rafael
 */ 
#include <avr/io.h>

#include "include/config.h"
#include "../MCAL/include/MCAL.h"
#include "include/KEYPAD.h"
#include <util/delay.h>

char keymap[4][4]  = {
	{'7', '8', '9', '/'},
	{'4', '5', '6', '*'},
	{'1', '2', '3', '-'},
	{'c', '0', '=', '+'}
};

void init_keypad()
{
	set_direction_port(DDR_ADDR(CONFIG_KEYPAD_OUT_PORT), 0xf0);
	write_port(PORT_ADDR(CONFIG_KEYPAD_OUT_PORT), 0xff);
}

char getKey()
{
	char* port_ptr = make_pointer(PORT_ADDR(CONFIG_KEYPAD_OUT_PORT));
	volatile char* pin_ptr = make_pointer(CONFIG_KEYPAD_OUT_PORT);
	
	char col = 0, row = 0;
	for(col = 0; col < 4; col++) {
		add_to_port(PORT_ADDR(CONFIG_KEYPAD_OUT_PORT), 0xf0);
		subtract_from_port(PORT_ADDR(CONFIG_KEYPAD_OUT_PORT), (1 << col) << 4);
		_delay_ms(1);
		row = *(pin_ptr) & 0x0f;
		if(row != 0x0f) {
			while((*(pin_ptr) & 0x0f) != 0x0F);
			break;
		}
	}
	
	if(col < 4) {
		row = getRowIndex(row);
		return keymap[row][col];
	}
	return '\0';
	
}

char getRowIndex(char row)
{
	row = (~row) & 0x0f;
	char index = 0;
	while(row >>= 1){
		index++;
	}
	return index;
}