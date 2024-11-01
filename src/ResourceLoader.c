//
// Created by cristi on 30.10.2024.
//

#include <string.h>
#include <stdio.h>
#include "raylib.h"
#include "../include/DataStructs.h"
#include "../include/Graphics.h"

static GmlibHashMap *textures = NULL;
static GmlibHashMap *fonts = NULL;

void GmlibLoadAssetsDir(const char *directory) {
    FilePathList list = LoadDirectoryFiles(directory);
    unsigned int nameSize;
    char *file, *fileName;
    Image image;
    Texture2D texture;
    Font font;

    if (textures == NULL) {
        textures = GmlibNewHashMap(256, true);
    }

    if (fonts == NULL) {
        fonts = GmlibNewHashMap(256, true);
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
            if (strstr(fileName + nameSize - 4, ".ttf") != NULL) {
                font = LoadFont(file);
                GmlibInsertHashMap(fonts, fileName, &font, sizeof(Font));
            }
        } else {
            GmlibLoadAssetsDir(file);
        }
    }
    UnloadDirectoryFiles(list);
}

void GmlibUnloadAssets() {
    GmlibHashMapIterator iterator = GmlibNewHashMapIterator(textures);
    GmlibPair *pair;
    Texture2D *texture;
    Font *font;

    while (pair = GmlibNextHashMapIterator(&iterator)) {
        texture = (Texture2D *) pair->value;
        UnloadTexture(*texture);
    }
    iterator = GmlibNewHashMapIterator(fonts);
    while (pair = GmlibNextHashMapIterator(&iterator)) {
        font = (Font *) pair->value;
        UnloadFont(*font);
    }
}

Texture2D *GmlibGetTexture(const char *name) {
    return GmlibGetHashMap(textures, name);
}

Font *GmlibGetFont(const char *name) {
    return GmlibGetHashMap(fonts, name);
}
