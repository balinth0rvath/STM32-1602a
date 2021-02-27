/*
 * application.c
 *
 *  Created on: Feb 26, 2021
 *      Author: balint
 */
#include "application.h"
#include "lcd_driver.h"
#include "FreeRTOS.h"
#include "task.h"


void application_task()
{
  int i = 0;
  char msg[] = "nucleo";
  while(1)
  {
    lcd_driver_write(msg);
    i++;
    if (i>9)
    {
      i=0;
      msg[0]++;
      lcd_driver_home();
    }
    vTaskDelay(200);
  }
}
