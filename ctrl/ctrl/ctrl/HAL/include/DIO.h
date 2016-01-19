/*
 * DIO.h
 *
 * Created: 12/29/2015 4:00:45 PM
 *  Author: Rafael
 */ 


#ifndef DIO_H_
#define DIO_H_

#define DDR_OFFSET 0x01
#define PORT_OFFSET 0x02

#define PINA_ADDR 0x39
#define PINC_ADDR 0x33
#define PINB_ADDR 0x36
#define PIND_ADDR 0x30

#define DDR_ADDR(PIN_ADDR) (PIN_ADDR + DDR_OFFSET)
#define PORT_ADDR(PIN_ADDR) (PIN_ADDR + PORT_OFFSET)

#endif /* DIO_H_ */