#include <stddef.h>

#include "process.h"
#include "scheduler.h"

struct process *mfp_next(int quantum[static 1])
{
    (void)quantum;
    return NULL;
}

void mfp_push(struct process *p)
{
    (void)p;
}
