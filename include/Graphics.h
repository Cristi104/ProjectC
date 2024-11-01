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

typedef struct {
    void (*draw)(void *);
    void (*handleEvent)(void *);
    void (*destroy)(void *);
} GmlibUIComponent;

typedef struct {
    GmlibUIComponent base;
    Texture2D *texture;
    Texture2D *texturePressed;
    void (*onClick)(void *);
    void *params;
    Vector2 position;
    bool prv_pressed;
} GmlibButton;

typedef struct {
    GmlibUIComponent base;
    Texture2D *sliderTexture;
    Texture2D *pointTexture;
    void (*onClick)(float);
    Vector2 slidePosition;
    Vector2 pointPosition;
    bool prv_pressed;
    float percent;
} GmlibSlider;

GAME_EXPORTS void GmlibLoadTexturesDir(const char *directory);
GAME_EXPORTS void GmlibUnloadTextures();
GAME_EXPORTS Texture2D *GmlibGetTexture(const char *name);
GAME_EXPORTS GmlibButton *GmlibCreateButton(const char *name);
GAME_EXPORTS void GmlibHandleButton(GmlibButton *button);
GAME_EXPORTS void GmlibDrawButton(GmlibButton *button);
GAME_EXPORTS void GmlibDestroyButton(GmlibButton *button);
GAME_EXPORTS GmlibSlider *GmlibCreateSlider(const char *sliderTexture, const char *pointTexture);
GAME_EXPORTS void GmlibHandleSlider(GmlibSlider *slider);
GAME_EXPORTS void GmlibDrawSlider(GmlibSlider *slider);
GAME_EXPORTS void GmlibDestroySlider(GmlibSlider *slider);


#ifdef __cplusplus
}
#endif

#endif //PROJECTC_GRAPHICS_H
