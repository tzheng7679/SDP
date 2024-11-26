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
    /**
     * @brief Writes character save to file at path as thus:
     * health
     * spriteindex
     * hitbox width
     * hitbox length
     * x
     * y
     * z
     */
    static void writeCharacterSave(char* path, Character character) {
        ofstream f(path);

        Shapes::Rectangle hitbox = character.getHitbox();

        f << character.getSpriteIndex() NEWLINE
        f << character.getHealth() NEWLINE
        f << hitbox.getTR().x - hitbox.getTL().x NEWLINE;
        f << hitbox.getBR().y - hitbox.getTR().y NEWLINE;

        // write position
        Vector3 pos = character.getPosition();
        f << pos.x NEWLINE
        f << pos.y NEWLINE
        f << pos.z NEWLINE

        f.close();
    };

    /* Reads in character data from file at #path */
    /* Returns character object from save file */
    static Character readCharacterData(char* path) {
        FILE* save = fopen(path, "r");

        // peek at first character in file
        std::ifstream peeker(path);
        if(peeker.peek() == EOF) 
            return Character(Vector3(), CHARACTER_IMAGE_INDEX, Shapes::Rectangle(20, 20)); // if no character detected, return default character
        peeker.close();

        // read in character attributes
        float health, wid, hei, x, y, z;
        int spriteIndex;

        fscanf(save, "%f%d%f%f%f%f%f", &health, &spriteIndex, &wid, &hei, &x, &y, &z);

        Vector3 pos = {x, y, z};
        Shapes::Rectangle hitbox(wid, hei);

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

    // writes hittables to save file
    static void writeHittables(char* path, deque<Hittable> obs) {
        ofstream f(path);
        
        for(int i = 0; i < obs.size(); i++) {
            Shapes::Rectangle hitbox = obs[i].getHitbox();

            f << obs[i].getSpriteIndex() TABEND
            f << hitbox.getTR().x - hitbox.getTL().x TABEND
            f << hitbox.getBR().y - hitbox.getTR().y TABEND

            // write position
            Vector3 pos = obs[i].getPosition();
            f << pos.x TABEND
            f << pos.y TABEND
            f << pos.z TABEND
        }

        f.close();
    };
    
    // read in hittables
    static deque<Hittable> readHittables(char* path) {
        FILE* f = fopen(path, "r");
        deque<Hittable> obs;

        float x, y, z, w, h;
        int index;

        while(fscanf(f, "%d\t%f\t%f\t%f\t%f\t%f\n", &index, &w, &h, &x, &y, &z) != EOF) {
            Shapes::Rectangle hitbox(w, h);

            Hittable ob = Hittable(hitbox, {x,y,z}, index);
        }

        fclose(f);

        return obs;
    };

    // shifts obs that are on screen into proxim, ones to the left to the left of the screen to left, and to the right of the screen to right
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