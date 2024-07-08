#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdbool.h>

#include "process.h"

#define SCHEDULER_XS(X) X(mfp) X(psjf)

#define SCHEDULER_API_XS(X, Y)                  \
    X(next, Y, void, struct process*[static 1]); \
    X(push, Y, void, struct process [static 1], enum state)

#define AS_INIT(ALG) void scheduler_##ALG(void);
#define AS_DEP(ALG) SCHEDULER_API_XS(AS_FUN, ALG);

#define AS_TYPE(OP, _, R, ...) typedef R OP##_f(__VA_ARGS__)
#define AS_FUN( OP, MOD,  ...)           OP##_f MOD##_##OP

SCHEDULER_XS(AS_INIT)
SCHEDULER_API_XS(AS_TYPE, 0);
SCHEDULER_API_XS(AS_FUN , extern *scheduler);
SCHEDULER_XS(AS_DEP)

extern bool scheduler_is_empty;

#endif
