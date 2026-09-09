/*
 * producer.h
 *
 *  Created on: May 29, 2026
 *      Author: shreyash
 */

#ifndef INC_PRODUCER_H_
#define INC_PRODUCER_H_

#include "main.h"
#include "packet.h"
#include <stdint.h>

void Producer_Init(void);
void Producer_Next(TelemetryPacket_t *pkt);

#endif /* INC_PRODUCER_H_ */
