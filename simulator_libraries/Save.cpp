/* Class of save file utilities for writing and reading saves */

#ifndef Save_cpp
#define Save_cpp

#include "Constants.cpp"
#include <stdio.h>
#include <string>
#include <fstream>
#include "classes.cpp"
#include <vector>
#include <deque>
#include <iostream>
using namespace std;


bool onScreen(int x, int camPos) {
    return x >= camPos && x <= camPos + SCREEN_WIDTH;
};

/// @brief Util. class for dealing with data; primarily deals with "caching" blocks that may need to be written to screen and with save files
struct Save{
    static void writeCharacterSave(char* path, Character character) {
        ofstream f(path);

        f << character.getHealth() NEWLINE
        f << character.getHitbox().getTL().x NEWLINE
        f << character.getHitbox().getTL().y NEWLINE
        f << character.getHitbox().getBR().x NEWLINE
        f << character.getHitbox().getBR().y NEWLINE

        // write position
        Vector3 pos = character.getPosition();
        f << pos.x NEWLINE
        f << pos.y NEWLINE
        f << pos.z NEWLINE
        f << character.getSpriteIndex() NEWLINE

        f.close();
    };

    /* Reads in character data from file at #path */
    /* Returns character object from save file */
    static Character readCharacterData(char* path) {
        FILE* save = fopen(path, "r");

        std::ifstream peeker(path);
        if(peeker.peek() == EOF) return Character(Vector3(), 0, Rectangle(RectangleData {0, 0, 0, 20, 5, 0, 5, 20})); // if no character detected, return default character

        float health, TLx, TLy, BRx, BRy, px, py, pz;
        int spriteIndex;

        fscanf(save, "%f%f%f%f%f%f%f%f%d", &health, &TLx, &TLy, &BRx, &BRy, &px, &py, &pz, &spriteIndex);

        Vector3 pos = {px, py, pz};
        Rectangle hitbox({TLx, TLy, BRx, TLy, TLx, BRy, BRx, BRy});

        fclose(save);

        Character c(pos, spriteIndex, hitbox); c.setHealth(health);
        return c;
    };

    // writes save file for GameObjects in array #obs, with n elements
    static void writeGameObjects(char* path, deque<GameObject> obs) {
        ofstream f(path);
        
        for(int i = 0; i < obs.size(); i++) {
            // get position and rotation values for object and write to file
            Vector3 pos = obs[i].getPosition();
            f << pos.x TAB 
                pos.y TAB 
                pos.z TAB 
                obs[i].getRotation() TAB
                obs[i].getSpriteIndex() NEWLINE;
        }

        f.close();
    };
    
    // writes save file for GameObjects in array #obs, with n elements
    static deque<GameObject> readGameObjects(char* path) {
        FILE* f = fopen(path, "r");
        deque<GameObject> obs;

        float x, y, z, rotation;
        int index;

        while(fscanf(f, "%f\t%f\t%f\t%f\t%f\n", &x, &y, &z, &rotation, &index) != EOF) {
            GameObject ob = GameObject({x,y,z}, index);
            ob.setRotation(rotation);
            obs.push_back(ob);
        }

        fclose(f);

        return obs;
    };

    static void shiftObs(int newX, vector<GameObject> *left, deque<GameObject> *proxim, vector<GameObject> *right) {
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
    }
};

#endif