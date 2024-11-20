#include "FEHLCD.h"
#include "FEHUtility.h"
#include "classes.cpp"
#include "Save.cpp"
#include <vector>
#include <iostream>
#include <Graphics.cpp>

#define SPACE << " " << 
int main() {
    // // Clear background
    // LCD.WriteLine("hello world!");

    // Vector3 pos({1, 2, 3});
    // Rectangle hitbox;
    // Character c (pos, hitbox);

    // cout << c.getHealth() NEWLINE
    // cout << c.getHitbox().getTL().x NEWLINE
    // cout << c.getHitbox().getTL().y NEWLINE
    // cout << c.getHitbox().getBR().x NEWLINE
    // cout << c.getHitbox().getBR().y NEWLINE

    // // write position
    // pos = c.getPosition();
    // cout << pos.x NEWLINE
    // cout << pos.y NEWLINE
    // cout << pos.z NEWLINE

    // Save s;
    // c.setHealth(25);
    // s.writeCharacterSave("c.txt", c);

    // Character c2 = s.readCharacterData("c.txt");

    // cout << c2.getHealth() NEWLINE
    // cout << c2.getHitbox().getTL().x NEWLINE
    // cout << c2.getHitbox().getTL().y NEWLINE
    // cout << c2.getHitbox().getBR().x NEWLINE
    // cout << c2.getHitbox().getBR().y NEWLINE

    // // write position
    // pos = c2.getPosition();
    // cout << pos.x NEWLINE
    // cout << pos.y NEWLINE
    // cout << pos.z NEWLINE

    Graphics::drawPauseMenu();

    int a, b;
    while(!LCD.Touch(&a, &b));
}