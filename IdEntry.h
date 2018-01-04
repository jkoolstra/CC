#ifndef IDENTRY_H
#define IDENTRY_H

#define MAX_NUMBER_OF_PARAMS 97   /* choose a small prime */

typedef enum type {
	TYPE_PROGRAM,
	TYPE_FUNCTION,
	TYPE_VARIABLE
} Type; 

typedef enum valueType {
	VALUETYPE_REAL,
	VALUETYPE_INTEGER,
	VALUETYPE_BOOL
} ValueType;

typedef struct idEntry{
	unsigned strtabIndex;
	Type type;
} *IdEntry;

IdEntry makeIdEntry(unsigned, Type);
void printEntry(IdEntry entry);

#endif