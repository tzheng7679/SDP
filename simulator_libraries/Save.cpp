/* Class of save file utilities for writing and reading saves */

#ifndef Save_cpp
#define Save_cpp
#include <stdio.h>
#include <string>
#include <fstream>
#include "classes.cpp"
#include <vector>
#include <deque>
#include <iostream>
using namespace std;

// macro so I don't have to write this every damn time
#define NEWLINE << "\n";
#define TAB << "\t" << 

/* Writes save data for character object to file at #path */
/* w/ format below
health
hitbox.TL.x
hitbox.TL.y
hitbox.BR.x
hitbox.BR.y
position.x
position.y
position.z
*/
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
        if(peeker.peek() == EOF) return Character(Vector3(), 0, Rectangle()); // if no character detected, return default character

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
};

#endif