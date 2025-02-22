//
// Created by Cristi on 12/9/2024.
//

#ifndef PROJECTC_RESOURCES_H
#define PROJECTC_RESOURCES_H

#include <map>
#include <string>
#include <memory>
#include "raylib.h"
#include "Game_exports.h"

namespace GmLib {
    class GAME_EXPORTS Resources{
    public:
        static std::map<std::string, std::shared_ptr<Texture2D>> textures;
        static std::map<std::string, std::shared_ptr<Font>> fonts;

        static void Load(const std::string &directory);
        static void Unload();
        static std::weak_ptr<Texture2D> getTexture(const std::string &fileName);
        static std::weak_ptr<Font> getFont(const std::string &fileName);
    };
}

#endif //PROJECTC_RESOURCES_H
