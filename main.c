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
//    settings.borderless = true;
//    settings.fullscreen = false;
    GmlibSettingsApply();
    GmlibLoadAssets("../res");
//    GmlibPanel *panel = GmlibPanelCreate(NULL, (Rectangle) {0, 0, 480, 270});
//    GmlibArrayAppend(panel->components, GmlibTextCreate("Lorem ipsum testus maximus", (Vector2) {10, 10}, NULL, 8, 20),
//                     0);
//    GmlibArrayAppend(panel->components, GmlibButtonCreate(NULL), 0);
//    GmlibArrayAppend(panel->components, GmlibSliderCreate(NULL, NULL), 0);
//    GmlibArrayAppend(panel->components, GmlibTextBoxCreate(NULL, NULL), 0);
//    GmlibArrayAppend(panel->components, GmlibCheckBoxCreate(NULL), 0);
    GmlibMap map = GmlibMapCreate(100, 100);
//    GmlibMapUpdate(map);
    Camera2D camera = {{settings.resolutionWidth / 2, settings.resolutionHeight / 2}, {0, 0}, 0, 1};
    Camera2D uiCamera = {{0, 0}, {0, 0}, 0, settings.scaleWidth};
    Vector2 position = {0, 0};
    Texture2D *texture = GmlibGetTexture("Point.png");
    bool fixed = false;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);

        if (IsKeyReleased(KEY_Q)) {
            fixed = !fixed;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            camera.zoom += 0.03;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            camera.zoom -= 0.03;
        }
        if (IsKeyDown(KEY_W)) {
//            camera.offset.y += 10;
            if (fixed) {
                position.y -= 10;
            } else {
                camera.target.y -= 10;
            }
        }
        if (IsKeyDown(KEY_A)) {
//            camera.offset.x += 10;
            if (fixed) {
                position.x -= 10;
            } else {
                camera.target.x -= 10;
            }
        }
        if (IsKeyDown(KEY_S)) {
//            camera.offset.y -= 10;
            if (fixed) {
                position.y += 10;
            } else {
                camera.target.y += 10;
            }
        }
        if (IsKeyDown(KEY_D)) {
//            camera.offset.x -= 10;
            if (fixed) {
                position.x += 10;
            } else {
                camera.target.x += 10;
            }
        }
        if (fixed) {
            camera.target = position;
        }
        BeginMode2D(camera);

        GmlibMapDraw(map);
        DrawTextureV(*texture, position, WHITE);

        EndMode2D();
        BeginMode2D(uiCamera);
        DrawFPS(960 - 700, 0);
//        GmlibTextDraw(text);
//        GmlibPanelHandle(panel);
//        GmlibPanelDraw(panel);
        EndMode2D();
//        DrawTexturePro(*GmlibGetTexture("Grass.png"), (Rectangle) {0, 0, 256, 256}, (Rectangle) {0, 0, 512, 512}, (Vector2) {0, 0}, 0, WHITE);
        EndDrawing();
    }

//    GmlibPanelDestory(panel);
    GmlibMapDestory(map);
    GmlibUnloadAssets();
    GmlibSettingsLog();
    CloseWindow();

    return 0;
}
