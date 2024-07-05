#include <assert.h>
#include <stddef.h>

#include "process.h"
#include "scheduler.h"

static struct process  *heads[8] = {0};
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

struct process *mfp_next(int quantum[static 1])
{
    struct process *chosen = NULL;

    for (int i = 0; i <= 7; i++)
        if (heads[i])
        {
            chosen = heads[i];
            heads[i] = chosen->next;
            chosen->next = NULL;
            if (NULL == heads[i])
                lasts[i] = &heads[i];
            assert(i == chosen->priority);
            *quantum = 1 << i;
        }

    return chosen;
}

void mfp_push(struct process *p, enum state from)
{
    assert(NULL == p->next);

    // I'm a fucking three-star programmer! and I didn't even flinch, bitch
    struct process ***end = &lasts[7];

    if (STATE_WAIT == from)
        end = &lasts[p->priority = 0];
    else if (p->priority <= 6)
        end = &lasts[++p->priority];

    **end = p;
    *end = &p->next;
}
