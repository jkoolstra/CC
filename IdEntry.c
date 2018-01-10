/* symtab.c: very simple symbol table.
 * author: Arnold Meijster (a.meijster@rug.nl)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IdEntry.h"
#include "common.h"

// PRINTING
void printProcedure(ProcedureData* data, StringTable table){
	printf("parameters : [ \n");
	for(int i = 0; i < data->parameters->numberOfParameters; i++){
		ParameterData p = data->parameters->parameters[i];
		printf("{ name : %s, base : %s, secondary : %s }", retrieveFromStringTable(table, p.strtabIndex), baseTypeString(p.type.base), secondaryTypeString(p.type.secondary));
	}
	printf("]");
}

void printFunction(FunctionData* data, StringTable table){
	printf("base_return : %s, secondary_return: %s, parameters : [ ", baseTypeString(data->returnType.base), secondaryTypeString(data->returnType.secondary));
	for(int i = 0; i < data->parameters->numberOfParameters; i++){
		ParameterData p = data->parameters->parameters[i];
		printf("{ name : %s, base : %s, secondary : %s }", retrieveFromStringTable(table, p.strtabIndex), baseTypeString(p.type.base), secondaryTypeString(p.type.secondary));
	}
	printf("]");
}

void printVariable(VariableData* data, StringTable table){
	printf("base : %s, secondary: %s", baseTypeString(data->type.base), secondaryTypeString(data->type.secondary));
}

void printData(IdType t, void* data, StringTable table){
	printf("{");
	switch(t){
		case TYPE_VARIABLE : printVariable((VariableData *)data, table); return;
		case TYPE_PROCEDURE : printProcedure((ProcedureData *)data, table); return;
		case TYPE_FUNCTION : printFunction((FunctionData *)data, table); return;
	}
	printf("}");
}

void printEntry(IdEntry entry, StringTable table){
      unsigned index = entry.strtabIndex;
      printf("{ index : %u , string : %s", index, retrieveFromStringTable(table, index));
      printf(" idType : %s", idTypeString(entry.idType));
	  printf(", data :");
      printData(entry.idType, entry.data, table);
      printf(" }\n");
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

char *baseTypeString(BaseType type){
  switch(type) {
      case TYPE_INTEGER : return "INTEGER";
      case TYPE_REAL : return "REAL";
      default: return "BOOL";
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

ParameterList *createParameterList(StrtabIndexList list, Type t){
    ParameterList *newList = safeMalloc(sizeof(ParameterList));
    newList->numberOfParameters = list.numberOfIndices;
    newList->parameters = safeMalloc(list.numberOfIndices * sizeof(ParameterData));

    for(int i =0 ; i < list.numberOfIndices; i++){
        ParameterData data; // = safeMalloc(sizeof(ParameterData));
        data.strtabIndex = list.indices[i];
        data.type = t;

        newList->parameters[i] = data;
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
void appendParameterLists(ParameterList* list, StrtabIndexList indices, Type t){
	int oldLength = list->numberOfParameters;
	list->numberOfParameters = list->numberOfParameters + indices.numberOfIndices;
    safeRealloc(list->parameters, list->numberOfParameters * sizeof(ParameterData));
	int j = 0;
    for(int i = oldLength; i < list->numberOfParameters; i++){
		j++;
		ParameterData data;
        data.strtabIndex = indices.indices[j];
        data.type = t;

        list->parameters[i] = data;
    }

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
	//printf("Paramaterlist is now : %d long \n", list->numberOfTypes);
    safeRealloc(list->types, list->numberOfTypes * sizeof(Type));
    list->types[list->numberOfTypes-1] = t;
}
