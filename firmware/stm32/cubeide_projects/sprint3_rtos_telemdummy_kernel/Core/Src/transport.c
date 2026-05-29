/*
 * transport.c
 *
 *  Created on: May 29, 2026
 *      Author: shreyash
 */

#include "transport.h"

#include <stdio.h>
#include <string.h>

extern UART_HandleTypeDef huart3;

static UART_HandleTypeDef *s_uart = NULL;

void Transport_Init(void)
{
    s_uart = &huart3;
}

void Transport_SetReady(void)
{
    HAL_GPIO_WritePin(DATA_READY_GPIO_Port, DATA_READY_Pin, GPIO_PIN_SET);
}

void Transport_ClearReady(void)
{
    HAL_GPIO_WritePin(DATA_READY_GPIO_Port, DATA_READY_Pin, GPIO_PIN_RESET);
}

HAL_StatusTypeDef Transport_DebugSend(const TelemetryPacket_t *pkt)
{
    if (pkt == NULL || s_uart == NULL)
    {
        return HAL_ERROR;
    }

    char buffer[256];

    int len = snprintf(
        buffer,
        sizeof(buffer),
        "MAGIC=%08lX,SEQ=%lu,TS=%lu,AX=%ld,AY=%ld,AZ=%ld,GX=%ld,GY=%ld,GZ=%ld\r\n",
        (unsigned long)pkt->magic,
        (unsigned long)pkt->seq,
        (unsigned long)pkt->ts_us,
        (long)pkt->ax,
        (long)pkt->ay,
        (long)pkt->az,
        (long)pkt->gx,
        (long)pkt->gy,
        (long)pkt->gz);

    return HAL_UART_Transmit(s_uart, (uint8_t *)buffer, (uint16_t)len, 100);
}
