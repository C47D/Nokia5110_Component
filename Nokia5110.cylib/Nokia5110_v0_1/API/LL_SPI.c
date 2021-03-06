/****************************************************************************
* This file is part of the Custom Component for the Nokia5110 LCD Driver
*
* Original port: 2016 Sebastian Hernandez <sxxh@live.com>
* PSoC Custom Component: 2017 Carlos Diaz <carlos.santiago.diaz@gmail.com>
*
* Permission to use, copy, modify, and/or distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
****************************************************************************/

#include "`$DC_PIN`.h"
#include "`$RST_PIN`.h"
#include "`$SPI_PERIPHERAL`.h"

#if defined(CY_SCB_`$SPI_PERIPHERAL`_H)
#include "`$SPI_PERIPHERAL`_SPI_UART.h"
#endif

#include <stdint.h>
#include "`$INSTANCE_NAME`_LL_SPI.h"

/**
* Description : Sends data to display controller.
* Argument(s) : data -> Data to be sent
* Return value : None.
*/
void `$INSTANCE_NAME`_SendData(const uint8_t data)
{
    `$RST_PIN`_Write(1);
    `$DC_PIN`_Write(1);
#if defined(CY_SCB_`$SPI_PERIPHERAL`_H) // SCB based SPI
    `$SPI_PERIPHERAL`_SpiUartWriteTxData(data);
    while (!(`$SPI_PERIPHERAL`_SpiIsBusBusy()) {
    }
#else
    `$SPI_PERIPHERAL`_WriteTxData(data);
    while (!(`$SPI_PERIPHERAL`_TX_STATUS_REG & `$SPI_PERIPHERAL`_STS_SPI_IDLE)) {
    }
#endif
}

/**
* Description : Sends command to display controller.
* Argument(s) : command -> Command to be sent
* Return value : None.
*/
void `$INSTANCE_NAME`_SendCommand(const uint8_t command)
{
    `$RST_PIN`_Write(1);
    `$DC_PIN`_Write(0);
#if defined(CY_SCB_`$SPI_PERIPHERAL`_H) // SCB based SPI
    `$SPI_PERIPHERAL`_SpiUartWriteTxData(command);
    while (`$SPI_PERIPHERAL`_SpiIsBusBusy()) {
    }
#else
    `$SPI_PERIPHERAL`_WriteTxData(command);
    while (!(`$SPI_PERIPHERAL`_TX_STATUS_REG & `$SPI_PERIPHERAL`_STS_SPI_IDLE)) {
    }
#endif
}

/* [] END OF FILE */
