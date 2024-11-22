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

// set physical constants
#define VELOCITY_INITIAL 1
#define VELOCITY_MAX 3.0
#define ACCELERATION 1
#define DELTA_T .05

int main() {
    int x, y;

    Button pause {"||", 0, 0, 25, 20, 0};
    Character c = Save::readCharacterData(C_SAVE_PATH);
    c.setPosition({0, 25, 0});
    vector<GameObject> v = Save::readGameObjects(O_SAVE_PATH);
    if(v.size() == 0) { // if no GameObjects saved, generate random world
        v = Generation::generateWorld(c.getPosition().x, -100, 100);
    }

    int xtemp, ytemp;
    while(true) {
        // if screen is touched
        if(LCD.Touch(&xtemp, &ytemp)) {
            x = xtemp; y = ytemp; // update cursor position
            double velocity = 0;

            // while the screen is still touched
            while(LCD.Touch(&x, &y)) {
                // if not touching the pause button
                if(!pause.isClicked(x, y)) {
                    // Move screen if cursor is not in the center of the screen
                    if(x > SCREEN_WIDTH/2 + 20) { // if touching right of character
                        /*
                        * set velocity to small initial value if you were moving to the left
                        * otherwise, increase velocity since you were moving to the right initially
                        */ 
                        if(velocity <= 0) velocity = VELOCITY_INITIAL;
                        else velocity = min(velocity + ACCELERATION, VELOCITY_MAX); // increase velocity until it reaches maximum

                        //update position
                        Vector3 pos = c.getPosition();
                        pos.x += velocity;
                        c.setPosition(pos);

                        //update screen, and sleep
                        Graphics::drawGameScreen(c.getPosition().x - SCREEN_WIDTH / 2, v, c, pause);
                        Sleep(DELTA_T);
                    } else if(x < SCREEN_WIDTH/2 - 20) {
                        // see above
                        if(velocity >= 0) velocity = -VELOCITY_INITIAL;
                        else velocity= max(velocity - ACCELERATION, -VELOCITY_MAX); // increase velocity until it reaches maximum

                        // update position
                        Vector3 pos = c.getPosition();
                        pos.x += velocity;
                        c.setPosition(pos);

                        // update screen
                        Graphics::drawGameScreen(c.getPosition().x - SCREEN_WIDTH / 2, v, c, pause);
                        Sleep(DELTA_T);
                    }
                }
            } 

            // if cursor ended on pause button, draw pause menu
            if(pause.isClicked(x,y)) Graphics::drawPauseMenu();
        }

        Graphics::drawGameScreen(c.getPosition().x - SCREEN_WIDTH / 2, v, c, pause);
    }
}