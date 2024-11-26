#ifndef Collisions_cpp
#define Collisions_cpp

#include "Constants.cpp"
#include <math.h>
#include "Shapes.cpp"
#include "classes.cpp"

using namespace Shapes;

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
    static bool intersectingRectangles(Shapes::Rectangle rect1, Shapes::Rectangle rect2) {
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
   static void pushCharacter(Character* character, Shapes::Rectangle collidingBlock) {
    
        /*
        Push the character out by reversing the velocity until the character doesn't collide with the hitbo anymore
        */
        Shapes::Rectangle hitbox = character -> getHitbox();

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
            double g_x = pos.x - BLOCK_SIZE;
            double c_x = c.getPosition().x;
            if(c_x - g_x >= 0 && c_x - g_x <= BLOCK_SIZE && c.getHitbox().getBL().y >= g.getPosition().y) return true;
        }
        return false;
    }

    static double getGround(int pos, std::deque<GameObject> proxim) {
        double ground = SCREEN_HEIGHT;

        for(GameObject g: proxim) {
            Vector3 g_pos = g.getPosition();
            double g_x = g_pos.x - BLOCK_SIZE;
            if(g_pos.x - g_x >= 0 && g_pos.x - g_x <= BLOCK_SIZE)
                ground = min(g_pos.y, ground);
        }

        return ground;
    }

    static bool collidingRight(Hittable c, deque<GameObject> proxim) {
        double x = c.getPosition().x;
        for(GameObject g : proxim) {
            Shapes::Rectangle temp(RectangleData {g.getPosition().x, g.getPosition().y, g.getPosition().x + BLOCK_SIZE, g.getPosition().y, g.getPosition().x, g.getPosition().y + BLOCK_SIZE, g.getPosition().x + BLOCK_SIZE, g.getPosition().y + BLOCK_SIZE});
            if(x <= g.getPosition().x && intersectingRectangles(c.getHitbox(), temp)) return true;
        }
        return false;
    }

    static bool collidingLeft(Hittable c, deque<GameObject> proxim) {
        double x = c.getPosition().x;
        for(GameObject g : proxim) {
            Shapes::Rectangle temp(RectangleData {g.getPosition().x, g.getPosition().y, g.getPosition().x + BLOCK_SIZE, g.getPosition().y, g.getPosition().x, g.getPosition().y + BLOCK_SIZE, g.getPosition().x + BLOCK_SIZE, g.getPosition().y + BLOCK_SIZE});
            if(x >= g.getPosition().x && intersectingRectangles(c.getHitbox(), temp)) return true;
        }
        return false;
    }
};

#endif