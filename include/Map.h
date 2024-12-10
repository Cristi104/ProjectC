//
// Created by Cristi on 12/10/2024.
//

#ifndef PROJECTC_MAP_H
#define PROJECTC_MAP_H

#include <vector>
#include "raylib.h"
#include "Tile.h"
#include "Game_exports.h"

namespace GmLib {
    class GAME_EXPORTS Map{
    private:
        std::vector<std::vector<Tile>>tiles;
        RenderTexture2D prerender;
        unsigned int width;
        unsigned int height;
        Camera2D camera;
    public:
        Map();
        void update();
        void draw();
        void handle();
        Vector2 mouseToTileCoords();
    };
}

#endif //PROJECTC_MAP_H
