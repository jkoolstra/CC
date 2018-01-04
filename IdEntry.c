/* symtab.c: very simple symbol table.
 * author: Arnold Meijster (a.meijster@rug.nl)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IdEntry.h"

IdEntry makeIdEntry(unsigned index, Type type){
    IdEntry entry;

    entry.strtabIndex = index;
    entry.type = type;

    return entry;
}

void printEntry(IdEntry entry){
      unsigned index = entry.strtabIndex;
      Type type = entry.type;
      printf("{ index : %u , type : ", index);
      if(type == TYPE_PROGRAM){
        printf("TYPE_PROGRAM");
      } else if (type == TYPE_FUNCTION){
        printf("TYPE_FUNCTION");
      } else if (type == TYPE_VARIABLE){
        printf("TYPE_IDENTIFIER");
      } else {
        printf("TYPE_UNKNOWN");
      }
      printf(" } | ");
}