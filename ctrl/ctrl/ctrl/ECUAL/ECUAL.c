
/*
 * ECUAL.c
 *
 * Created: 11/28/2015 6:55:21 PM
 *  Author: Rafael
 */
 
#include "include/config.h"
#include "../MCAL/include/MCAL.h"
#include "include/ECUAL.h"


char read_button(char pin_addr, char pin_no)
{	
	set_direction_pin(DDR_ADDR(pin_addr), pin_no, 0);
	return read_pin(pin_addr, pin_no);
}

void control_motor(char value)
{
	set_direction_pin(DDR_ADDR(CONFIG_MOTOR_PORT), CONFIG_MOTOR_PIN_NO, 1);
	write_pin(PORT_ADDR(CONFIG_MOTOR_PORT), CONFIG_MOTOR_PIN_NO, value);
}

void control_led(char value)
{
	set_direction_pin(DDR_ADDR(CONFIG_MOTOR_PORT), CONFIG_LED_PIN_NO, 1);
	write_pin(PORT_ADDR(CONFIG_MOTOR_PORT), CONFIG_LED_PIN_NO, value);
}
