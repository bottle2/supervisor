#include <assert.h>
#include <math.h>
#include <stddef.h>

#include "process.h"
#include "scheduler.h"

float aging = 0.5; // Valor default.

static struct process *ready = NULL;

static float Tn(struct process p[static 1])
{
    return p->Ta = aging * (p->runtime - p->burst) + (1 - aging) * p->Ta;
}

void psjf_next(struct process *current[static 1])
{
    struct process **shortest = NULL;

    float Tn_shortest = *current ? Tn(*current) : HUGE_VAL;

    for (struct process **i = &ready; *i; i = &(*i)->next)
    {
        extern int ready_or_waiting;
        ready_or_waiting++;
	(*i)->ready++;
#if 1
        float Tn_candidate = Tn(*i);

        if (Tn_candidate < Tn_shortest)
        {
            Tn_shortest = Tn_candidate;
            shortest = i;
        }
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
        (*current)->ready--;

        if (old)
        {
            extern char *state;
            state = "preempted";
            psjf_push(old, STATE_READY);
        }
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
