
#ifndef _STRING_TABLE_H
#define _STRING_TABLE_H
#include <stdio.h>

#define DEFAULT_STRING_TAB_BUF_SIZE 100
#define STRING_TAB_BUF_RESIZE_FACTOR 2

typedef struct StringTable {
    char *tab;
    int size, bufSize;
} StringTable;


StringTable newStringTable(int);
void freeStringTable(StringTable);
int appendToStringTable(StringTable, char*);
char* retrieveFromStringTable(StringTable, int);
#endif // #ifndef _STRING_TABLE_H
