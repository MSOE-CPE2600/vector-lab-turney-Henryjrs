/*
* Filename: Vector.c
* Description: Vector Calculator
* Author: Stephen Henry
* Date: 10/3/2025
* how to compile: gcc VectorCalc.c VectorMem.c VectorUI.c Vector.c -o VectorCalc
*/


#include "VectorCalc.h"

Vector add(Vector a, Vector b) {
    Vector result = {a.x + b.x, a.y + b.y, a.z + b.z};
    return result;
}

Vector subtract(Vector a, Vector b) {
    Vector result = {a.x - b.x, a.y - b.y, a.z - b.z};
    return result;
}

Vector scalar_multiply(Vector v, float scalar) {
    Vector result = {v.x * scalar, v.y * scalar, v.z * scalar};
    return result;
}
