/**
* @file graphics.c
* @author YOUR NAME HERE
* @date DATE HERE
* @brief A graphics library for drawing geometry, for Homework 9 of Georgia Tech
*        CS 2110, Summer 2018.
*/

// Please take a look at the header file below to understand what's required for
// each of the functions.
#include "graphics.h"

Pixel noFilter(Pixel c) {

    return c;
}

// TODO: Complete according to the prototype in graphics.h
Pixel greyscaleFilter(Pixel c) {
    return c;
}

// TODO: Complete according to the prototype in graphics.h
Pixel redOnlyFilter(Pixel c) {
    return c;
}

// TODO: Complete according to the prototype in graphics.h
Pixel brighterFilter(Pixel c) {
    return c;
}


// TODO: Complete according to the prototype in graphics.h
void drawPixel(Screen *screen, Vector coordinates, Pixel pixel) {
    UNUSED(screen);
    UNUSED(coordinates);
    UNUSED(pixel);
}

// TODO: Complete according to the prototype in graphics.h
void drawFilledRectangle(Screen *screen, Rectangle *rectangle) {
    UNUSED(screen);
    UNUSED(rectangle);
}


// TODO: Complete according to the prototype in graphics.h
void drawCircle(Screen *screen, Circle *circle) {
    UNUSED(screen);
    UNUSED(circle);
}

// TODO: Complete according to the prototype in graphics.h
void drawImage(Screen *screen, Image *image, CropWindow *cropWindow, Pixel (*colorFilter)(Pixel)) {
    UNUSED(screen);
    UNUSED(image);
    UNUSED(cropWindow);
    UNUSED(colorFilter);
}

// TODO: Complete according to the prototype in graphics.              
void rotateImage(Screen *screen, Image *image, Pixel (*colorFilter)(Pixel)) {
	 UNUSED(screen);
     UNUSED(image);
     UNUSED(colorFilter);
}
