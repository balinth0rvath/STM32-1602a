#include "main.h"
#include "lcd_driver.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "string.h"
#include "portable.h"

/*
 *  RS  - GPIOB_PIN_5 - Register select
 *  RW  - L-write     - Read / Write
 *  E   - GPIOA_PIN_8 - Enable signal
 *
 *  Data signals
 *
 *  DB4 - GPIOB_PIN_4
 *  DB5 - GPIOB_PIN_0
 *  DB6 - GPIOC_PIN_1
 *  DB7 - GPIOC_PIN_0
 */

typedef enum {OFF, ON} state_t;
typedef enum {COMMAND, DATA} mode_t;
static void lcd_driver_send(uint8_t value,mode_t mode);
static void lcd_driver_send_cmd(uint8_t cmd);
static void lcd_driver_send_data(uint8_t data);

static state_t state = OFF;

static QueueHandle_t lcd_queue;

extern TIM_HandleTypeDef htim2;

static uint8_t go_home       =  0x80;
static uint8_t cursor_shift  =  0x10;

static uint8_t init_sequence[] = {
    0x02, // 0000 0010  Set 4 bit mode
    0x28, // 0010 1000  Set 2 line display mode, 5x8 font
    0x0c, // 0000 1100  Display on, cursor off, cursor blink off
    0x06, // 0000 0110  Cursor blink moves to right and DDRAM address increased by 1
    0x01, // 0000 0001  Clear display
    0x80, // 1000 0000  Set DDRAM address to 0
    0x00};

void lcd_driver_init()
{
  uint8_t* p = init_sequence;
  for (int i=0; *p; ++i )
  {
    lcd_driver_send_cmd(*(p++));
  }

  lcd_queue = xQueueCreate(10, sizeof(char*));

  if (lcd_queue != NULL)
  {
    state = ON;
  }
}

void lcd_driver_write(char* message)
{
  if (state == ON)
  {
    char* buffer = NULL;
    buffer = pvPortMalloc(strlen(message)+1);
    memcpy(buffer, message, strlen(message));
    *(buffer+strlen(message)) = 0;
    xQueueSend(lcd_queue, &buffer, 0);
  }
}

void lcd_driver_task()
{
  char* buffer = NULL;
  lcd_driver_init();
  while(1)
  {
    if (xQueueReceive(lcd_queue, &buffer, portMAX_DELAY))
    {
      if (buffer != NULL)
      {
        int i = 0;
        while(buffer[i])
        {
          lcd_driver_send_data(buffer[i++]);
        }
        vPortFree(buffer);
      }
    }

  }
}

void lcd_driver_home()
{
  lcd_driver_send_cmd(go_home);
}


void lcd_driver_shift_right(uint8_t pos)
{
  for(int i=0;i<pos;++i)
    lcd_driver_send_cmd(cursor_shift | 4);
}

void lcd_driver_shift_left(uint8_t pos)
{
  for(int i=0;i<pos;++i)
      lcd_driver_send_cmd(cursor_shift);
}


static void lcd_driver_send_cmd(uint8_t cmd)
{
  lcd_driver_send(cmd, COMMAND);
}

static void lcd_driver_send_data(uint8_t cmd)
{
  lcd_driver_send(cmd, DATA);

}

static void lcd_driver_send(uint8_t value, mode_t mode)
{
  uint8_t value_half;
  for (int i=0; i<2; ++i)
  {
    if (!i)
      value_half = (value & 0xf0) >> 4; // high 4 bit
    else
      value_half = value & 0x0f; // low 4 bit

    if (value_half & 8)
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,  GPIO_PIN_SET);
    else
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,  GPIO_PIN_RESET);

    if (value_half & 4)
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,  GPIO_PIN_SET);
      else
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,  GPIO_PIN_RESET);

    if (value_half & 2)
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,  GPIO_PIN_SET);
      else
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,  GPIO_PIN_RESET);

    if (value_half & 1)
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);
      else
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);

    switch(mode)
    {
      case DATA:
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
        break;
      case COMMAND:
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
        break;

      default:
        break;
    }
    __HAL_TIM_SET_COUNTER(&htim2,0);
    while(__HAL_TIM_GET_COUNTER(&htim2)<16) // 160us
    {
    }

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
    __HAL_TIM_SET_COUNTER(&htim2,0);
    while(__HAL_TIM_GET_COUNTER(&htim2)<8) // 80us
    {
    }

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
  }
}

