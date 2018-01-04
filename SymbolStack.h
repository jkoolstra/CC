/* symtab.h: very simple symbol table.
 * author: Arnold Meijster (a.meijster@rug.nl)
 */

#ifndef SYMBOLSTACK_H
#define SYMBOLSTACK_H

#include "StringTable.h"
#include "SymbolTable.h"

#define MAX_INDENT 2 

typedef struct symbolStack {
	unsigned curLvl;
	StringTable *strTab;
	SymbolTable tables[MAX_INDENT];
} SymbolStack;

SymbolStack initSymbolStack(StringTable*);
void freeSymbolStack(SymbolStack*);
IdEntry *lookupSymbol(SymbolStack*, unsigned);
void insertSymbol(SymbolStack*, unsigned, IdEntry*);
void indent(SymbolStack*);
void outdent(SymbolStack*);
void printSymbolStack(SymbolStack*);

#endif
