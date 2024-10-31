//
// Created by cristi on 30.10.2024.
//

#ifndef PROJECTC_GRAPHICS_H
#define PROJECTC_GRAPHICS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Game_exports.h"
#include "raylib.h"

typedef struct Button {
    Texture2D *texture;
    Texture2D *texturePressed;
    void (*onClick)(void *);
    void *params;
    Vector2 position;
    bool prv_pressed;
} Button;

GAME_EXPORTS void LoadTexturesDir(const char *directory);
GAME_EXPORTS void UnloadTextures();
GAME_EXPORTS Texture2D *GetTexture(const char *name);
GAME_EXPORTS Button *CreateButton(const char *name);
GAME_EXPORTS void HandleButton(Button *button);
GAME_EXPORTS void DrawButton(Button *button);
GAME_EXPORTS void DestroyButton(Button *button);


#ifdef __cplusplus
}
#endif

#endif //PROJECTC_GRAPHICS_H
