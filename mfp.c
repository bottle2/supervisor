#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "process.h"
#include "scheduler.h"

static struct process  *heads[8] = {0};
static struct process **slots[8] = {0};
static struct process **lasts[8] = {
    [0] = &heads[0],
    [1] = &heads[1],
    [2] = &heads[2],
    [3] = &heads[3],
    [4] = &heads[4],
    [5] = &heads[5],
    [6] = &heads[6],
    [7] = &heads[7],
};
// Refatorar isso, só se for com Boost Preprocessor!

static bool is_pushing = false;

void mfp_next(struct process *current[static 1])
{
    assert(NULL == *current || (*current)->quantum >= 1);

    // Trata quantum.
    if (*current != NULL && !(--(*current)->quantum))
    {
        mfp_push(*current, STATE_READY);
        *current = NULL;
    }

    // Escolhe candidato.
    struct process **chosen = NULL;
    int quantum = 0;
    for (int i = 0; i <= 7; i++)
        if (heads[i])
        {
            chosen = &heads[i];
            quantum = 1 << i;
            break;
        }

    // Descarta candidato ou força preempção.
    if (*current != NULL && chosen != NULL)
    {
        if ((*current)->priority <= (*chosen)->priority)
            chosen = NULL;
        else
        {
            mfp_push(*current, STATE_READY);
            *current = NULL;
        }
    }

    // Substitui processo atual.
    if (chosen != NULL)
    {
        assert(NULL == *current);

        *current = *chosen;

        *chosen = (*chosen)->next;

        (*current)->next = NULL;
        (*current)->quantum = quantum;
    }

    // Atualiza estado interno.
    scheduler_is_empty = true;
    // XXX check when last is chosen and update it directly.
    for (int i = 0; i <= 7; i++)
#if 1
    {
        if (heads[i])
            scheduler_is_empty = false;
        lasts[i] = &heads[i];
        while (*lasts[i] != NULL)
            lasts[i] = &(*lasts[i])->next;
    }
#else
        if (NULL == heads[i])
            lasts[i] = &heads[i];
        else
        {
            scheduler_is_empty = false;
            while (*lasts[i] != NULL)
                lasts[i] = &(*lasts[i])->next;
        }
#endif
    is_pushing = false;
}

void mfp_push(struct process p[static 1], enum state from)
{
    assert(NULL == p->next);

    scheduler_is_empty = false;

    if (!is_pushing)
    {
        (void)memcpy(slots, lasts, sizeof (lasts));
        is_pushing = true;
    }

    struct process **where = slots[7];

    switch (from)
    {
        case STATE_NEW:
            where = slots[p->priority];
        break;

        case STATE_READY:
            if (0 == p->quantum)
                p->priority++;
            where = slots[p->priority];
        break;

        case STATE_WAIT:
            where = slots[p->priority];
            p->priority = 0;
        break;

        default: assert(!"Unknown state!"); break;
    }

    while (*where != NULL && (*where)->pid < p->pid)
        where = &(*where)->next;

    p->next = *where;
    *where = p;
}
