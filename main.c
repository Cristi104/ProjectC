#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "include/DataStructs.h"
#include "include/SystemFunc.h"
#include "include/UI.h"

int main() {
    InitWindow(800, 600, "Hello World");
    SetTargetFPS(60);
    GmlibSettingsInit();
    GmlibSettingsApply();
    GmlibLoadAssets("../res");

    GmlibText *text = GmlibTextCreate("Lorem ipsum testus maximus", (Vector2) {10, 10}, NULL, 8, 20);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);
        GmlibTextDraw(text);

        DrawFPS(settings.resolutionWidth - 100, 0);
        EndDrawing();
    }

    GmlibTextDestroy(text);
    GmlibUnloadAssets();
    GmlibSettingsLog();
    CloseWindow();

    return 0;
}
