//
// Created by China on 07/07/2018.
//

// Make a whatever I don't know GBA game
// Name: Ruiyang Qin

#include <stdbool.h>
#include <stdio.h>
#include "myLib.h"

volatile int counter = 0;

int main() {

    REG_DISPCNT = MODE3 | BG2_ENABLE;
    enum GBAState state = STATE_START;
    int holdState = STATE_MENU;

    while (1) {
        waitForVBlank();

        switch (state) {
            case STATE_START:
		counter = 0;
                drawImage3(0, 0 , IMG_START_WIDTH, IMG_START_HEIGHT, img_start);
                state = STATE_MENU;
                holdState = STATE_MENU;
                while (KEY_DOWN_NOW(BUTTON_START)) {
                    // do nothing
                }
                break;
            case STATE_MENU:
                if (KEY_DOWN_NOW(BUTTON_START)) {
                    state = STATE_GAMING;
                }
                if (KEY_DOWN_NOW(BUTTON_SELECT)) {
		    counter = 0;
                    state = STATE_START;
                }
                if (holdState == STATE_LOSE) {
                    state = STATE_LOSE;
                }
                if (holdState == STATE_WIN) {
                    state = STATE_WIN;
                }
                if (holdState == STATE_START) {
                    state = STATE_START;
                }
                break;
            case STATE_GAMING:
                holdState = game();
                state = STATE_MENU;
                while (KEY_DOWN_NOW(BUTTON_SELECT)) {
                    // do nothing
                }
                if (KEY_DOWN_NOW(BUTTON_SELECT)) {
		    counter = 0;
		    holdState = STATE_START;
                    state = STATE_START;
                }
                break;
            case STATE_LOSE:
                drawImage3(0, 0 , IMG_LOSE_WIDTH, IMG_LOSE_HEIGHT, img_lose); 
                state = STATE_MENU;
                holdState = STATE_MENU;
                while (KEY_DOWN_NOW(BUTTON_SELECT)) {
                    // do nothing
                }
                if (KEY_DOWN_NOW(BUTTON_SELECT)) {
		    counter = 0;
		    holdState = STATE_START;
                    state = STATE_START;
                }
                break;
            case STATE_WIN:
                drawImage3(0, 0, IMG_WIN_WIDTH, IMG_WIN_HEIGHT, img_win);
                state = STATE_MENU;
                holdState = STATE_MENU;
                while (KEY_DOWN_NOW(BUTTON_SELECT)) {
                    // do nothing
                }
                if (KEY_DOWN_NOW(BUTTON_SELECT)) {
		    counter = 0;
		    holdState = STATE_START;
                    state = STATE_START;
                }
                break;
        }
    }
    return 0;
}

void Square(square sqr) {
    drawRectangle(sqr.row, sqr.column, sqr.size, sqr.size, sqr.color);
}

int getHorizontalSpeed(square sqr) {
    int speed = 0;
    if (sqr.column + sqr.horizontalSpeed > sqr.right || sqr.column + sqr.horizontalSpeed < sqr.left) {
        speed = (-1) * sqr.horizontalSpeed;
    } else {
        speed = sqr.horizontalSpeed;
    }
    return speed;
}

int getVerticalSpeed(square sqr) {
    int speed = 0;
    if (sqr.row + sqr.verticalSpeed > sqr.bottom || sqr.row + sqr.verticalSpeed < sqr.top) {
        speed = (-1) * sqr.verticalSpeed;
    } else {
        speed = sqr.verticalSpeed;
    }
    return speed;
}

void clean(square sqr) {
    drawRectangle(sqr.row, sqr.column, sqr.size, sqr.size, BLACK);
}

int game() {
    clear();
    drawRectangle(15, 0, 35, 2, BLUE);
    drawRectangle(40, 0, 35, 2, BLUE);
    drawRectangle(0, 50, 2, 20, BLUE);
    drawRectangle(100, 160, 2, 60, BLUE);
    drawImage3(130, 220, IMG_GREEN_BAR_WIDTH, IMG_GREEN_BAR_HEIGHT, img_green_bar);

    square vertiMove1;
    vertiMove1.row = 100; vertiMove1.column = 200; vertiMove1.size = 4; vertiMove1.horizontalSpeed = 0; vertiMove1.verticalSpeed = 1.5; vertiMove1.color = YELLOW;
    vertiMove1.left = 180; vertiMove1.right = 100; vertiMove1.top = 0; vertiMove1.bottom = 157;

    square vertiMove2;
    vertiMove2.row = 140; vertiMove2.column = 120; vertiMove2.size = 4; vertiMove2.horizontalSpeed = 0; vertiMove2.verticalSpeed = 1.5; vertiMove2.color = BLUE;
    vertiMove2.left = 120; vertiMove2.right = 120; vertiMove2.top = 0; vertiMove2.bottom = 157;

    square vertiMove3;
    vertiMove3.row = 0; vertiMove3.column = 180; vertiMove3.size = 4; vertiMove3.horizontalSpeed = 0; vertiMove3.verticalSpeed = 1; vertiMove3.color = CYAN;
    vertiMove3.left = 180; vertiMove3.right = 180; vertiMove3.top = 0; vertiMove3.bottom = 157;

    square vertiMove4;
    vertiMove4.row = 90; vertiMove4.column = 80; vertiMove4.size = 4; vertiMove4.horizontalSpeed = 0; vertiMove4.verticalSpeed = 1; vertiMove4.color = CYAN;
    vertiMove4.left = 90; vertiMove4.right = 90; vertiMove4.top = 0; vertiMove4.bottom = 157;

    square vertiMove5;
    vertiMove5.row = 60; vertiMove5.column = 40; vertiMove5.size = 4; vertiMove5.horizontalSpeed = 0; vertiMove5.verticalSpeed = 1; vertiMove5.color = GREEN;
    vertiMove5.left = 180; vertiMove5.right = 90; vertiMove5.top = 0; vertiMove5.bottom = 157;

    square horizMove1;
    horizMove1.row = 80; horizMove1.column = 0; horizMove1.size = 4; horizMove1.horizontalSpeed = 1; horizMove1.verticalSpeed = 0; horizMove1.color = WHITE;
    horizMove1.left = 0; horizMove1.right = 236; horizMove1.top = 70; horizMove1.bottom = 70;

    square horizMove2;
    horizMove2.row = 30; horizMove2.column = 60; horizMove2.size = 4; horizMove2.horizontalSpeed = 1; horizMove2.verticalSpeed = 0; horizMove2.color = YELLOW;
    horizMove2.left = 0; horizMove2.right = 236; horizMove2.top = 90; horizMove2.bottom = 90;

    square horizMove3;
    horizMove3.row = 50; horizMove3.column = 180; horizMove3.size = 4; horizMove3.horizontalSpeed = 1; horizMove3.verticalSpeed = 0; horizMove3.color = GRAY;
    horizMove3.left = 0; horizMove3.right = 236; horizMove3.top = 50; horizMove3.bottom = 50;

    square self;
    self.row = 0; self.column = 0; self.size = 3; self.horizontalSpeed = 0; self.verticalSpeed = 0; self.color = RED;
    self.left = 0; self.right = 238; self.top = 0; self.bottom = 160;

    Square(self);
    Square(vertiMove1);
    Square(vertiMove2);
    Square(vertiMove3);
    Square(vertiMove4);
    Square(vertiMove5);
    Square(horizMove1);
    Square(horizMove2);
    Square(horizMove3);

    while (1) {
	drawImage3(130, 220, IMG_GREEN_BAR_WIDTH, IMG_GREEN_BAR_HEIGHT, img_green_bar);
        drawString(140, 0, "Score: ", RED);
	char buffer[100];
        if (counter <= 0) {
            counter = 0;
        }
	sprintf(buffer, "%d", counter);
	drawString(150, 13, buffer, RED);
        int x = self.column;
        int y = self.row;

	if(KEY_DOWN_NOW(BUTTON_RIGHT) || KEY_DOWN_NOW(BUTTON_B)) {
	    drawRectangle(125, 0 , 40, 10, BLACK);
	    drawString(125, 0, "RIGHT", RED);
            x = self.column + 1;
            if (x > 238) {
                x = 238;
            }
            if (x == 47 && y < 20) {
                x -= 1;
            }
            if (x == 157 && y > 100) {
                x -= 1;
            }
        }

        if(KEY_DOWN_NOW(BUTTON_LEFT) || KEY_DOWN_NOW(BUTTON_A)) {
	    drawRectangle(125, 0 , 40, 10, BLACK);
	    drawString(125, 0, "LEFT", RED);
            x = self.column - 1;
            if (x < 0 ) {
                x = 0;
            }
            if ((x < 35 && y == 15) || (x < 35 && y == 14)) {
                x += 1;
            }
            if ((x < 35 && y == 38) || (x < 35 && y == 39)) {
                x += 1;
            }
            if (x == 52 && y < 20) {
                x += 1;
            }
            if (x == 162 && y > 100) {
                x += 1;
            }
        }

        if(KEY_DOWN_NOW(BUTTON_UP) || KEY_DOWN_NOW(BUTTON_L)) {
	    drawRectangle(125, 0 , 40, 10, BLACK);
	    drawString(125, 0, "UP", RED);
            y = self.row - 1;
            if (y < 0) {
                y = 0;
            }
            if (x < 35 && y == 16) {
                y += 1;
            }
            if (x < 35 && y == 41) {
                y += 1;
            }
            if ((x == 50 && y < 20) || (x == 51 && y < 20)) {
                y += 1;
            }
        }

        if(KEY_DOWN_NOW(BUTTON_DOWN) || KEY_DOWN_NOW(BUTTON_R)) {
	    drawRectangle(125, 0 , 40, 10, BLACK);
	    drawString(125, 0, "DOWN", RED);
            y = self.row + 1;
            if (y > 157) {
                y = 157;
            }
            if (x < 35 && y == 13) {
                y -= 1;
            }
            if (x < 35 && y == 38) {
                y -= 1;
            }
	    if ((x == 160 && y > 98) || (x == 161 && y > 98)) {
                y -= 1;
            }
        }
        waitForVBlank();
        clean(self);
        self.column = x;
        self.row = y;
        clean(self);
        Square(self);


        clean(vertiMove1);
        vertiMove1.row = vertiMove1.row + vertiMove1.verticalSpeed;
        vertiMove1.verticalSpeed = getVerticalSpeed(vertiMove1);
        clean(vertiMove1);
        Square(vertiMove1);
        if ((self.row >= (vertiMove1.row - vertiMove1.size))
            && (self.row <= (vertiMove1.row + self.size))
            && (self.column <= (vertiMove1.column + vertiMove1.size))
            && (self.column >= (vertiMove1.column - self.size))) {
	    counter--;
            return STATE_LOSE;
        }

        clean(vertiMove2);
        vertiMove2.row = vertiMove2.row + vertiMove2.verticalSpeed;
        vertiMove2.verticalSpeed = getVerticalSpeed(vertiMove2);
        clean(vertiMove2);
        Square(vertiMove2);
        if ((self.row >= (vertiMove2.row - vertiMove2.size))
            && (self.row <= (vertiMove2.row + self.size))
            && (self.column <= (vertiMove2.column + vertiMove2.size))
            && (self.column >= (vertiMove2.column - self.size))) {
	    counter--;
            return STATE_LOSE;
        }

        clean(vertiMove3);
        vertiMove3.row = vertiMove3.row + vertiMove3.verticalSpeed;
        vertiMove3.verticalSpeed = getVerticalSpeed(vertiMove3);
        clean(vertiMove3);
        Square(vertiMove3);
        if ((self.row >= (vertiMove3.row - vertiMove3.size))
            && (self.row <= (vertiMove3.row + self.size))
            && (self.column <= (vertiMove3.column + vertiMove3.size))
            && (self.column >= (vertiMove3.column - self.size))) {
	    counter--;
            return STATE_LOSE;
        }

        clean(vertiMove4);
        vertiMove4.row = vertiMove4.row + vertiMove4.verticalSpeed;
        vertiMove4.verticalSpeed = getVerticalSpeed(vertiMove4);
        clean(vertiMove4);
        Square(vertiMove4);
        if ((self.row >= (vertiMove4.row - vertiMove4.size))
            && (self.row <= (vertiMove4.row + self.size))
            && (self.column <= (vertiMove4.column + vertiMove4.size))
            && (self.column >= (vertiMove4.column - self.size))) {
	    counter--;
            return STATE_LOSE;
        }

        clean(vertiMove5);
        vertiMove5.row = vertiMove5.row + vertiMove5.verticalSpeed;
        vertiMove5.verticalSpeed = getVerticalSpeed(vertiMove5);
        clean(vertiMove5);
        Square(vertiMove5);
        if ((self.row >= (vertiMove5.row - vertiMove5.size))
            && (self.row <= (vertiMove5.row + self.size))
            && (self.column <= (vertiMove5.column + vertiMove5.size))
            && (self.column >= (vertiMove5.column - self.size))) {
	    counter--;
            return STATE_LOSE;
        }

        clean(horizMove1);
        horizMove1.column = horizMove1.column + horizMove1.horizontalSpeed;
        horizMove1.horizontalSpeed = getHorizontalSpeed(horizMove1);
        clean(horizMove1);
        Square(horizMove1);
        if ((self.row >= (horizMove1.row - horizMove1.size))
            && (self.row <= (horizMove1.row + self.size))
            && (self.column <= (horizMove1.column + horizMove1.size))
            && (self.column >= (horizMove1.column - self.size))) {
	    counter--;
            return STATE_LOSE;
        }

        clean(horizMove2);
        horizMove2.column = horizMove2.column + horizMove2.horizontalSpeed;
        horizMove2.horizontalSpeed = getHorizontalSpeed(horizMove2);
        clean(horizMove2);
        Square(horizMove2);
        if ((self.row >= (horizMove2.row - horizMove2.size))
            && (self.row <= (horizMove2.row + self.size))
            && (self.column <= (horizMove2.column + horizMove2.size))
            && (self.column >= (horizMove2.column - self.size))) {
	    counter--;
            return STATE_LOSE;
        }

        clean(horizMove3);
        horizMove3.column = horizMove3.column + horizMove3.horizontalSpeed;
        horizMove3.horizontalSpeed = getHorizontalSpeed(horizMove3);
        clean(horizMove3);
        Square(horizMove3);
        if ((self.row >= (horizMove3.row - horizMove3.size))
            && (self.row <= (horizMove3.row + self.size))
            && (self.column <= (horizMove3.column + horizMove3.size))
            && (self.column >= (horizMove3.column - self.size))) {
	    counter--;
            return STATE_LOSE;
        }


        if (self.row >= 130 && self.row <= 160 && self.column >= 220 && self.column <= 240) {
	    counter++;
            return STATE_WIN;
        }
        if (KEY_DOWN_NOW(BUTTON_SELECT)) {
	    counter = 0;
            return STATE_START;
        }
    }
}

