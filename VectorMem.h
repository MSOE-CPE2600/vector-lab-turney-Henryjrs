/*
* Filename: VectorMem.h
* Description: Vector Calculator
* Author: Stephen Henry
* Date: 10/3/2025
* how to compile: gcc VectorCalc.c VectorMem.c VectorUI.c Vector.c -o VectorCalc
*


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
*/


#ifndef VECTORMEM_H
#define VECTORMEM_H

#define NAME_LEN 32

typedef struct {
    char name[NAME_LEN];
    double x, y, z;
} Vector;

typedef struct {
    Vector* vectors;
    int count;
    int capacity;
} VectorStorage;

void initVectorStorage(VectorStorage* storage);
void freeVectorStorage(VectorStorage* storage);
void clearVectorStorage(VectorStorage* storage);
int addVector(VectorStorage* storage, const char* name, double x, double y, double z);
int loadVectorsFromCSV(VectorStorage* storage, const char* filename);
int saveVectorsToCSV(VectorStorage* storage, const char* filename);
void listVectors(const VectorStorage* storage);

#endif

