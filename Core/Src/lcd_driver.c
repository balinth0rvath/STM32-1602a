#include "main.h"
#include "lcd_driver.h"

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

typedef enum {COMMAND, DATA} mode_t;
static void lcd_driver_send(uint8_t value,mode_t mode);
static void lcd_driver_write_cmd(uint8_t cmd);
static void lcd_driver_write_data(uint8_t data);

static uint8_t init_sequence[] = {0x02, 0x28, 0x0c, 0x06, 0x01, 0x80, 0x00};

void lcd_driver_init()
{
  uint8_t* p = init_sequence;
  for (int i=0; *p; ++i )
  {
    lcd_driver_write_cmd(*(p++));
  }
}

void lcd_driver_write(char* message)
{
  while(*message)
  {
     lcd_driver_write_data(*(message++));
  }
}

static void lcd_driver_write_cmd(uint8_t cmd)
{
  lcd_driver_send(cmd, COMMAND);
}

static void lcd_driver_write_data(uint8_t cmd)
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

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
    HAL_Delay(50);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
    HAL_Delay(200);
  }
}

