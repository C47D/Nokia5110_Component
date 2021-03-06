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

#ifndef `$INSTANCE_NAME`_HAL_SPI_H_
#define `$INSTANCE_NAME`_HAL_SPI_H_

#include <stdint.h>
#include <string.h>

void `$INSTANCE_NAME`_sendData(const uint8_t data);
void `$INSTANCE_NAME`_sendArrayData(const uint8_t *data, const size_t size);
void `$INSTANCE_NAME`_sendCommand(uint8_t command);

#endif /* `$INSTANCE_NAME`_HAL_SPI_H_ */

/* [] END OF FILE */
