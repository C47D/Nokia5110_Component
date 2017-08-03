/****************************************************************************
* This file is part of the Custom Component for the Nokia5110 LCD Driver
*
* Copyright (C) 2017 Carlos Diaz <carlos.santiago.diaz@gmail.com>
*               2017 Sebastian Hernandez <sxxh@live.com>
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

#ifndef `$INSTANCE_NAME`_DISPLAY_H_
#define `$INSTANCE_NAME`_DISPLAY_H_
    
/***************************************************************************
* Include font files
***************************************************************************/
#include "`$INSTANCE_NAME`_FONTS.h"

#include "cytypes.h"
#include "cyfitter.h"

/***************************************************************************
* DRAW_OVER_BACKGROUND: Compiler directive that allow using backgroung under
* painting, this feature is enabled by default, to disable it
* place #undef DRAW_OVER_BACKGROUND between the
*
* // `#START DRAW_OVER_BACKGROUND` //
*
* // `#END` //
*
* section bellow.
***************************************************************************/
#define DRAW_OVER_BACKGROUND
/* `#START DRAW_OVER_BACKGROUND` */

/* `#END` */

#ifdef DRAW_OVER_BACKGROUND

static const char *Background;

typedef enum{
    DRAW_OR = 0,
    DRAW_XOR = 1,
    DRAW_CLEAR = 2
}DRAW_TYPE_t;

#endif // DRAW_OVER_BACKGROUND

typedef enum{
    Small_Font = 0,
    Middle_Font = 1
}FONT_TYPE_t;

/***************************************************************************
* Function prototypes
***************************************************************************/

#ifdef DRAW_OVER_BACKGROUND
void `$INSTANCE_NAME`_Init(const char* dataPtr);
void `$INSTANCE_NAME`_SetBackground(const char* dataPtr);
void `$INSTANCE_NAME`_Chr(char ch, DRAW_TYPE_t dtype, FONT_TYPE_t ftype);
void `$INSTANCE_NAME`_Str(const char* dataPtr, DRAW_TYPE_t dtype, FONT_TYPE_t ftype);
void `$INSTANCE_NAME`_BigStr(char* dataPtr, DRAW_TYPE_t dtype);
void `$INSTANCE_NAME`_VBargraph(uint8_t x, uint8_t ystart, uint8_t yend, uint8_t yposition, DRAW_TYPE_t dtype);
void `$INSTANCE_NAME`_HBargraph(uint8_t y, uint8_t xstart, uint8_t xend, uint8_t xposition, DRAW_TYPE_t dtype);
void `$INSTANCE_NAME`_Line(uint8_t xb, uint8_t yb, uint8_t xe, uint8_t ye, DRAW_TYPE_t dtype);
#else /* DRAW_OVER_BACKGROUND */
void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Chr(char ch, FONT_TYPE_t ftype);
void `$INSTANCE_NAME`_Str(const char* dataPtr, FONT_TYPE_t ftype);
void `$INSTANCE_NAME`_VBargraph(uint8_t x, uint8_t ystart, uint8_t yend, uint8_t yposition);
void `$INSTANCE_NAME`_HBargraph(uint8_t y, uint8_t xstart, uint8_t xend, uint8_t xposition);
void `$INSTANCE_NAME`_Line (uint8_t xb, uint8_t yb, uint8_t xe, uint8_t ye);
#endif /* DRAW_OVER_BACKGROUND */

void `$INSTANCE_NAME`_Clear(void);
void `$INSTANCE_NAME`_Contrast(uint8_t contrast);
void `$INSTANCE_NAME`_Goto(uint8_t column, uint8_t row);
void `$INSTANCE_NAME`_Image(uint8_t x, uint8_t y, uint8_t xsize, uint8_t ysize, const char* dataPtr);

#endif // `$INSTANCE_NAME`_DISPLAY_H_

/* [] END OF FILE */
