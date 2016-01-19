 /*
 * MCAL.c
 *
 * Created: 11/28/2015 6:55:02 PM
 *  Author: Rafael
 */ 

#include "include/MCAL.h"

void set_direction_pin(char ddr_address, char pin_no, char dir)
{
	volatile char* ddr_ptr = make_pointer(ddr_address);
	if(dir == 1) {
		*ddr_ptr |= 1 << pin_no;
	} else if(dir == 0) {
		*ddr_ptr &= ~(1 << pin_no);
	} 
}

char read_pin(char pin_address, char pin_no)
{
	volatile char* pin_ptr = make_pointer(pin_address);
	// Like: if((PINC & (1 << PC3)) != 0){}
	return (*pin_ptr & (1 << pin_no)) != 0;
}

void write_pin(char port_address, char pin_no, char value)
{
	volatile char* port_ptr = make_pointer(port_address);
	if(value == 1) {
		*port_ptr |= 1 << pin_no;
	} else if(value == 0) {
		*port_ptr &= ~(1 << pin_no);
	}
}

void set_direction_port(char ddr_address, char value)
{
	volatile char* ddr_ptr = make_pointer(ddr_address);
	*ddr_ptr = value;
}

void write_port(char port_address, char value)
{
	volatile char* port_ptr = make_pointer(port_address);
	*port_ptr = value;
}

void add_to_port(char port_address, char value)
{
	volatile char* port_ptr = make_pointer(port_address);
	*port_ptr |= value;
}

void subtract_from_port(char port_address, char value)
{
	volatile char* port_ptr = make_pointer(port_address);
	*port_ptr &= ~value;
}

char* make_pointer(char element_addr)
{
	volatile char *ptr = element_addr;
	return ptr;
}