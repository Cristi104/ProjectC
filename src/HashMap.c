//
// Created by Cristi on 10/27/2024.
//
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/DataStructs.h"

static size_t hash(const char *key) {
    size_t hash = 5381;
    while (key[0]) {
        hash = (hash << 5) + hash + (size_t) key[0];
        key++;
    }
    return hash;
}

HashMap *NewHashMap(size_t size, bool autoCopy) {
    HashMap *map;
    map = malloc(sizeof(HashMap));
    *((bool *) &map->autoCopy) = autoCopy;
    if (map == NULL) {
        return NULL;
    }
    map->count = size;
    map->buckets = malloc(size * sizeof(Bucket));
    if (map->buckets == NULL) {
        free(map);
        return NULL;
    }
    memset(map->buckets, 0, size * sizeof(Bucket));
    return map;
}

void FreeHashMap(HashMap *map) {
    Bucket *bucket;
    Pair *pair;
    if (map == NULL) {
        return;
    }
    for (size_t i = 0; i < map->count; i++) {
        bucket = &map->buckets[i];
        for (size_t j = 0; j < bucket->count; j++) {
            pair = &bucket->pairs[j];
            if (map->autoCopy) {
                free(pair->value);
            }
            free(pair->key);
        }
        free(bucket->pairs);
    }
    free(map);
}

void *GetHashMap(const HashMap *map, const char *key) {
    size_t index;
    Bucket *bucket;
    Pair *pair;
    if (key == NULL || map == NULL) {
        return NULL;
    }
    index = hash(key) % map->count;
    bucket = &map->buckets[index];
    if (bucket == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < bucket->count; i++) {
        pair = &bucket->pairs[i];
        if (strcmp(key, pair->key) == 0) {
            return pair->value;
        }
    }
    return NULL;
}

void InsertHashMap(HashMap *map, const char *key, const void *value, size_t valueSize) {
    size_t index;
    size_t keySize;
    Bucket *bucket;
    Pair *pair;
    Pair *buf;
    if (map == NULL || key == NULL || value == NULL) {
        return;
    }
    index = hash(key) % map->count;
    keySize = strlen(key);
    bucket = &map->buckets[index];
    bucket->count++;
    if (bucket->count == 0) {
        bucket->pairs = malloc(sizeof(Pair));
    } else {
        buf = realloc(bucket->pairs, bucket->count * sizeof(Pair));
        if (buf == NULL) {
            return;
        }
        bucket->pairs = buf;
    }
    pair = &bucket->pairs[bucket->count - 1];
    pair->key = malloc(keySize + 1);
    strncpy(pair->key, key, keySize);
    pair->key[keySize] = '\0';
    if (map->autoCopy) {
        pair->value = malloc(valueSize);
        memcpy(pair->value, value, valueSize);
    } else {
        pair->value = (void *) value;
    }
}

HashMapIterator NewHashMapIterator(HashMap *map) {
    HashMapIterator iterator;
    iterator.hashMap = map;
    iterator.bucketIndex = 0;
    iterator.pairIndex = -1;
    return iterator;
}

Pair *NextHashMapIterator(HashMapIterator *iterator) {
    HashMap *map = iterator->hashMap;
    Bucket *bucket = map->buckets + iterator->bucketIndex;

    if (iterator->pairIndex == -1 && bucket->count) {
        iterator->pairIndex = 0;
        return &bucket->pairs[0];
    }

    if (iterator->pairIndex == bucket->count - 1) {
        if (iterator->bucketIndex == map->count - 1) {
            return NULL;
        } else {
            do {
                iterator->bucketIndex++;
                if (iterator->bucketIndex == map->count)
                    return NULL;
                bucket = map->buckets + iterator->bucketIndex;
            } while (bucket->count == 0);
            iterator->pairIndex = 0;
        }
    } else {
        iterator->pairIndex++;
    }
    return &map->buckets[iterator->bucketIndex].pairs[iterator->pairIndex];
}

Pair *PreviousHashMapIterator(HashMapIterator *iterator) {
    HashMap *map = iterator->hashMap;
    Bucket *bucket;

    if (iterator->pairIndex == 0) {
        if (iterator->bucketIndex == 0) {
            iterator->pairIndex = -1;
            return NULL;
        } else {
            do {
                iterator->bucketIndex--;
                if (iterator->bucketIndex == -1)
                    return NULL;
                bucket = map->buckets + iterator->bucketIndex;
            } while (bucket->count == 0);
            iterator->pairIndex = map->buckets[iterator->bucketIndex].count - 1;
        }
    } else {
        iterator->pairIndex--;
    }
    return &map->buckets[iterator->bucketIndex].pairs[iterator->pairIndex];
}

