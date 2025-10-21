/*
 * Filename: VectorUI.c
 * Description: Vector Calculator
 * Author: Stephen Henry
 * Date: 10/3/2025
 * how to compile: gcc VectorCalc.c VectorMem.c VectorUI.c Vector.c -o VectorCalc
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VectorCalc.h"
#include "VectorUI.h"


void trim_newline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }
}

void print_help() {
    printf("Usage:\n");
    printf("  A= 1 2 3         Assign vector A\n");
    printf("  B= 4 5 6         Assign vector B\n");
    printf("  add              A + B = C, C * 2 = D, A + D = display, show B\n");
    printf("  subtract         A - B = display\n");
    printf("  dot              A . B = display\n");
    printf("  cross            A x B = display\n");
    printf("  scalar           C * 2 = D\n");
    printf("  clear            Erase memory\n");
    printf("  list             Display stored vectors\n");
    printf("  exit             Quit program\n");
}

void run_ui() {
    char input[100];
    printf("Welcome to my Vector Calculator!! Let's get started...\n");
    print_help();

    while (1) {
        printf("VectorCalc> ");
        if (!fgets(input, sizeof(input), stdin)) break;
        trim_newline(input);

        if (strcmp(input, "exit") == 0) break;
        if (strcmp(input, "clear") == 0) { clear_vectors(); continue; }
        if (strcmp(input, "list") == 0) { list_vectors(); continue; }
        if (strcmp(input, "help") == 0) { print_help(); continue; }

        if (strcmp(input, "add") == 0) {
            Vector *a = get_vector("A");
            Vector *b = get_vector("B");
            if (!a || !b) {
                printf("Vectors A and B must be assigned first.\n");
                continue;
            }
            Vector c = {"C", 0, 0, 0};
            addvec(a, b, &c);
            store_vector(c);
            printf("C = A + B = %.2f %.2f %.2f\n", c.x, c.y, c.z);

            Vector d = {"D", 0, 0, 0};
            scalarvec(&c, 2.0, &d);
            store_vector(d);
            printf("D = C * 2 = %.2f %.2f %.2f\n", d.x, d.y, d.z);

            Vector temp = {"", 0, 0, 0};
            addvec(a, &d, &temp);
            printf("A + D = %.2f %.2f %.2f\n", temp.x, temp.y, temp.z);

            printf("B = %.2f %.2f %.2f\n", b->x, b->y, b->z);
            continue;
        }

        if (strcmp(input, "subtract") == 0) {
            Vector *a = get_vector("A");
            Vector *b = get_vector("B");
            if (!a || !b) {
                printf("Vectors A and B must be assigned first.\n");
                continue;
            }
            Vector result;
            subvec(a, b, &result);
            printf("A - B = %.2f %.2f %.2f\n", result.x, result.y, result.z);
            continue;
        }

        if (strcmp(input, "dot") == 0) {
            Vector *a = get_vector("A");
            Vector *b = get_vector("B");
            if (!a || !b) {
                printf("Vectors A and B must be assigned first.\n");
                continue;
            }
            double result;
            dotvec(a, b, &result);
            printf("A . B = %.2f\n", result);
            continue;
        }

        if (strcmp(input, "cross") == 0) {
            Vector *a = get_vector("A");
            Vector *b = get_vector("B");
            if (!a || !b) {
                printf("Vectors A and B must be assigned first.\n");
                continue;
            }
            Vector result;
            crossvec(a, b, &result);
            printf("A x B = %.2f %.2f %.2f\n", result.x, result.y, result.z);
            continue;
        }

        if (strcmp(input, "scalar") == 0) {
            Vector *c = get_vector("C");
            if (!c) {
                printf("Vector C must be assigned first.\n");
                continue;
            }
            Vector d = {"D", 0, 0, 0};
            scalarvec(c, 2.0, &d);
            store_vector(d);
            printf("D = C * 2 = %.2f %.2f %.2f\n", d.x, d.y, d.z);
            continue;
        }

        char *lhs = strtok(input, "=");
        char *rhs = strtok(NULL, "");

        if (!rhs) {
            Vector *v = get_vector(lhs);
            if (v) printf("%s = %.2f %.2f %.2f\n", v->name, v->x, v->y, v->z);
            else printf("Vector not found.\n");
            continue;
        }

        char name[NAME_LEN];
        sscanf(lhs, "%s", name);

        char *tok1 = strtok(rhs, " ");
        char *tok2 = strtok(NULL, " ");
        char *tok3 = strtok(NULL, " ");

        if (tok1 && tok2 && tok3) {
            Vector result;
            strncpy(result.name, name, NAME_LEN);
            result.x = atof(tok1);
            result.y = atof(tok2);
            result.z = atof(tok3);
            store_vector(result);
        } else {
            printf("Invalid input. Type 'help' for usage.\n");
        }
    }
    printf("Thanks for trying out my Vector Calculator...\n");
}
