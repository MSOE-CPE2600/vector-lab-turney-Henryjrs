/*
* Filename: VectorMem.c
* Description: Vector Calculator
* Author: Stephen Henry
* Date: 10/3/2025
* how to compile: gcc VectorCalc.c VectorMem.c VectorUI.c Vector.c -o VectorCalc
*/


#include <string.h>
#include "VectorMem.h"

void store_vector(NamedVector storage[], int *count, const char *name, Vector v) {
    for (int i = 0; i < *count; i++) {
        if (strcmp(storage[i].name, name) == 0) {
            storage[i].vec = v;
            return;
        }
    }
    if (*count < MAX_VECTORS) {
        strcpy(storage[*count].name, name);
        storage[*count].vec = v;
        (*count)++;
    }
}

Vector* get_vector(NamedVector storage[], int count, const char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(storage[i].name, name) == 0) {
            return &storage[i].vec;
        }
    }
    return NULL;
}
