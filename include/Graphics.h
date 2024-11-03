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
    Rectangle position;
    bool prv_pressed;
} GmlibButton;

typedef struct {
    GmlibUIComponent base;
    Texture2D *sliderTexture;
    Texture2D *pointTexture;
    void (*onClick)(void *, float);
    void *params;
    Rectangle slidePosition;
    float pointPosition;
    bool prv_pressed;
    float percent;
} GmlibSlider;

typedef struct {
    GmlibUIComponent base;
    Texture2D *background;
    void (*onClick)(void *, char *);
    void *params;
    Rectangle position;
    bool prv_pressed;
    char text[31];
    Font *font;
} GmlibTextBox;

typedef struct {
    GmlibUIComponent base;
    Texture2D *texture;
    Texture2D *textureChecked;
    Rectangle position;
    bool checked;
} GmlibCheckBox;

typedef struct {
    GmlibUIComponent base;
    Texture2D *background;
    Texture2D *border;
    Rectangle position;
    GmlibArray *components;
    bool visible;
} GmlibPanel;

typedef struct {
    unsigned int resolutionWidth;
    unsigned int resolutionHeight;
    float scaleWidth;
    float scaleHeight;
    bool fullscreen;
    bool borderless;
} GmlibSettings;

GAME_EXPORTS extern GmlibSettings settings;

GAME_EXPORTS void GmlibLoadAssets(const char *directory);           // Recursively load assets(.png, .ttf, etc.) from a directory
GAME_EXPORTS void GmlibUnloadAssets();                              // Frees all loaded assets from memory
GAME_EXPORTS Texture2D *GmlibGetTexture(const char *name);          // Get a pointer to a loaded texture
GAME_EXPORTS Font *GmlibGetFont(const char *name);                  // Get a pointer to a loaded font
GAME_EXPORTS GmlibButton *GmlibButtonCreate(const char *texture);   // Create a button with a given texture (texture.png and texturePressed.png)
GAME_EXPORTS void GmlibButtonHandle(GmlibButton *button);           // Calls onClick(params) if the button was pressed
GAME_EXPORTS void GmlibButtonDraw(GmlibButton *button);             // Draws the Button to the screen
GAME_EXPORTS void GmlibButtonDestroy(GmlibButton *button);          // Frees the button
GAME_EXPORTS GmlibSlider *GmlibSliderCreate(const char *sliderTexture, const char *pointTexture);   // Create a Slider with the given textures
GAME_EXPORTS void GmlibSliderHandle(GmlibSlider *slider);           // Calls onClick(params, percent) if the slider was let go
GAME_EXPORTS void GmlibSliderDraw(GmlibSlider *slider);             // Draws the slider and point to the screen
GAME_EXPORTS void GmlibSliderDestroy(GmlibSlider *slider);          // Frees the slider
GAME_EXPORTS GmlibTextBox *GmlibTextBoxCreate(const char *backgroundTexture, const char *font); // Create a TextBox with a given background texture and font
GAME_EXPORTS void GmlibTextBoxHandle(GmlibTextBox *textBox);        // if clicked on will start listening for keyboard input on an Enter press will call onClick(params, text)
GAME_EXPORTS void GmlibTextBoxDraw(GmlibTextBox *textBox);          // Draws the textBox and the corresponding text
GAME_EXPORTS void GmlibTextBoxDestroy(GmlibTextBox *textBox);       // Frees the textBox to the screen
GAME_EXPORTS GmlibCheckBox *GmlibCheckBoxCreate(const char *texture);   // Create a CheckBox with a given texture (texture.png and textureChecked.png)
GAME_EXPORTS void GmlibCheckBoxHandle(GmlibCheckBox *checkBox);     // if clicked on will toggle between checked and not checked
GAME_EXPORTS void GmlibCheckBoxDraw(GmlibCheckBox *checkBox);       // Draws the checkBox to the screen
GAME_EXPORTS void GmlibCheckBoxDestroy(GmlibCheckBox *checkBox);    // Frees the checkBox
GAME_EXPORTS GmlibPanel *GmlibPanelCreate(const char *background, Rectangle position);  // Creates a Panel of a given position and background (background.png and backgroundBorder.png)
GAME_EXPORTS void GmlibPanelDraw(GmlibPanel *panel);                // Draws the panel and components (with the order background, components[0], components[1], ...)
GAME_EXPORTS void GmlibPanelHandle(GmlibPanel *panel);              // Calls handle() for every component inside
GAME_EXPORTS void GmlibPanelDestory(GmlibPanel *panel);             // Frees the panel and all components inside
GAME_EXPORTS void GmlibSettingsInit();                              // Loads settings.txt if it exists otherwise sets settings to default and saves settings
GAME_EXPORTS void GmlibSettingsSave();                              // Saves settings to settings.txt
GAME_EXPORTS void GmlibSettingsApply();                             // Applies settings to the screen
GAME_EXPORTS void GmlibSettingsLog();                               // Logs settings to stdout

#ifdef __cplusplus
}
#endif

#endif //PROJECTC_GRAPHICS_H
