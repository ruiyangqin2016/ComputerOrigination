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
    Pixel r = c & 31;
    c = c >> 5;
    Pixel g = c & 31;
    c = c >> 5;
    Pixel b = c & 31;
    c =  ((r * 77) + (g * 151) + (b * 28)) >> 8;
    g = c;
    b = c;
    r = c;
    g = g << 5;
    b = b << 10;
    // b|g|r
    c = r | g;
    c = c | b;

    return c;
}

// TODO: Complete according to the prototype in graphics.h
Pixel redOnlyFilter(Pixel c) {
   
    Pixel r = c & 31;
    c = c >> 5;
    Pixel g = c & 31;
    c = c >> 5;
    Pixel b = c & 31;
//    c = ((r * 77) + (g * 151) + (b * 28)) >> 8;
    g = 0;
    b = 0;
//    r = c;
    g = g << 5;
    b = b << 10;
    // b|g|r

    c = r | g;
    c = c | b;
    return c;
}

// TODO: Complete according to the prototype in graphics.h
Pixel brighterFilter(Pixel c) {
    Pixel r = c & 31;
    c = c >> 5;
    Pixel g = c & 31;
    c = c >> 5;
    Pixel b = c & 31;
    Pixel diff_r = (31 & ~r) >> 1;
    diff_r = diff_r + r;
    Pixel diff_g = (31 & ~g) >> 1;
    diff_g = diff_g + g;
    Pixel diff_b = (31 & ~b) >> 1;
    diff_b = diff_b + b;
    diff_g = diff_g << 5;
    diff_b = diff_b << 10;
    c = diff_r | diff_g;
    c = c | diff_b;
    return c;
}


// TODO: Complete according to the prototype in graphics.h
void drawPixel(Screen *screen, Vector coordinates, Pixel pixel) {
//    UNUSED(screen);
//    UNUSED(coordinates);
//    UNUSED(pixel);
    int width = screen->size.x;
    int height = screen->size.y;
    int xCoord = coordinates.x;
    int yCoord = coordinates.y;
    if (xCoord < 0 || yCoord < 0 || xCoord >= width || yCoord >= height) {
        return;
    }

    /**
     * how to get pixel
     */
    screen->buffer[yCoord * width + xCoord] = pixel;
}

// TODO: Complete according to the prototype in graphics.h
void drawFilledRectangle(Screen *screen, Rectangle *rectangle) {
//    UNUSED(screen);
//    UNUSED(rectangle);
    int width = rectangle->size.x;
    int height = rectangle->size.y;

    int x = rectangle->top_left.x;
    int y = rectangle->top_left.y;

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            Vector newVector;
            newVector.x = x + c;
            newVector.y = y + r;
            drawPixel(screen, newVector, rectangle->color);
        }
    }
}


// TODO: Complete according to the prototype in graphics.h
void drawCircle(Screen *screen, Circle *circle) {
//    UNUSED(screen);
//    UNUSED(circle);

    Vector center = circle->center;
    Pixel color = circle->color;

    int mx = center.x;
    int my = center.y;
    int y = circle->radius;
    int d = 1 - circle->radius;
    int x = 0;
    
    while (x <= y) {
        Vector v1, v2, v3, v4, v5, v6, v7, v8;
        v1.x = mx + x;
        v1.y = my + y;
        drawPixel(screen, v1, color);
        
        v2.x = mx + x;
        v2.y = my - y;
        drawPixel(screen, v2, color);
        
        v3.x = mx - x;
        v3.y = my + y;
        drawPixel(screen, v3, color);
        
        v4.x = mx - x;
        v4.y = my - y;
        drawPixel(screen, v4, color);
        
        v5.x = mx + y;
        v5.y = my + x;
        drawPixel(screen, v5, color);
        
        v6.x = mx + y;
        v6.y = my - x;
        drawPixel(screen, v6, color);
        
        v7.x = mx - y;
        v7.y = my + x;
        drawPixel(screen, v7, color);
        
        v8.x = mx - y;
        v8.y = my - x;
        drawPixel(screen, v8, color);
        
        if (d < 0) {
            d = d + 2 * x + 3;
            x += 1;
        } else {
            d = d + 2 * (x - y) + 5;
            x += 1;
            y -= 1;
        }
    }
}

// TODO: Complete according to the prototype in graphics.h
void drawImage(Screen *screen, Image *image, CropWindow *cropWindow, Pixel (*colorFilter)(Pixel)) {
    int width = image->size.x;
    int height = image->size.y;
    
    int xI = image->top_left.x;
    int yI = image->top_left.y;

    /**
     * Draw the whole picture
     */
    int count = 0;
    if (cropWindow == NULL) {
        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                Vector newVector;
                newVector.x = xI + c;
                newVector.y = yI + r;
                drawPixel(screen, newVector, colorFilter(image->buffer[count]));
                count++;
            }
        }
    } else { // draw part of the picture
        /**
         * Knowing the difference between coordinate of image and coordinate of cropwindow
         */
        int absX = image->top_left.x - cropWindow->top_left.x;
        int absY = image->top_left.y - cropWindow->top_left.y;

        /**
         * do for loops from top_left of cropwindow
         */
        for (int r = 0; r < (int) cropWindow->size.y; r++) {
            for (int c = 0; c < (int) cropWindow->size.x; c++) {

                /**
                 * (newX, newY) is coordinate of current point
                 */
                int newX = (int) cropWindow->top_left.x + c;
                int newY = (int) cropWindow->top_left.y + r;

                /**
                 * if (newX, newY) is in image
                 */
                if ((newX >= (int) xI) && (newX < (int) screen->size.x)
                    && (newY >= (int) yI) && (newY < (int) screen->size.y)) {
                    Vector newVector;
                    int index = width * newY + newX;

                    /*
                     * absX is less than zero means cropwindow's top_left in right side of image;s top_left
                     */
                    if (absX < 0) {
                        newX += absX;
                    }

                    if (absY < 0) {
                        newY += absY;
                    }
                    newVector.x = newX;
                    newVector.y = newY;
                    drawPixel(screen, newVector, colorFilter(image->buffer[index]));
                }
            }
        }
    }
}


// TODO: Complete according to the prototype in graphics.              
void rotateImage(Screen *screen, Image *image, Pixel (*colorFilter)(Pixel)) {
    int width = image->size.x;
    int height = image->size.y;

    int xI = image->top_left.x;
    int yI = image->top_left.y;

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            int x = xI + c;
            int y = yI + r;
            Vector newVector;
            newVector.x = xI + width - c - 1;
            newVector.y = yI + height - r - 1;
            drawPixel(screen, newVector, colorFilter(image->buffer[width * y + x]));
        }
    }
}
