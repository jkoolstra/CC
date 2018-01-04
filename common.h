
#ifndef _COMMON_H
#define _COMMON_H
#include <stdio.h>

#define UNUSED(expr) do { (void)(expr); } while (0)

void *safeMalloc(unsigned int);
void *safeRealloc(void*, unsigned int);
#endif // #ifndef _COMMON_H
