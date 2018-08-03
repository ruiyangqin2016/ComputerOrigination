//
// Created by China on 07/07/2018.
//

// Make a whatever I don't know GBA game
// Name: Ruiyang Qin

#include <stdbool.h>

#include "myLib.h"

//enum GBAState {
//    STATE_START,
//    STATE_WIN,
//    STATE_MENU,
//    STATE_GAMING,
//    STATE_LOSE,
//};

//void waitForVBlank();
//void drawFullscreenImage3(const unsigned short *image);


int main() {

    REG_DISPCNT = MODE3 | BG2_ENABLE;
    enum GBAState state = STATE_START;
    int holdState = STATE_MENU;

    while (1) {
        waitForVBlank();

        switch (state) {
            case STATE_START:
                drawFullscreenImage3(0, 0 , IMG_START_WIDTH, IMG_START_HEIGHT, img_start);
//                while (KEY_DOWN_NOW(BUTTON_START)) {
//                    // do nothing
//                }
//                while (KEY_DOWN_NOW(BUTTON_SELECT)) {
//                    // do nothing
//                }
                state = STATE_MENU;
                holdState = STATE_MENU;
                break;
            case STATE_MENU:
                if (KEY_DOWN_NOW(BUTTON_START)) {
                    state = STATE_GAMING;
                }
                if (KEY_DOWN_NOW(BUTTON_SELECT)) {
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
                /**
                 * To implement: Game part
                 *
                 */
                holdState = game();
//                while (KEY_DOWN_NOW(BUTTON_START)) {
//                    // do nothing
//                }
//                while (KEY_DOWN_NOW(BUTTON_A)) {
//                    // do nothing
//                }
                state = STATE_MENU;

                break;
            case STATE_LOSE:
                drawFullscreenImage3(0, 0 , IMG_LOSE_WIDTH, IMG_LOSE_HEIGHT, img_lose);
//                while (KEY_DOWN_NOW(BUTTON_START)) {
//                    // do nothing
//                }
//                while (KEY_DOWN_NOW(BUTTON_SELECT)) {
//                    // do nothing
//                }
                state = STATE_MENU;
                holdState = STATE_MENU;
                break;
            case STATE_WIN:
                drawFullscreenImage3(0, 0, IMG_WIN_WIDTH, IMG_WIN_HEIGHT, img_win);
//                while (KEY_DOWN_NOW(BUTTON_START)) {
//                    // do nothing
//                }
//                while (KEY_DOWN_NOW(BUTTON_SELECT)) {
//                    // do nothing
//                }
                state = STATE_MENU;
                holdState = STATE_MENU;
                break;
        }
    }
    return 0;
}

