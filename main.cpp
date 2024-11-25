#include "FEHLCD.h"
#include "FEHUtility.h"
#include "classes.cpp"
#include "Save.cpp"
#include <vector>
#include <deque>
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
#define DELTA_T .00

bool onScreen(int x, int camPos) {
    return x >= camPos && x <= camPos + SCREEN_WIDTH;
};

/// @brief Shifts GameObjects based on proximity to character to speed up drawing
/// @pre Objects in each vector are sorted in ascending order by x-position
/// @param left Vector containing objects far to the left of the character (front of stack is right-most obs)
/// @param proxim Double-ended queue containing objects within drawing distance of the character
/// @param right Vector containing objects far to the right of the character (front of stack is left-most obs)
void shiftObs(int newX, vector<GameObject> *left, deque<GameObject> *proxim, vector<GameObject> *right) {
    // push proxim left end into left
    while((*proxim).size() > 0 && 
            !(onScreen((*proxim).front().getPosition().x, newX))
        ) {
            (*left).push_back((*proxim).front());
            (*proxim).pop_front();
        }
    
    // push (*proxim) (*right) end into (*right)
    while((*proxim).size() > 0 && 
            !onScreen((*proxim).front().getPosition().x, newX)
        )   {
                (*left).push_back((*proxim).back());
                (*proxim).pop_back();
            }
    // push (*left) (*right) end into (*proxim) (*left) end
    while((*left).size() > 0 && 
            onScreen((*left).back().getPosition().x, newX)
        ) {
            (*proxim).push_front((*left).back());
            (*left).pop_back();
        }
    // push (*proxim) (*right) end into (*right)
    while((*right).size() > 0 && 
            onScreen((*right).back().getPosition().x, newX)
        ){
                (*proxim).push_back((*right).back());
                (*right).pop_back();
            }        
};

int main() {
    int x, y;

    Button pause {"||", 0, 0, 25, 20, 0};
    Character c = Save::readCharacterData(C_SAVE_PATH);
    c.setPosition({0, 25, 0});
    deque<GameObject> proxim = Save::readGameObjects(O_SAVE_PATH);
    if(proxim.size() == 0) { // if no GameObjects saved, generate random world
        proxim = Generation::generateWorld(c.getPosition().x, -1000, 1000);
    }

    vector<GameObject> left;
    vector<GameObject> right;

    shiftObs(0, &left, &proxim, &right);
    cout << "blah";

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
                        Graphics::drawGameScreen(c.getPosition().x - SCREEN_WIDTH / 2, proxim, c, pause);
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
                        Graphics::drawGameScreen(c.getPosition().x - SCREEN_WIDTH / 2, proxim, c, pause);
                        Sleep(DELTA_T);
                    }
                }

                shiftObs(c.getPosition().x - SCREEN_WIDTH / 2, &left, &proxim, &right);
            } 

            // if cursor ended on pause button, draw pause menu
            if(pause.isClicked(x,y)) Graphics::drawPauseMenu();
        }

        Graphics::drawGameScreen(c.getPosition().x - SCREEN_WIDTH / 2, proxim, c, pause);
    }
}