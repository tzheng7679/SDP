#include <math.h>

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

        RectangleData getShape() {
            return shape;
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

    public:
        
        GameObject(Vector3 pos) {
            position = pos;
        }


        Vector3 getPosition() {
            return position;
        }

        double getRotation() {
            return rotation;
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
        Character(Vector3 pos, Rectangle hitbox) : GameObject(pos), Hittable(hitbox){
            
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
    calculate if two rectangles are intersecting
    TODO: change return type to give more detail about nature of intersection
    */
    static bool intersectingRectangles(Rectangle rect1, Rectangle rect2) {

    }
};

class Sprites {

    private:
        //list of literlly every sprite in the game
        static constexpr char* spritesList[] = {"player.png"};
    public:
        static constexpr char* getSpritePath(int index) {
            return spritesList[index];
        }

};