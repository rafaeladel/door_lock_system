/*
 * ctrl.c
 *
 * Created: 1/12/2016 6:23:38 PM
 * Author : Rafael
 */ 

#include "ECUAL/include/config.h"
#include "ECUAL/include/functions.h"
#include "MCAL/include/I2C.h"

char pw_err_counter = 0;
char state = '\0';
unsigned char pw[4] = {'\0', '\0', '\0', '\0'};

int main(void)
{
    while (1) 
    {
		state = ctrl_recieve_state();
		
		switch(state)
		{
			case STATE_FIRST_RUN:
				if(ctrl_check_firstrun()) {
					ctrl_send_state(STATE_FIRST_RUN_YES);
				} else {
					ctrl_send_state(STATE_FIRST_RUN_NO);
				}
			break;
			
			case STATE_CHANGE_PW:
				ctrl_recieve_data(pw);
				ctrl_save_pw(pw);
			break;
			
			case STATE_CHECK_PW:
				ctrl_recieve_data(pw);
				if(ctrl_check_pw(pw)) {
					pw_err_counter = 0;
					ctrl_send_state(STATE_CORRECT_PW);
				} else {
					pw_err_counter++;
					if(pw_err_counter == 3)
					{
						control_led(1);
						ctrl_send_state(STATE_SYS_LOCK);
					}
					ctrl_send_state(STATE_WRONG_PW);
				}
			break;
			
			case STATE_DOOR_OPEN:
				control_motor(1);
			break;
			
			case STATE_DOOR_CLOSE:
				control_motor(0);
			break;
		}
    }
}
