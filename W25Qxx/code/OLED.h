#ifndef _oled_h
#define _oled_h

#include "i2c.h"
#include "string.h"
// #include "stdio.h"
#include "stdlib.h"
#include "font.h"
#include "W25Q64.h"


// 移除冗余空行，保持头文件整洁

typedef enum {
    OLED_COLOR_NORMAL = 0, // 正常模式 黑底白字
    OLED_COLOR_REVERSED = 1    // 反色模式 白底黑字
  } OLED_ColorMode;

void OLED_Init(void);
// void oled_test(void);
void OLED_SendCmd(uint8_t cmd);
void OLED_Show(void);
void OLED_Clear(void);

void OLED_SetColorMode(OLED_ColorMode mode);
void OLED_SetByte_Fine(uint8_t page, uint8_t column, uint8_t data, uint8_t start, uint8_t end, OLED_ColorMode color);
void OLED_SetByte(uint8_t page, uint8_t column, uint8_t data, OLED_ColorMode color);
void OLED_SetBits_Fine(uint8_t x, uint8_t y, uint8_t data, uint8_t len, OLED_ColorMode color);
void OLED_SetBits(uint8_t x, uint8_t y, uint8_t data, OLED_ColorMode color);
void OLED_SetBlock(uint8_t x, uint8_t y, const uint8_t *data, uint8_t w, uint8_t h, OLED_ColorMode color);

void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);

void OLED_DisplayPixel(uint8_t x,uint8_t y,OLED_ColorMode color);
void OLED_DisplayLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,OLED_ColorMode color);
void OLED_DisplayRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h,OLED_ColorMode color);
void OLED_DisplayFilledRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h,OLED_ColorMode color);
void OLED_DisplayTriangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, OLED_ColorMode color);
void OLED_DisplayFilledTriangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, OLED_ColorMode color);
void OLED_DisplayCircle(uint8_t x, uint8_t y, uint8_t r, OLED_ColorMode color);
void OLED_DisplayFilledCircle(uint8_t x, uint8_t y, uint8_t r, OLED_ColorMode color);
void OLED_DisplayEllipse(uint8_t x, uint8_t y, uint8_t a, uint8_t b, OLED_ColorMode color);
void OLED_DisplayPicture(uint8_t x, uint8_t y, const Image *img, OLED_ColorMode color);

// void OLED_PrintString(uint8_t x, uint8_t y, char *str, uint8_t * Data, OLED_ColorMode color);
void OLED_PrintString(uint8_t x, uint8_t y, char *str, OLED_ColorMode color);
void OLED_PrintASCIIChar(uint8_t x, uint8_t y, char ch, const ASCIIFont *font, OLED_ColorMode color);
void OLED_PrintASCIIString(uint8_t x, uint8_t y, char *str, const ASCIIFont *font, OLED_ColorMode color);


#endif
