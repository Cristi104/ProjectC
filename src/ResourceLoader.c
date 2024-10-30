//
// Created by cristi on 30.10.2024.
//

#include <string.h>
#include <stdio.h>
#include "raylib.h"
#include "../include/DataStructs.h"

static HashMap *textures = NULL;

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
                image = LoadImage(file);
                texture = LoadTextureFromImage(image);
                InsertHashMap(textures, fileName, &texture, sizeof(texture));

                UnloadTexture(texture);

                UnloadImage(image);
            }
        } else {
            LoadTexturesDir(file);
        }
    }
    UnloadDirectoryFiles(list);
}

void UnloadTextures() {
    //need HashMap iterator for this function
}
