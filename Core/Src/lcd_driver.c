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


void lcd_driver_init()
{
  lcd_driver_set_4bit();
  lcd_driver_write_cmd(0x28);
  lcd_driver_write_cmd(0x0c);
  lcd_driver_write_cmd(0x06);
  lcd_driver_write_cmd(0x01);
  lcd_driver_write_cmd(0x80);

  lcd_driver_write_data('H');
  lcd_driver_write_data('5');
  lcd_driver_write_data('3');
}

void lcd_driver_set_4bit()
{
  uint8_t cmd_high = 2;
   // 7654 3210
   // x--- ----
   if (cmd_high & 8)
     HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,  GPIO_PIN_SET);
   else
     HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,  GPIO_PIN_RESET);

   // 7654 3210
   // -x-- ----
   if (cmd_high & 4)
       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,  GPIO_PIN_SET);
     else
       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,  GPIO_PIN_RESET);

   // 7654 3210
   // --x- ----
   if (cmd_high & 2)
       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,  GPIO_PIN_SET);
     else
       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,  GPIO_PIN_RESET);

   // 7654 3210
   // ---x ----
   if (cmd_high & 1)
       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);
     else
       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);

   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
   HAL_Delay(50);
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
   HAL_Delay(200);


}

void lcd_driver_write_cmd(uint8_t cmd)
{

  uint8_t cmd_high = (cmd & 0xf0) >> 4;
  // 7654 3210
  // x--- ----
  if (cmd_high & 8)
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,  GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,  GPIO_PIN_RESET);

  // 7654 3210
  // -x-- ----
  if (cmd_high & 4)
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,  GPIO_PIN_SET);
    else
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,  GPIO_PIN_RESET);

  // 7654 3210
  // --x- ----
  if (cmd_high & 2)
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,  GPIO_PIN_SET);
    else
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,  GPIO_PIN_RESET);

  // 7654 3210
  // ---x ----
  if (cmd_high & 1)
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);
    else
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
  HAL_Delay(50);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
  HAL_Delay(200);

  uint8_t cmd_low = cmd & 0x0f;
  // 7654 3210
  // ---- x---
  if (cmd_low & 8)
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,  GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,  GPIO_PIN_RESET);

  // 7654 3210
  // ---- -x--
  if (cmd_low & 4)
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,  GPIO_PIN_SET);
    else
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,  GPIO_PIN_RESET);

  // 7654 3210
  // ---- --x-
  if (cmd_low & 2)
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,  GPIO_PIN_SET);
    else
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,  GPIO_PIN_RESET);

  // 7654 3210
  // ---- ---x
  if (cmd_low & 1)
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);
    else
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
  HAL_Delay(50);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
  HAL_Delay(200);

}

void lcd_driver_write_data(uint8_t cmd)
{
  uint8_t cmd_high = (cmd & 0xf0) >> 4;
  // 7654 3210
  // x--- ----
  if (cmd_high & 8)
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,  GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,  GPIO_PIN_RESET);

  // 7654 3210
  // -x-- ----
  if (cmd_high & 4)
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,  GPIO_PIN_SET);
    else
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,  GPIO_PIN_RESET);

  // 7654 3210
  // --x- ----
  if (cmd_high & 2)
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,  GPIO_PIN_SET);
    else
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,  GPIO_PIN_RESET);

  // 7654 3210
  // ---x ----
  if (cmd_high & 1)
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);
    else
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
  HAL_Delay(50);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
  HAL_Delay(200);

  uint8_t cmd_low = cmd & 0x0f;
  // 7654 3210
  // ---- x---
  if (cmd_low & 8)
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,  GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,  GPIO_PIN_RESET);

  // 7654 3210
  // ---- -x--
  if (cmd_low & 4)
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,  GPIO_PIN_SET);
    else
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,  GPIO_PIN_RESET);

  // 7654 3210
  // ---- --x-
  if (cmd_low & 2)
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,  GPIO_PIN_SET);
    else
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,  GPIO_PIN_RESET);

  // 7654 3210
  // ---- ---x
  if (cmd_low & 1)
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);
    else
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
  HAL_Delay(50);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
  HAL_Delay(200);

}
