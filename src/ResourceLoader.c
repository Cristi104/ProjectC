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

void GmlibLoadAssets(const char *directory) {
    FilePathList list = LoadDirectoryFiles(directory);
    unsigned int nameSize;
    char *file, *fileName;
    Image image;
    Texture2D texture;
    Font font;

    // init hashmaps
    if (textures == NULL) {
        textures = GmlibHashMapCreate(256, true);
    }
    if (fonts == NULL) {
        fonts = GmlibHashMapCreate(256, true);
    }

    // iterate through files
    for (int i = 0; i < list.count; i++) {
        file = list.paths[i];
        fileName = file + strlen(directory) + 1;
        nameSize = strlen(fileName);

        // check if file or dir
        if (strchr(fileName, '.') != NULL) {

            // if .png
            if (strstr(fileName + nameSize - 4, ".png") != NULL) {

                // check if exists
                if (GmlibHashMapGet(textures, fileName)) {
                    image = LoadImage(file);
                    texture = LoadTextureFromImage(image);
                    GmlibHashMapInsert(textures, fileName, &texture, sizeof(texture));
                    UnloadImage(image);
                }
            }

            // if .ttf
            if (strstr(fileName + nameSize - 4, ".ttf") != NULL) {

                // check if exists
                if (GmlibHashMapGet(fonts, fileName)) {
                    font = LoadFont(file);
                    GmlibHashMapInsert(fonts, fileName, &font, sizeof(Font));
                }
            }
        } else {
            // recursive loading
            GmlibLoadAssets(file);
        }
    }
    UnloadDirectoryFiles(list);
}

void GmlibUnloadAssets() {
    GmlibHashMapIterator iterator = GmlibHashMapIteratorCreate(textures);
    GmlibPair *pair;
    Texture2D *texture;
    Font *font;

    // free hashmaps
    while (pair = GmlibHashMapIteratorNext(&iterator)) {
        texture = (Texture2D *) pair->value;
        UnloadTexture(*texture);
    }
    iterator = GmlibHashMapIteratorCreate(fonts);
    while (pair = GmlibHashMapIteratorNext(&iterator)) {
        font = (Font *) pair->value;
        UnloadFont(*font);
    }
}

Texture2D *GmlibGetTexture(const char *name) {
    return GmlibHashMapGet(textures, name);
}

Font *GmlibGetFont(const char *name) {
    return GmlibHashMapGet(fonts, name);
}
