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

typedef enum {
  nRF24_TX_ERROR = 0,
  nRF24_TX_SUCCESS,
  nRF24_TX_TIMEOUT,
  nRF24_TX_MAXRT
} nRF24_TX_Result;

static nRF24_TX_Result nRF24_TransmitPacket(uint8_t* payload, uint8_t payload_length);

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
  uint8_t payload_length = 10;
  uint8_t otx;
  uint8_t otx_plot;
  uint8_t otx_arc;
  nRF24_TX_Result ret;

  while(1)
  {
    ret = nRF24_TransmitPacket(payload, payload_length);
    otx = nRF24_GetRetransmitCounters();
    otx_plot = (otx & nRF24_MASK_PLOS_CNT) >> 4;
    otx_arc = otx & nRF24_MASK_ARC_CNT;
    vTaskDelay(500);
  }
}

nRF24_TX_Result nRF24_TransmitPacket(uint8_t* payload, uint8_t payload_length)
{
  volatile uint32_t wait = 0xfffff;
  uint8_t status;
  nRF24_CE_L();
  nRF24_WritePayload(payload, payload_length);
  nRF24_CE_H();

  do {
    status = nRF24_GetStatus();
    if (status & (nRF24_FLAG_TX_DS | nRF24_FLAG_MAX_RT)) {
      break;
    }
    vTaskDelay(1);
  } while (wait--);

  nRF24_CE_L();

  if (!wait)
  {
    return nRF24_TX_TIMEOUT;
  }

  nRF24_ClearIRQFlags();

  if (status & nRF24_FLAG_MAX_RT)
  {
    return nRF24_TX_MAXRT;
  }
  if (status & nRF24_FLAG_TX_DS)
  {
    return nRF24_TX_SUCCESS;
  }
  nRF24_FlushTX();
  return nRF24_TX_ERROR;
}

