//
// Created by Cristi on 11/5/2024.
//

#ifndef PROJECTC_GAME_H
#define PROJECTC_GAME_H

#include "DataStructs.h"
#include "raylib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int test;
} GmlibMapObject;

typedef struct {
    GmlibArray *objects;
    unsigned int id;
} GmlibTile;

typedef struct {
    GmlibTile **tiles;
    RenderTexture2D prerender;
    unsigned int width;
    unsigned int height;
} GmlibMap;

GAME_EXPORTS GmlibTile GmlibTileCreate(unsigned int id);
GAME_EXPORTS void GmlibTileDestroy(GmlibTile tile);
GAME_EXPORTS GmlibMap GmlibMapCreate(unsigned int width, unsigned int height);
GAME_EXPORTS void GmlibMapDraw(GmlibMap map);
GAME_EXPORTS void GmlibMapUpdate(GmlibMap map);
GAME_EXPORTS void GmlibMapDestory(GmlibMap map);

#ifdef __cplusplus
}
#endif

#endif //PROJECTC_GAME_H
