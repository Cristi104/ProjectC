#include <stdio.h>
#include "raylib.h"
#include "include/DataStructs.h"


int main() {
    InitWindow(800, 600, "Hello World");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    char *keys[] = {"abc", "aaa", "3", "asdf", "4sa"};
    int values[] = {1, 2, 3, 4, 5,};
    HashMap *test = newHashMap(2);
    for (int i = 0; i < 5; i++) {
        hashMapSet(test, keys[i], &values[i], sizeof(int));
    }
    for (int i = 0; i < 5; i++) {
        printf("%i\n", *(int *) hashMapGet(test, keys[i]));
    }
    printf("%i\n", *(int *) hashMapGet(test, "abc"));

    printf("Hello, World!\n");
    return 0;
}
