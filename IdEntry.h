#ifndef IDENTRY_H
#define IDENTRY_H

#include "StringTable.h"

#define MAX_NUMBER_OF_PARAMS 97   /* choose a small prime */

typedef struct strtabIndexList {
    unsigned numberOfIndices;
	unsigned *indices;
} StrtabIndexList;

typedef enum idType {
	NO_ID_TYPE,
	TYPE_PROGRAM,
	TYPE_FUNCTION,
	TYPE_PROCEDURE,
	TYPE_VARIABLE,
	TYPE_PARAMETER
} IdType; 

typedef enum baseType {
	NO_BASE_TYPE,
	TYPE_SINGLE,
	TYPE_ARRAY
} BaseType;

typedef enum secondaryType {
	NO_SECONDARY_TYPE,
	TYPE_INTEGER,
	TYPE_REAL,
	TYPE_BOOL
} SecondaryType ;

typedef struct valueType {
	BaseType base;
	SecondaryType secondary;
} ValueType;

typedef struct type {
	IdType idType;
	ValueType valueType;
} Type;

typedef struct idEntry{
	unsigned strtabIndex;
	Type type;
} IdEntry;

IdEntry makeIdEntry(unsigned);
void printEntry(IdEntry entry, StringTable table);

#endif