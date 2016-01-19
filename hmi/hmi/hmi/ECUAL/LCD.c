/*
 * LCD.c
 *
 * Created: 12/29/2015 3:55:58 PM
 *  Author: Rafael
 */ 

#include "include/config.h"
#include "../MCAL/include/MCAL.h"
#include "include/LCD.h"

#include <util/delay.h>

void init_lcd()
{
	set_direction_port(DDR_ADDR(CONFIG_LCD_CONF_PORT), 0xff);
	set_direction_port(DDR_ADDR(CONFIG_LCD_DATA_PORT), 0xff);
	
	#if defined(CONFIG_LCD_MODE_4_BIT) && (CONFIG_LCD_MODE_4_BIT == 1)
	lcd_send_cmd(0x02);
	lcd_send_cmd(0x28);
	#else
	lcd_send_cmd(0x38);
	#endif
	lcd_send_cmd(0x0c);
		
}

void set_control_reg(char reg)
{
	set_direction_pin(DDR_ADDR(CONFIG_LCD_CONF_PORT), CONFIG_LCD_CONF_RS_PIN, 1);
	write_pin(PORT_ADDR(CONFIG_LCD_CONF_PORT), CONFIG_LCD_CONF_RS_PIN, reg);
}

void set_lcd_dir(char dir)
{
	set_direction_pin(DDR_ADDR(CONFIG_LCD_CONF_PORT), CONFIG_LCD_CONF_RW_PIN, 1);
	write_pin(PORT_ADDR(CONFIG_LCD_CONF_PORT), CONFIG_LCD_CONF_RW_PIN, dir);
}

void set_lcd_enable(char is_enabled)
{
	set_direction_pin(DDR_ADDR(CONFIG_LCD_CONF_PORT), CONFIG_LCD_CONF_E_PIN, 1);
	write_pin(PORT_ADDR(CONFIG_LCD_CONF_PORT), CONFIG_LCD_CONF_E_PIN, is_enabled);
}

void lcd_send_cmd(char cmd)
{
	set_lcd_dir(0);
	set_control_reg(0);
	
	#if defined(CONFIG_LCD_MODE_4_BIT) && (CONFIG_LCD_MODE_4_BIT == 1)
	lcd_send(cmd & 0xf0);
	lcd_save();
	
	lcd_send((cmd & 0x0f) << 4);
	lcd_save();
	#else 
	lcd_send(cmd);
	lcd_save();
	#endif
}

void lcd_send_char(char c)
{
	set_lcd_dir(0);
	set_control_reg(1);
	
	#if defined(CONFIG_LCD_MODE_4_BIT) && (CONFIG_LCD_MODE_4_BIT == 1)
	lcd_send(c & 0xf0);
	lcd_save();
	
	lcd_send((c & 0x0f) << 4);
	lcd_save();
	#else
	lcd_send(c);
	lcd_save();
	#endif
}

void lcd_send_string(char* str, char x, char y)
{
	lcd_set_pos_xy(x, y);
	char i = 0;
	while(str[i] != '\0') {
		lcd_send_char(str[i++]);
	}
}

void lcd_set_pos_xy(char x, char y)
{
	switch(y) {
		case 0: lcd_send_cmd(0x80 + x); break;
		case 1: lcd_send_cmd(0x80 + 0x40 + x); break;
		case 2: lcd_send_cmd(0x80 + 0x14 + x); break;
		case 3: lcd_send_cmd(0x80 + 0x54 + x); break;
	}
}

void lcd_send(char c)
{
	write_port(PORT_ADDR(CONFIG_LCD_DATA_PORT), c);
}

void lcd_save()
{
	set_lcd_enable(0);
	_delay_ms(10);
	set_lcd_enable(1);	
	_delay_ms(10);
	set_lcd_enable(0);
}

//void lcd_is_busy()
//{
	//set_control_reg(0);
	//set_lcd_dir(1);
	//while(read_button(PINC_ADDR, 7)){}
//}