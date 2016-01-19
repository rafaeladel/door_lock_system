/*
 * functions.c
 *
 * Created: 1/12/2016 6:34:04 PM
 *  Author: Rafael
 */ 

#define  F_CPU 8000000UL
#include "../MCAL/include/USART.h"
#include "../MCAL/include/I2C.h"
#include "include/config.h"
#include "include/functions.h"
#include <string.h>
#include <util/delay.h>


void ctrl_recieve_data(unsigned char* container)
{
	char i ;
	usart_init();
	for(i = 0; i < PW_LENGTH; i++) {
		container[i] = recieve();
	}
}

char ctrl_recieve_state()
{
	char state = '\0';
	usart_init();
	state = recieve();
	return state;
}

void ctrl_send_state(char state)
{
	usart_init();
	usart_transmit(state);
}

char ctrl_check_firstrun()
{
	unsigned char firstrun = '\0';
	read_data(CONFIG_FIRSTRUN_ADDR, &firstrun, 1);

	if(firstrun == 0x10) {
		return 0;
	} else {
		return 1;
	}
}

void ctrl_save_pw(unsigned char*  container)
{
	send_data_array(CONIFG_PW_ADDR, container, PW_LENGTH);
	_delay_ms(500);
	send_data(CONFIG_FIRSTRUN_ADDR, 0x10);

}

char ctrl_check_pw(unsigned char* container)
{
	char i;
	unsigned char correct_pw[4];
	read_data(CONIFG_PW_ADDR, correct_pw, PW_LENGTH);
	for(i = 0; i < PW_LENGTH; i++)
	{
		if(correct_pw[i] != container[i])
		{

			return 0;
		}
	}
	//Delay to prevent consicutive USART parity error
	_delay_ms(10);
	return 1;
}