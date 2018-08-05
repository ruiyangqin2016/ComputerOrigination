#include "myLib.h"

u16* videoBuffer = (u16*)0x6000000;

void setPixel(int row, int col, u16 color) {
    videoBuffer[row * 240 + col] = color;
}

void waitForVblank()
{
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 160);
}

void drawRedRectangle(int row, int col, int width, int height) {
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            setPixel(row + r, col + c, RED);
        }
    }
}

void drawImage(int row, int col, int width, int height, const u16* image) {
    for (int i = 0; i < height; i++) {
        DMA[3].dst = videoBuffer + OFFSET(i + row, col, 240);
        DMA[3].src = image + OFFSET(i, 0, width);
        DMA[3].cnt = width | DMA_ON | DMA_SOURCE_INCREMENT;
    }
}

void drawImageRotateLR(int row, int col, int width, int height, const u16* image) {
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            setPixel(ro)
        }
    }
}

void drawImageFlippedLR(int row, int col, int width, int height, const u16* image) {
    for (int i = 0; i < height; i++) {
        DMA[3].dst = videoBuffer + OFFSET(i + row, col, 240);
        // DMA[3].src = image + OFFSET(i + 1, -1, width);
        //DMA[3].src = image + OFFSET(i, width-1 ,width);
        DMA[3].src = image + OFFSET(i + 1, -1, width);
        DMA[3].cnt = width | DMA_ON | DMA_SOURCE_DECREMENT;
    }
}

void drawImageFlippedUD(int row, int col, int width, int height, const u16* image) {
    for (int i = 0; i < height; i++) {
        DMA[3].dst = videoBuffer + OFFSET(i + row, col, 240);
        DMA[3].src = image + OFFSET(height - i - 1, 0, width);
        //DMA[3].src = image + OFFSET(row - i - 1, col, width);
        DMA[3].cnt = width | DMA_ON;
    }
}
