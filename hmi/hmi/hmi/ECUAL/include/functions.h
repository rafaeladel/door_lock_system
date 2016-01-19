/*
 * functions.h
 *
 * Created: 1/12/2016 6:35:55 PM
 *  Author: Rafael
 */ 


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

char hmi_check_firstrun();
char hmi_uart_send_pw(char*);
char hmi_uart_save_pw(char*);
char hmi_uart_check_pw();
char hmi_uart_send(char);

void hmi_lcd_put();
void hmi_lcd_notify();
void hmi_lcd_menu();

void hmi_keypad_get_pw();
void hmi_keypad_get_order(char*);

void update_state(char*);

#endif /* FUNCTIONS_H_ */