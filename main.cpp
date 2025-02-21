#include "raylib.h"
#include "include/Settings.h"
#include "include/Resources.h"
#include "include/Map.h"
#include "include/PerlinNoiseGenerator.h"
#include "include/Settings.h"
#include "include/Floor.h"
#include <iostream>
#include <memory>
int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(800, 600, "Hello World");
    GmLib::Floor fl;
    GmLib::Deserialize(std::cin, "Floor", fl);
    GmLib::Serialize(std::cout, "Floor", fl);
//    Gmlib::Settings::reset();
    GmLib::Settings::load();
    GmLib::Settings::setFullscreen(true);
    GmLib::Settings::setBorderless(true);
    GmLib::Settings::apply();
//    GmLib::Slider
    GmLib::Settings::save();
    GmLib::Resources::Load("../res");
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

    GmLib::Resources::Unload();
    CloseWindow();
    GmLib::Settings::log();
    return 0;
}
