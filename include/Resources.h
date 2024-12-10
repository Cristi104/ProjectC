//
// Created by Cristi on 12/9/2024.
//

#ifndef PROJECTC_RESOURCES_H
#define PROJECTC_RESOURCES_H

#include <map>
#include <string>
#include "raylib.h"
#include "Game_exports.h"

namespace GmLib {
    class GAME_EXPORTS Resources{
    public:
        static std::map<std::string, Texture2D*> textures;
        static std::map<std::string, Font*> fonts;

        static void Load(const std::string &directory);
        static void Unload();
        static Texture2D *getTexture(const std::string &fileName);
        static Font *getFont(const std::string &fileName);
    };
}

#endif //PROJECTC_RESOURCES_H
