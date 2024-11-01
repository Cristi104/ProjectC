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

GAME_EXPORTS GmlibHashMap *GmlibHashMapCreate(size_t size, bool autoCopy);
GAME_EXPORTS void GmlibHashMapDestory(GmlibHashMap *map);
GAME_EXPORTS void *GmlibHashMapGet(const GmlibHashMap *map, const char *key);
GAME_EXPORTS void GmlibHashMapInsert(GmlibHashMap *map, const char *key, const void *value, size_t valueSize);
GAME_EXPORTS GmlibHashMapIterator GmlibHashMapIteratorCreate(GmlibHashMap *map);
GAME_EXPORTS GmlibPair *GmlibHashMapIteratorNext(GmlibHashMapIterator *iterator);
GAME_EXPORTS GmlibPair *GmlibHashMapIteratorPrevious(GmlibHashMapIterator *iterator);
GAME_EXPORTS GmlibArray *GmlibArrayCreate(size_t length, bool autoCopy);
GAME_EXPORTS void GmlibArrayDestroy(GmlibArray *array);
GAME_EXPORTS void GmlibArrayInsert(GmlibArray *array, size_t index, void *value, size_t valueSize);
GAME_EXPORTS void GmlibArrayAppend(GmlibArray *array, void *value, size_t valueSize);
GAME_EXPORTS void GmlibArrayDelete(GmlibArray *array, size_t index);

#ifdef __cplusplus
}
#endif

#endif //PROJECTC_DATASTRUCTS_H
