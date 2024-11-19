/* Class of save file utilities for writing and reading saves */
#include <stdio.h>
#include <string>
#include <fstream>
#include "classes.cpp"

using namespace std;

// macro so I don't have to write this every damn time
#define NEWLINE << "\n";
#define TAB << "\t" << 

/* Writes save data for character object to file at #path */
/* w/ format below
health
hitbox.x
hitbox.x2
hitbox.y
hitbox.y2
position.x
position.y
position.z
*/
struct Save{
    void writeCharacterSave(char* path, Character character) {
        ofstream f(path);

        f << character.getHealth() NEWLINE
        f << character.getHitbox().getShape().x NEWLINE
        f << character.getHitbox().getShape().x2 NEWLINE
        f << character.getHitbox().getShape().y NEWLINE
        f << character.getHitbox().getShape().y2 NEWLINE

        // write position
        Vector3 pos = character.getPosition();
        f << pos.x NEWLINE
        f << pos.y NEWLINE
        f << pos.z NEWLINE

        f.close();
    };

    /* Reads in character data from file at #path */
    /* Returns character object from save file */
    Character readCharacterData(char* path) {
        FILE* save = fopen(path, "r");

        double health, x, x2, y, y2, px, py, pz;

        scanf("%f%f%f%f%f%f%f%f", &health, &x, &x2, &y, &y2, &px, &py, &pz);

        Vector3 pos = {px, py, pz};
        Rectangle hitbox({x, x2, y, y2});

        fclose(save);
        return Character(pos, hitbox);
    };

    // writes save file for GameObjects in array #obs, with n elements
    void writeGameObjects(char* path, GameObject obs[], int n) {
        ofstream f(path);
        
        for(int i = 0; i < n; i++) {
            // get position and rotation values for object and write to file
            Vector3 pos = obs[i].getPosition();
            f << pos.x TAB 
                pos.y TAB 
                pos.z TAB 
                obs[i].getRotation() NEWLINE;
        }

        f.close();
    };
};