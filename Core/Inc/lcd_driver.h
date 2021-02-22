/*
 * lcd_driver.h
 *
 *  Created on: Feb 19, 2021
 *      Author: balint
 */

#ifndef INC_LCD_DRIVER_H_
#define INC_LCD_DRIVER_H_

void lcd_driver_init();
void lcd_driver_write(char* message);
void lcd_driver_home();
void lcd_driver_shift_right(uint8_t pos);
void lcd_driver_shift_left(uint8_t pos);


#endif /* INC_LCD_DRIVER_H_ */
