/*
 * transport.c
 *
 *  Created on: May 29, 2026
 *      Author: shreyash
 */

#include "transport.h"
#include "cmsis_os.h"
#include <stdio.h>
#include <string.h>

extern UART_HandleTypeDef huart3;
extern SPI_HandleTypeDef hspi1;

static UART_HandleTypeDef *s_uart = NULL;

static TelemetryPacket_t s_spi_tx_packet;
static volatile uint8_t s_spi_tx_busy = 0;

void Transport_Init(void)
{
    s_uart = &huart3;

    memset(&s_spi_tx_packet, 0, sizeof(s_spi_tx_packet));

    s_spi_tx_busy = 0;

    Transport_ClearReady();
}

void Transport_SetReady(void)
{
    HAL_GPIO_WritePin(
        DATA_READY_GPIO_Port,
        DATA_READY_Pin,
        GPIO_PIN_SET);
}

void Transport_ClearReady(void)
{
    HAL_GPIO_WritePin(
        DATA_READY_GPIO_Port,
        DATA_READY_Pin,
        GPIO_PIN_RESET);
}

HAL_StatusTypeDef Transport_SendPacket(const TelemetryPacket_t *pkt)
{
    HAL_StatusTypeDef status;

    if (pkt == NULL)
    {
        return HAL_ERROR;
    }

    /*
     * Do not overwrite the packet while the SPI peripheral is
     * transmitting the previous one.
     */
    if (s_spi_tx_busy != 0U)
    {
        return HAL_BUSY;
    }

    memcpy(&s_spi_tx_packet, pkt, sizeof(s_spi_tx_packet));

    s_spi_tx_busy = 1U;

    /*
     * Arm SPI1 slave TX before asserting DATA_READY.
     * The Jetson will generate the clock after seeing DATA_READY.
     */
    status = HAL_SPI_Transmit_IT(
        &hspi1,
        (uint8_t *)&s_spi_tx_packet,
        sizeof(s_spi_tx_packet));

    if (status != HAL_OK)
    {
        s_spi_tx_busy = 0U;
        return status;
    }

    Transport_SetReady();

    return HAL_OK;
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if (hspi->Instance == SPI1)
    {
        Transport_ClearReady();
        s_spi_tx_busy = 0U;
    }
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
    if (hspi->Instance == SPI1)
    {
        Transport_ClearReady();
        s_spi_tx_busy = 0U;
    }
}

HAL_StatusTypeDef Transport_DebugSend(const TelemetryPacket_t *pkt)
{
    if (pkt == NULL || s_uart == NULL)
    {
        return HAL_ERROR;
    }

    char buffer[256];

    int len = snprintf(
        buffer,
        sizeof(buffer),
        "MAGIC=%08lX,SEQ=%lu,TS=%lu,AX=%ld,AY=%ld,AZ=%ld,GX=%ld,GY=%ld,GZ=%ld\r\n",
        (unsigned long)pkt->magic,
        (unsigned long)pkt->seq,
        (unsigned long)pkt->ts_us,
        (long)pkt->ax,
        (long)pkt->ay,
        (long)pkt->az,
        (long)pkt->gx,
        (long)pkt->gy,
        (long)pkt->gz);

    if (len < 0)
    {
        return HAL_ERROR;
    }

    if (len >= (int)sizeof(buffer))
    {
        len = sizeof(buffer) - 1;
    }

    return HAL_UART_Transmit(
        s_uart,
        (uint8_t *)buffer,
        (uint16_t)len,
        100);
}
