#ifndef Menus_cpp
#define Menus_cpp

#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 50
#define PADDING 5
#include <FEHLCD.h>
#include <classes.cpp>
#include <FEHUtility.h>

// Representation of pause menu button
struct Button {
    char *text;
    int x;
    int y;

    bool isClicked(int x, int y) {
        return (x >= this -> x && y >= this -> y && x <= this -> x + BUTTON_WIDTH && y <= this -> y + BUTTON_HEIGHT);
    }
};

// Package for drawing any graphical stuff
struct Graphics {
    static void drawPauseMenu() {
        LCD.Clear();

        Button cont {"Continue", PADDING, PADDING};
        Button stats {"View Stats", PADDING + BUTTON_WIDTH + PADDING, PADDING};
        Button insts {"Instructions", PADDING, PADDING + BUTTON_HEIGHT + PADDING};
        Button creds {"Credits", PADDING + BUTTON_WIDTH + PADDING, PADDING + BUTTON_HEIGHT + PADDING};

        Button buttons[] = {cont, stats, insts, creds};
        Button exit {"Back To Menu", PADDING, PADDING};

        drawMenuInterface(buttons);

        int x, y;
        int touched = -1;
        while(touched == -1) { // while the continue button is not pressed
            awaitPress(&x, &y);

            for(int i = 0; i < 4; i++) {
                if(buttons[i].isClicked(x, y))
                    touched = i;
            }

            if(touched == 1) { // if stats menu is opened
                LCD.Clear();

                drawButton(exit);
                
                /* TODO:
                Put stats here when necessary
                */
                LCD.WriteAt("put stats here", 100, 100);
                
                do {
                    awaitPress(&x, &y);
                } while(!exit.isClicked(x, y));

                touched = -1;
            }

            if(touched == 2) { // if instructions menu is opened
                LCD.Clear();

                
                drawButton(exit);
                
                char* lines[] = {"Touch screen in", "direction to move there", "Touch above character", "to jump"};
                int spacer = 0;
                for(char* l : lines) {
                    LCD.WriteAt(l, PADDING, PADDING + BUTTON_HEIGHT + PADDING + spacer);
                    spacer += 20;
                }
                
                LCD.WriteAt("Touch ", PADDING, PADDING + BUTTON_HEIGHT + PADDING);
                
                do {
                    awaitPress(&x, &y);
                } while(!exit.isClicked(x, y));

                touched = -1;
            }

            if(touched == 3) { // if credits are opened
                LCD.Clear();

                
                drawButton(exit);
                
                char* lines[] = {"Kevin Zhang", "Tony Zheng"};
                int spacer = 0;
                for(char* l : lines) {
                    LCD.WriteAt(l, PADDING, PADDING + BUTTON_HEIGHT + PADDING + spacer);
                    spacer += 20;
                }
                
                do {
                    awaitPress(&x, &y);
                } while(!exit.isClicked(x, y));

                touched = -1;
            }

            drawMenuInterface(buttons);
        }

        LCD.Clear();
    }

    static void drawGameObject(GameObject g) {

    }

    private:
        static void drawButton(Button b) {
            LCD.DrawRectangle(b.x, b.y, BUTTON_WIDTH, BUTTON_HEIGHT);
            LCD.WriteAt(b.text, b.x + PADDING, b.y + PADDING);
        }

        static void drawMenuInterface(Button buttons[4]) {
            LCD.Clear();
            for(int i = 0; i < 4; i++) {
                drawButton(buttons[i]);
            }
        }

        static void awaitPress(int *x, int *y) {
            while(!LCD.Touch(x, y));
            while(LCD.Touch(x, y));
        }
};

#endif