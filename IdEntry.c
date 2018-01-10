/* symtab.c: very simple symbol table.
 * author: Arnold Meijster (a.meijster@rug.nl)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IdEntry.h"
#include "common.h"

// PRINTING
void printEntry(IdEntry entry, StringTable table){
      unsigned index = entry.strtabIndex;
      printf("{ index : %u , string : %s", index, retrieveFromStringTable(table, index));
      /*printf(" idType : ");
      printIdType(entry.idType);
      printData(entry.idType, entry.data);*/
      printf(" }");
}

char *idTypeString(IdType type){
  switch(type) {
      case TYPE_PROGRAM : return "PROGRAM";
      case TYPE_FUNCTION : return "FUNCTION";
      case TYPE_PROCEDURE : return "PROCEDURE";
      case TYPE_VARIABLE : return "VARIABLE";
      default: return "-";
  }
}

char *secondaryTypeString(SecondaryType type){
  switch(type) {
      case TYPE_SCALAR : return "SCALAR";
      case TYPE_ARRAY : return "ARRAY";
      default: return "-";
  }
}

// INITIALIZING

IdEntry makeIdEntry(unsigned index){
    IdEntry entry;
    entry.strtabIndex = index;
    return entry;
}

Type makeType(BaseType tb, SecondaryType ts){
  Type t;
  t.base = tb;
  t.secondary = ts;
  return t;
}

ParameterList createParameterList(StrtabIndexList list, Type t){
    ParameterList newList; // = safeMalloc(sizeof(ParameterList));
    newList.numberOfParameters = list.numberOfIndices;
    newList.parameters = safeMalloc(list.numberOfIndices * sizeof(ParameterData));

    for(int i =0 ; i < list.numberOfIndices; i++){
        ParameterData data; // = safeMalloc(sizeof(ParameterData));
        data.strtabIndex = list.indices[i];
        data.type = t;

        newList.parameters[i] = data;
    }
    return newList;
}


TypeList createTypeList(Type t){
    TypeList newList;
	newList.numberOfTypes = 1;
	newList.types = safeMalloc(1 * sizeof(Type));

	newList.types[0] = t;
	return newList;
}

// OPERATIONS
ParameterList combineParameterLists(ParameterList listOne, ParameterList listTwo){
    ParameterList newList;
    newList.numberOfParameters = listOne.numberOfParameters + listTwo.numberOfParameters;
    newList.parameters = safeMalloc(newList.numberOfParameters * sizeof(ParameterData));
    int i;
    int j;
    for(i =0 ; i < listOne.numberOfParameters; i++){
        newList.parameters[i] = listOne.parameters[i];
    }
    for(j =0 ; j < listTwo.numberOfParameters; j++){
        newList.parameters[j+i] = listTwo.parameters[j];
    }
    return newList;
}

StrtabIndexList combineIdentifiers(StrtabIndexList listOne, StrtabIndexList listTwo){
    StrtabIndexList newList;
    newList.numberOfIndices = listOne.numberOfIndices + listTwo.numberOfIndices;
    newList.indices = safeMalloc(newList.numberOfIndices * sizeof(unsigned));
    int i;
    int j;
    for(i =0 ; i < listOne.numberOfIndices; i++){
        newList.indices[i] = listOne.indices[i];
    }
    for(j =0 ; j < listTwo.numberOfIndices; j++){
        newList.indices[j+i] = listTwo.indices[j];
    }
    return newList;
}

void appendToTypeLists(TypeList* list, Type t){
    list->numberOfTypes = list->numberOfTypes + 1;
    safeRealloc(list->types, list->numberOfTypes * sizeof(Type));
    list->types[list->numberOfTypes-1] = t;
}
