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

#endif

GAME_EXPORTS Thread NewThread(void (*main)(void *), void *data);

GAME_EXPORTS void JoinThread(Thread *thread);


#ifdef __cplusplus
}
#endif

#endif //PROJECTC_SYSTEMFUNC_H
