/* symtab.c: very simple symbol table.
 * author: Arnold Meijster (a.meijster@rug.nl)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StringTable.h"
#include "SymbolTable.h"

SymbolTable initSymbolTable(StringTable* strtab) {
  SymbolTable table;
  table.stringTab = strtab;
  unsigned int i;
  for (i=0; i < TABSIZE; i++) {
    table.hashtab[i] = NULL;
  }
  return table;
}

void freeSymbolTable(SymbolTable* table) {
  unsigned int i;
  for (i=0; i < TABSIZE; i++) {
    while (table->hashtab[i] != NULL) {
      bucket b = table->hashtab[i];
      table->hashtab[i] = table->hashtab[i]->next;
      free(b->data);
      free(b);
    }
  }
}

static unsigned int hash(char *str) {
  /* famous hash function: google for Jenkins' hash function */
  unsigned int i, hash = 0, len = strlen(str);
  for(i = 0; i < len; ++i) {
    hash += str[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash%TABSIZE;
}

static IdEntry *linearSearch(unsigned strtabIndex, bucket b) {
  while (b != NULL) {
    if (strtabIndex == b->key) {
      return b->data;
    }
    b = b-> next;
  }
  return NULL;
}


IdEntry *lookupSymbolInTable(SymbolTable* table, unsigned strtabIndex) {
  char *str = retrieveFromStringTable(*table->stringTab, strtabIndex);
  return linearSearch(strtabIndex, table->hashtab[hash(str)]);
}

void insertSymbolInTable(SymbolTable* table, unsigned strtabIndex, IdEntry *entry) {
  char *str = retrieveFromStringTable(*table->stringTab, strtabIndex);
  unsigned int h = hash(str);
  bucket nxt = table->hashtab[h];
  table->hashtab[h] = malloc(sizeof(struct bucket));
  table->hashtab[h]->next = nxt;
  table->hashtab[h]->key = strtabIndex; 
  table->hashtab[h]->data = entry;
  //printf("Inserted [%s] at hash index : %um", retrieveFromStringTable(*table->stringTab, strtabIndex));
}

void printSymbolTable(SymbolTable* table){
  unsigned int i;
  for (i=0; i < TABSIZE; i++) {
    bucket b = table->hashtab[i];
    if(b != NULL)
      printf("\t [%d] | ", i);
    else {
      continue;
    }
    while (b != NULL) {
      IdEntry *entry = b->data;
      unsigned index = entry->strtabIndex;
      Type type = entry->type;
      printf("{ index : %u , type : ", index);
      if(type == TYPE_PROGRAM){
        printf("TYPE_PROGRAM");
      } else if (type == TYPE_FUNCTION){
        printf("TYPE_FUNCTION");
      } else if (type == TYPE_IDENTIFIER){
        printf("TYPE_IDENTIFIER");
      } else {
        printf("TYPE_UNKNOWN");
      }
      printf(" } | ");
      b = b->next;
    }
    printf("\n");
  }
}