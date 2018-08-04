//
// Created by China on 07/08/2018.
//

#include "myLib.h"

u16 *videoBuffer = (u16*) 0x6000000;

void setPixel(int r, int c, u16 color) {
    videoBuffer[OFFSET(r, c, 240)] = color;
}

void drawImage3(int row, int col, int width, int height, const u16* image) {
    for (int i = 0; i < height; i++) {
        DMA[3].dst = videoBuffer + OFFSET(i + row, col, 240);
        DMA[3].src = image + OFFSET(i, 0, width);
        DMA[3].cnt = width | DMA_ON;
    }
}

void waitForVBlank() {
    if (SCANLINECOUNTER > 160) {
        while (SCANLINECOUNTER > 160);
    } else {
        while (SCANLINECOUNTER < 160);
    }
}

void drawRectangle(int row, int column, int width, int height, u16 color) {
    for (int i = 0; i < height; i++) {
        DMA[3].cnt = width | DMA_SOURCE_FIXED | DMA_ON;
        DMA[3].src = &color;
        DMA[3].dst = videoBuffer + OFFSET(i + row, column, 240);
    }
}

void clear() {
    volatile u16 color = RED;
    for (int i = 0; i < 160; i++) {
        DMA[3].cnt = 240 | DMA_ON | DMA_SOURCE_FIXED;
        DMA[3].src = &color;
        DMA[3].dst = videoBuffer + OFFSET(i, 240, 240);
    }
}

void drawChar(int row, int col, char ch, unsigned short color)
{
    for(int r = 0; r<8; r++)
    {
        for(int c=0; c<6; c++)
        {
            if(fontdata_6x8[OFFSET(r, c, 6) + ch*48])
            {
                setPixel(row+r, col+c, color);
            }
        }
    }
}

void drawString(int row, int col, char *str, unsigned short color)
{
    while(*str)
    {
        drawChar(row, col, *str++, color);
        col += 6;
    }
}
