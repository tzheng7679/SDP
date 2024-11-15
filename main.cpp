#include "FEHLCD.h"
#include "FEHUtility.h"

int main() {
    // Clear background
    LCD.WriteLine("hello world!");

    float x, y;
    while(!LCD.Touch(&x, &y)) {}
    while(LCD.Touch(&x, &y)) {}
}