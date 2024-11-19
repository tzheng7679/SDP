#include "FEHLCD.h"
#include "FEHUtility.h"
#include "classes.cpp"
#include "Save.cpp"

int main() {
    // Clear background
    LCD.WriteLine("hello world!");

    float x, y;
    while(!LCD.Touch(&x, &y)) {}
    while(LCD.Touch(&x, &y)) {}
}