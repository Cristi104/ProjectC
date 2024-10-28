#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "raylib.h"
#include "include/DataStructs.h"
#include "include/SystemFunc.h"

Mutex mutexTest;

void testFunc(void *arg) {
    LockMutex(mutexTest);
    ((char *) arg)[2] = '\n';
    UnlockMutex(mutexTest);
}

int main() {
//    InitWindow(800, 600, "Hello World");
//
//    while (!WindowShouldClose()) {
//        BeginDrawing();
//        ClearBackground(RAYWHITE);
//        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
//        EndDrawing();
//    }
//
//    CloseWindow();
    char *arg = malloc(100);
    strcpy_s(arg, 10, "it works!");

    mutexTest = NewMutex();

    Thread thread = NewThread(testFunc, arg);
    for (int i = 0; i < 100; i++) {
        printf("%s", arg);
    }

    LockMutex(mutexTest);
    printf("%s", arg);
    UnlockMutex(mutexTest);

    JoinThread(&thread);
    FreeMutex(mutexTest);
    return 0;
}
