
#define _STRING_TABLE_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "StringTable.h"

// use 0 for the default DEFAULT_STRING_TAB_BUF_SIZE
StringTable newStringTable(int bufSize) {
    StringTable tab;
    if (bufSize == 0) {
        bufSize = DEFAULT_STRING_TAB_BUF_SIZE;
    }
    tab.tab = safeMalloc(bufSize * sizeof(char));
    tab.size = 0;
    tab.bufSize = bufSize;
    return tab;
}


void freeStringTable(StringTable tab) {
    free(tab.tab);
}

int appendToStringTable(StringTable *tab, char *str) {
    int index, strLen = strlen(str);
    if ((index = lookupStringTable(*tab, str)) < tab->size) {
        return index;
    }
    if (tab->bufSize < tab->size + strLen + 1) {
        tab->bufSize = strLen + 1 + tab->bufSize *
          STRING_TAB_BUF_RESIZE_FACTOR;
        tab->tab = safeRealloc(tab->tab, tab->bufSize * sizeof(char));
    }
    strcpy(tab->tab + tab->size, str);
    tab->size += strLen + 1;
    return index;
}

int lookupStringTable(StringTable tab, char *str) {
    int index = 0;
    while (index < tab.size) {
        if (strcmp(tab.tab + index, str) == 0) {
            break;
        }
        index += strlen(tab.tab + index) + 1;
    }
    return index;
}

char* retrieveFromStringTable(StringTable tab, int index) {
    return tab.tab + index;
}

void printStringTable(StringTable tab) {
    int index = 0;
    printf("STRING TABLE;\n");
    while (index < tab.size) {
        printf("%s\n", tab.tab + index);
        index += strlen(tab.tab + index) + 1;
    }
}



























