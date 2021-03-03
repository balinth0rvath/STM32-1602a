/*
 * transmitter.c
 *
 *  Created on: Mar 3, 2021
 *      Author: balint
 */

#include "transmitter.h"
#include "FreeRTOS.h"
#include "task.h"
#include "nrf24.h"

static uint8_t nRF24_TransmitPacket(uint8_t* payload, uint8_t payload_length);

void transmitter_task()
{
  nRF24_SetRFChannel(40);
  nRF24_SetDataRate(nRF24_DR_2Mbps);
  nRF24_SetCRCScheme(nRF24_CRC_2byte);
  nRF24_SetAddrWidth(3);
  const uint8_t addr[] = {0x01, 0x10, 0xE3};
  nRF24_SetAddr(nRF24_PIPETX, addr);
  nRF24_SetAddr(nRF24_PIPE0, addr);
  nRF24_SetTXPower(nRF24_TXPWR_0dBm);
  nRF24_SetAutoRetr(nRF24_ARD_2500us, 10);
  nRF24_EnableAA(nRF24_PIPE0);
  nRF24_SetOperationalMode(nRF24_MODE_TX);
  nRF24_ClearIRQFlags();
  nRF24_SetPowerMode(nRF24_PWR_UP);
  nRF24_SetOperationalMode(nRF24_MODE_TX);

  uint8_t payload[10] = {1,2,3,4,5,6,7,8,9,10};

  while(1)
  {
    uint8_t ret = nRF24_TransmitPacket(payload, sizeof(payload));
    vTaskDelay(500);
  }
}

uint8_t nRF24_TransmitPacket(uint8_t* payload, uint8_t payload_length)
{
  return 0;
}

