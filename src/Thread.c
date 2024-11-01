//
// Created by Cristi on 10/28/2024.
//
#include "../include/SystemFunc.h"

#ifdef WIN32

#include <Windows.h>

GmlibThread GmlibNewThread(void (*main)(void *), void *data) {
    GmlibThread thread;
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

void GmlibJoinThread(GmlibThread *thread) {
    WaitForSingleObject(thread->handle, INFINITE);
    CloseHandle(thread->handle);
    thread->handle = NULL;
    thread->threadId = 0;
}

GmlibMutex GmlibNewMutex() {
    HANDLE mutex;
    mutex = CreateMutex(NULL, FALSE, NULL);
    return mutex;
}

void GmlibFreeMutex(GmlibMutex mutex) {
    CloseHandle(mutex);
}

void GmlibLockMutex(GmlibMutex mutex) {
    WaitForSingleObject(mutex, INFINITE);
}

void GmlibUnlockMutex(GmlibMutex mutex) {
    ReleaseMutex(mutex);
}

#elif defined(unix) || defined(__APPLE__)

#include <stdlib.h>
#include <pthread.h>

GmlibThread GmlibNewThread(void (*main)(void *), void *data) {
    GmlibThread thread = malloc(sizeof(pthread_t));
    pthread_create(thread, NULL, (void *(*)(void *)) main, data);
    return thread;
}

void GmlibJoinThread(GmlibThread *thread) {
    pthread_join(**thread, NULL);
    free(*thread);
    *thread = NULL;
}

GmlibMutex GmlibNewMutex() {
    GmlibMutex mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex, NULL);
    return mutex;
}

void GmlibFreeMutex(GmlibMutex mutex) {
    pthread_mutex_destroy(mutex);
    free(mutex);
}

void GmlibLockMutex(GmlibMutex mutex) {
    pthread_mutex_lock(mutex);
}

void GmlibUnlockMutex(GmlibMutex mutex) {
    pthread_mutex_unlock(mutex);
}

#endif
