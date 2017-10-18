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

#include <`$DC`.h>
#include <`$SS`.h>
#include <`$SPI`.h>

#if defined(CY_SCB_`$SPI`_H)
#include <`$SPI`_SPI_UART.h>
#endif

#include <stdint.h>

#include "`$INSTANCE_NAME`_LL_SPI.h"

/**
* Description : Sends data to display controller.
* Argument(s) : data -> Data to be sent
* Return value : None.
*/
void `$INSTANCE_NAME`_sendData(const uint8_t data)
{
    `$DC`_Write(1);
#if defined(CY_SCB_`$SPI_INTERFACE`_H) // SCB Block

    `$SPI`_SpiUartClearRxBuffer();
    `$SPI`_SpiUartClearTxBuffer();

    `$SS`_Write(0);
    `$SPI`_SpiUartWriteTxData(data);

    while (`$SPI`_SpiUartGetRxBufferSize() != 1) {
    }
    `$SS`_Write(1);

#else // UDB Block

    `$SPI`_ClearRxBuffer();
    `$SPI`_ClearTxBuffer();

    `$SS`_Write(0);
    `$SPI`_WriteTxData(data);

    while (!(`$SPI`_ReadTxStatus() & `$SPI`_STS_BYTE_COMPLETE)) {
    }
    `$SS`_Write(1);

#endif
}

void `$INSTANCE_NAME`_sendArrayData(const uint8_t *data, const size_t size)
{
    `$DC`_Write(1);
#if defined(CY_SCB_`$SPI_PERIPHERAL`_H) // SCB based SPI
    
    `$SPI`_SpiUartClearRxBuffer();
    `$SPI`_SpiUartClearTxBuffer();

    `$SS`_Write(0);
    `$SPI`_SpiUartPutArray(data, size);

    // Wait for the RxBuffer to have size + 1 bytes (W_REGISTER_CMD + data)
    // we're not using the SS pin embedded on the SCB component, so can't
    // rely on using the SPI_Status function.
    while (`$SPI`_SpiUartGetRxBufferSize() != size) {
    }
    `$SS`_Write(1);

#else
    
    `$SPI`_ClearRxBuffer();
    `$SPI`_ClearTxBuffer();

    `$SS`_Write(0);
    `$SPI`_PutArray(data, size);

    while (!(`$SPI`_ReadTxStatus() & `$SPI`_STS_BYTE_COMPLETE)) {
    }
    `$SS`_Write(1);
    
#endif
}

/**
* Description : Sends command to display controller.
* Argument(s) : command -> Command to be sent
* Return value : None.
*/
void `$INSTANCE_NAME`_sendCommand(const uint8_t cmd)
{
    `$DC`_Write(0);
#if defined(CY_SCB_`$SPI_INTERFACE`_H) // SCB Block

    `$SPI`_SpiUartClearRxBuffer();
    `$SPI`_SpiUartClearTxBuffer();

    `$SS`_Write(0);
    `$SPI`_SpiUartWriteTxData(cmd);

    while (`$SPI`_SpiUartGetRxBufferSize() != 1) {
    }
    `$SS`_Write(1);

#else // UDB Block

    `$SPI`_ClearRxBuffer();
    `$SPI`_ClearTxBuffer();

    `$SS`_Write(0);
    `$SPI`_WriteTxData(cmd);

    while (!(`$SPI`_ReadTxStatus() & `$SPI`_STS_BYTE_COMPLETE)) {
    }
    `$SS`_Write(1);

#endif
}

/* [] END OF FILE */
