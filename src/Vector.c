//
// Created by Cristi on 10/28/2024.
//

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/DataStructs.h"

Vector *NewVector(size_t length, bool createCopy) {
    Vector *vector;
    vector = malloc(sizeof(Vector));
    if (vector == NULL) {
        return NULL;
    }
    *((bool *) &vector->auto_copy) = createCopy;
    if (length == 0) {
        vector->maxSize = 1;
    } else {
        vector->maxSize = length;
    }
    vector->size = 0;
    vector->array = malloc(sizeof(void *) * vector->maxSize);
    if (vector->array == NULL) {
        free(vector);
        return NULL;
    }
    return vector;
}

void FreeVector(Vector *vector) {
    if (vector == NULL) {
        return;
    }
    if (vector->auto_copy) {
        for (size_t i = 0; i < vector->size; i++) {
            free(vector->array[i]);
        }
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
    memcpy(vec + index + 1, vec + index, size);
    if (vector->auto_copy) {
        vec[index] = malloc(valueSize);
        memcpy(vec[index], value, valueSize);
    } else {
        vec[index] = value;
    }
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
    if (vector->auto_copy) {
        vec[vector->size] = malloc(valueSize);
        memcpy(vec[vector->size], value, valueSize);
    } else {
        vec[vector->size] = value;
    }
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
    if (vector->auto_copy) {
        free(vec[index]);
    }
    size = (vector->size - index) * sizeof(void *);
    memcpy(vec + index, vec + index + 1, size);
    vec[vector->size] = NULL;
}
