//
// Created by Cristi on 12/10/2024.
//

#ifndef PROJECTC_TILE_H
#define PROJECTC_TILE_H

#include <vector>
#include "raylib.h"
#include "Game_exports.h"

namespace GmLib {
    class GAME_EXPORTS Tile{
    private:
        static std::vector<Texture2D*> floorTextures;
        static void init();
    public:
        unsigned int floorId = 0;
        unsigned int wallId = 0;
        explicit Tile(unsigned int floorId);
    };
}

#endif //PROJECTC_TILE_H
