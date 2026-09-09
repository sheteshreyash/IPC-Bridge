/*
 * producer.c
 *
 *  Created on: May 29, 2026
 *      Author: shreyash
 */

#include "producer.h"

static uint32_t s_seq = 0;
static uint32_t s_ts_us = 0;

void Producer_Init(void)
{
    s_seq = 0;
    s_ts_us = 0;
}

void Producer_Next(TelemetryPacket_t *pkt)
{
    if (pkt == NULL)
    {
        return;
    }

    Packet_Build(pkt, s_seq, s_ts_us);

    s_seq++;
    s_ts_us += 10000U; // 100 Hz = 10 ms = 10000 us
}
