#include <assert.h>
#include <stdbool.h>

#include "scheduler.h"

#define AS_INIT_IMPL(ALG) void scheduler_##ALG(void) { SCHEDULER_API_XS(AS_ASS, ALG); }
#define AS_ASS(OP, ALG, ...) inner_##OP = ALG##_##OP

SCHEDULER_API_XS(AS_FUN, static *inner);
SCHEDULER_XS(AS_INIT_IMPL)

static int n_inside = 0;

struct process * scheduler_next(int quantum[static 1])
{
    n_inside--;
    assert(n_inside >= 0);
    return inner_next(quantum);
}

void scheduler_push(struct process *p, enum state from)
{
    n_inside++;
    inner_push(p, from);
}

bool scheduler_empty(void)
{
    return !n_inside;
}
