/*
 * logger.c
 *
 *  Created on: Feb 28, 2021
 *      Author: balint
 */

#include "logger.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"
#include "string.h"
#include "portable.h"

#include "stm32f1xx_hal.h"

static char message[32] = "";

extern UART_HandleTypeDef huart2;

void logger_task()
{
  sprintf(message,"* FreeRTOS ");
  strcat(message, tskKERNEL_VERSION_NUMBER);
  strcat(message, "\r\n");
  HAL_UART_Transmit(&huart2, (uint8_t*) message, 32, 100);
  sprintf(message,"Total heap: %d bytes \r\n", configTOTAL_HEAP_SIZE);
  HAL_UART_Transmit(&huart2, (uint8_t*) message, 32, 100);

  memset(message,0,32);
  while(1)
  {
    size_t free_heap = xPortGetFreeHeapSize();
    sprintf(message,"Free heap: %d bytes \n\r", free_heap);
    HAL_UART_Transmit(&huart2, (uint8_t*) message, 32, 100);
    vTaskDelay(5000);
  }
}
