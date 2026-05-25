/*
 * telemetry.c
 *
 *  Created on: May 25, 2026
 *      Author: msi_katana_12
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
    frame->uptime_ms = s_uptime_ms++;

    /*
     * Dummy telemetry pattern:
     * Keep it simple and predictable for Sprint 1.
     * These values are just changing numbers, not real sensor data yet.
     */
    frame->ax_mg = (int32_t)((frame->seq * 7) % 2000) - 1000;
    frame->ay_mg = (int32_t)((frame->seq * 11) % 2000) - 1000;
    frame->az_mg = 1000 + (int32_t)((frame->seq * 3) % 250);

    frame->gx_mdps = (int32_t)((frame->seq * 13) % 4000) - 2000;
    frame->gy_mdps = (int32_t)((frame->seq * 17) % 4000) - 2000;
    frame->gz_mdps = (int32_t)((frame->seq * 19) % 4000) - 2000;
}

void Telemetry_FormatString(const TelemetryFrame_t *frame, char *out, size_t out_size)
{
    if (frame == NULL || out == NULL || out_size == 0U)
    {
        return;
    }

    /*
     * Text format is easiest for Sprint 1 validation in hterm/serial terminal.
     * Example:
     * SEQ=12,UPTIME_MS=12,AX=-345mg,AY=111mg,AZ=1023mg,GX=...
     */
    (void)snprintf(out,
                   out_size,
                   "SEQ=%lu,UPTIME_MS=%lu,AX=%ldmg,AY=%ldmg,AZ=%ldmg,GX=%ldmdps,GY=%ldmdps,GZ=%ldmdps\r\n",
                   (unsigned long)frame->seq,
                   (unsigned long)frame->uptime_ms,
                   (long)frame->ax_mg,
                   (long)frame->ay_mg,
                   (long)frame->az_mg,
                   (long)frame->gx_mdps,
                   (long)frame->gy_mdps,
                   (long)frame->gz_mdps);
}

HAL_StatusTypeDef Telemetry_SendFrame(const TelemetryFrame_t *frame, uint32_t timeout_ms)
{
    if (s_huart == NULL || frame == NULL)
    {
        return HAL_ERROR;
    }

    char msg[128];
    memset(msg, 0, sizeof(msg));
    Telemetry_FormatString(frame, msg, sizeof(msg));

    return HAL_UART_Transmit(s_huart, (uint8_t *)msg, (uint16_t)strlen(msg), timeout_ms);
}

