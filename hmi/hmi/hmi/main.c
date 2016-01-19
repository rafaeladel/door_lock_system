/*
 * hmi.c
 *
 * Created: 1/12/2016 6:16:44 PM
 * Author : Rafael
 */ 

#define F_CPU 8000000UL

#include <util/delay.h>
#include "HAL/include/DIO.h"
#include "MCAL/include/MCAL.h"
#include "ECUAL/include/config.h"
#include "ECUAL/include/messages.h"
#include "ECUAL/include/functions.h"

char pw[PW_LENGTH] = {'\0', '\0', '\0', '\0'};
char confirm_pw[PW_LENGTH] = {'\0', '\0', '\0', '\0'};
char order = '\0';
char check_result = '\0';

void enter_pw();
char check_pw();
void enter_new_pw();
char enter_confirm_pw();

int main(void)
{
	//1. Check if first run
	//2a. If yes -> Change password
	//2b.			Enter new password
	//2c.			Confirm password
	//2d.				If match yes -> show menu
	//2e.				If match no -> show error
	//3. If no  -> Enter password
	//3a.		   Compare password
	//3b.				If yes -> show menu
	//3c.				If no -> show error, repeate
	
	char state = STATE_FIRST_RUN;
	char prev_state = '\0';
	
	while(state != STATE_SYS_LOCK) {
		switch(state) {
			case STATE_FIRST_RUN:
				if(hmi_check_firstrun()) {
					state = STATE_CHANGE_PW;
				} else {
					state = STATE_ENTER_PW;
				}
			break;
			
			case STATE_ENTER_PW:
				hmi_lcd_put(MSG_ENTER_PW);
				enter_pw();
				state = STATE_CHECK_PW;
			break;
			
			case STATE_CHECK_PW:
				check_result = check_pw();
				if(check_result == STATE_CORRECT_PW){
					state = prev_state != '\0' ? prev_state : STATE_CORRECT_PW;
				} else if(check_result == STATE_WRONG_PW){
					state = STATE_WRONG_PW;
				} else if(check_result == STATE_SYS_LOCK) {
					hmi_lcd_put(MSG_SYS_LOCK);
					state = STATE_SYS_LOCK;
				}
			break;
			
			case STATE_DOOR_OPEN:
				hmi_uart_send(STATE_DOOR_OPEN);
				hmi_lcd_notify(MSG_DOOR_OPEN);
				state = STATE_CORRECT_PW;
			break;
			
			case STATE_DOOR_CLOSE:
				hmi_uart_send(STATE_DOOR_CLOSE);
				hmi_lcd_notify(MSG_DOOR_CLOSE);
				state = STATE_CORRECT_PW;
			break;
			
			case STATE_CHANGE_PW:
				if(!hmi_check_firstrun() && prev_state == '\0') {
					prev_state = state;
					state = STATE_ENTER_PW;
					continue;
				}
				hmi_lcd_put(MSG_ENTER_NEW_PW);
				enter_new_pw();
				state = STATE_CONFIRM_PW;	
			break;
			
			case STATE_CONFIRM_PW:
				hmi_lcd_put(MSG_CONFIRM_PW);
				if(enter_confirm_pw()) {
					hmi_uart_save_pw(pw);
					prev_state = '\0';
					state = STATE_CORRECT_PW;
				} else {
					state = STATE_WRONG_CONFIRM_PW;
				}
			break;
			
			case STATE_WRONG_CONFIRM_PW:
				hmi_lcd_notify(MSG_CONFIRM_WRONG);
				state = STATE_CHANGE_PW;
			break;
			
			case STATE_CORRECT_PW:
				hmi_lcd_menu();
				hmi_keypad_get_order(&order);
				if(order == '1') {
					state = STATE_DOOR_OPEN;
				} else if(order == '2') {
					state = STATE_DOOR_CLOSE;
				} else if(order == '3') {
					state = STATE_CHANGE_PW;
				}
			break;
			
			case STATE_WRONG_PW:
				hmi_lcd_notify(MSG_INVALID_PW);
				state = STATE_ENTER_PW;
			break;
		}
	}
	
	
}

void enter_pw()
{
	hmi_keypad_get_pw(pw);
	hmi_uart_send_pw(pw);	
}

char check_pw()
{
	char result = '\0';
	result = hmi_uart_check_pw(pw);
	return result;
}

void enter_new_pw()
{
	hmi_keypad_get_pw(pw);
}

char enter_confirm_pw()
{
	char i;
	hmi_keypad_get_pw(confirm_pw);
	for(i = 0; i < PW_LENGTH; i++)
	{
		if(pw[i] != confirm_pw[i]){
			return 0;
		}
	}
	return 1;
}