#include <stddef.h>

#include "CyLib.h"

#include "`$RST_PIN`.h"
#include "`$DC_PIN`.h"
#include "`$SS_PIN`.h"
#include "`$SPI_INTERFACE`.h"

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

static uint8_t displayMap[displaySize] = {0};

static inline bool `$INSTANCE_NAME`_isValidCoordinate(const uint8_t column, const uint8_t row)
{
    return ((row < LCD_WIDTH) && (column < LCD_HEIGHT)) ? true : false;
}

void `$INSTANCE_NAME`_start(void)
{
    `$SPI_INTERFACE`_Start();
    `$SS_PIN`_Write(1);
    `$DC_PIN`_Write(0);
    //`$RST_PIN`_Write(1);
    
    /*
     * 8.1 Initialization
     * Immediately following power-on, the contents of all internal registers and
     * of the RAM are undefined. A /RES pulse must be applied.
     * 
    */
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

    // After reset the Display is Blank, so this can be removed?
    //`$INSTANCE_NAME`_clearDisplay();
    //`$INSTANCE_NAME`_updateDisplay();
}

void `$INSTANCE_NAME`_reset(void)
{
    `$RST_PIN`_Write(0);
    CyDelay(RST_DELAY);
    `$RST_PIN`_Write(1);
}

// this function clear the entire display
// eigther white or black.
void `$INSTANCE_NAME`_clearDisplay(void)
{
    // por ahora solo escribimos en fondo blanco y pixel negro
    memset(displayMap, 0, displaySize);
}

void `$INSTANCE_NAME`_updateDisplay(void)
{
    `$INSTANCE_NAME`_goto(0, 0);
    // check for a function to write the whole array
    #if 0
    for(size_t i = 0; i < displaySize; i++) {
        `$INSTANCE_NAME`_sendData(displayMap[i]);
    }
    #else
        `$INSTANCE_NAME`_sendArrayData(displayMap, displaySize);
    #endif
}

void `$INSTANCE_NAME`_goto(const uint8_t column, const uint8_t row)
{
    `$INSTANCE_NAME`_sendCommand(0x80 | column);
    `$INSTANCE_NAME`_sendCommand(0x40 | row);
}

void `$INSTANCE_NAME`_writePixel(const pixel pixel,const uint8_t column, const uint8_t row)
{
    if(`$INSTANCE_NAME`_isValidCoordinate(column, row)) {
        const uint8_t shift = column % 8;
        
        if (PIXEL_WHITE != pixel) {
            displayMap[column + (row/8)*LCD_WIDTH] |= 1 << shift;
        } else {
            displayMap[column + (row/8)*LCD_WIDTH] &= ~(1<< shift);
        }
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
#if 1
    uint8_t pix = PIXEL_WHITE;
    
    if(`$INSTANCE_NAME`_isValidCoordinate(column, row)) {
        const uint8_t shift = column % 8;
        pix = (displayMap[column + (row/8)*LCD_WIDTH] & (1 << shift)) != PIXEL_WHITE;
    } else {
        pix = UINT8_MAX;
    }
    
    return pix;
#else
    return (displayMap[column + (row/8)*LCD_WIDTH] & (1 << shift)) != PIXEL_WHITE;
#endif
}

/* [] END OF FILE */
