/*
 * functions.c
 *
 * Created: 1/12/2016 6:36:06 PM
 *  Author: Rafael
 */ 

#define F_CPU 8000000UL
#include "include/config.h"
#include "include/LCD.h"
#include "include/KEYPAD.h"
#include "../MCAL/include/USART.h"
#include "include/functions.h"
#include <util/delay.h>

char hmi_check_firstrun()
{
	char result = '\0';
	usart_init();
	usart_transmit(STATE_FIRST_RUN);
	result = usart_recieve();
	return result == STATE_FIRST_RUN_YES;
}

char hmi_uart_send_pw(char* pw)
{
	char i;
	usart_init();
	usart_transmit(STATE_CHECK_PW);
	for(i = 0; i < PW_LENGTH; i++)
	{
		usart_transmit(pw[i]);	
	}
	return 1;
}


char hmi_uart_save_pw(char* pw)
{
	char i;
	usart_init();
	usart_transmit(STATE_CHANGE_PW);
	for(i = 0; i < PW_LENGTH; i++)
	{
		usart_transmit(pw[i]);
	}
	return 1;
}

char hmi_uart_check_pw() 
{
	char result = '\0';
	usart_init();
	result = usart_recieve();
	return result;
}

char hmi_uart_send(char command)
{
	usart_init();
	usart_transmit(command);
	return 1;
}

void hmi_lcd_put(char* msg)
{
	init_lcd();
	lcd_send_cmd(0x01);
	lcd_send_string(msg, 0, 0);
}

void hmi_lcd_notify(char* notification)
{
	hmi_lcd_put(notification);
	_delay_ms(1000);
}

void hmi_lcd_menu()
{
	init_lcd();
	lcd_send_cmd(0x01);
	lcd_send_string("1. Open", 0, 0);
	lcd_send_string("2. Close", 0, 1);
	lcd_send_string("3. Change password", 0, 2);
}
	

void hmi_keypad_get_pw(char* container)
{
	init_keypad();
	init_lcd();
	char i;
	for(i = 0; i < PW_LENGTH; i++)
	{
		
		do {
			container[i] = getKey();
		} while(container[i] == '\0');
		
		lcd_send_string("*", 6 + i, 2);
		
	}
}

void hmi_keypad_get_order(char* order_ptr)
{
	do {
		*order_ptr = getKey();
	} while(*order_ptr != '1' && *order_ptr != '2' && *order_ptr != '3');
}

void update_state(char* state)
{
	usart_init();
	state = usart_recieve();	
}