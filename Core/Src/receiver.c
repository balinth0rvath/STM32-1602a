/*
 * receiver.c
 *
 *  Created on: Mar 3, 2021
 *      Author: balint
 */

#include "transmitter.h"
#include "FreeRTOS.h"
#include "task.h"
#include "nrf24.h"

static uint8_t payload[10] = {};
static uint8_t payload_length = 10;

void receiver_task()
{
  nRF24_SetRFChannel(40);
  nRF24_SetDataRate(nRF24_DR_2Mbps);
  nRF24_SetCRCScheme(nRF24_CRC_2byte);
  nRF24_SetAddrWidth(3);
  static const uint8_t addr[] = {0x01, 0x10, 0xE3};
  nRF24_SetAddr(nRF24_PIPE1, addr);
  nRF24_SetRXPipe(nRF24_PIPE1, nRF24_AA_ON, 10);
  nRF24_SetTXPower(nRF24_TXPWR_0dBm);
  nRF24_SetOperationalMode(nRF24_MODE_RX);
  nRF24_ClearIRQFlags();
  nRF24_SetPowerMode(nRF24_PWR_UP);
  nRF24_CE_H();

  nRF24_RXResult pipe;

  while(1)
  {
    if (nRF24_GetStatus_RXFIFO() != nRF24_STATUS_RXFIFO_EMPTY)
    {
      pipe = nRF24_ReadPayload(payload, &payload_length);
      nRF24_ClearIRQFlags();
    }

    vTaskDelay(450);
  }
}
