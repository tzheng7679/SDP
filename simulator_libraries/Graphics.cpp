#ifndef Menus_cpp
#define Menus_cpp

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 50
#define PADDING 5
#include <FEHLCD.h>
#include <classes.cpp>
#include <FEHUtility.h>
#include <FEHImages.h>
#include <vector>

// Representation of pause menu button
struct Button {
    char *text;
    int x;
    int y;

    int width = BUTTON_WIDTH;
    int height = BUTTON_HEIGHT;

    int padding = PADDING;
    /**
     * Returns if a click at (x, y) is within the boundaries of #this
     * 
     * @param x
     *  The x position of the click
     * @param y
     *  The y position of the click
     * @return Whether the button is clicked or not
     */
    bool isClicked(int x, int y) {
        return (x >= this -> x && y >= this -> y && x <= this -> x + width && y <= this -> y + height);
    }
};

// Package for drawing any graphical stuff
struct Graphics {
    /**
     * Draws the pause menu with associated buttons; executes until the "continue" button is pressed
     */
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
                
                LCD.WriteAt("Placeholder for stats", 0, 100);
                
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
                
                char* lines[] = {"Kevin Zhang", "Tony Zheng", "Instructor: Edgar Casale"};
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

    /**
     * Draws all the GameObjects in #obs plus a puase button at pausePos
     * @param obs
     *  The objects to draw
     * @param c
     *  The character object
     * @param pause
     *  The pause button object
     */
    static void drawGameScreen(int camPos, std::deque<GameObject> obs, GameObject c, Button pause) {
        LCD.Clear();
        for(GameObject ob : obs) {
            drawGameObjectNoUpdate(camPos, ob);
        }
        drawButton(pause);
        drawGameObjectNoUpdate(camPos, c);

        LCD.Update();
    }

    /**
     * Draws a GameObject
     * @param g
     *  The GameObject to draw
     */
    static void drawGameObjectNoUpdate(int camPos, GameObject g) {
        char* path = Sprites::getSpritePath(g.getSpriteIndex());
        
        FEHImage im;
        im.Open(path);
        Vector3 pos = g.getPosition();
        
        if(camPos <= pos.x && camPos + SCREEN_WIDTH >= pos.x) im.Draw(pos.x - camPos, pos.y); // only draw if in screen
    }
    
    /**
     * Draws a GameObject
     * @param g
     *  The GameObject to draw
     */
    static void drawGameObject(int camPos, GameObject g) {
        drawGameObjectNoUpdate(camPos, g);
        LCD.Update();
    }

    /**
     * Executes until the screen is pressed and released; assigns final touch position to (*x, *y)
     * @param x
     *  The x-position variable to assign to
     * @param y
     *  The y-position variable to assign to
     */
    static void awaitPress(int *x, int *y) {
        while(!LCD.Touch(x, y));
        while(LCD.Touch(x, y));
    }

    private:
        /**
         * Draws a button
         * @param b
         *  The button to draw
         */
        static void drawButton(Button b) {
            LCD.DrawRectangle(b.x, b.y, b.width, b.height);
            LCD.WriteAt(b.text, b.x + b.padding, b.y + b.padding);
        }

        /**
         * Draws all the buttons in the menu
         * @param buttons
         *  The array of buttons (continue, stats, instructions, credits))
         */
        static void drawMenuInterface(Button buttons[4]) {
            LCD.Clear();
            for(int i = 0; i < 4; i++) {
                drawButton(buttons[i]);
            }
        }

};

#endif