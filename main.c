#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "include/DataStructs.h"
#include "include/SystemFunc.h"
#include "include/UI.h"
#include "include/Game.h"

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(800, 600, "Hello World");
//    SetTargetFPS(60);
    GmlibSettingsInit();
    GmlibSettingsApply();
    GmlibLoadAssets("../res");
    GmlibMap map = GmlibMapCreate(100, 100);
    Camera2D uiCamera = {{0, 0}, {0, 0}, 0, settings.scaleWidth};
    Texture2D *texture = GmlibGetTexture("Point.png");
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(GRAY);

        GmlibMapHandle(&map);
        GmlibMapDraw(map);

        BeginMode2D(uiCamera);

        DrawFPS(960 - 100, 0);

        EndMode2D();

        EndDrawing();
    }

    GmlibMapDestory(map);
    GmlibUnloadAssets();
    GmlibSettingsLog();
    CloseWindow();

    return 0;
}
