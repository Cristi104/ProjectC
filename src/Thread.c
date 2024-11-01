//
// Created by Cristi on 10/28/2024.
//
#include "../include/SystemFunc.h"

#ifdef WIN32

#include <Windows.h>

GmlibThread GmlibThreadCreate(void (*main)(void *), void *data) {
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

void GmlibThreadJoin(GmlibThread *thread) {
    WaitForSingleObject(thread->handle, INFINITE);
    CloseHandle(thread->handle);
    thread->handle = NULL;
    thread->threadId = 0;
}

GmlibMutex GmlibMutexCreate() {
    HANDLE mutex;
    mutex = CreateMutex(NULL, FALSE, NULL);
    return mutex;
}

void GmlibMutexDestory(GmlibMutex mutex) {
    CloseHandle(mutex);
}

void GmlibMutexLock(GmlibMutex mutex) {
    WaitForSingleObject(mutex, INFINITE);
}

void GmlibMutexUnlock(GmlibMutex mutex) {
    ReleaseMutex(mutex);
}

#elif defined(unix) || defined(__APPLE__)

#include <stdlib.h>
#include <pthread.h>

GmlibThread GmlibThreadCreate(void (*main)(void *), void *data) {
    GmlibThread thread = malloc(sizeof(pthread_t));
    pthread_create(thread, NULL, (void *(*)(void *)) main, data);
    return thread;
}

void GmlibThreadJoin(GmlibThread *thread) {
    pthread_join(**thread, NULL);
    free(*thread);
    *thread = NULL;
}

GmlibMutex GmlibMutexCreate() {
    GmlibMutex mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex, NULL);
    return mutex;
}

void GmlibMutexDestroy(GmlibMutex mutex) {
    pthread_mutex_destroy(mutex);
    free(mutex);
}

void GmlibMutexLock(GmlibMutex mutex) {
    pthread_mutex_lock(mutex);
}

void GmlibMutexUnlock(GmlibMutex mutex) {
    pthread_mutex_unlock(mutex);
}

#endif
