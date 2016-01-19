
#include "avr/io.h"
#include "include/USART.h"

void usart_init()
{
	//Set baud
	//UBRRH = (unsigned char) (6 >> 8);
	//UBRRL = (unsigned char) 6;
	UBRRH = 0x00;
	UBRRL = 51;
	//Enable TX & RX
	UCSRB |= (1 << TXEN) | (1 << RXEN);

	//Set parity EVEN
	UCSRC = (1 << URSEL) | (1 << UPM1);
	
	//Set stop bits (2 bits)
	//UCSRC |= (1 << USBS);
	
	//Set data size 8bit
	UCSRC |= (1 << UCSZ0) | (1 << UCSZ1);
}

void usart_transmit(unsigned char data)
{
	while(! (UCSRA & (1 << UDRE))){}
	UCSRB &= ~(1 << TXB8);
	if(data & 0x0100) {
		UCSRB |= (1 << TXB8);
	}
	UDR = data;
}

unsigned char recieve()
{
	while(! (UCSRA & (1 << RXC))){}
	if ( UCSRA & ((1<<FE)|(1<<DOR)|(1<<PE))){
		return -1;
	}
	char result_h = (UCSRB & (1 << TXB8));
	return (result_h << 8) | UDR;
}
