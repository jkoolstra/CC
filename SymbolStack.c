/* symtab.c: very simple symbol table.
 * author: Arnold Meijster (a.meijster@rug.nl)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymbolStack.h"

SymbolStack initSymbolStack(StringTable* strtab){
  SymbolStack stack;
  stack.strTab = strtab;
  stack.curLvl = 0;
  stack.tables[0] = initSymbolTable(stack.strTab);
  return stack;
}

void freeSymbolStack(SymbolStack* stack){
  for(int i = stack->curLvl; i >= 0; i--){
    freeSymbolTable(&stack->tables[i]);
  }
}

IdEntry *lookupSymbol(SymbolStack* stack, unsigned strtabIndex){
  for(int i = stack->curLvl; i >= 0; i--){
    IdEntry *entry = lookupSymbol(&stack->tables[i], strtabIndex);
    if(entry != NULL){
      return entry;
    }
  }
  return NULL;
}

void insertSymbol(SymbolStack* stack, unsigned strtabIndex, IdEntry* entry){
  //printf("INSERTING AT LAYER\n");
  insertSymbolInTable(&stack->tables[stack->curLvl], strtabIndex, entry);
}

void indent(SymbolStack* stack){
  stack->curLvl++;
  stack->tables[stack->curLvl] = initSymbolTable(&stack->strTab);
}

void outdent(SymbolStack* stack){
  freeSymbolTable(&stack->tables[stack->curLvl]);
  stack->curLvl--;
}

void printSymbolStack(SymbolStack* stack){
  printf("GLOBALS: \n");
  printSymbolTable(&stack->tables[0]);
  printf("LOCAL: \n");
  if(stack->curLvl == 1){
    printSymbolTable(&stack->tables[1]);
  } else {
    printf("\t NONE\nm");
  }
}