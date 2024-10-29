//
// Created by Cristi on 10/28/2024.
//
#include "../include/SystemFunc.h"

#ifdef WIN32

#include <Windows.h>

Thread NewThread(void (*main)(void *), void *data) {
    Thread thread;
    void *test;

    thread.handle = CreateThread(
            NULL,
            0,
            (LPTHREAD_START_ROUTINE) main,
            data,
            0,
            &thread.threadId);

    if (thread.handle == NULL) {
        thread.threadId = 0;
    }

    return thread;
}

void JoinThread(Thread *thread) {
    WaitForSingleObject(thread->handle, INFINITE);
    CloseHandle(thread->handle);
}

Mutex NewMutex() {
    HANDLE mutex;
    mutex = CreateMutex(NULL, FALSE, NULL);
    return mutex;
}

void FreeMutex(Mutex mutex) {
    CloseHandle(mutex);
}

void LockMutex(Mutex mutex) {
    WaitForSingleObject(mutex, INFINITE);
}

void UnlockMutex(Mutex mutex) {
    ReleaseMutex(mutex);
}

#elif defined(unix)

Thread NewThread(void (*main)(void *), void *data){

}

void JoinThread(Thread *thread){

}

Mutex NewMutex(){

}

void FreeMutex(Mutex mutex){

}

void LockMutex(Mutex mutex){

}

void UnlockMutex(Mutex mutex){

}

#endif
