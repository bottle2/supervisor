#include <assert.h>
#include <stdbool.h>

#include "scheduler.h"

#define AS_INNER(_, R, OP, ...) static OP##_f *inner_##OP
SCHEDULER_API_XS(AS_INNER, 0);

static int n_inside = 0;

struct process * scheduler_next(void)
{
    n_inside--;
    assert(n_inside >= 0);
    return inner_next();
}

void scheduler_push(struct process *p)
{
    n_inside++;
    inner_push(p);
}

bool scheduler_empty(void)
{
    return !n_inside;
}

#define AS_DECL(ALG, R, OP, ...) R ALG##_##OP(__VA_ARGS__)
#define AS_ASS(ALG, R, OP, ...) inner_##OP = ALG##_##OP

#define X(ALG) void scheduler_##ALG(void) { \
    SCHEDULER_API_XS(AS_DECL, ALG); SCHEDULER_API_XS(AS_ASS, ALG); \
}
SCHEDULER_XS
#undef X
