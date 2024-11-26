#ifndef classes_cpp
#define classes_cpp

#include <deque>
#include <stdio.h>
#include <math.h>

#include "vectors.cpp"
#include "Constants.cpp"
#include "Shapes.cpp"
/* Basic structs to store the data in */

/*
GameObject class is what every single object used in the game will have. It will have basic functionality like position
*/
class GameObject {
    private:
        Vector3 position;

        Vector3 velocity;

        //rotation in degrees of the object from a baseline
        double rotation;

        // sprite
        int spriteIndex;

        int collidableState;

        bool hasGravity;



    public:
        
        GameObject(Vector3 pos, int spriteIndex) {
            position = pos;
            this -> spriteIndex = spriteIndex;

            this -> collidableState = 0;
            
            this -> hasGravity = false;
        }

        GameObject(Vector3 pos, int spriteIndex, int collidableState, bool hasGravity) {
            position = pos;
            this -> spriteIndex = spriteIndex;

            this -> collidableState = collidableState;
            
            this -> hasGravity = hasGravity;
      
        }


        /*
        Update method is called once per frame for all GameObjects in the scene
        */
        void Update() {
            //update position based on the velocity
            this -> position = this -> position + velocity;
        }

        Vector3 getPosition() {
            return position;
        }

        void setPosition(Vector3 pos) {
            this -> position = pos;
        }


        Vector3 getVelocity() {
            return velocity;
        }

        void setVelocity(Vector3 vel) {
            velocity = vel;
        }

        double getRotation() {
            return this -> rotation;
        }

        void setRotation(double r) {
            this -> rotation = r;
        }


        

        int getSpriteIndex() {
            return this -> spriteIndex;
        }

        void setSpriteIndex(int spriteIndex) {
            this -> spriteIndex = spriteIndex;
        }

        int getCollidableState() {
            return this -> collidableState;
        }

        bool getHasGravity() {
            return this -> hasGravity;
        }


        /*
        Sets the collidableState of the GameObject (0 is no collisions, 1 is detectable but no active collisions, 2 is fully active collisions)
        */
        void setCollidableState(int state) {
            this -> collidableState = state;

        }


        void setGravity(bool grav) {
            this -> hasGravity = grav;
        }


};

/*
Hittable class is a class that defines a GameObject with collisions by extending GameObject and adding collision stuff
The rectangle hitbox is represented internally as the LOCAL POSITION of the rectangle relative to the player
*/
class Hittable : public GameObject {
    private:
        Shapes::Rectangle hitbox;

        //whether or not the colliding object is standing on the ground
        bool grounded;

    public:
        Hittable(Shapes::Rectangle hbox) : GameObject({0, 0, 0}, -1) {
            hitbox = hbox;

            grounded = false;

            //set default state of objects to not collide and not have gravity
            this->setCollidableState(0);
            this->setGravity(false);
        }

        Hittable(Shapes::Rectangle hbox, Vector3 pos, int spriteIndex) : GameObject(pos, spriteIndex) {
            this -> hitbox = hbox;

            this -> grounded = false;

            //set default state of objects to not collide and not have gravity
            this->setCollidableState(0);
            this->setGravity(false);
        }

        //returns hitbox as a rectangle of global coordinates
        Shapes::Rectangle getHitbox() {
            return hitbox.returnAdd({getPosition().x, getPosition().y});
        }

        //gets local coordinates of the hitbox
        Shapes::Rectangle getHitboxLocal() {return hitbox;}




        bool isGrounded() {
            return grounded;
        }

        void setGrounded(bool val) {
            grounded = val;
        }

        /*
        Method to determine what happens on hit for the object (NOTE: this will BE OVERRIDDEN TO IMPLEMENT NEW FUNCTIONALITY)
        TODO: determine if onHit() Should be in Hittable or in the Character class
        */
        int onHit(Hittable* otherHit) {
            //TODO: fill in the default case for collisions
        }

    
};

/*
Character class is what all NPCs, Enemies, and the player's character will have.
All character objects will of course have a hitbox and be a gameobject
*/
class Character : public Hittable {
    private:
        double health;

        //the last direction the character moved (used to help check collisions)
        int lastDirection;

    

    public:
        Character(Vector3 pos, int spriteIndex, Shapes::Rectangle hitbox) : Hittable(hitbox, pos, spriteIndex){
            
        }
        double getHealth() {
            return health;
        }
        void setHealth(double newHealth) {
            health = newHealth;
        }

        void setSprite() {
            
        }


};



class Player : public Character {
    private:
    
    public:
    Player(Vector3 pos, int spriteIndex, Shapes::Rectangle hitbox) : Character(pos, spriteIndex, hitbox) {

        

    
    }

    
    /*
    Overridden Update method for the player

     */
    void Update() {

        setPosition(getPosition() + getVelocity());
        if (getHasGravity() && !isGrounded()) {
            setVelocity(getVelocity() + Vector3{0, G, 0});
        }

    }


    //overridden onHit method for the player
    void onHit(Hittable* otherHit) {
        setVelocity(VECTOR3_ZERO);
        printf("The Player's onhit method has executed");
    }

};


class Block : public Hittable {

    private:
        double health;

        
    public:
        Block(double constr_health, Shapes::Rectangle hitbox, Vector3 pos, int spriteIndex) : Hittable(hitbox, pos, spriteIndex) {
            health = constr_health;
        }


        void Update() {
            //do nothing
        }

        double getHealth() {
            return health;
        }
        void setHealth(double newHealth) {
            health = newHealth;
            
        }

        /*
        return the dropped item, override the getDroppedItem method to change the index of the dropped item
        the number returned is the ID of the dropped item (or index, if we implement that)
        */
        int getDroppedItem() {
            return -1;
        }

        
        
};




class SandBlock : public Block {

    private:

    public:
        /*
        Constructs block with a hitbox of 1
        */
        SandBlock(double constr_health, Shapes::Rectangle hitbox, Vector3 pos)  : Block(constr_health, hitbox, pos, 1) {

        }
        

        /*
        Get index of SandBlock (which is 1)
        */
        int getDroppedItem() {
            return 1;
        }

};



/*
Item class for player items

TODO: finish defining Item, Weapon and their subclasses
*/

class Item {
    private:
        int id;
    public:


};


class Weapon : public Item {
    private:

    public:
};

class DragonSword : public Weapon {



    private:


    public:


};


#endif