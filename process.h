#ifndef PROCESS_H
#define PROCESS_H

struct process
{
    int pid; // XXX fazer const essa porra porra porra porra porra
    int arrival;
    int burst;
    int priority;
    struct process *next;

    int quantum;
};

enum state { STATE_NEW, STATE_WAIT, STATE_READY, };

// XXX slk API pras putarias de lista encadeada
// inclusive the **

#endif
