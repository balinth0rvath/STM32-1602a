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
  while(1)
  {
    lcd_driver_write("nucleo ");
    vTaskDelay(200);
  }
}
