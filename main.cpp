#include "FEHLCD.h"
#include "FEHUtility.h"
#include "classes.cpp"
#include "Save.cpp"
#include <vector>
#include <iostream>
#include <Graphics.cpp>
#include <Generation.cpp>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// save file for character
#define C_SAVE_PATH "saves/c.txt"

// save file for GameObjects
#define O_SAVE_PATH "saves/obs.txt"

int main() {
    int x, y, camPos = 0;

    Button pause {"||", 0, 0, 25, 20, 0};
    Character c = Save::readCharacterData(C_SAVE_PATH);
    c.setPosition({0, 25, 0});
    vector<GameObject> v = Save::readGameObjects(O_SAVE_PATH);
    if(v.size() == 0) { // if no GameObjects saved, generate random world
        v = Generation::generateWorld(SCREEN_WIDTH * 2);
    }

    int xtemp, ytemp;
    while(true) {
        if(LCD.Touch(&xtemp, &ytemp)) {
            x = xtemp; y = ytemp; // if screen was touched, update cursor position
            while(LCD.Touch(&x, &y)) {} // wait until finger is lifted

            if(pause.isClicked(x,y)) Graphics::drawPauseMenu();
            else {
                if(x > SCREEN_WIDTH/2 + 20) {
                    camPos += 1;
                } else if(x < SCREEN_WIDTH/2 - 20) {
                    camPos -= 1;
                }
            }
        }

        Graphics::drawGameScreen(camPos, v, c, pause);
        Sleep(.05);
    }
}