#include <stddef.h>

#include "process.h"
#include "scheduler.h"

float aging = 0.5; // Valor default.

struct process *psjf_next(int quantum[static 1])
{
    (void)quantum;
    return NULL;
}

void psjf_push(struct process *p)
{
    (void)p;
}
