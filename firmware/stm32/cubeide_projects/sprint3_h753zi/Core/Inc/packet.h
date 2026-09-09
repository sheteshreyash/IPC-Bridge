/*
 * packet.h
 *
 *  Created on: May 29, 2026
 *      Author: shreyash
 */

#ifndef INC_PACKET_H_
#define INC_PACKET_H_

#include <stdint.h>
#include <stddef.h>

#define PACKET_MAGIC 0x54454C4DUL

typedef struct __attribute__((packed))
{
    uint32_t magic;

    uint32_t seq;
    uint32_t ts_us;

    int32_t ax;
    int32_t ay;
    int32_t az;

    int32_t gx;
    int32_t gy;
    int32_t gz;

} TelemetryPacket_t;

void Packet_Init(void);

void Packet_Build(
        TelemetryPacket_t *pkt,
        uint32_t seq,
        uint32_t ts_us);

#endif /* INC_PACKET_H_ */
