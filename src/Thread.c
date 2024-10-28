//
// Created by Cristi on 10/28/2024.
//
#include <Windows.h>
#include "../include/SystemFunc.h"

#ifdef WIN32

typedef struct prv_ThreadData {
    void (*main)(void *);

    void *data;
} prv_ThreadData;

static DWORD WINAPI threadInit(LPVOID parameters) {
    HANDLE stdout;
    prv_ThreadData *data;
    prv_ThreadData copy;

    data = parameters;
    copy.main = data->main;
    copy.data = data->data;

    stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (stdout == INVALID_HANDLE_VALUE) {
        return 1;
    }

    copy.main(copy.data);

    return 0;
}

Thread NewThread(void (*main)(void *), void *data) {
    Thread thread;
    prv_ThreadData threadData = {main, data};

    thread.handle = CreateThread(
            NULL,
            0,
            threadInit,
            &threadData,
            0,
            &thread.threadId);

    if (thread.handle == NULL) {
        thread.threadId = 0;
    }

    return thread;
}

void JoinThread(Thread *thread) {
    TerminateThread(thread->handle, 0);
    WaitForSingleObject(thread->handle, INFINITE);
    CloseHandle(thread->handle);
}


#endif
