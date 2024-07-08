#include <stddef.h>

#include "process.h"
#include "scheduler.h"

float aging = 0.5; // Valor default.

void psjf_next(struct process *current[static 1])
{
    (void)current;
}

void psjf_push(struct process *p, enum state from)
{
    (void)p;
    (void)from;
}
