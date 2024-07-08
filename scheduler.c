#include <assert.h>
#include <stdbool.h>

#include "scheduler.h"

#define AS_INIT_IMPL(ALG) void scheduler_##ALG(void) { SCHEDULER_API_XS(AS_ASS, ALG); }
#define AS_ASS(OP, ALG, ...) scheduler_##OP = ALG##_##OP

SCHEDULER_API_XS(AS_FUN, *scheduler); // Fica esperto!
SCHEDULER_XS(AS_INIT_IMPL)

bool scheduler_is_empty = true;
