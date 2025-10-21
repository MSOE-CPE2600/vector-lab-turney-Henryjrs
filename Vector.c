/*
* Filename: Vector.c
* Description: Vector Calculator now joining Github
* Author: Stephen Henry
* Date: 10/3/2025
* how to compile: gcc VectorCalc.c VectorMem.c VectorUI.c Vector.c -o VectorCalc
*/



//#include <stdio.h>
#include "VectorCalc.h"

void addvec(const Vector *a, const Vector *b, Vector *result) {
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
}

void subvec(const Vector *a, const Vector *b, Vector *result) {
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
}

void dotvec(const Vector *a, const Vector *b, double *result) {
    *result = a->x * b->x + a->y * b->y + a->z * b->z;
}

void crossvec(const Vector *a, const Vector *b, Vector *result) {
    result->x = a->y * b->z - a->z * b->y;
    result->y = a->z * b->x - a->x * b->z;
    result->z = a->x * b->y - a->y * b->x;
}

void scalarvec(const Vector *a, double scalar, Vector *result) {
    result->x = a->x * scalar;
    result->y = a->y * scalar;
    result->z = a->z * scalar;
}
