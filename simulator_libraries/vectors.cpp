#ifndef vectors_cpp
#define vectors_cpp

/**
* @brief Basic struct representing a 3d vector of doubles. x and y represent x and y on screen, z represents the "depth" (for use in drawing)
* @author Kevin.Z
*/
struct Vector3 {
    double x;
    double y;
    double z;
};



/**
* @brief Basic struct representing a 2d vector of doubles, x and y represent the absolute position on the screen
* @author Kevin Z.
*/
struct Vector2 {
    double x;
    double y;
};


/*
declare useful vector constants
*/
const Vector3 VECTOR3_ZERO = Vector3{0, 0, 0};
const Vector2 VECTOR2_ZERO = Vector2{0, 0};



/*
declare operations for vectors to make life easier
*/

/*
subtraction operations between Vector2 and Vector3
*/
Vector3 operator -(const Vector3& vec1, const Vector3& vec2) {
    return Vector3{vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z};
}

//maybe change later to -vec2.z?
Vector3 operator -(const Vector2& vec1, const Vector3& vec2) {
    return Vector3{vec1.x - vec2.x, vec1.y - vec2.y, vec2.z};
}

Vector3 operator -(const Vector3& vec1, const Vector2& vec2) {
    return Vector3{vec1.x - vec2.x, vec1.y - vec2.y, vec1.z};
}

Vector2 operator -(const Vector2& vec1, const Vector2& vec2) {
    return Vector2{vec1.x - vec2.x, vec1.y - vec2.y};
}


/*

Subtraction operations between Vector3/Vector2 and a scalar
*/
Vector2 operator -(const Vector2& vec, const double scalar) {
    return Vector2{vec.x - scalar, vec.y - scalar};
}

Vector3 operator -(const Vector3& vec, const double scalar) {
    return Vector3{vec.x - scalar, vec.y - scalar, vec.z - scalar};
}
Vector2 operator -(const double scalar, const Vector2& vec) {
    return Vector2{scalar - vec.x, scalar - vec.y};
}
Vector3 operator -(const double scalar, const Vector3& vec) {
    return Vector3{scalar - vec.x, scalar - vec.y, scalar - vec.z};
}



/*
Addition operations between Vector3 and Vector2
*/
Vector3 operator +(const Vector3& vec1, const Vector3& vec2) {
    return Vector3{vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z};
}

Vector3 operator +(const Vector2& vec1, const Vector3& vec2) {
    return Vector3{vec1.x + vec2.x, vec1.y + vec2.y, vec2.z};
}

Vector3 operator +(const Vector3& vec1, const Vector2& vec2) {
    return vec1 + vec2;
}

Vector2 operator +(const Vector2& vec1, const Vector2& vec2) {
    return Vector2{vec1.x + vec2.x, vec1.y + vec2.y};
}

/*
Addition operations between a scalar and a Vector2/Vector3
*/

Vector2 operator +(const Vector2& vec, const double scalar) {
    return Vector2{scalar + vec.x, scalar + vec.y};
}

Vector3 operator +(const Vector3& vec, const double scalar) {
    return Vector3{scalar + vec.x, scalar + vec.y, scalar + vec.z};
}
Vector2 operator +(const double scalar, const Vector2& vec) {
    return Vector2{scalar + vec.x, scalar + vec.y};
}
Vector3 operator +(const double scalar, const Vector3& vec) {
    return Vector3{scalar + vec.x, scalar + vec.y, scalar + vec.z};
}


/*
Multiplication operations between scalar and vectors
*/
Vector3 operator *(const double& scalar, const Vector3& vec) {
    return Vector3{scalar * vec.x, scalar * vec.y, scalar * vec.z};
}

Vector3 operator *(const Vector3& vec, const double& scalar) {
    return scalar * vec;
}


Vector2 operator *(const double& scalar, const Vector2& vec) {
    return Vector2{scalar * vec.x, scalar * vec.y};
}

Vector2 operator *(const Vector2& vec, const double& scalar) {
    return scalar * vec;
}



/*
Division operations between vectors and scalars
*/
Vector3 operator /(const Vector3& vec, const double& scalar) {
    return Vector3{vec.x/scalar, vec.y/scalar, vec.z/scalar};
}


Vector2 operator /(const Vector2& vec, const double& scalar) {
    return Vector2{vec.x/scalar, vec.y/scalar};
}

#endif