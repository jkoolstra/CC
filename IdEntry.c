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

void printType(Type t){

  printf("{ baseType : ");
  if(t.base == TYPE_SINGLE){
        printf("TYPE_SINGLE");
      } else if (t.base == TYPE_ARRAY){
        printf("TYPE_ARRAY");
      } else {
        printf("NO_BASE_TYPE");
      }
    printf(", secondaryType : ");
  if(t.secondary == TYPE_INTEGER){
        printf("TYPE_INTEGER");
      } else if (t.secondary == TYPE_REAL){
        printf("TYPE_REAL");
      } else if (t.secondary == TYPE_BOOL){
        printf("TYPE_BOOL");
      } else {
        printf("NO_SECONDARY_TYPE");
      }
  printf(" }");
}

void printFunctionData(FunctionData* data){
  printf("returnType : ");
  printType(data->returnType);
  printf(", parameters : %u", data->parameters->numberOfParameters);
}

void printVariableData(VariableData* data){
  printType(data->type);
}

void printIdType(IdType type){
  printf(" idType : ");
  if(type == TYPE_PROGRAM){
        printf("TYPE_PROGRAM");
      } else if (type == TYPE_FUNCTION){
        printf("TYPE_FUNCTION");
      } else if (type == TYPE_PROCEDURE){
        printf("TYPE_PROCEDURE");
      } else if (type == TYPE_VARIABLE){
        printf("TYPE_VARIABLE");
      } else {
        printf("NO_ID_TYPE");
      }
}

void printData(IdType type, void *data){
  printf(" , data : { ");
  if(type == TYPE_PROGRAM){
        printf("TYPE_PROGRAM");
      } else if (type == TYPE_FUNCTION){
        printFunctionData((FunctionData *)data);
      } else if (type == TYPE_PROCEDURE){
        printf("TYPE_PROCEDURE");
      } else if (type == TYPE_VARIABLE){
        printVariableData((VariableData *)data);
      } else {
        printf("NO_ID_TYPE");
    }
    printf(" }");
}

void printEntry(IdEntry entry, StringTable table){
      unsigned index = entry.strtabIndex;
      printf("{ index : %u , string : %s", index, retrieveFromStringTable(table, index));
      printIdType(entry.idType);
      printData(entry.idType, entry.data);
      printf(" }");
}








