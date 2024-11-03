#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "include/DataStructs.h"
#include "include/SystemFunc.h"
#include "include/Graphics.h"

int main() {
    InitWindow(800, 600, "Hello World");
    SetTargetFPS(60);
    GmlibSettingsInit();
    GmlibSettingsApply();

    GmlibLoadAssets("../res");

//    GmlibUIComponent *button = (GmlibUIComponent *) GmlibPanelCreate(NULL, CLITERAL(Rectangle) {0, 0, 960 / 2, 540 / 2});
    GmlibUIComponent *button = GmlibButtonCreate(NULL);
    ((GmlibButton *) button)->position = CLITERAL(Rectangle) {100, 100, 32, 16};
//    GmlibUIComponent *button = GmlibCheckBoxCreate(NULL);
//    ((GmlibCheckBox *) button)->position = CLITERAL(Rectangle) {100, 100, 16, 16};
//    GmlibUIComponent *button = GmlibTextBoxCreate(NULL, NULL);
//    ((GmlibTextBox *) button)->position = CLITERAL(Rectangle) {100, 100, 100, 16};
//    GmlibUIComponent *button = GmlibSliderCreate(NULL, NULL);
//    ((GmlibSlider *) button)->slidePosition = CLITERAL(Rectangle) {100, 100, 100, 16};
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        button->handleEvent(button);
        button->draw(button);

        DrawFPS(settings.resolutionWidth - 100, 0);
        EndDrawing();
    }
    button->destroy(button);

    GmlibUnloadAssets();
    CloseWindow();
    GmlibSettingsLog();

    return 0;
}
