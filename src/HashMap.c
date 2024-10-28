//
// Created by Cristi on 10/27/2024.
//
#include <malloc.h>
#include <string.h>
#include "../include/DataStructs.h"

static size_t hash(const char *key) {
    size_t hash = 5381;
    while (key[0]) {
        hash = (hash << 5) + hash + (size_t) key[0];
        key++;
    }
    return hash;
}

HashMap *NewHashMap(size_t size) {
    HashMap *map;
    map = malloc(sizeof(HashMap));
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
            free(pair->value);
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
    strncpy_s(pair->key, keySize + 1, key, keySize);
    pair->value = malloc(valueSize);
    memcpy_s(pair->value, valueSize, value, valueSize);
}
