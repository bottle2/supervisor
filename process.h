#ifndef PROCESS_H
#define PROCESS_H

struct process
{
    int pid;
    int arrival;
    int burst;
    int priority;
    struct process *next;
};

// XXX slk API pras putarias de lista encadeada
// inclusive the **

#endif