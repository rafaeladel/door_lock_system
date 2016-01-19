/*
 * I2C.c
 *
 * Created: 12/30/2015 12:20:13 AM
 *  Author: Rafael
 */ 

#include "../HAL/include/HW_TWI.h"
#include "../MCAL/include/MCAL.h"
#include "include/I2C.h"

void send_data(char location, char data)
{
	if(i2c_send_start(TW_START))
	{
		if(i2c_send_addr(0xa0, TW_MT_SLA_ACK))
		{
			i2c_send_data(location, TW_MT_DATA_ACK);
			if(i2c_send_data(data, TW_MT_DATA_ACK))
			{
				i2c_send_stop();
			}
		}
	}
}

void send_data_array(char location, char* data, char length)
{
	char i;
	if(i2c_send_start(TW_START))
	{
		if(i2c_send_addr(0xa0, TW_MT_SLA_ACK))
		{
			i2c_send_data(location, TW_MT_DATA_ACK);
			for(i = 0; i < length; i++) 
			{
				if(!i2c_send_data(data[i], TW_MT_DATA_ACK))
				{
					break;
				}
			}	
			i2c_send_stop();		
		}
	}
}

void read_data(char location, unsigned char *data_ptr, char length)
{
	if(i2c_send_start(TW_START))
	{
		if(i2c_send_addr(0xa0, TW_MT_SLA_ACK))
		{
			i2c_send_data(location, TW_MT_DATA_ACK);
			
			if(i2c_send_start(TW_REP_START)) {
				if(i2c_send_data(0xa1, TW_MR_SLA_ACK)) {
					if(i2c_receive_data(data_ptr, length))
					{
						
						i2c_send_stop();
					}		
				}
			}
			
		}
	}
}

char i2c_send_start(char cond)
{
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);

	while(!(TWCR & (1 << TWINT))){}
	
	return i2c_check_status(cond);

}

char i2c_send_addr(char addr, char cond)
{
	TWDR = addr;
	TWCR = (1 << TWINT) | (1 << TWEN);


	while(!(TWCR & (1 << TWINT))){}
	
	return i2c_check_status(cond);

}

char i2c_send_data(char data, char cond)
{
	TWDR = data;

	TWCR = (1 << TWINT) | (1 << TWEN);


	while(!(TWCR & (1 << TWINT))){}
	
	return i2c_check_status(cond);
	
}



char i2c_receive_data(unsigned char *ptr, char limit)
{
	char i = 0;
	for(i = 0; i < limit - 1; i++) {
		*ptr = i2c_read_ack();
		ptr++;
	}
	*ptr = i2c_read_nack();
	return i2c_check_status(TW_MR_DATA_NACK);
	
}


char i2c_read_ack()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while(!(TWCR & (1 << TWINT))){}
	return TWDR;
}

char i2c_read_nack()
{
	TWCR = (1 << TWINT) | (1 << TWEN);
	while(!(TWCR & (1 << TWINT))){}
	return TWDR;
}

void i2c_send_stop()
{
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

char i2c_check_status(char status)
{
	if((TWSR & 0xf8) == status) {
		return 1;
	} else {
		return 0;
	}
}