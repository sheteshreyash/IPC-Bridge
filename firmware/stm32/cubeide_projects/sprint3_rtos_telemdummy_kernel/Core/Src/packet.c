/*
 * packet.c
 *
 *  Created on: May 29, 2026
 *      Author: shreyash
 */

#include "packet.h"
#include <stddef.h>

void Packet_Init(void)
{
}

void Packet_Build(TelemetryPacket_t *pkt, uint32_t seq, uint32_t ts_us)
{
    if (pkt == NULL)
    {
        return;
    }

    pkt->magic = PACKET_MAGIC;

    pkt->seq = seq;
    pkt->ts_us = ts_us;

    pkt->ax = ((seq * 7U) % 2000U) - 1000;
    pkt->ay = ((seq * 11U) % 2000U) - 1000;
    pkt->az = ((seq * 13U) % 2000U) - 1000;

    pkt->gx = ((seq * 3U) % 500U) - 250;
    pkt->gy = ((seq * 5U) % 500U) - 250;
    pkt->gz = ((seq * 9U) % 500U) - 250;
}
