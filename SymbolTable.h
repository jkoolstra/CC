/* symtab.h: very simple symbol table.
 * author: Arnold Meijster (a.meijster@rug.nl)
 */

#ifndef HASHTAB_H
#define HASHTAB_H

#include "StringTable.h"
#include "IdEntry.h"

#define TABSIZE 97   /* choose a small prime */

typedef struct bucket {
  unsigned key;   
  IdEntry *data;
  struct bucket *next;
} *bucket; 

typedef struct symbolTable {
	StringTable *stringTab;
	bucket hashtab[TABSIZE];
} SymbolTable;

SymbolTable initSymbolTable(StringTable*);
void freeSymbolTable(SymbolTable*);
IdEntry *lookupSymbolInTable(SymbolTable*, unsigned);
void insertSymbolInTable(SymbolTable*, IdEntry);
void printSymbolTable(SymbolTable*);

#endif
