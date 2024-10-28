#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "raylib.h"
#include "include/DataStructs.h"
#include "include/SystemFunc.h"

void testFunc(void *arg) {
    ((char *) arg)[2] = '\n';
    printf("%s\n", (char *) arg);
}

int main() {
    InitWindow(800, 600, "Hello World");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    char *arg = malloc(101);
    strcpy_s(arg, 10, "it works!");

    Thread thread = NewThread(&testFunc, arg);
    printf("%s\n", (char *) arg);
    printf("%s\n", (char *) arg);
    JoinThread(&thread);

    free(arg);
    return 0;
}
