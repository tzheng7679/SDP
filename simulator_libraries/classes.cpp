#include <math.h>

#ifndef classes_cpp
#define classes_cpp
/* Basic structs to store the data in */

/*
Basic struct representing a 3d vector of doubles. x and y represent x and y on screen, z represents the "depth" (for use in drawing)
*/
struct Vector3 {
    double x;
    double y;
    double z;
};

/*
Basic struct representing a 2d vector of doubles, x and y represent the absolute position on the screen
*/
struct Vector2 {
    double x;
    double y;
};



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
};





/*
GameObject class is what every single object used in the game will have. It will have basic functionality like position
*/
class GameObject {
    private:
        Vector3 position;

        //rotation in degrees of the object from a baseline
        double rotation;

        // sprite
        int spriteIndex;

    public:
        
        GameObject(Vector3 pos, int spriteIndex) {
            position = pos;
            this -> spriteIndex = spriteIndex;
        }


        Vector3 getPosition() {
            return position;
        }

        double getRotation() {
            return rotation;
        }

        void setRotation(double r) {
            rotation = r;
        }

        int getSpriteIndex() {
            return this -> spriteIndex;
        }

        void setSpriteIndex(int spriteIndex) {
            this -> spriteIndex = spriteIndex;
        }
};

/*
Hittable class is a class that simply contains the hitbox
Hitbox is just a rectangle with certain points
*/
class Hittable {
    private:
    Rectangle hitbox;
    public:
    Hittable(Rectangle hbox) {
        hitbox = hbox;
    }
    Rectangle getHitbox() {return hitbox;}
};

/*
Character class is what all NPCs, Enemies, and the player's character will have.
All character objects will of course have a hitbox and be a gameobject
*/
class Character : public Hittable, public GameObject {
    private:
        double health;


    public:
        Character(Vector3 pos, int spriteIndex, Rectangle hitbox) : GameObject(pos, spriteIndex), Hittable(hitbox){
            
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


class Block : public Hittable, public GameObject {

    private:
        double health;
        int droppedItem;
        
    public:

        Block(double constr_health) :{
            health = constr_health;
        }
        double getHealth() {
            return health;
        }
        void setHealth(double newHealth) {
            health = newHealth;
        }
};





/*utility class for handling collisions

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
    calculate if two rectangles are intersecting (rectangles must not be rotated)
    TODO: change return type to give more detail about nature of intersection
    TODO: possibly make it work for rotated rectangles
    */
    static bool intersectingRectangles(Rectangle rect1, Rectangle rect2) {
        //totally original code
        Vector2 Pos1 = rect1.getBL();
        Vector2 Pos2 = rect2.getBL();

        Vector2 Rect1_TR = rect1.getTR();
        Vector2 Rect2_TR = rect2.getTR();

        return (Pos1.x < Rect2_TR.x) && (Pos1.y < Rect2_TR.y) && (Pos2.x < Rect1_TR.x) && (Pos2.y < Rect1_TR.y);
    }
};

class Sprites {

    private:
        //list of literlly every sprite in the game
        static constexpr char* spritesList[] = {"sprites/player.png"};
    public:
        static constexpr char* getSpritePath(int index) {
            return spritesList[index];
        }

};

#endif