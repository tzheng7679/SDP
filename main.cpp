#include "FEHLCD.h"
#include "FEHUtility.h"
#include "classes.cpp"
#include "Save.cpp"
#include <vector>
#include <iostream>
#include <Graphics.cpp>

// save file for character
#define C_SAVE_PATH "c.txt"

// save file for GameObjects
#define O_SAVE_PATH "obs.txt"

int main() {
    int x, y;
    Character c = Save::readCharacterData(C_SAVE_PATH);
    vector<GameObject> v = Save::readGameObjects(O_SAVE_PATH);

    Graphics::drawGameScreen(v);
}