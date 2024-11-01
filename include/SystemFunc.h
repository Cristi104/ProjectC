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

typedef struct {
    void *handle;
    unsigned long threadId;
} GmlibThread;

typedef void *GmlibMutex;

#elif defined(unix) || defined(__APPLE__)

#include <pthread.h>

typedef pthread_t *GmlibThread;

typedef pthread_mutex_t *GmlibMutex;

#endif

GAME_EXPORTS GmlibThread GmlibNewThread(void (*main)(void *), void *data);
GAME_EXPORTS void GmlibJoinThread(GmlibThread *thread);
GAME_EXPORTS GmlibMutex GmlibNewMutex();
GAME_EXPORTS void GmlibFreeMutex(GmlibMutex mutex);
GAME_EXPORTS void GmlibLockMutex(GmlibMutex mutex);
GAME_EXPORTS void GmlibUnlockMutex(GmlibMutex mutex);

#ifdef __cplusplus
}
#endif

#endif //PROJECTC_SYSTEMFUNC_H
