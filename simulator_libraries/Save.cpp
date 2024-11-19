/* Class of save file utilities for writing and reading saves */
#include <stdio.h>
#include <string>
#include <fstream>
#include "classes.cpp"
#include <vector>

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
    void writeCharacterSave(char* path, Character character) {
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

        f.close();
    };

    /* Reads in character data from file at #path */
    /* Returns character object from save file */
    Character readCharacterData(char* path) {
        FILE* save = fopen(path, "r");

        double health, TLx, TLy, BRx, BRy, px, py, pz;

        scanf("%f%f%f%f%f%f%f%f", &health, &TLx, &TLy, &BRx, &BRy, &px, &py, &pz);

        Vector3 pos = {px, py, pz};
        Rectangle hitbox({TLx, TLy, BRx, TLy, TLx, BRy, BRx, BRy});

        fclose(save);
        return Character(pos, hitbox);
    };

    // writes save file for GameObjects in array #obs, with n elements
    void writeGameObjects(char* path, vector<GameObject> obs) {
        ofstream f(path);
        
        for(int i = 0; i < obs.size(); i++) {
            // get position and rotation values for object and write to file
            Vector3 pos = obs[i].getPosition();
            f << pos.x TAB 
                pos.y TAB 
                pos.z TAB 
                obs[i].getRotation() NEWLINE;
        }

        f.close();
    };
    
    // writes save file for GameObjects in array #obs, with n elements
    vector<GameObject> readGameObjects(char* path) {
        FILE* f = fopen(path, "r");
        vector<GameObject> obs;

        double x, y, z, rotation;
        while(fscanf(f, "%f%f%f%f", &x, &y, &z, &rotation) != EOF) {
            GameObject ob = GameObject({x,y,z});
            ob.setRotation(rotation);
            obs.push_back(ob);
        }

        fclose(f);

        return obs;
    };
};