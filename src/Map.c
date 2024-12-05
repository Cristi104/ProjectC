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
    return (Vector2) {(int) coords.x / 16 + 1, map.height - 2 - ((int) coords.y / 16)};
}

GmlibMap GmlibMapCreate(unsigned int width, unsigned int height) {
    GmlibMap map;

    map.width = width + 2;
    map.height = height + 2;

    map.tiles = malloc((width + 2) * sizeof(GmlibTile *));
    for (unsigned int x = 0; x < width + 2; x++) {
        map.tiles[x] = malloc((height + 2) * sizeof(GmlibTile));
        for (unsigned int y = 0; y < height + 2; y++) {
            if (x * y * (width + 1 - x) * (height + 1 - y) == 0) {
                map.tiles[x][y] = GmlibTileCreate(0);
            } else {
                map.tiles[x][y] = GmlibTileCreate(rand() % 2);
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
    for (unsigned int x = 1; x < map->width - 1; x++) {
        dest.x = 16 * x;
        for (unsigned int y = 1; y < map->height - 1; y++) {
            //random sprites
            src.x = 16 * ((x + y * 3) % 5);

            // main tile texture
            src.y = 0;
            src.width = 16;
            src.height = 16;
            dest.y = 16 * y;
            dest.width = 16;
            dest.height = 16;
            DrawTexturePro(*texture[tiles[x][y].id], src, dest, (Vector2) {0, 0}, 180, WHITE);

            continue;
            // corners
            src.width = 8;
            src.height = 8;
            dest.width = 8;
            dest.height = 8;
            src.y = 48;

            // top right
            if (tiles[x][y].id < tiles[x - 1][y - 1].id && (tiles[x - 1][y - 1].id != tiles[x - 1][y].id && tiles[x - 1][y - 1].id != tiles[x][y - 1].id)) {
                dest.x -= 8;
                dest.y -= 8;
                DrawTexturePro(*texture[tiles[x - 1][y - 1].id], src, dest, (Vector2) {0, 0}, 180, WHITE);
                dest.x += 8;
                dest.y += 8;
            }

            // top left
            if (tiles[x][y].id < tiles[x + 1][y - 1].id && (tiles[x + 1][y - 1].id != tiles[x + 1][y].id && tiles[x + 1][y - 1].id != tiles[x][y - 1].id)) {
                src.x -= 8;
                dest.y -= 8;
                DrawTexturePro(*texture[tiles[x + 1][y - 1].id], src, dest, (Vector2) {0, 0}, 180, WHITE);
                src.x += 8;
                dest.y += 8;
            }

            // bottom right
            if (tiles[x][y].id < tiles[x - 1][y + 1].id && (tiles[x - 1][y + 1].id != tiles[x - 1][y].id && tiles[x - 1][y + 1].id != tiles[x][y + 1].id)) {
                dest.x -= 8;
                src.y += 8;
                DrawTexturePro(*texture[tiles[x - 1][y + 1].id], src, dest, (Vector2) {0, 0}, 180, WHITE);
                dest.x += 8;
                src.y -= 8;
            }

            // bottom left
            if (tiles[x][y].id < tiles[x + 1][y + 1].id && (tiles[x + 1][y + 1].id != tiles[x + 1][y].id && tiles[x + 1][y + 1].id != tiles[x][y + 1].id)) {
                src.x -= 8;
                src.y += 8;
                DrawTexturePro(*texture[tiles[x + 1][y + 1].id], src, dest, (Vector2) {0, 0}, 180, WHITE);
                src.x += 8;
                src.y -= 8;
            }

            // edges
            src.height = 16;
            dest.height = 16;
            dest.x -= 8;

            // right
            if (tiles[x][y].id < tiles[x - 1][y].id) {
                src.y = 32;
                DrawTexturePro(*texture[tiles[x - 1][y].id], src, dest, (Vector2) {0, 0}, 180, WHITE);
            }

            // left
            if (tiles[x][y].id < tiles[x + 1][y].id) {
                src.y = 32;
                src.x += 8;
                dest.x += 8;
                DrawTexturePro(*texture[tiles[x + 1][y].id], src, dest, (Vector2) {0, 0}, 180, WHITE);
                src.x -= 8;
                dest.x -= 8;
            }

            dest.x += 8;
            src.width = 16;
            src.height = 8;
            dest.width = 16;
            dest.height = 8;
            dest.y -= 8;

            // top
            if (tiles[x][y].id < tiles[x][y - 1].id) {
                src.y = 16;
                DrawTexturePro(*texture[tiles[x][y - 1].id], src, dest, (Vector2) {0, 0}, 180, WHITE);
            }

            // bottom
            if (tiles[x][y].id < tiles[x][y + 1].id) {
                src.y = 24;
                dest.y += 8;
                DrawTexturePro(*texture[tiles[x][y + 1].id], src, dest, (Vector2) {0, 0}, 180, WHITE);
                dest.y -= 8;
            }
            dest.y += 8;
        }
    }
    EndTextureMode();
}

void GmlibMapDraw(GmlibMap map) {
    BeginMode2D(map.camera);
    DrawTextureEx(map.prerender.texture, (Vector2) {0, 0}, 0, 1,
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
