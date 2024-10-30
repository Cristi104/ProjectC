//
// Created by cristi on 30.10.2024.
//

#ifndef PROJECTC_GRAPHICS_H
#define PROJECTC_GRAPHICS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Game_exports.h"

GAME_EXPORTS void LoadTexturesDir(const char *directory);

GAME_EXPORTS void UnloadTextures();

#ifdef __cplusplus
}
#endif

#endif //PROJECTC_GRAPHICS_H
