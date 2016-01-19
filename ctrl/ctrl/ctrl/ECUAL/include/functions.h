/*
 * functions.h
 *
 * Created: 1/12/2016 6:34:15 PM
 *  Author: Rafael
 */ 


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

void ctrl_recieve_data(unsigned char*);
char ctrl_recieve_state();
void ctrl_send_state(char);

char ctrl_check_firstrun();
void ctrl_save_pw(unsigned char*);
char ctrl_check_pw(unsigned char*);

#endif /* FUNCTIONS_H_ */