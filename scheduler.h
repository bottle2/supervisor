#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdbool.h>

#include "process.h"

enum scheduler
{
    SCHEDULER_MFP, // Múltiplas filas com prioridade.
    SCHEDULER_PSJF, // Preemptive Shortest Job First
};
// XXX Fragmentação
// TODO Some com enumeração, caso comum escolhe um só, uma função pra cada escalonador

union scheduler2; // XXX namespace issue

void scheduler_init(enum scheduler which);

#define SCHEDULER_XS(X) X(mfp) X(psjf)
#define SCHEDULER_API_XS(X) X(next) X(push) X(empty)

void scheduler_mfp(void);
void scheduler_psjf(void);

extern struct process * (*scheduler_next)(union scheduler2 *);
extern void (*scheduler_push)(union scheduler2 *, struct process *); // Exclusivamente processos Ready 
extern bool (*scheduler_empty)(union scheduler2 *);

#endif
