/*
 * lcd_driver.h
 *
 *  Created on: Feb 19, 2021
 *      Author: balint
 */

#ifndef INC_LCD_DRIVER_H_
#define INC_LCD_DRIVER_H_

void lcd_driver_init();
void lcd_driver_write_cmd(uint8_t cmd);
void lcd_driver_write_data(uint8_t data);
void lcd_driver_set_4bit();


#endif /* INC_LCD_DRIVER_H_ */
