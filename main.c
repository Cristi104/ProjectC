#include <stdio.h>
#include "raylib.h"
#include "include/LibTest.h"


int main() {
    InitWindow(800, 600, "Hello World");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    testFunc();
    
    printf("Hello, World!\n");
    return 0;
}
