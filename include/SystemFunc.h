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

GAME_EXPORTS GmlibThread GmlibThreadCreate(void (*main)(void *), void *data);
GAME_EXPORTS void GmlibThreadJoin(GmlibThread *thread);
GAME_EXPORTS GmlibMutex GmlibMutexCreate();
GAME_EXPORTS void GmlibMutexDestory(GmlibMutex mutex);
GAME_EXPORTS void GmlibMutexLock(GmlibMutex mutex);
GAME_EXPORTS void GmlibMutexUnlock(GmlibMutex mutex);

#ifdef __cplusplus
}
#endif

#endif //PROJECTC_SYSTEMFUNC_H
