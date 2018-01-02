#define _HASH_TABLE_C
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"
#include "HashTable.h"


HashTable* newHashTable(size_t hashTableSize) {
    HashTable *newHashTable = safeMalloc(sizeof(HashTable));
    newHashTable->size = (hashTableSize > 0) ? hashTableSize : DEFAULT_HASH_TABLE_SIZE;
    newHashTable->numberOfBuckets = 0;
    newHashTable->buckets = calloc(newHashTable->size, sizeof(Bucket));
    return newHashTable;
}

void iterateHashTable(HashTable *hashTable, HashTable *targetHashTable,
  void (*iterator)(HashTable*, Bucket*)) {
    int i;
    for (i=0; i < hashTable->size; ++i) {
        Bucket* bucket = getHashTableBucketByIndex(hashTable, i);
        while (bucket != NULL) {
            (*iterator)(targetHashTable, bucket);
            bucket = bucket->next;
        }
    }
}

void freeHashTable(HashTable* hashTable) {
    iterateHashTable(hashTable, NULL, freeBucket);
    free(hashTable->buckets);
    free(hashTable);
}

static void freeBucket(HashTable* NOT_USED, Bucket* bucket) {
    if (bucket->data != NULL) {
        free(bucket->data);
    }
    free(bucket->key);
}

static Bucket* getHashTableBucketByIndex(HashTable *hashTable, int index) {
      return &hashTable->buckets[index];
}

Bucket* getHashTableBucketByKey(HashTable *hashTable, byte *key, size_t keySize) {
    uint32_t keyHash = hashData(key, keySize);
    int index = keyHash % hashTable->size;
    return getHashTableBucketByIndex(hashTable, index);
}

uint32_t hashData(byte *data, size_t dataSize) {
    uint32_t state = 0;
    while (dataSize--) {
        state = (state << 3) ^ (state >> 29) ^ data[dataSize];
        state = (state << 11) ^ (state >> 21) ^ data[dataSize];
        state = (state << 19) ^ (state >> 13) ^ data[dataSize];
        state = (state << 31) ^ (state >> 1) ^ data[dataSize];
    }
    return state;
}

Bucket* bucketForKeyInHashTable(HashTable *hashTable, byte* key, size_t keySize) {
    Bucket* bucket = getHashTableBucketByKey(hashTable, key, keySize);
    while (bucket != NULL) {
        if (bucket->key != NULL && memcmp(bucket->key, key, keySize) == 0) {
            return bucket;
        }
        bucket = bucket->next;
    }
    return NOT_IN_HASH_TABLE;
}

AddHashTableDataCollisionFlag addDataToHashTable(HashTable *hashTable, byte *key, byte *data,
  size_t keySize, size_t dataSize) {
    AddHashTableDataCollisionFlag collisionFlag = NO_COLLISION;
    byte *dataCopy, *keyCopy;
    Bucket* bucket = getHashTableBucketByKey(hashTable, key, keySize);

    while (bucket->key != NULL) {
        collisionFlag = WEAK_COLLISION;
        #ifdef _CHECK_STRONG_COLLISIONS
          if ((bucket->data == NULL && data == NULL) ||
            (bucket->data != NULL && !memcmp(bucket->data, data, dataSize))) {
              return STRONG_COLLISION;
          }
        #endif
        if (bucket->next == NULL) {
            bucket->next = calloc(sizeof(BucketList), 1);
        }
        bucket = bucket->next;
    }
    dataCopy = malloc(dataSize * sizeof(byte));
    keyCopy = malloc(keySize * sizeof(byte));
    memcpy(dataCopy, data, dataSize);
    memcpy(keyCopy, key, keySize);
    bucket->data = dataCopy;
    bucket->dataSize = dataSize;
    bucket->key = keyCopy;
    bucket->keySize = keySize;
    ++hashTable->numberOfBuckets;
    return collisionFlag;
}

AddHashTableDataCollisionFlag addDataToHashTableAndResize(HashTableP *hashTablePointer, byte *key,
  byte *data, size_t keySize, size_t dataSize) {
    if (hashTableLoadFactor(*hashTablePointer) > HASH_TABLE_LOAD_FACTOR_THRESHOLD) {
        *hashTablePointer = resizeHashTable(*hashTablePointer,
          HASH_TABLE_RESIZE_FACTOR * (*hashTablePointer)->size);
    }
    return addDataToHashTable(*hashTablePointer, key, data, keySize, dataSize);
}

static void moveBucket(HashTable* moveToHashTable, Bucket* bucket) {
    addDataToHashTable(moveToHashTable, bucket->key, bucket->data, bucket->keySize, bucket->dataSize);
    freeBucket(NULL, bucket);
}

HashTable* resizeHashTable(HashTable* hashTable, size_t newHashTableSize) {
    HashTable *resizedHashTable = newHashTable(newHashTableSize);
    iterateHashTable(hashTable, resizedHashTable, moveBucket);
    free(hashTable->buckets);
    free(hashTable);
    return resizedHashTable;
}

double hashTableLoadFactor(HashTable* hashTable) {
    return (double) hashTable->numberOfBuckets / hashTable->size;
}

/* For reference only. */
bool deleteHashTableData(HashTable *hashTable, byte *key, byte *data, size_t keySize,
 size_t dataSize) {
    return false;
}

void printHashTable(HashTable *hashTable, PrintHashTableOptions option) {
    int i;
    printf("HASH TABLE; #items / size : %d / %d; load: %f.\nCONTENT =\n",
      hashTable->numberOfBuckets, hashTable->size, hashTableLoadFactor(hashTable));
    for (i=0; i < hashTable->size; ++i) {
        Bucket* bucket = getHashTableBucketByIndex(hashTable, i);
        if (bucket->key != NULL) {
            printf("(#%d) ", i);
            switch (option) {
                case PRINT_AS_STRINGS:
                    printBucketAsStrings(bucket); break;
                case PRINT_AS_BYTES:
                    printBucketAsBytes(bucket); break;
                case PRINT_AS_ALL_BYTES:
                    printBucketAsAllBytes(bucket); break;
            }
            printf("\n\n");
        }
    }
}

static void printBucketAsStrings(Bucket* bucket) {
    while (bucket != NULL) {
        printf("[ \"%s\" : \"%s\" ]", (char*) bucket->key, (char*) bucket->data);
        if (bucket->next != NULL) {
            printf(" --> ");
        }
        bucket = bucket->next;
    }
}

static void printBucketAsAllBytes(Bucket* bucket) {
    int i;
    while (bucket != NULL) {
        printf("[ ");
        for (i = 0; i < bucket->keySize; ++i) {
            printf("%X ", bucket->key[i]);
        }
        printf(": ");
        for (i = 0; i < bucket->dataSize; ++i) {
            printf("%X ", bucket->data[i]);
        }
        printf("]");
        if (bucket->next != NULL) {
            printf(" --> ");
        }
        bucket = bucket->next;
    }
}

static void printBucketAsBytes(Bucket* bucket) {
    int i;
    while (bucket != NULL) {
        printf("[ \"%s\" : ", (char*) bucket->key);
        for (i = 0; i < bucket->dataSize; ++i) {
            printf("%X ", bucket->data[i]);
        }
        printf("]");
        if (bucket->next != NULL) {
            printf(" --> ");
        }
        bucket = bucket->next;
    }
}




















