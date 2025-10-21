/*
* Filename: VectorMem.c
* Description: Vector Calculator
* Author: Stephen Henry
* Date: 10/3/2025
* how to compile: gcc VectorCalc.c VectorMem.c VectorUI.c Vector.c -o VectorCalc
*/



#include <stdio.h>
#include <string.h>
#include "VectorCalc.h"

static Vector memory[MAX_VECTORS];
static int count = 0;

int store_vector(Vector v) {
    for (int i = 0; i < count; i++) {
        if (strcmp(memory[i].name, v.name) == 0) {
            memory[i] = v;
            return 1;
        }
    }
    if (count >= MAX_VECTORS) {
        printf("Memory maxed out, buddy!! Type clear to wipe the memory,champ...");
        return 0;
    }
    memory[count++] = v;
    return 1;
}

Vector* get_vector(const char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(memory[i].name, name) == 0) {
            return &memory[i];
        }
    }
    return NULL;
}

void list_vectors() {
    for (int i = 0; i < count; i++) {
        printf("%s = %.2f %.2f %.2f", memory[i].name, memory[i].x, memory[i].y, memory[i].z);
    }
}

void clear_vectors() {
    count = 0;
    printf("Memory wiped...");
}
