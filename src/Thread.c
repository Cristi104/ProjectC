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
    thread->handle = NULL;
    thread->threadId = 0;
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

#include <stdlib.h>
#include <pthread.h>

Thread NewThread(void (*main)(void *), void *data) {
    Thread thread = malloc(sizeof(pthread_t));
    pthread_create(thread, NULL, (void *(*)(void *)) main, data);
    return thread;
}

void JoinThread(Thread *thread) {
    pthread_join(**thread, NULL);
    free(*thread);
    *thread = NULL;
}

Mutex NewMutex() {
    Mutex mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex, NULL);
    return mutex;
}

void FreeMutex(Mutex mutex) {
    pthread_mutex_destroy(mutex);
    free(mutex);
}

void LockMutex(Mutex mutex) {
    pthread_mutex_lock(mutex);
}

void UnlockMutex(Mutex mutex) {
    pthread_mutex_unlock(mutex);
}

#endif
