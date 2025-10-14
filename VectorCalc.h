/*
* Filename: VectorCalc.h
* Description: Vector Calculator
* Author: Stephen Henry
* Date: 10/3/2025
* how to compile: gcc VectorCalc.c VectorMem.c VectorUI.c Vector.c -o VectorCalc
*/


#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x, y, z;
} Vector;

Vector add(Vector a, Vector b);
Vector subtract(Vector a, Vector b);
Vector scalar_multiply(Vector v, float scalar);

#endif
