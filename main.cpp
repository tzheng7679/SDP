#include "FEHLCD.h"
#include "FEHUtility.h"
#include "classes.cpp"
#include "Save.cpp"
#include <vector>
#include <iostream>
#include <Graphics.cpp>

#define SPACE << " " << 
int main() {
    // Clear background
    LCD.WriteLine("hello world!");

    Vector3 pos {20, 20, 20};
    Rectangle rect;
    Character c (pos, 0, rect);

    Graphics::drawGameObject(c);

    int x, y;
    Graphics::awaitPress(&x, &y);
}