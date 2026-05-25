/*
 * telemetry.h
 *
 *  Created on: May 25, 2026
 *      Author: msi_katana_12
 */

#ifndef INC_TELEMETRY_H_
#define INC_TELEMETRY_H_

#include "stm32h7xx_hal.h"
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

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
void Telemetry_FormatString(const TelemetryFrame_t *frame, char *out, size_t out_size);
HAL_StatusTypeDef Telemetry_SendFrame(const TelemetryFrame_t *frame, uint32_t timeout_ms);

#ifdef __cplusplus
}
#endif

#endif /* INC_TELEMETRY_H_ */
