//
// Created by Cristi on 10/28/2024.
//

#ifndef PROJECTC_SYSTEMFUNC_H
#define PROJECTC_SYSTEMFUNC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Game_exports.h"

#ifdef WIN32

typedef struct Thread {
    void *handle;
    unsigned long threadId;
} Thread;

typedef void *Mutex;

#elif defined(unix) || defined(__APPLE__)

#include <pthread.h>

typedef pthread_t *Thread;

typedef pthread_mutex_t *Mutex;

#endif

GAME_EXPORTS Thread NewThread(void (*main)(void *), void *data);
GAME_EXPORTS void JoinThread(Thread *thread);
GAME_EXPORTS Mutex NewMutex();
GAME_EXPORTS void FreeMutex(Mutex mutex);
GAME_EXPORTS void LockMutex(Mutex mutex);
GAME_EXPORTS void UnlockMutex(Mutex mutex);

#ifdef __cplusplus
}
#endif

#endif //PROJECTC_SYSTEMFUNC_H
