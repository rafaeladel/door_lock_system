/*
 * config.h
 *
 * Created: 1/3/2016 10:33:50 PM
 *  Author: Rafael
 */ 

#include "../../HAL/include/DIO.h"

#ifndef CONFIG_H_
#define CONFIG_H_

#define CONFIG_MOTOR_PORT PINA_ADDR
#define CONFIG_MOTOR_PIN_NO 0

#define CONFIG_LED_PORT PINA_ADDR
#define CONFIG_LED_PIN_NO 7
#define CONIFG_PW_ADDR 0x00
#define CONFIG_FIRSTRUN_ADDR 0x04

#define STATE_DOOR_OPEN 0xa0
#define STATE_DOOR_CLOSE 0xa1
#define STATE_CHANGE_PW 0xa2
#define STATE_ENTER_PW 0xa3
#define STATE_CORRECT_PW 0xa5
#define STATE_WRONG_PW 0xa6
#define STATE_SYS_LOCK 0xa8
#define STATE_FIRST_RUN 0xa9
#define STATE_CHECK_PW 0xb0
#define STATE_CONFIRM_PW 0xb2
#define STATE_WRONG_CONFIRM_PW 0xb3
#define STATE_FIRST_RUN_YES 0xb4
#define STATE_FIRST_RUN_NO 0xb5

#define PW_LENGTH 4

#endif /* CONFIG_H_ */