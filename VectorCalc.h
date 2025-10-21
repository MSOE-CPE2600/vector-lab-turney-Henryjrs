/*
 * Filename: VectorCalc.h
 * Description: Vector Calculator
 * Author: Stephen Henry
 * Date: 10/3/2025
 * how to compile: gcc VectorCalc.c VectorMem.c VectorUI.c Vector.c -o VectorCalc
 */




#ifndef VECTORCALC_H
#define VECTORCALC_H

#define MAX_VECTORS 10
#define NAME_LEN 20
//#define run_ui

typedef struct {
    char name[NAME_LEN];
    double x, y, z;
} Vector;

void addvec(const Vector *a, const Vector *b, Vector *result);
void subvec(const Vector *a, const Vector *b, Vector *result);
void dotvec(const Vector *a, const Vector *b, double *result);
void crossvec(const Vector *a, const Vector *b, Vector *result);
void scalarvec(const Vector *a, double scalar, Vector *result);

int store_vector(Vector v);
Vector* get_vector(const char *name);
void list_vectors();
void clear_vectors();

#endif

