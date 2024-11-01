//
// Created by Cristi on 10/28/2024.
//

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/DataStructs.h"

GmlibArray *GmlibArrayCreate(size_t length, bool autoCopy) {
    GmlibArray *vector;
    vector = malloc(sizeof(GmlibArray));
    if (vector == NULL) {
        return NULL;
    }
    *((bool *) &vector->autoCopy) = autoCopy;
    if (length == 0) {
        vector->maxSize = 1;
    } else {
        vector->maxSize = length;
    }
    vector->size = 0;
    vector->arr = malloc(sizeof(void *) * vector->maxSize);
    if (vector->arr == NULL) {
        free(vector);
        return NULL;
    }
    return vector;
}

void GmlibArrayDestroy(GmlibArray *array) {
    if (array == NULL) {
        return;
    }
    if (array->autoCopy) {
        for (size_t i = 0; i < array->size; i++) {
            free(array->arr[i]);
        }
    }
    free(array->arr);
}

void GmlibArrayInsert(GmlibArray *array, size_t index, void *value, size_t valueSize) {
    void **buf;
    void **vec;
    size_t size;
    if (array == NULL || value == NULL) {
        return;
    }
    if (index >= array->size) {
        GmlibArrayAppend(array, value, valueSize);
        return;
    }
    if (array->size == array->maxSize) {
        array->maxSize++;
        buf = realloc(array->arr, array->maxSize * sizeof(void *));
        if (buf == NULL) {
            return;
        }
        array->arr = buf;
    }
    vec = array->arr;
    size = (array->size - index) * sizeof(void *);
    memcpy(vec + index + 1, vec + index, size);
    if (array->autoCopy) {
        vec[index] = malloc(valueSize);
        memcpy(vec[index], value, valueSize);
    } else {
        vec[index] = value;
    }
    array->size++;
}

void GmlibArrayAppend(GmlibArray *array, void *value, size_t valueSize) {
    void **buf;
    void **vec;
    if (array == NULL || value == NULL) {
        return;
    }
    if (array->size == array->maxSize) {
        array->maxSize++;
        buf = realloc(array->arr, array->maxSize * sizeof(void *));
        if (buf == NULL) {
            return;
        }
        array->arr = buf;
    }
    vec = array->arr;
    if (array->autoCopy) {
        vec[array->size] = malloc(valueSize);
        memcpy(vec[array->size], value, valueSize);
    } else {
        vec[array->size] = value;
    }
    array->size++;
}

void GmlibArrayDelete(GmlibArray *array, size_t index) {
    void **vec;
    size_t size;
    if (array == NULL) {
        return;
    }
    if (index >= array->size) {
        return;
    }
    vec = array->arr;
    array->size--;
    if (array->autoCopy) {
        free(vec[index]);
    }
    size = (array->size - index) * sizeof(void *);
    memcpy(vec + index, vec + index + 1, size);
    vec[array->size] = NULL;
}
