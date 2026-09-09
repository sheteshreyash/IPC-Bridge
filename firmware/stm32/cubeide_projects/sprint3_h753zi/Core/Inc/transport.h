/*
 * transport.h
 *
 *  Created on: May 29, 2026
 *      Author: shreyash
 */

#ifndef INC_TRANSPORT_H_
#define INC_TRANSPORT_H_

#include "main.h"
#include "packet.h"

#define TRANSPORT_PACKET_SIZE sizeof(TelemetryPacket_t)

void Transport_Init(void);

void Transport_SetReady(void);
void Transport_ClearReady(void);

HAL_StatusTypeDef Transport_DebugSend(const TelemetryPacket_t *pkt);

/*
 * Arm the SPI1 slave transmitter with the packet.
 * DATA_READY is asserted only after the SPI transfer is armed.
 */
HAL_StatusTypeDef Transport_SendPacket(const TelemetryPacket_t *pkt);

#endif /* INC_TRANSPORT_H_ */
