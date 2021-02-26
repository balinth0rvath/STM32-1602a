/*
 * application.c
 *
 *  Created on: Feb 26, 2021
 *      Author: balint
 */
#include "application.h"
#include "lcd_driver.h"


void application_task()
{
  while(1)
  {
    lcd_driver_write("alma");
    HAL_Delay(200);
  }
}
