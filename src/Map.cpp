//
// Created by Cristi on 11/5/2024.
//

#include "raylib.h"
#include "../include/UI.h"
#include "../include/Map.h"
#include "../include/Resources.h"

namespace GmLib {

    Map::Map() : width(100),
                 height(100){
        this->tiles.reserve(width + 2);
        while (tiles.size() < width + 2){
            std::vector<Tile>& row = this->tiles.emplace_back();
            row.reserve(height + 2);
            while (row.size() < height + 2){
                row.emplace_back();
            }
        }
        this->prerender = LoadRenderTexture(width * 16, height * 16);
        this->update();
    }

    void Map::update() {
        Rectangle src = {0, 0, 16, 16}, dest = {0, 0, 16, 16};
        Texture2D *texture[] = {Resources::getTexture("Dirt.png"), Resources::getTexture("Grass.png")};
        BeginTextureMode(this->prerender);
        for (unsigned int x = 1; x < this->width - 1; x++) {
            dest.x = 16 * x;
            for (unsigned int y = 1; y < this->height - 1; y++) {
                //random sprites
                src.x = 16 * ((x + y * 3) % 5);

                // main tile texture
                src.y = 0;
                src.width = 16;
                src.height = 16;
                dest.y = 16 * y;
                dest.width = 16;
                dest.height = 16;
                DrawTexturePro(*texture[tiles[x][y].id], src, dest, {0, 0}, 180, WHITE);

                continue;
                // corners
                src.width = 8;
                src.height = 8;
                dest.width = 8;
                dest.height = 8;
                src.y = 48;

                // top right
                if (tiles[x][y].id < tiles[x - 1][y - 1].id && (tiles[x - 1][y - 1].id != tiles[x - 1][y].id && tiles[x - 1][y - 1].id != tiles[x][y - 1].id)) {
                    dest.x -= 8;
                    dest.y -= 8;
                    DrawTexturePro(*texture[tiles[x - 1][y - 1].id], src, dest, {0, 0}, 180, WHITE);
                    dest.x += 8;
                    dest.y += 8;
                }

                // top left
                if (tiles[x][y].id < tiles[x + 1][y - 1].id && (tiles[x + 1][y - 1].id != tiles[x + 1][y].id && tiles[x + 1][y - 1].id != tiles[x][y - 1].id)) {
                    src.x -= 8;
                    dest.y -= 8;
                    DrawTexturePro(*texture[tiles[x + 1][y - 1].id], src, dest, {0, 0}, 180, WHITE);
                    src.x += 8;
                    dest.y += 8;
                }

                // bottom right
                if (tiles[x][y].id < tiles[x - 1][y + 1].id && (tiles[x - 1][y + 1].id != tiles[x - 1][y].id && tiles[x - 1][y + 1].id != tiles[x][y + 1].id)) {
                    dest.x -= 8;
                    src.y += 8;
                    DrawTexturePro(*texture[tiles[x - 1][y + 1].id], src, dest, {0, 0}, 180, WHITE);
                    dest.x += 8;
                    src.y -= 8;
                }

                // bottom left
                if (tiles[x][y].id < tiles[x + 1][y + 1].id && (tiles[x + 1][y + 1].id != tiles[x + 1][y].id && tiles[x + 1][y + 1].id != tiles[x][y + 1].id)) {
                    src.x -= 8;
                    src.y += 8;
                    DrawTexturePro(*texture[tiles[x + 1][y + 1].id], src, dest, {0, 0}, 180, WHITE);
                    src.x += 8;
                    src.y -= 8;
                }

                // edges
                src.height = 16;
                dest.height = 16;
                dest.x -= 8;

                // right
                if (tiles[x][y].id < tiles[x - 1][y].id) {
                    src.y = 32;
                    DrawTexturePro(*texture[tiles[x - 1][y].id], src, dest, {0, 0}, 180, WHITE);
                }

                // left
                if (tiles[x][y].id < tiles[x + 1][y].id) {
                    src.y = 32;
                    src.x += 8;
                    dest.x += 8;
                    DrawTexturePro(*texture[tiles[x + 1][y].id], src, dest, {0, 0}, 180, WHITE);
                    src.x -= 8;
                    dest.x -= 8;
                }

                dest.x += 8;
                src.width = 16;
                src.height = 8;
                dest.width = 16;
                dest.height = 8;
                dest.y -= 8;

                // top
                if (tiles[x][y].id < tiles[x][y - 1].id) {
                    src.y = 16;
                    DrawTexturePro(*texture[tiles[x][y - 1].id], src, dest, {0, 0}, 180, WHITE);
                }

                // bottom
                if (tiles[x][y].id < tiles[x][y + 1].id) {
                    src.y = 24;
                    dest.y += 8;
                    DrawTexturePro(*texture[tiles[x][y + 1].id], src, dest, {0, 0}, 180, WHITE);
                    dest.y -= 8;
                }
                dest.y += 8;
            }
        }
        EndTextureMode();

    }

    void Map::draw() {
        BeginMode2D(this->camera);
        DrawTextureEx(this->prerender.texture, {0, 0}, 0, 1,
                      WHITE);
        EndMode2D();
    }

    void Map::handle() {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            this->camera.zoom += 0.03;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            this->camera.zoom -= 0.03;
        }
        if (IsKeyDown(KEY_W)) {
            this->camera.target.y -= 10;
        }
        if (IsKeyDown(KEY_A)) {
            this->camera.target.x -= 10;
        }
        if (IsKeyDown(KEY_S)) {
            this->camera.target.y += 10;
        }
        if (IsKeyDown(KEY_D)) {
            this->camera.target.x += 10;
        }
        if (IsKeyReleased(KEY_Z)) {
            Vector2 coords = this->mouseToTileCoords();
            printf("coords: %f, %f\n", coords.x, coords.y);
        }
    }

    Vector2 Map::mouseToTileCoords() {
        Vector2 coords = GetScreenToWorld2D(GetMousePosition(), this->camera);
        return {coords.x / 16 + 1, this->height - 2 - (coords.y / 16)};
    }
}
