/*
 * MCAL.h
 *
 * Created: 11/28/2015 6:54:53 PM
 *  Author: Rafael
 */ 

#include "../../HAL/include/DIO.h"

void set_direction_pin(char, char, char);
char read_pin(char, char);
void write_pin(char, char, char);

void set_direction_port(char, char);
void write_port(char, char);
void add_to_port(char, char);
void subtract_from_port(char, char);

char* make_pointer(char);