/*
 * telemetry.c
 *
 *  Created on: May 28, 2026
 *      Author: shreyash
 */

#include "telemetry.h"

#include <stdio.h>
#include <string.h>

static UART_HandleTypeDef *s_huart = NULL;

static uint32_t s_seq = 0;
static uint32_t s_uptime_ms = 0;

void Telemetry_Init(UART_HandleTypeDef *huart)
{
    s_huart = huart;

    s_seq = 0;
    s_uptime_ms = 0;
}

void Telemetry_Generate(TelemetryFrame_t *frame)
{
    if (frame == NULL)
    {
        return;
    }

    frame->seq = s_seq++;
    frame->uptime_ms = s_uptime_ms;

    s_uptime_ms += 100;

    frame->ax_mg = ((frame->seq * 7) % 2000) - 1000;
    frame->ay_mg = ((frame->seq * 11) % 2000) - 1000;
    frame->az_mg = ((frame->seq * 13) % 2000);

    frame->gx_mdps = ((frame->seq * 3) % 500) - 250;
    frame->gy_mdps = ((frame->seq * 5) % 500) - 250;
    frame->gz_mdps = ((frame->seq * 9) % 500) - 250;
}

void Telemetry_FormatString(const TelemetryFrame_t *frame,
                            char *buffer,
                            uint32_t buffer_size)
{
    if ((frame == NULL) || (buffer == NULL))
    {
        return;
    }

    snprintf(buffer,
             buffer_size,
             "SEQ=%lu,UPTIME=%lu ms,"
             "AX=%ld mg,AY=%ld mg,AZ=%ld mg,"
             "GX=%ld mdps,GY=%ld mdps,GZ=%ld mdps\r\n",

             (unsigned long)frame->seq,
             (unsigned long)frame->uptime_ms,

             (long)frame->ax_mg,
             (long)frame->ay_mg,
             (long)frame->az_mg,

             (long)frame->gx_mdps,
             (long)frame->gy_mdps,
             (long)frame->gz_mdps);
}

void Telemetry_SendFrame(const TelemetryFrame_t *frame,
                         uint32_t timeout_ms)
{
    if ((frame == NULL) || (s_huart == NULL))
    {
        return;
    }

    char tx_buffer[256];

    memset(tx_buffer, 0, sizeof(tx_buffer));

    Telemetry_FormatString(frame,
                           tx_buffer,
                           sizeof(tx_buffer));

    HAL_UART_Transmit(s_huart,
                      (uint8_t *)tx_buffer,
                      strlen(tx_buffer),
                      timeout_ms);
}

