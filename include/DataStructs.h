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

typedef struct Vector {
    void **array;
    size_t size;
    size_t maxSize;
} Vector;

GAME_EXPORTS HashMap *NewHashMap(size_t size);

GAME_EXPORTS void FreeHashMap(HashMap *map);

GAME_EXPORTS void *GetHashMap(const HashMap *map, const char *key);

GAME_EXPORTS void InsertHashMap(HashMap *map, const char *key, const void *value, size_t valueSize);

GAME_EXPORTS Vector *NewVector(size_t length);

GAME_EXPORTS void FreeVector(Vector *vector);

GAME_EXPORTS void InsertVector(Vector *vector, size_t index, void *value, size_t valueSize);

GAME_EXPORTS void AppendVector(Vector *vector, void *value, size_t valueSize);

GAME_EXPORTS void DeleteVector(Vector *vector, size_t index);

#ifdef __cplusplus
}
#endif

#endif //PROJECTC_DATASTRUCTS_H
