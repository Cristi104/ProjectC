#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "include/DataStructs.h"
#include "include/SystemFunc.h"
#include "include/UI.h"
#include "include/Game.h"

int main() {
    InitWindow(800, 600, "Hello World");
    SetTargetFPS(60);
    GmlibSettingsInit();
//    GmlibSettingsApply();
    GmlibLoadAssets("../res");

    GmlibText *text = GmlibTextCreate("Lorem ipsum testus maximus", (Vector2) {10, 10}, NULL, 8, 20);
    GmlibMap map = GmlibMapCreate(11, 11);

    Camera2D camera = {{0, 0}, {0, 0}, 0, 1};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            camera.zoom += 0.03;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            camera.zoom -= 0.03;
        }
        if (IsKeyDown(KEY_W)) {
            camera.offset.y += 10;
        }
        if (IsKeyDown(KEY_A)) {
            camera.offset.x += 10;
        }
        if (IsKeyDown(KEY_S)) {
            camera.offset.y -= 10;
        }
        if (IsKeyDown(KEY_D)) {
            camera.offset.x -= 10;
        }

        BeginMode2D(camera);

        GmlibMapDraw(map);

        EndMode2D();

        GmlibTextDraw(text);
//        DrawTexturePro(*GmlibGetTexture("Grass.png"), (Rectangle) {0, 0, 256, 256}, (Rectangle) {0, 0, 512, 512}, (Vector2) {0, 0}, 0, WHITE);
        DrawFPS(settings.resolutionWidth - 100, 0);
        EndDrawing();
    }

    GmlibMapDestory(map);
    GmlibUnloadAssets();
    GmlibSettingsLog();
    CloseWindow();
    GmlibTextDestroy(text);

    return 0;
}
