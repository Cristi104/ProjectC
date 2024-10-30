#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "include/DataStructs.h"
#include "include/SystemFunc.h"

int main() {
    InitWindow(800, 600, "Hello World");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
//
//    char *keys[] = {"abc", "dfg", "asdg", "54rf", "45reds"};
//    int values[] = {1, 2, 3, 4, 5,};
//
//    HashMap *hashMap = NewHashMap(10, false);
//    for (int i = 0; i < 5; i++) {
//        InsertHashMap(hashMap, keys[i], &values[i], 0);
//    }
//    for (int i = 0; i < 5; i++) {
//        printf("%i\n", *(int *) GetHashMap(hashMap, keys[i]));
//        (*(int *) GetHashMap(hashMap, keys[i]))++;
//    }
//    FreeHashMap(hashMap);
//    for (int i = 0; i < 5; i++) {
//        printf("%i\n", values[i]);
//    }
//    Vector *vector = NewVector(5, false);
//    for (int i = 0; i < 5; i++) {
//        AppendVector(vector, &values[i], 0);
//    }
//    for (int i = 0; i < 5; i++) {
//        printf("%i\n", *(int *) vector->array[i]);
//        (*(int *) vector->array[i])++;
//    }
//    FreeVector(vector);
//    for (int i = 0; i < 5; i++) {
//        printf("%i\n", values[i]);
//    }
    return 0;
}
