#ifndef IDENTRY_H
#define IDENTRY_H

#include "StringTable.h"
#include "common.h"

#define MAX_NUMBER_OF_PARAMS 97   /* choose a small prime */

typedef enum idType {
	TYPE_PROGRAM,
	TYPE_FUNCTION,
	TYPE_PROCEDURE,
	TYPE_VARIABLE
} IdType;

typedef enum secondaryType {
	TYPE_SCALAR,
	TYPE_ARRAY
} SecondaryType;

typedef enum baseType {
	TYPE_INTEGER = 1,
	TYPE_REAL = 2,
	TYPE_BOOL = 3
} BaseType;

typedef struct type {
	BaseType base;
	SecondaryType secondary;
	unsigned low;
	unsigned high;
} Type;

typedef struct parameterData {
	unsigned strtabIndex;
	Type type;
} ParameterData;

typedef struct strtabIndexList {
    unsigned numberOfIndices;
	unsigned *indices;
} StrtabIndexList;

typedef struct parameterList {
    unsigned numberOfParameters;
	ParameterData **parameters;
} ParameterList;

typedef struct typeList {
	unsigned numberOfTypes;
	Type *types;
}	TypeList;

typedef struct variableData {
	Type type;
} VariableData;

typedef struct functionData {
	Type returnType;
	ParameterList parameters;
} FunctionData;

typedef struct ProcedureData {
	ParameterList parameters;
} ProcedureData;

typedef struct idEntry{
	unsigned strtabIndex;
	IdType idType;
	void *data;
} IdEntry;

//PRINTING
void printEntry(IdEntry entry, StringTable table);
char *idTypeString(IdType type);
char *secondaryTypeString(SecondaryType type);
char *baseTypeString(BaseType type);

//INITIALIZING
IdEntry makeIdEntry(unsigned);
void freeIdEntry(IdEntry*);
Type makeType(BaseType, SecondaryType, unsigned, unsigned);
void freeStrtabIndexList(StrtabIndexList *list);
StrtabIndexList createStrtabIndexList(unsigned index);
ParameterList createParameterList(StrtabIndexList list, Type t);
TypeList createTypeList(Type t);

//OPERATIONS
StrtabIndexList combineIdentifiers(StrtabIndexList, StrtabIndexList);
ParameterList combineParameterLists(ParameterList listOne, ParameterList listTwo);
void appendParameterLists(ParameterList*, StrtabIndexList, Type);
TypeList combineTypeLists(TypeList listOne, TypeList listTwo);
void appendToTypeLists(TypeList*, Type);


#endif
