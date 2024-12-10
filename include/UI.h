//
// Created by cristi on 30.10.2024.
//

#ifndef PROJECTC_UI_H
#define PROJECTC_UI_H

#include "Game_exports.h"
#include "raylib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    unsigned int resolutionWidth;
    unsigned int resolutionHeight;
    float scaleWidth;
    float scaleHeight;
    bool fullscreen;
    bool borderless;
} GmlibSettings;

GAME_EXPORTS extern GmlibSettings settings;

GAME_EXPORTS void GmlibSettingsInit();                              // Loads settings.txt if it exists otherwise sets settings to default and saves settings
GAME_EXPORTS void GmlibSettingsSave();                              // Saves settings to settings.txt
GAME_EXPORTS void GmlibSettingsApply();                             // Applies settings to the screen
GAME_EXPORTS void GmlibSettingsLog();                               // Logs settings to stdout

#ifdef __cplusplus
}
#endif

#endif //PROJECTC_UI_H
