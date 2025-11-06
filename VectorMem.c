/*
* Filename: VectorMem.c
* Description: Vector Calculator
* Author: Stephen Henry
* Date: 10/3/2025
* how to compile: gcc VectorCalc.c VectorMem.c VectorUI.c Vector.c -o VectorCalc
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <signal.h>
#include "VectorCalc.h"


static Vector *memory = NULL;
static size_t  count  = 0;
static size_t  cap    = 0;
static bool cap_check(size_t memory_needed) {
    if (cap >= memory_needed) return true;
    size_t new_cap = (cap == 0) ? 8 : cap * 2;
    while (new_cap < memory_needed) new_cap *= 2;

    void *tmp = realloc(memory, new_cap * sizeof(*memory));
    if (!tmp) {
        fprintf(stderr, "ERROR: Out of memory growing to %zu vectors.\n", new_cap);
        return false;
    }
    memory = (Vector*)tmp;
    cap = new_cap;
    return true;
}

static int name_equals(const char *a, const char *b) {
    return strcmp(a, b) == 0;
}

static void rstrip_newline(char *s) {
    if (!s) return;
    for (size_t n = strlen(s); n > 0 && (s[n-1] == '\n' || s[n-1] == '\r'); --n)
        s[n-1] = '\0';
}


int store_vector(Vector v) {

    for (size_t i = 0; i < count; ++i) {
        if (name_equals(memory[i].name, v.name)) {
            memory[i] = v;
            return 1;
        }
    }

    if (!cap_check(count + 1)) {
        fprintf(stderr, "Memory allocation failed... Use 'clear' to free memory.\n");
        return 0;
    }
    memory[count++] = v;
    return 1;
}

Vector* get_vector(const char *name) {
    for (size_t i = 0; i < count; ++i) {
        if (name_equals(memory[i].name, name)) {
            return &memory[i];
        }
    }
    return NULL;
}

void list_vectors(void) {
    if (count == 0) {
        puts("(No vectors in memory)");
        return;
    }
    for (size_t i = 0; i < count; ++i) {
        printf("%s = %.6f %.6f %.6f\n",
               memory[i].name, memory[i].x, memory[i].y, memory[i].z);
    }
}

void clear_vectors(void) {
    free(memory);
    memory = NULL;
    count = 0;
    cap   = 0;
    puts("Memory wiped...");
}


bool load_vectors_csv(const char *path, bool clear_first) {
    if (!path || !*path) {
        fprintf(stderr, "Unknown filename...\n");
        return false;
    }

    FILE *f = fopen(path, "r");
    if (!f) {
        fprintf(stderr, "No file to open... '%s': %s\n", path, strerror(errno));
        return false;
    }

    if (clear_first) {
        clear_vectors();
    }

    char line[512];
    size_t line_no = 0, ok = 0, bad = 0;

    while (fgets(line, sizeof(line), f)) {
        line_no++;
        rstrip_newline(line);

        const char *p = line;
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '\0' || *p == '#') continue;

        Vector v = {0};

        int parsed = sscanf(p, "%19[^,],%lf,%lf,%lf", v.name, &v.x, &v.y, &v.z);
        if (parsed != 4) {
            if (ok == 0 && bad == 0 && (strstr(p, "name") || strstr(p, "x") || strstr(p, "y") || strstr(p, "z"))) {
                continue;
            }
            fprintf(stderr, "WARNING: malformed line %zu in '%s': \"%s\"\n", line_no, path, line);
            bad++;
            continue;
        }

        if (!store_vector(v)) {
            fprintf(stderr, "Failed to store vector... %zu.\n", line_no);
            fclose(f);
            return false;
        }
        ok++;
    }

    fclose(f);

    if (ok == 0 && bad > 0) {
        fprintf(stderr, "No vectors loaded from... '%s'.\n", path);
        return false;
    }

    printf("Loaded %zu vector from '%s'%s.\n", ok, path, bad ? " (with warnings)" : "");
    return true;
}

bool save_vectors_csv(const char *path) {
    if (!path || !*path) {
        fprintf(stderr, "Save failed. Missing filename...\n");
        return false;
    }

    FILE *f = fopen(path, "w");
    if (!f) {
        fprintf(stderr, "Can't open '%s' for writing: %s\n", path, strerror(errno));
        return false;
    }

    fprintf(f, "name,x,y,z\n");

    for (size_t i = 0; i < count; ++i) {
        const Vector *v = &memory[i];
        if (fprintf(f, "%s,%.17g,%.17g,%.17g\n", v->name, v->x, v->y, v->z) < 0) {
            fprintf(stderr, "Write failed while saving to... '%s'.\n", path);
            fclose(f);
            return false;
        }
    }

    if (fclose(f) != 0) {
        fprintf(stderr, "Closing '%s' failed: %s\n", path, strerror(errno));
        return false;
    }

    printf("Saved %zu vector(s) to '%s'.\n", count, path);
    return true;
}

static void mem_cleanup_on_exit(void) {
    if (memory) {
        free(memory);
        memory = NULL;
    }
    count = cap = 0;
}

static void on_sigint(int signum) {
    (void)signum;
    fprintf(stderr, "\n(SIGINT) Cleaning up and exiting...\n");
    mem_cleanup_on_exit();
    exit(130);
}

void mem_initialize(void) {
    atexit(mem_cleanup_on_exit);
    signal(SIGINT, on_sigint);
}

size_t vector_count(void) {
    return count;
}
