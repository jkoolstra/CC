
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

int appendToStringTable(StringTable tab, char *str) {
    int insertPos = tab.size;
    int strLen = strlen(str);
    if (tab.bufSize < tab.size + strLen + 1) {
        tab.bufSize = strLen + 1 + tab.bufSize *
          STRING_TAB_BUF_RESIZE_FACTOR;
        tab.tab = safeRealloc(tab.tab, tab.bufSize * sizeof(char));
    }
    strcpy(tab.tab + insertPos, str);
    tab.size += strLen + 1;
    return insertPos;
}

char* retrieveFromStringTable(StringTable tab, int index) {
    return tab.tab + index;
}





























