#ifndef classes_cpp
#define classes_cpp

#include <math.h>
#include "vectors.cpp"
#include <stdio.h>
#include <deque>
#define SCREEN_HEIGHT 240
#define BLOCK_SIZE 10
/* Basic structs to store the data in */


/*
TODO: decide if shapes should be structs or classes and edit them accordingly
 */
/*
Struct to represent a circle with x, y, and radius. 
This can also be used to represent a disc (can be both, difference is in how struct is used)
*/
struct Circle {
    double x;
    double y;
    double radius;
};

/*
Four corners of a rectangle
 */
struct RectangleData {
    //top left
    Vector2 tl;
    //top right
    Vector2 tr;
    //bottom left
    Vector2 bl;
    //bottom right
    Vector2 br;
};

//Should we use a struct only, or use a class for rectangle?
class Rectangle {

    private:
        RectangleData shape;
    
    public:
        Rectangle() {
            shape = {0, 0, 0, 0, 0, 0, 0, 0};
        }
        Rectangle(RectangleData rdata) {
            shape = rdata;
        }

        //top left corner (with no rotation) in global coordinates
        Vector2 getTL() {
            return shape.tl;
        }
        
        //top right corner (with no rotation)
        Vector2 getTR() {
            return shape.tr;
        }

        Vector2 getBL() {
            return shape.bl;
        }
        Vector2 getBR() {
            return shape.br;
        }


        //utility functions

        /*
        Adds a coordinate pair (x, y) to this rectangle, while returning the result
        */
        Rectangle returnAdd(Vector2 vec) { 
            return Rectangle({getTL() + vec, getTR() + vec, getBL() + vec, getBR() + vec});
        }


        //For the following functions, the rectangle is assumed to be non-rotated

        /*
        Get the width of the rectangle (assuming rectangle is non-rotated)
        */
        double getWidth() {
            return shape.tr.x - shape.tl.x;
        }
        
        /*
        Get the height of the rectangle (assuming rectangle is non-rotated)
        */
       double getHeight() {
            return shape.tl.y - shape.bl.y;
       }



};





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
            this -> position.x += this -> velocity.x;

            this -> position.y += this -> velocity.y;

            this -> position.z += this -> velocity.z;

            
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
        Rectangle hitbox;

        //whether or not the colliding object is standing on the ground
        bool grounded;

    public:
        Hittable(Rectangle hbox) : GameObject({0, 0, 0}, -1) {
            hitbox = hbox;

            grounded = false;

            //set default state of objects to not collide and not have gravity
            this->setCollidableState(0);
            this->setGravity(false);
        }

        Hittable(Rectangle hbox, Vector3 pos, int spriteIndex) : GameObject(pos, spriteIndex) {
            this -> hitbox = hbox;

            this -> grounded = false;

            //set default state of objects to not collide and not have gravity
            this->setCollidableState(0);
            this->setGravity(false);
        }

        //returns hitbox as a rectangle of global coordinates
        Rectangle getHitbox() {
            return hitbox.returnAdd({getPosition().x, getPosition().y});
        }

        //gets local coordinates of the hitbox
        Rectangle getHitboxLocal() {return hitbox;}




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
        Character(Vector3 pos, int spriteIndex, Rectangle hitbox) : Hittable(hitbox, pos, spriteIndex){
            
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
    Player(Vector3 pos, int spriteIndex, Rectangle hitbox) : Character(pos, spriteIndex, hitbox) {
        
    }

    
    /*
    Overridden Update method for the player

     */
    void Update() {
        GameObject::Update();
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
        Block(double constr_health, Rectangle hitbox, Vector3 pos, int spriteIndex) : Hittable(hitbox, pos, spriteIndex) {
            health = constr_health;
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
        SandBlock(double constr_health, Rectangle hitbox, Vector3 pos)  : Block(constr_health, hitbox, pos, 1) {

        }
        

        /*
        Get index of SandBlock (which is 1)
        */
        int getDroppedItem() {
            return 1;
        }

};






/* Utility class for handling collisions

Collisions class contains static methods that are useful for handling collisions
*/
class Collisions {

    public:
    
    /*calculate if two Circles are intersecting
    
    TODO: change return type to give more detail about nature of intersection
    */
    static bool intersectingCircles(Circle circle1, Circle circle2) {
        double distance = sqrt(pow(circle2.x - circle1.x, 2) + pow(circle2.y - circle1.y, 2));

        double largestDiameter = 2 * fmax(circle1.radius, circle2.radius);


        //maybe should be just less than instead of less than or equal?
        return distance <= largestDiameter;
    }

    /*
    Calculate if two ranges, x and y, overlap and return boolean if they do
    */
    static bool overlappingRanges(double x_start, double x_end, double y_start, double y_end) {
        return (x_start <= y_end) && (y_start <= x_end);
    }

    /*
    Calculate if two rectangles are intersecting (rectangles must not be rotated)
    @returns if they are intersecting or not

    @todo change return type to give more detail about nature of intersection
    @todo possibly make it work for rotated rectangles
    */
    static bool intersectingRectangles(Rectangle rect1, Rectangle rect2) {
        //totally original code
        Vector2 Pos1 = rect1.getTL();
        Vector2 Pos2 = rect2.getTL();

        Vector2 Rect1_BR = rect1.getBR();
        Vector2 Rect2_BR = rect2.getBR();

        //code from https://stackoverflow.com/a/27624434
        return (Pos1.x < Rect2_BR.x) && (Pos1.y < Rect2_BR.y) && (Pos2.x < Rect1_BR.x) && (Pos2.y < Rect1_BR.y);
  
    }



    /*
    pushes Character out of block that they are colliding with by mutating the @p character
    outside of the block (assumes that both hitbox rectangles are non-rotated)

    @pre the character and collidingBlock are already intersecting

    */
   static void pushCharacter(Character* character, Rectangle collidingBlock) {
    
        /*
        Push the character out by reversing the velocity until the character doesn't collide with the hitbo anymore
        */
        Rectangle hitbox = character -> getHitbox();

        //local position of character hitbox relative to hitbox
        Vector2 localPos = collidingBlock.getTL() - hitbox.getTL();

        Vector3 velocity = character -> getVelocity();

        //reversed velocity
        Vector3 reversedVelocity = -1 * velocity;




        //this is a buggy, hacky fix for pushing out (character will def vibrate and jitter around walls)
        //FIX THIS LATER if time
        while (true) {
            character -> setPosition(character -> getPosition() + reversedVelocity);
            if (intersectingRectangles(character -> getHitbox(), collidingBlock)) {
                break;
            }
        }

        

   }

    static bool onGround(Character c, std::deque<GameObject> proxim) {
        if(c.getHitbox().getBL().y >= SCREEN_HEIGHT) return true;

        for(GameObject g : proxim) {
            Vector3 pos = g.getPosition();
            if(c.getPosition().x - pos.x >= 0 && c.getPosition().x - pos.x <= BLOCK_SIZE && c.getHitbox().getBL().y >= g.getPosition().y - 1) return true;
        }
        return false;
    }

};

class Sprites {
    public:
        static constexpr char* getSpritePath(int index) {
            char* spritesList[] = {"sprites/player.png", "sprites/block.png"};
            return spritesList[index];
        }

};

#endif