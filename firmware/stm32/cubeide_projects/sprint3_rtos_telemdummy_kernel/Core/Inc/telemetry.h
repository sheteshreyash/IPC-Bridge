/*
 * telemetry.h
 *
 *  Created on: May 28, 2026
 *      Author: shreyash
 */

#ifndef INC_TELEMETRY_H_
#define INC_TELEMETRY_H_

#include "main.h"
#include <stdint.h>

typedef struct
{
    uint32_t seq;
    uint32_t uptime_ms;

    int32_t ax_mg;
    int32_t ay_mg;
    int32_t az_mg;

    int32_t gx_mdps;
    int32_t gy_mdps;
    int32_t gz_mdps;

} TelemetryFrame_t;

void Telemetry_Init(UART_HandleTypeDef *huart);

void Telemetry_Generate(TelemetryFrame_t *frame);

void Telemetry_FormatString(const TelemetryFrame_t *frame,
                            char *buffer,
                            uint32_t buffer_size);

void Telemetry_SendFrame(const TelemetryFrame_t *frame,
                         uint32_t timeout_ms);


#endif /* INC_TELEMETRY_H_ */
