//
// Created by Cristi on 11/5/2024.
//

#include "stdlib.h"
#include "raylib.h"
#include "../include/UI.h"
#include "../include/Game.h"

GmlibMap GmlibMapCreate(unsigned int width, unsigned int height) {
    GmlibMap map;

    map.width = width;
    map.height = height;

    map.tiles = malloc(height * sizeof(GmlibTile *));
    for (unsigned int i = 0; i < height; i++) {
        map.tiles[i] = malloc(width * sizeof(GmlibTile));
        for (unsigned int j = 0; j < height; j++) {
            map.tiles[i][j] = GmlibTileCreate(0);
        }
    }

    return map;
}

void GmlibMapDraw(GmlibMap map) {
    Rectangle src, dest;
    Texture2D *texture = GmlibGetTexture("Grass.png");

    src = (Rectangle) {0, 0, 16, 16};
    dest = (Rectangle) {0, 0, 16 * settings.scaleWidth, 16 * settings.scaleHeight};
    for (unsigned int y = 0; y < map.height; y++) {
        for (unsigned int x = 0; x < map.width; x++) {
            src.x = 16 * ((x + y * 3) % 5);
            dest.x = 16 * x * settings.scaleWidth;
            DrawTexturePro(*texture, src, dest, (Vector2) {0, 0}, 0, WHITE);
        }
        dest.y = 16 * y * settings.scaleHeight;
    }
}

void GmlibMapDestory(GmlibMap map) {
    for (unsigned int y = 0; y < map.height; y++) {
        for (unsigned int x = 0; x < map.width; x++) {
            GmlibTileDestroy(map.tiles[y][x]);
        }
        free(map.tiles[y]);
    }
    free(map.tiles);
}
