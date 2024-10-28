//
// Created by Cristi on 10/28/2024.
//

#include <malloc.h>
#include <string.h>
#include "../include/DataStructs.h"

Vector *NewVector(size_t length) {
    Vector *vector;
    vector = malloc(sizeof(Vector));
    if (length == 0) {
        vector->maxSize = 1;
    } else {
        vector->maxSize = length;
    }
    vector->size = 0;
    vector->array = malloc(sizeof(void *) * vector->maxSize);
    return vector;
}

void FreeVector(Vector *vector) {
    if (vector == NULL) {
        return;
    }
    for (size_t i = 0; i < vector->size; i++) {
        free(vector->array[i]);
    }
    free(vector->array);
}

void InsertVector(Vector *vector, size_t index, void *value, size_t valueSize) {
    void **buf;
    void **vec;
    size_t size;
    if (vector == NULL || value == NULL) {
        return;
    }
    if (index >= vector->size) {
        AppendVector(vector, value, valueSize);
        return;
    }
    if (vector->size == vector->maxSize) {
        vector->maxSize++;
        buf = realloc(vector->array, vector->maxSize * sizeof(void *));
        if (buf == NULL) {
            return;
        }
        vector->array = buf;
    }
    vec = vector->array;
    size = (vector->size - index) * sizeof(void *);
    memcpy_s(vec + index + 1, size, vec + index, size);
    vec[index] = malloc(valueSize);
    memcpy_s(vec[index], valueSize, value, valueSize);
    vector->size++;
}

void AppendVector(Vector *vector, void *value, size_t valueSize) {
    void **buf;
    void **vec;
    if (vector == NULL || value == NULL) {
        return;
    }
    if (vector->size == vector->maxSize) {
        vector->maxSize++;
        buf = realloc(vector->array, vector->maxSize * sizeof(void *));
        if (buf == NULL) {
            return;
        }
        vector->array = buf;
    }
    vec = vector->array;
    vec[vector->size] = malloc(valueSize);
    memcpy_s(vec[vector->size], valueSize, value, valueSize);
    vector->size++;
}

void DeleteVector(Vector *vector, size_t index) {
    void **vec;
    size_t size;
    if (vector == NULL) {
        return;
    }
    if (index >= vector->size) {
        return;
    }
    vec = vector->array;
    vector->size--;
    free(vec[index]);
    size = (vector->size - index) * sizeof(void *);
    memcpy_s(vec + index, size, vec + index + 1, size);
    vec[vector->size] = NULL;
}
