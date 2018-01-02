
#define _COMMON_C
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

void *safeMalloc(unsigned int sz) {
    void *ptr = malloc(sz);
    if (ptr == NULL) {
        fprintf(stderr, "Fatal error: malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void *safeRealloc(void *ptr, unsigned int sz) {
    ptr = realloc(ptr, sz);
    if (ptr == NULL) {
        fprintf(stderr, "Fatal error: realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}
