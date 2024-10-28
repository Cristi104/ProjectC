#include <stdio.h>
#include <string.h>
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
//    HashMap *test = NewHashMap(2);
//    for (int i = 0; i < 5; i++) {
//        InsertHashMap(test, keys[i], &values[i], sizeof(int));
//    }
//    for (int i = 0; i < 5; i++) {
//        printf("%i\n", *(int *) GetHashMap(test, keys[i]));
//    }
//    printf("%i\n", *(int *) GetHashMap(test, "abc"));
//    FreeHashMap(test);

    Vector *vector = NewVector(0);
    for (int i = 0; i < 5; i++) {
        AppendVector(vector, keys[i], strlen(keys[i]) + 1);
    }
    InsertVector(vector, 3, keys[0], strlen(keys[0]) + 1);
    DeleteVector(vector, 2);
    for (int i = 0; i < vector->size; i++) {
        printf("%s\n", (char *) vector->array[i]);
    }
    FreeVector(vector);

    printf("Hello, World!\n");
    return 0;
}
