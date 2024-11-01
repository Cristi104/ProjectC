//
// Created by cristi on 30.10.2024.
//

#include <string.h>
#include "raylib.h"
#include "../include/DataStructs.h"
#include "../include/Graphics.h"

static GmlibHashMap *textures = NULL;

void GmlibLoadTexturesDir(const char *directory) {
    FilePathList list = LoadDirectoryFiles(directory);
    unsigned int nameSize;
    char *file, *fileName;
    Image image;
    Texture2D texture;

    if (textures == NULL) {
        textures = GmlibNewHashMap(256, true);
    }

    for (int i = 0; i < list.count; i++) {
        file = list.paths[i];
        fileName = file + strlen(directory) + 1;
        nameSize = strlen(fileName);

        if (strchr(fileName, '.') != NULL) {
            if (strstr(fileName + nameSize - 4, ".png") != NULL) {
                image = LoadImage(file);
                texture = LoadTextureFromImage(image);
                GmlibInsertHashMap(textures, fileName, &texture, sizeof(texture));
                UnloadImage(image);
            }
        } else {
            GmlibLoadTexturesDir(file);
        }
    }
    UnloadDirectoryFiles(list);
}

void GmlibUnloadTextures() {
    GmlibHashMapIterator iterator = GmlibNewHashMapIterator(textures);
    GmlibPair *pair;
    Texture2D *texture;

    while (pair = GmlibNextHashMapIterator(&iterator)) {
        texture = (Texture2D *) pair->value;
        UnloadTexture(*texture);
    }
}

Texture2D *GmlibGetTexture(const char *name) {
    return GmlibGetHashMap(textures, name);
}
