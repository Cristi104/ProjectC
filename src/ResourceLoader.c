//
// Created by cristi on 30.10.2024.
//

#include <string.h>
#include <stdio.h>
#include "raylib.h"
#include "../include/DataStructs.h"

HashMap *textures = NULL;

void LoadTexturesDir(const char *directory) {
    FilePathList list = LoadDirectoryFiles(directory);
    unsigned int nameSize;
    char *file, *fileName;
    Image image;
    Texture2D texture;

    if (textures == NULL) {
        textures = NewHashMap(256, true);
    }

    for (int i = 0; i < list.count; i++) {
        file = list.paths[i];
        fileName = file + strlen(directory) + 1;
        nameSize = strlen(fileName);

        if (strchr(fileName, '.') != NULL) {
            if (strstr(fileName + nameSize - 4, ".png") != NULL) {
                printf("%s\n", fileName);
                image = LoadImage(file);
                texture = LoadTextureFromImage(image);
                InsertHashMap(textures, fileName, &texture, sizeof(texture));
                UnloadImage(image);
            }
        } else {
            LoadTexturesDir(file);
        }
    }
    UnloadDirectoryFiles(list);
}

void UnloadTextures() {
    HashMapIterator iterator = NewHashMapIterator(textures);
    Pair *pair;
    Texture2D *texture;

    while (pair = NextHashMapIterator(&iterator)) {
        texture = (Texture2D *) pair->value;
        UnloadTexture(*texture);
    }
}

Texture2D *GetTexture(const char *name) {
    return GetHashMap(textures, name);
}
