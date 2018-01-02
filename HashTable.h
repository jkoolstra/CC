#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define _CHECK_STRONG_COLLISIONS

#define DEFAULT_HASH_TABLE_SIZE 100
#define HASH_TABLE_LOAD_FACTOR_THRESHOLD 0.5
#define HASH_TABLE_RESIZE_FACTOR 2

#define NOT_IN_HASH_TABLE NULL

typedef unsigned char byte;

struct BucketList {
    byte* key, *data;
    size_t keySize, dataSize;
    struct BucketList* next;
};
typedef struct BucketList BucketList;
typedef BucketList Bucket;

typedef struct HashTable {
    size_t size, numberOfBuckets;
    Bucket* buckets;
} HashTable;
typedef HashTable* HashTableP;

typedef enum AddHashTableDataCollisionFlag {
    NO_COLLISION, WEAK_COLLISION, STRONG_COLLISION
} AddHashTableDataCollisionFlag;

typedef enum PrintHashTableOptions {
    PRINT_AS_BYTES, PRINT_AS_ALL_BYTES, PRINT_AS_STRINGS
} PrintHashTableOptions;


#ifdef _HASH_TABLE_C
  static void freeBucket(HashTable*, Bucket*);
  static Bucket* getHashTableBucketByIndex(HashTable*, int);
  static void moveBucket(HashTable*, Bucket*);
  static void printBucketAsStrings(Bucket*);
  static void printBucketAsBytes(Bucket*);
  static void printBucketAsAllBytes(Bucket*);
#endif
HashTable* newHashTable(size_t);
void iterateHashTable(HashTable*, HashTable*, void (*)(HashTable*, Bucket*));
void freeHashTable(HashTable*);
Bucket* getHashTableBucketByKey(HashTable*, byte*, size_t);
uint32_t hashData(byte*, size_t);
Bucket* bucketForKeyInHashTable(HashTable*, byte*, size_t);
AddHashTableDataCollisionFlag addDataToHashTable(HashTable*, byte*, byte*, size_t, size_t);
AddHashTableDataCollisionFlag addDataToHashTableAndResize(HashTable**, byte*, byte*, size_t, size_t);
HashTable* resizeHashTable(HashTable*, size_t);
double hashTableLoadFactor(HashTable*);
bool deleteHashTableData(HashTable*, byte*, byte*, size_t, size_t);
void printHashTable(HashTable*, PrintHashTableOptions);
#endif // #ifndef _HASH_TABLE_H



















