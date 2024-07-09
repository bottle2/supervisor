#include <assert.h>
#include <stddef.h>

#include "process.h"
#include "scheduler.h"

float aging = 0.5; // Valor default.

static struct process *ready = NULL;

//static float Ta(float ta, float XXX terminar essa porra de merda

void psjf_next(struct process *current[static 1])
{
    struct process **shortest = NULL;

    for (struct process **i = &ready; *i; i = &(*i)->next)
    {
#if 1
        // XXX Calcular porra de exponential smoothing
#else
        if (!shortest)
        {
            if (!*current || (*i)->burst < (*current)->burst)
                shortest = i;
        }
        else if ((*i)->burst < (*shortest)->burst && (*i)->pid < (*shortest)->burst)
            shortest = i;
#endif
    }

    if (shortest)
    {
        struct process *old = *current;

        *current = *shortest;
        *shortest = (*shortest)->next;
        (*current)->next = NULL;

        if (old)
            psjf_push(old, STATE_READY);
    }

    scheduler_is_empty = !ready;
}

void psjf_push(struct process p[static 1], enum state from)
{
    if (0 == p->runtime)
        p->Ta = p->runtime = p->burst;

    (void)from;

    scheduler_is_empty = true;

    p->next = ready;
    ready = p;
}
