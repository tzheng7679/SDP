/*
TODO: decide if shapes should be structs or classes and edit them accordingly
 */
/*
Struct to represent a circle with x, y, and radius. 
This can also be used to represent a disc (can be both, difference is in how struct is used)
*/

#ifndef Shapes_cpp
#define Shapes_cpp
#include "vectors.cpp"

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

#endif