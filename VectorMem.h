/*
* Filename: VectorMem.h
* Description: Vector Calculator
* Author: Stephen Henry
* Date: 10/3/2025
* how to compile: gcc VectorCalc.c VectorMem.c VectorUI.c Vector.c -o VectorCalc
*/


#ifndef VECTORMEM_H
#define VECTORMEM_H

#include "VectorCalc.h"

#define MAX_VECTORS 100

typedef struct {
    char name[20];
    Vector vec;
} NamedVector;

void store_vector(NamedVector storage[], int *count, const char *name, Vector v);
Vector* get_vector(NamedVector storage[], int count, const char *name);

#endif VECTORMEM_H
