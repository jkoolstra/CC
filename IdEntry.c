/* symtab.c: very simple symbol table.
 * author: Arnold Meijster (a.meijster@rug.nl)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IdEntry.h"

IdEntry makeIdEntry(unsigned index){
    IdEntry entry;

    entry.strtabIndex = index;

    return entry;
}

void printSecondaryType(SecondaryType type){
  printf(", secondaryType : ");
  if(type == TYPE_INTEGER){
        printf("TYPE_INTEGER");
      } else if (type == TYPE_REAL){
        printf("TYPE_REAL");
      } else if (type == TYPE_BOOL){
        printf("TYPE_BOOL");
      } else {
        printf("NO_SECONDARY_TYPE");
      }
}

void printBaseType(BaseType type){
  printf("baseType : ");
  if(type == TYPE_PROGRAM){
        printf("TYPE_SINGLE");
      } else if (type == TYPE_SINGLE){
        printf("TYPE_ARRAY");
      } else {
        printf("NO_BASE_TYPE");
      }
}

void printValueType(ValueType type){
  printf(" , valueType : { ");
  printBaseType(type.base);
  printSecondaryType(type.secondary);
}

void printIdType(IdType type){
  printf("idType : ");
  if(type == TYPE_PROGRAM){
        printf("TYPE_PROGRAM");
      } else if (type == TYPE_FUNCTION){
        printf("TYPE_FUNCTION");
      } else if (type == TYPE_PROCEDURE){
        printf("TYPE_PROCEDURE");
      } else if (type == TYPE_VARIABLE){
        printf("TYPE_VARIABLE");
      } else if (type == TYPE_PARAMETER){
        printf("TYPE_PARAMETER");
      } else {
        printf("NO_ID_TYPE");
      }
}

void printType(Type type){
  printf(" , type : { ");
  printIdType(type.idType);
  printValueType(type.valueType);
}

void printEntry(IdEntry entry, StringTable table){
      unsigned index = entry.strtabIndex;
      printf("{ index : %u , string : %s", index, retrieveFromStringTable(table, index));
      printType(entry.type);
      printf(" }");
}