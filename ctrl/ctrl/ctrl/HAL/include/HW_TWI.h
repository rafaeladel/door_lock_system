/*
 * HW_TWI.h
 *
 * Created: 12/29/2015 11:58:03 PM
 *  Author: Rafael
 */ 

#include <avr/io.h>


#ifndef HW_TWI_H_
#define HW_TWI_H_

#define 	TW_START   0x08
#define 	TW_REP_START   0x10
#define 	TW_MT_SLA_ACK   0x18
#define 	TW_MT_SLA_NACK   0x20
#define 	TW_MT_DATA_ACK   0x28
#define 	TW_MT_DATA_NACK   0x30
#define 	TW_MT_ARB_LOST   0x38
#define 	TW_MR_ARB_LOST   0x38
#define 	TW_MR_SLA_ACK   0x40
#define 	TW_MR_SLA_NACK   0x48
#define 	TW_MR_DATA_ACK   0x50
#define 	TW_MR_DATA_NACK   0x58
#define 	TW_ST_SLA_ACK   0xA8
#define 	TW_ST_ARB_LOST_SLA_ACK   0xB0
#define 	TW_ST_DATA_ACK   0xB8
#define 	TW_ST_DATA_NACK   0xC0
#define 	TW_ST_LAST_DATA   0xC8
#define 	TW_SR_SLA_ACK   0x60
#define 	TW_SR_ARB_LOST_SLA_ACK   0x68
#define 	TW_SR_GCALL_ACK   0x70
#define 	TW_SR_ARB_LOST_GCALL_ACK   0x78
#define 	TW_SR_DATA_ACK   0x80
#define 	TW_SR_DATA_NACK   0x88
#define 	TW_SR_GCALL_DATA_ACK   0x90
#define 	TW_SR_GCALL_DATA_NACK   0x98
#define 	TW_SR_STOP   0xA0
#define 	TW_NO_INFO   0xF8
#define 	TW_BUS_ERROR   0x00
#define 	TWCR_CMD_MASK   0x0F
#define 	TWSR_STATUS_MASK   0xF8
#define 	I2C_OK   0x00
#define 	I2C_ERROR_NODEV   0x01


#endif /* HW_TWI_H_ */