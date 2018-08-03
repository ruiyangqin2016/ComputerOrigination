// Name: *YOUR NAME HERE*

#include "myLib.h"
#include "im1.h"
#include "im2.h"
#include "im3.h"
#include "im4.h"
#include <stdint.h>

volatile unsigned short *videoBuffer = (unsigned short *)0x6000000;

#define UNUSED_PARAM(param) ((void) (param))

/*
	Use DMA to implement to fill the top half of the GBA screen
	with the color specified by the parameter color, and the bottom half
	of the screen with the complement of the original color.
	The complement of the color can be found by subtracting each 
	channel's value from the maximum possible value for each channel.
	For example: 
		                    | Blue  | Green | Red   |
		Red:              0 | 00000 | 00000 | 11111 |
		Red's complement: 0 | 11111 | 11111 | 00000 |
	Notes:
		- The parameter will never be NULL.
		- You must use DMA.
		- Do not use any looping constructs.
*/
void fillScreen(volatile u16* color) {

	DMA[3].cnt = 19200 | DMA_ON | DMA_SOURCE_FIXED;
	DMA[3].src = color;
	DMA[3].dst = videoBuffer + 0;

    volatile u16 newColor = *color;	
	u16 r = 0x1F - newColor;
	newColor = newColor >> 5;
	u16 g = 0x1F - newColor;
	newColor = newColor >> 5;
	u16 b = 0x1F - newColor;
	g = g << 5;
	b = b << 10;
	newColor = r | g;
	newColor = newColor | b;
	DMA[3].cnt = 19200 | DMA_ON | DMA_SOURCE_FIXED;
	DMA[3].src = &newColor;
	DMA[3].dst = videoBuffer + 19200;
//========================================================
	// uint16_t r = (uint16_t)&color - 0x1F;
	// (uint16_t)&color = (uint16_t)&color >> 5;
	// uint16_t g = (uint16_t)&color - 0x1F;
	// (uint16_t)&color = (uint16_t)&color >> 5;
	// uint16_t b = (uint16_t)&color - 0x1F;
	// g = g << 5;
	// b = b << 10;
	// (uint16_t)&color = r | g;
	// (uint16_t)&color = (uint16_t)color | b;
	
//	UNUSED_PARAM(color);
}


/*
	Use DMA to draw the cropped portion of an image on the GBA screen.
	If the cropWidth is larger than imWidth, or cropHeight is larger than 
	imHeight, do not draw anything to the screen and return a value of 1.
	Otherwise, return a value of 0 after drawing the cropped image to the
	screen, starting at row, col.

	Notes:
		- image will never be NULL
		- The crop window should be centered on the image. In other words, 
		  the margins should be evenly distributed.
		- Use exactly 1 for-loop (no nested loops).
*/
int cropAndDisplay(const unsigned short *image, unsigned int imWidth, unsigned int imHeight, 
	unsigned int cropWidth, unsigned int cropHeight,unsigned int row, unsigned int col) {
	if (cropHeight > imHeight || cropWidth > imWidth) {
		return 1;
	} else {
		unsigned int r = (imHeight - cropHeight)/2;
		unsigned int c = (imWidth - cropWidth)/2;
		for (unsigned int i = 0; i <= cropHeight; i++) {
			DMA[3].cnt = cropWidth | DMA_ON;
			DMA[3].dst = videoBuffer + OFFSET(i + row, col, 240);
			DMA[3].src = image + OFFSET(i + r, c, imWidth);
		}
		return 0;
	}


	// UNUSED_PARAM(image);
	// UNUSED_PARAM(imWidth);
	// UNUSED_PARAM(imHeight);
	// UNUSED_PARAM(cropWidth);
	// UNUSED_PARAM(cropHeight);
	// UNUSED_PARAM(row);
	// UNUSED_PARAM(col);
	// return 1;
}


/*
	Using the functions you just wrote, draw all the images onto the screen. 

*/
int main(void)
{
	/*
	You should not need to modify this function!
	*/
	volatile u16 blue = BLUE;
	volatile u16 magenta = MAGENTA;
	REG_DISPCNT = MODE3 | BG2_ENABLE;
	waitForVblank();

	// 1. Color the screen blue
	fillScreen(&blue);
	
	// 2. Draw the first image at top left section
	int r1 = cropAndDisplay(im1, IM1_WIDTH, IM1_HEIGHT, 60, 100, 0, 0);
	
	// 3.Draw the second image at middle top section
	int r2 = cropAndDisplay(im2, IM2_WIDTH, IM2_HEIGHT, 60, 100, 0, 62);
	
	// 4. Draw the third image at right section
	int r3 = cropAndDisplay(im3, IM3_WIDTH, IM3_HEIGHT, 116, 160, 0, 124);
	
	// 5. Draw the fourth image at bottom secion
	int r4 = cropAndDisplay(im4, IM4_WIDTH, IM4_HEIGHT, 124, 60, 100, 0);

	// 6. Try to draw image with invalid crop:
	int r5 = cropAndDisplay(im3, IM3_WIDTH, IM3_HEIGHT, 240, 160, 0, 0);


	// 7. Check if return values from cropAndDisplay() are correct. 
	// If your fill screen is correct but your return values for 
	// cropAndDisplay() were incorrect, you should see a screen
	// with the top half magenta and the bottom half green.
	while (!r1 && !r2 && !r3 && !r4 && r5);

	fillScreen(&magenta);
	while(1);
}


void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}
