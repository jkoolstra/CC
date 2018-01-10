#ifndef IDENTRY_H
#define IDENTRY_H

#include "StringTable.h"

#define MAX_NUMBER_OF_PARAMS 97   /* choose a small prime */

typedef enum idType {
	NO_ID_TYPE,
	TYPE_PROGRAM,
	TYPE_FUNCTION,
	TYPE_PROCEDURE,
	TYPE_VARIABLE
} IdType;

typedef enum secondaryType {
	TYPE_SINGLE,
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
} Type;

typedef struct variableData {
	Type type;
} VariableData;

typedef struct parameterData {
	unsigned strtabIndex;
	Type type;
} ParameterData;

typedef struct parameterList {
    unsigned numberOfParameters;
		ParameterData *parameters;
} ParameterList;

typedef struct functionData {
	Type returnType;
	ParameterList *parameters;
} FunctionData;

typedef struct procedureData {
	ParameterList *parameters;
} ProcedureData;

typedef struct strtabIndexList {
    unsigned numberOfIndices;
	unsigned *indices;
} StrtabIndexList;

typedef struct idEntry{
	unsigned strtabIndex;
	IdType idType;
	void *data;
} IdEntry;

IdEntry makeIdEntry(unsigned);

void printEntry(IdEntry entry, StringTable table);
char *idTypeString(IdType type);

#endif
