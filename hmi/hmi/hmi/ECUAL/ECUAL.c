
/*
 * ECUAL.c
 *
 * Created: 11/28/2015 6:55:21 PM
 *  Author: Rafael
 */
 

#include "../MCAL/include/MCAL.h"
#include "include/ECUAL.h"


char read_button(char pin_addr, char pin_no)
{	
	set_direction_pin(DDR_ADDR(pin_addr), pin_no, 0);
	return read_pin(pin_addr, pin_no);
}
