#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdbool.h>

#include "process.h"

#define SCHEDULER_XS X(mfp) X(psjf)

#define X(ALG) void scheduler_##ALG(void);
SCHEDULER_XS
#undef X

#define SCHEDULER_API_XS(X, Y)     \
X(Y, struct process *, next, void); \
X(Y, void, push, struct process *)

#define AS_TYPE(_, R, OP, ...) typedef R OP##_f(__VA_ARGS__)
#define AS_PUBLIC(_, R, OP, ...) OP##_f scheduler_##OP

SCHEDULER_API_XS(AS_TYPE  , 0);
SCHEDULER_API_XS(AS_PUBLIC, 0);

bool scheduler_empty(void);

#endif
