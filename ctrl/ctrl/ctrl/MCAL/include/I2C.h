/*
 * I2C.h
 *
 * Created: 12/30/2015 12:20:31 AM
 *  Author: Rafael
 */ 


#ifndef I2C_H_
#define I2C_H_

char i2c_send_start(char);
char i2c_send_addr(char, char);
char i2c_send_data(char, char);
char i2c_receive_data(unsigned char *, char);
void i2c_send_stop();
char i2c_check_status(char);
char i2c_read_ack();
char i2c_read_nack();;

void send_data(char, char);
void send_data_array(char, char*, char);
void read_data(char, unsigned char*, char);



#endif /* I2C_H_ */