#include "FEHLCD.h"
#include "FEHUtility.h"

#include "Constants.cpp"
#include "classes.cpp"
#include "Save.cpp"
#include "Shapes.cpp"
#include "Graphics.cpp"
#include "Collisions.cpp"
#include "Generation.cpp"

#include <vector>
#include <deque>
#include <iostream>
#include <winuser.h>

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
#define G 0.5
#define DELTA_T .00

#define CAM_POS c.getPosition().x - SCREEN_WIDTH / 2

enum Direction {
    LEFT,
    CENTER,
    RIGHT
};

int sign(double x) {
    if(x < 0) return -1;
    if(x > 0) return 1;
    return 0;
}

int horizontalKeyDown() {
    if((GetKeyState('D') & 0x8000) || (GetKeyState(VK_RIGHT) & 0x8000 )) return VK_RIGHT;
    if((GetKeyState('A') & 0x8000) || (GetKeyState(VK_LEFT) & 0x8000 )) return VK_LEFT;
    return -1;
}

int verticalKeyDown() {
    if((GetKeyState('S') & 0x8000) || (GetKeyState(VK_DOWN) & 0x8000 )) return VK_DOWN;
    if((GetKeyState('W') & 0x8000) || (GetKeyState(VK_UP) & 0x8000 )) return VK_UP;
    return -1;
}
int main() {
    int x, y;

    Button pause {"||", 0, 0, 25, 20, 0};
    Character c = Save::readCharacterData(C_SAVE_PATH);
    c.setPosition({0, 25, 0});
    deque<GameObject> proxim = Save::readGameObjects(O_SAVE_PATH);
    if(proxim.size() == 0) { // if no GameObjects saved, generate random world
        proxim = Generation::generateWorld(c.getPosition().x, -100, 100);
    }

    vector<GameObject> left;
    vector<GameObject> right;
    Save::shiftObs(CAM_POS, &left, &proxim, &right); // shift gameobjects into appropriate vectors

    int xtemp, ytemp;
    while(true) {
        // if screen is touched
        if(LCD.Touch(&xtemp, &ytemp)) {
            x = xtemp; y = ytemp; // update cursor position
            double velocity = 0;

            // while the screen is still touched
            while(LCD.Touch(&x, &y)) { /* wait for touch to release */ }

            // if cursor ended on pause button, draw pause menu
            if(pause.isClicked(x,y)) Graphics::drawPauseMenu();
        }

        int hkey = horizontalKeyDown();
        int vkey = verticalKeyDown();

        Vector3 vel = c.getVelocity();
        switch(hkey) { // switch horizontal component
            case VK_RIGHT:
                if(!Collisions::collidingRight(c, proxim)) {
                    if(vel.x <= 0) vel.x = VELOCITY_INITIAL;
                    else vel.x = min(vel.x + ACCELERATION, VELOCITY_MAX);
                } else {
                    vel.x = 0;
                }
                break;

            case VK_LEFT:
                if(!Collisions::collidingLeft(c, proxim)) {
                    if(vel.x >= 0) vel.x = -VELOCITY_INITIAL;
                    else vel.x = max(vel.x - ACCELERATION, -VELOCITY_MAX);
                } else {
                    vel.x = 0;
                }
                break;
            
            default:
                vel.x = 0;
                break;
        }
        
        if(c.isGrounded()) {
            switch(vkey) {
                case VK_UP:
                    vel.y = -5;
                    break;

                case VK_DOWN:
                    break;
                    
                default:
                    vel.y = 0;
                    break;
            }
        } else {
            vel.y += G;
        }
        c.setVelocity(vel);
        c.setGrounded(Collisions::onGround(c, proxim));
        c.Update();

        double y = min(c.getPosition().y, Collisions::getGround(c.getPosition().x + c.getHitbox().getHeight(), proxim));
        Vector3 pos = c.getPosition();
        pos.y = y;
        c.setPosition(pos);

        Graphics::drawGameScreen(CAM_POS, proxim, c, pause);
        LCD.SetFontColor(GREEN);

        double pos_y = c.getPosition().y;
        // LCD.DrawRectangle(SCREEN_WIDTH / 2, pos_y, c.getHitbox().getWidth(), c.getHitbox().getHeight());
        // Sleep(.01);
    }
}