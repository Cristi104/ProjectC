//
// Created by Cristi on 10/27/2024.
//

#ifndef PROJECTC_DATASTRUCTS_H
#define PROJECTC_DATASTRUCTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Game_exports.h"

typedef struct {
    char *key;
    void *value;
} GmlibPair;

typedef struct {
    size_t count;
    GmlibPair *pairs;
} GmlibBucket;

typedef struct {
    size_t count;
    GmlibBucket *buckets;
    const bool autoCopy;
} GmlibHashMap;

typedef struct {
    GmlibHashMap *hashMap;
    size_t bucketIndex;
    size_t pairIndex;
} GmlibHashMapIterator;

typedef struct {
    void **arr;
    size_t size;
    size_t maxSize;
    const bool autoCopy;
} GmlibArray;

GAME_EXPORTS GmlibHashMap *GmlibNewHashMap(size_t size, bool autoCopy);
GAME_EXPORTS void GmlibFreeHashMap(GmlibHashMap *map);
GAME_EXPORTS void *GmlibGetHashMap(const GmlibHashMap *map, const char *key);
GAME_EXPORTS void GmlibInsertHashMap(GmlibHashMap *map, const char *key, const void *value, size_t valueSize);
GAME_EXPORTS GmlibHashMapIterator GmlibNewHashMapIterator(GmlibHashMap *map);
GAME_EXPORTS GmlibPair *GmlibNextHashMapIterator(GmlibHashMapIterator *iterator);
GAME_EXPORTS GmlibPair *GmlibPreviousHashMapIterator(GmlibHashMapIterator *iterator);
GAME_EXPORTS GmlibArray *GmlibNewArray(size_t length, bool autoCopy);
GAME_EXPORTS void GmlibFreeArray(GmlibArray *array);
GAME_EXPORTS void GmlibInsertArray(GmlibArray *array, size_t index, void *value, size_t valueSize);
GAME_EXPORTS void GmlibAppendArray(GmlibArray *array, void *value, size_t valueSize);
GAME_EXPORTS void GmlibDeleteArray(GmlibArray *array, size_t index);

#ifdef __cplusplus
}
#endif

#endif //PROJECTC_DATASTRUCTS_H
