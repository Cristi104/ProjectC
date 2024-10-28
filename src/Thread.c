//
// Created by Cristi on 10/28/2024.
//
#include <stdio.h>
#include <Windows.h>
#include "../include/SystemFunc.h"

#ifdef WIN32

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


#endif
