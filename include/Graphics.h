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
#include "DataStructs.h"

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
    void (*onClick)(void *, float);
    void *params;
    Vector2 slidePosition;
    Vector2 pointPosition;
    bool prv_pressed;
    float percent;
} GmlibSlider;

typedef struct {
    GmlibUIComponent base;
    Texture2D *background;
    void (*onClick)(void *, char *);
    void *params;
    Vector2 position;
    bool prv_pressed;
    char text[31];
    Font *font;
} GmlibTextBox;

typedef struct {
    GmlibUIComponent base;
    Texture2D *texture;
    Texture2D *textureChecked;
    Vector2 position;
    bool checked;
} GmlibCheckBox;

typedef struct {
    GmlibUIComponent base;
    Texture2D *background;
    Texture2D *border;
    Rectangle location;
    GmlibArray *components;
    bool visible;
} GmlibPanel;

GAME_EXPORTS void GmlibLoadAssets(const char *directory);
GAME_EXPORTS void GmlibUnloadAssets();
GAME_EXPORTS Texture2D *GmlibGetTexture(const char *name);
GAME_EXPORTS Font *GmlibGetFont(const char *name);
GAME_EXPORTS GmlibButton *GmlibButtonCreate(const char *name);
GAME_EXPORTS void GmlibButtonHandle(GmlibButton *button);
GAME_EXPORTS void GmlibButtonDraw(GmlibButton *button);
GAME_EXPORTS void GmlibButtonDestroy(GmlibButton *button);
GAME_EXPORTS GmlibSlider *GmlibSliderCreate(const char *sliderTexture, const char *pointTexture);
GAME_EXPORTS void GmlibSliderHandle(GmlibSlider *slider);
GAME_EXPORTS void GmlibSliderDraw(GmlibSlider *slider);
GAME_EXPORTS void GmlibSliderDestroy(GmlibSlider *slider);
GAME_EXPORTS GmlibTextBox *GmlibTextBoxCreate(const char *backgroundTexture, const char *font);
GAME_EXPORTS void GmlibTextBoxHandle(GmlibTextBox *textBox);
GAME_EXPORTS void GmlibTextBoxDraw(GmlibTextBox *textBox);
GAME_EXPORTS void GmlibTextBoxDestroy(GmlibTextBox *textBox);
GAME_EXPORTS GmlibCheckBox *GmlibCheckBoxCreate(const char *texture);
GAME_EXPORTS void GmlibCheckBoxHandle(GmlibCheckBox *checkBox);
GAME_EXPORTS void GmlibCheckBoxDraw(GmlibCheckBox *checkBox);
GAME_EXPORTS void GmlibCheckBoxDestroy(GmlibCheckBox *checkBox);
GAME_EXPORTS GmlibPanel *GmlibPanelCreate(const char *background);
GAME_EXPORTS void GmlibPanelDraw(GmlibPanel *panel);
GAME_EXPORTS void GmlibPanelHandle(GmlibPanel *panel);
GAME_EXPORTS void GmlibPanelDestory(GmlibPanel *panel);

#ifdef __cplusplus
}
#endif

#endif //PROJECTC_GRAPHICS_H
