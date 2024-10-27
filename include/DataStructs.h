//
// Created by Cristi on 10/27/2024.
//

#ifndef PROJECTC_DATASTRUCTS_H
#define PROJECTC_DATASTRUCTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Game_exports.h"

typedef struct Pair {
    char *key;
    void *value;
} Pair;

typedef struct Bucket {
    size_t count;
    Pair *pairs;
} Bucket;

typedef struct HashMap {
    size_t count;
    Bucket *buckets;
} HashMap;

GAME_EXPORTS HashMap *newHashMap(size_t size);

GAME_EXPORTS void freeHashMap(HashMap *map);

GAME_EXPORTS void *hashMapGet(const HashMap *map, const char *key);

GAME_EXPORTS void hashMapSet(HashMap *map, const char *key, const void *value, size_t valueSize);

#ifdef __cplusplus
}
#endif

#endif //PROJECTC_DATASTRUCTS_H
