#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "include/DataStructs.h"
#include "include/SystemFunc.h"
#include "include/Graphics.h"

extern HashMap *textures;

int main() {
    InitWindow(800, 600, "Hello World");
    LoadTexturesDir("../res/textures");

    UIVtable *button = (UIVtable *) CreateButton(NULL);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        button->handleEvent(button);
        button->draw(button);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    button->destroy(button);

    UnloadTextures();
    CloseWindow();

//    FilePathList list = LoadDirectoryFiles("../res/textures");

//    for (int i = 0; i < list.count; i++) {
//        printf("%s\n", list.paths[i]);
//    }
//
//    char *keys[] = {"abc", "dfg", "asdg", "54rf", "45reds"};
//    int values[] = {1, 2, 3, 4, 5,};
//
//    HashMap *hashMap = NewHashMap(10, false);
//    for (int i = 0; i < 5; i++) {
//        InsertHashMap(hashMap, keys[i], &values[i], 0);
//    }
//    HashMapIterator iterator = NewHashMapIterator(hashMap);
//    Pair *pair;
//    while (pair = NextHashMapIterator(&iterator)) {
//        printf("%i\n", *(int *) pair->value);
//    }
//    printf("\n");
//    while (pair = PreviousHashMapIterator(&iterator)) {
//        printf("%i\n", *(int *) pair->value);
//    }
//    printf("\n");
//    while (pair = NextHashMapIterator(&iterator)) {
//        printf("%i\n", *(int *) pair->value);
//    }
//    pair = PreviousHashMapIterator(&iterator);
//    printf("%i\n", *(int *) pair->value);
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
