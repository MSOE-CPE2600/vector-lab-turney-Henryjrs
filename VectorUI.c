/*
* Filename: VectorUI.c
* Description: Vector Calculator
* Author: Stephen Henry
* Date: 10/3/2025
* how to compile: gcc VectorCalc.c VectorMem.c VectorUI.c Vector.c -o VectorCalc
*/


#include <stdio.h>
#include <string.h>
#include "VectorMem.h"
#include "VectorCalc.h"

void run_ui() {
    NamedVector storage[MAX_VECTORS];
    int count = 0;
    char line[100];

    printf("Vector Calculator\n");
    printf("Commands:\n");
    printf("  A=1.0,2.0,3.0       (store vector A)\n");
    printf("  add A B             (add vectors A and B)\n");
    printf("  sub A B             (subtract B from A)\n");
    printf("  mul A 2.5           (multiply A by scalar)\n");
    printf("  exit                (quit)\n");

    while (1) {
        printf("\n> ");
        if (!fgets(line, sizeof(line), stdin)) break;

        // Remove whitespace
        char cleaned[100];
        int j = 0;
        for (int i = 0; line[i]; i++) {
            if (!isspace(line[i])) {
                cleaned[j++] = line[i];
            }
        }
        cleaned[j] = '\0';

        if (strncmp(cleaned, "exit", 4) == 0) break;

        if (strchr(cleaned, '=')) {
            char name[20];
            float x, y, z;
            if (sscanf(cleaned, "%[^=]=%f,%f,%f", name, &x, &y, &z) == 4) {
                store_vector(storage, &count, name, (Vector){x, y, z});
                printf("Stored vector %s = (%.2f, %.2f, %.2f)\n", name, x, y, z);
            } else {
                printf("Invalid format. Use name=x,y,z\n");
            }
        } else if (strncmp(cleaned, "add", 3) == 0) {
            char a[20], b[20];
            if (sscanf(cleaned, "add%s%s", a, b) == 2) {
                Vector *va = get_vector(storage, count, a);
                Vector *vb = get_vector(storage, count, b);
                if (va && vb) {
                    Vector result = add(*va, *vb);
                    printf("Result: (%.2f, %.2f, %.2f)\n", result.x, result.y, result.z);
                } else {
                    printf("Error: One or both vectors not found.\n");
                }
            } else {
                printf("Invalid add command.\n");
            }
        } else if (strncmp(cleaned, "sub", 3) == 0) {
            char a[20], b[20];
            if (sscanf(cleaned, "sub%s%s", a, b) == 2) {
                Vector *va = get_vector(storage, count, a);
                Vector *vb = get_vector(storage, count, b);
                if (va && vb) {
                    Vector result = subtract(*va, *vb);
                    printf("Result: (%.2f, %.2f, %.2f)\n", result.x, result.y, result.z);
                } else {
                    printf("Error: One or both vectors not found.\n");
                }
            } else {
                printf("Invalid sub command.\n");
            }
        } else if (strncmp(cleaned, "mul", 3) == 0) {
            char a[20];
            float scalar;
            if (sscanf(cleaned, "mul%s%f", a, &scalar) == 2) {
                Vector *va = get_vector(storage, count, a);
                if (va) {
                    Vector result = scalar_multiply(*va, scalar);
                    printf("Result: (%.2f, %.2f, %.2f)\n", result.x, result.y, result.z);
                } else {
                    printf("Error: Vector not found.\n");
                }
            } else {
                printf("Invalid mul command.\n");
            }
        } else {
            printf("Invalid command.\n");
        }
    }
}
