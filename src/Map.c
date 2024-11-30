//
// Created by Cristi on 11/5/2024.
//

#include <stdio.h>
#include "stdlib.h"
#include "raylib.h"
#include "../include/UI.h"
#include "../include/Game.h"

Vector2 GetMouseTilePosition(GmlibMap map) {
    Vector2 coords = GetScreenToWorld2D(GetMousePosition(), map.camera);
    return (Vector2) {(int) coords.x / 16, (int) coords.y / 16};
}

GmlibMap GmlibMapCreate(unsigned int width, unsigned int height) {
    GmlibMap map;

    map.width = width;
    map.height = height;

    map.tiles = malloc(height * sizeof(GmlibTile *));
    for (unsigned int i = 0; i < height; i++) {
        map.tiles[i] = malloc(width * sizeof(GmlibTile));
        for (unsigned int j = 0; j < height; j++) {
            if (i * j * (width - 1 - i) * (height - 1 - j) == 0) {
                map.tiles[i][j] = GmlibTileCreate(0);
            } else {
                map.tiles[i][j] = GmlibTileCreate(rand() % 2);
            }
        }
    }

    map.prerender = LoadRenderTexture(16 * width, 16 * height);

    map.camera.offset.x = settings.resolutionWidth / 2;
    map.camera.offset.y = settings.resolutionHeight / 2;
    map.camera.target.x = 0;
    map.camera.target.y = 0;
    map.camera.rotation = 0;
    map.camera.zoom = 1;

    GmlibMapUpdate(&map);
    return map;
}

void GmlibMapUpdate(GmlibMap *map) {
    Rectangle src, dest;
    Texture2D *texture[] = {GmlibGetTexture("Dirt.png"), GmlibGetTexture("Grass.png")};
    GmlibTile **tiles = map->tiles;
    src = (Rectangle) {0, 0, 16, 16};
    dest = (Rectangle) {0, 0, 16, 16};
    BeginTextureMode(map->prerender);
    for (unsigned int y = 1; y < map->height - 1; y++) {
        for (unsigned int x = 1; x < map->width - 1; x++) {
            src.x = 16 * ((x + y * 3) % 5);
            src.y = 0;
            src.width = 16;
            src.height = 16;
            dest.x = 16 * (x + 1);
            dest.width = 16;
            dest.height = 16;

            DrawTexturePro(*texture[tiles[y][x].id], src, dest, (Vector2) {0, 0}, 0, WHITE);
//            continue;
            src.width = 8;
            src.height = 8;
            dest.width = 8;
            dest.height = 8;
            src.y = 48;
            if (tiles[y][x].id < tiles[y - 1][x - 1].id) {
                src.x += 8;
                src.y += 8;
                DrawTexturePro(*texture[tiles[y - 1][x - 1].id], src, dest, (Vector2) {0, 0}, 0, WHITE);
                src.x -= 8;
                src.y -= 8;
            }
            if (tiles[y][x].id < tiles[y - 1][x + 1].id) {
                src.y += 8;
                dest.x += 8;
                DrawTexturePro(*texture[tiles[y - 1][x + 1].id], src, dest, (Vector2) {0, 0}, 0, WHITE);
                src.y -= 8;
                dest.x -= 8;
            }
            if (tiles[y][x].id < tiles[y + 1][x - 1].id) {
                src.x += 8;
                dest.y += 8;
                DrawTexturePro(*texture[tiles[y + 1][x - 1].id], src, dest, (Vector2) {0, 0}, 0, WHITE);
                src.x -= 8;
                dest.y -= 8;
            }
            if (tiles[y][x].id < tiles[y + 1][x + 1].id) {
                dest.x += 8;
                dest.y += 8;
                DrawTexturePro(*texture[tiles[y + 1][x + 1].id], src, dest, (Vector2) {0, 0}, 0, WHITE);
                dest.x -= 8;
                dest.y -= 8;
            }
            src.height = 16;
            dest.height = 16;
            if (tiles[y][x].id < tiles[y][x - 1].id) {
                src.y = 32;
                src.x += 8;
                DrawTexturePro(*texture[tiles[y][x - 1].id], src, dest, (Vector2) {0, 0}, 0, WHITE);
                src.x -= 8;
            }
            if (tiles[y][x].id < tiles[y][x + 1].id) {
                src.y = 32;
                dest.x += 8;
                DrawTexturePro(*texture[tiles[y][x + 1].id], src, dest, (Vector2) {0, 0}, 0, WHITE);
                dest.x -= 8;
            }
            src.width = 16;
            src.height = 8;
            dest.width = 16;
            dest.height = 8;
            if (tiles[y][x].id < tiles[y - 1][x].id) {
                src.y = 24;
                DrawTexturePro(*texture[tiles[y - 1][x].id], src, dest, (Vector2) {0, 0}, 0, WHITE);
            }
            if (tiles[y][x].id < tiles[y + 1][x].id) {
                src.y = 16;
                dest.y += 8;
                DrawTexturePro(*texture[tiles[y + 1][x].id], src, dest, (Vector2) {0, 0}, 0, WHITE);
                dest.y -= 8;
            }
        }
        dest.y = 16 * y;
    }
    EndTextureMode();
}

void GmlibMapDraw(GmlibMap map) {
    BeginMode2D(map.camera);
    DrawTextureEx(map.prerender.texture, (Vector2) {map.prerender.texture.width, map.prerender.texture.height}, 180, 1,
                  WHITE);
    EndMode2D();
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

void GmlibMapHandle(GmlibMap *map) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        map->camera.zoom += 0.03;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        map->camera.zoom -= 0.03;
    }
    if (IsKeyDown(KEY_W)) {
        map->camera.target.y -= 10;
    }
    if (IsKeyDown(KEY_A)) {
        map->camera.target.x -= 10;
    }
    if (IsKeyDown(KEY_S)) {
        map->camera.target.y += 10;
    }
    if (IsKeyDown(KEY_D)) {
        map->camera.target.x += 10;
    }
    if (IsKeyReleased(KEY_Z)) {
        Vector2 coords = GetMouseTilePosition(*map);
        printf("coords: %f, %f\n", coords.x, coords.y);
    }
}
