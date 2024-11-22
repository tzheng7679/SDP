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
    int x, y;
    Character c = Save::readCharacterData(C_SAVE_PATH);
    vector<GameObject> v = Save::readGameObjects(O_SAVE_PATH);
    if(v.size() == 0) { // if no GameObjects saved, generate random world
        v = Generation::generateWorld(SCREEN_WIDTH * 2);
    }
    v.push_back(c);

    Graphics::drawGameScreen(0, v);
    while(!LCD.Touch(&x, &y)) {}
    LCD.Clear();
    Graphics::drawGameScreen(20, v);
    
    while(!LCD.Touch(&x, &y)) {}
}