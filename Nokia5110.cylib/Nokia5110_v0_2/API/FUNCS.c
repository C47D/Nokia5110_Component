#include <stddef.h>

#include "CyLib.h"

#include "`$RST`.h"
#include "`$DC`.h"
#include "`$SS`.h"
#include "`$SPI`.h"

#include "`$INSTANCE_NAME`_FUNCS.h"
//#include "`$INSTANCE_NAME`_CONFIG.h"
#include "`$INSTANCE_NAME`_LL_SPI.h"
#include "`$INSTANCE_NAME`_CMD.h"

#define RST_DELAY   500

// 84 pixel x 6 lines = 504
#define DISPLAY_ROWS    84
#define DISPLAY_LINES   6
#define LCD_WIDTH       84
#define LCD_HEIGHT      48
#define PIXEL_WHITE     0
#define PIXEL_BLACK     1

// https://github.com/sparkfun/GraphicLCD_Nokia_5110/blob/master/Firmware/Nokia-5100-LCD-Example/LCD_Functions.h
enum {
    displaySize = (LCD_WIDTH * LCD_HEIGHT) / 8,
};

/*
 * The displayMap variable stores a buffer representation of the
 * pixels on our display. There are 504 total bits in this array,
 * same as how many pixels there are on a 84 x 48 display.
 * Each byte in this array covers a 8-pixel vertical block on the
 * display. Each successive byte covers the next 8-pixel column over
 * until you reach the right-edge of the display and step down 8 rows.
 * To update the display, we first have to write to this array, then
 * call the updateDisplay() function, which sends this whole array
 * to the PCD8544.
 * Because the PCD8544 won't let us write individual pixels at a
 * time, this is how we can make targeted changes to the display.
 */
static uint8_t displayMap[displaySize] = {0};

static inline bool `$INSTANCE_NAME`_isValidCoordinate(const uint8_t column, const uint8_t row)
{
    return ((row < LCD_WIDTH) && (column < LCD_HEIGHT)) ? true : false;
}

void `$INSTANCE_NAME`_start(void)
{
    `$SPI`_Start();
    `$SS`_Write(1);
    `$DC`_Write(0);
    
    `$INSTANCE_NAME`_reset();
    
    // Extended Commands.
    `$INSTANCE_NAME`_sendCommand(PCD544_FUNCTION_SET_CMD | PCD544_FUNCTION_SET_ADVANCED_INSTRUCTION_SET);
    // Set Vop (Contrast).
    `$INSTANCE_NAME`_sendCommand(PCD544_SET_VOP_CMD | 0x40);
    // Set Temp coefficent.
    `$INSTANCE_NAME`_sendCommand(PCD544_TMP_CTRL_CMD | PCD544_TMP_CTRL_COEFF_2);
    // Set bias mode 1:48.
    `$INSTANCE_NAME`_sendCommand(PCD544_SET_BIAS_CMD | 3);
    // Standard Commands,
    `$INSTANCE_NAME`_sendCommand(PCD544_FUNCTION_SET_CMD | PCD544_FUNCTION_SET_BASIC_INSTRUCTION_SET);
    // Horizontal addressing mode
    `$INSTANCE_NAME`_sendCommand(PCD544_DISPLAY_CTRL_CMD | PCD544_DISPLAY_CTRL_NORMAL_MODE);
    
    // set row address
    `$INSTANCE_NAME`_sendCommand(PCD544_SET_Y_ADDR_CMD | 0);
    // set column address
    `$INSTANCE_NAME`_sendCommand(PCD544_SET_X_ADDR_CMD | 0);
    // write display data

    `$INSTANCE_NAME`_clearDisplay();
    `$INSTANCE_NAME`_updateDisplay();
}

void `$INSTANCE_NAME`_reset(void)
{
    `$RST`_Write(0);
    CyDelay(RST_DELAY);
    `$RST`_Write(1);
}

void `$INSTANCE_NAME`_clearDisplay(void)
{
    memset(displayMap, 0, displaySize);
}

void `$INSTANCE_NAME`_updateDisplay(void)
{
    `$INSTANCE_NAME`_goto(0, 0);
    `$INSTANCE_NAME`_sendArrayData(displayMap, displaySize);
}

void `$INSTANCE_NAME`_goto(const uint8_t column, const uint8_t row)
{
    `$INSTANCE_NAME`_sendCommand(PCD544_SET_X_ADDR_CMD | column);
    `$INSTANCE_NAME`_sendCommand(PCD544_SET_Y_ADDR_CMD | row);
}

void `$INSTANCE_NAME`_writePixel(const pixel pixel,const uint8_t column, const uint8_t row)
{
    const uint8_t shift = column % 8;
        
    if (PIXEL_WHITE != pixel) {
        displayMap[column + (row/8)*LCD_WIDTH] |= 1 << shift;
    } else {
        displayMap[column + (row/8)*LCD_WIDTH] &= ~(1<< shift);
    }
}

void `$INSTANCE_NAME`_setPixel(const uint8_t column, const uint8_t row)
{
    `$INSTANCE_NAME`_writePixel(PIXEL_BLACK, column, row);
}

void `$INSTANCE_NAME`_clearPixel(const uint8_t column, const uint8_t row)
{
    `$INSTANCE_NAME`_writePixel(PIXEL_WHITE, column, row);
}

uint8_t `$INSTANCE_NAME`_getPixel(const uint8_t column, const uint8_t row)
{
    const uint8_t shift = column % 8;
    return (displayMap[column + (row/8)*LCD_WIDTH] & (1 << shift)) != PIXEL_WHITE;
}

void `$INSTANCE_NAME`_setYBank(const uint8_t bank)
{
    `$INSTANCE_NAME`_sendCommand(PCD544_SET_Y_ADDR_CMD | (bank & 0x07));
}

void `$INSTANCE_NAME`_setXBank(const uint8_t bank)
{
    `$INSTANCE_NAME`_sendCommand(PCD544_SET_X_ADDR_CMD | (bank & 0x7F));
}

/* [] END OF FILE */
