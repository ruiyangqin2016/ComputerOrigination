#include "myLib.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;

void setPixel(int row, int col, u16 color)
{
	videoBuffer[OFFSET(row, col, 240)] = color;
}

void drawRect(int row, int col, int height, int width, u16 color)
{
	int r, c;
	for(r = 0; r < height; r++)
	{
		for(c = 0; c < width; c++)
		{
			setPixel(row+r, col+c, color);
		}
	}
}

void waitForVblank()
{
	while(*SCANLINECOUNTER > 220);
	while(*SCANLINECOUNTER < 220);
}

void drawImageSpray(int row, int col, int height, int width, const u16* image)
{
	int r;
	for(r = 0; r < height; r++)
	{
		DMA[3].src = &image[r * width];
		DMA[3].dst = &videoBuffer[OFFSET(row + r, col, 240)];
		DMA[3].cnt = DMA_ON | width;
	}
}

void drawHollowRect(int row, int col, int height, int width, u16 color)
{
	int r, c;
	for(r = 0; r < height; r++)
	{
		for(c = 0; c < width; c++)
		{
			setPixel((row+r), col, color);
			setPixel(row, (col+c), color);
		}
	}
	for(r = 0; r <= height; r++)
	{
		for(c = 0; c <= width; c++)
		{
			setPixel((row+height -r), (col + width), color);
			setPixel((row + height), (col+width - c), color);
		}
	}

}
