#ifndef `$INSTANCE_NAME`_FUNCS_H
#define `$INSTANCE_NAME`_FUNCS_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    PIXEL_WHITE = 0,
    PIXEL_BLACK = 1,
} pixel;

void `$INSTANCE_NAME`_start(void);
void `$INSTANCE_NAME`_reset(void);
void `$INSTANCE_NAME`_clearDisplay(void);
void `$INSTANCE_NAME`_updateDisplay(void);

void `$INSTANCE_NAME`_goto(const uint8_t column, const uint8_t row);

void `$INSTANCE_NAME`_writePixel(const pixel pixel,const uint8_t column, const uint8_t row);
void `$INSTANCE_NAME`_setPixel(const uint8_t column, const uint8_t row);
void `$INSTANCE_NAME`_clearPixel(const uint8_t column, const uint8_t row);
uint8_t `$INSTANCE_NAME`_getPixel(const uint8_t column, const uint8_t row);

#endif

/* [] END OF FILE */
