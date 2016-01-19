/*
 * LCD.h
 *
 * Created: 12/29/2015 3:56:35 PM
 *  Author: Rafael
 */ 


#ifndef LCD_H_
#define LCD_H_

void init_lcd();
void set_control_reg(char);
void set_lcd_dir(char);
void set_lcd_enable(char);
void lcd_save();
void lcd_is_busy();
void lcd_send(char);

void lcd_send_cmd(char);
void lcd_send_char(char);
void lcd_send_string(char*, char, char);
void lcd_set_pos_xy(char, char);


#endif /* LCD_H_ */