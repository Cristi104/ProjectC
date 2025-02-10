#include "raylib.h"
#include "include/UI.h"
#include "include/Resources.h"
#include "include/Map.h"
#include "include/PerlinNoiseGenerator.h"
#include <iostream>
#include <iomanip>
int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(800, 600, "Hello World");
//    SetTargetFPS(60);
    GmlibSettingsInit();
    GmlibSettingsApply();
    GmLib::Resources::Load("../res");
//    GmlibMap map = GmlibMapCreate(100, 100);
    GmLib::Map map;
//    Camera2D uiCamera = {{0, 0}, {0, 0}, 0, settings.scaleWidth};
//    Texture2D *texture = GmlibGetTexture("Point.png");
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(GRAY);

        map.draw();
        map.handle();

//        BeginMode2D(uiCamera);

        DrawFPS(960 - 100, 0);

//        EndMode2D();

        EndDrawing();
    }

//    GmlibMapDestory(map);
//    GmlibUnloadAssets();
    GmLib::Resources::Unload();
    GmlibSettingsLog();
    CloseWindow();

    std::vector<std::vector<float>> noise = Gmlib::GeneratePerlinNoise(20, 11, 123);
    std::cout << std::fixed << std::setprecision(2);
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            std::cout << std::setw(5) << noise[i][j] << ' ';
        }
//        std::cout << '\n';
    }

    return 0;
}
