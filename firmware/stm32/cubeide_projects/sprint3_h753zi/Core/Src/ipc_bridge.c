/*
 * ipc_bridge.c
 *
 *  Created on: May 29, 2026
 *      Author: shreyash
 */

#include "ipc_bridge.h"

#include "packet.h"
#include "producer.h"
#include "transport.h"

void IPC_Bridge_Init(void)
{
    Packet_Init();
    Producer_Init();
    Transport_Init();
    Transport_ClearReady();
}

void IPC_Bridge_Task(void)
{
    TelemetryPacket_t pkt;

    Producer_Next(&pkt);

    /*
     * Keep UART alive as the independent STM32 debug path.
     */
    (void)Transport_DebugSend(&pkt);

    /*
     * Prepare and advertise the packet to the Jetson.
     *
     * The SPI transfer itself occurs asynchronously.
     */
    (void)Transport_SendPacket(&pkt);
}
