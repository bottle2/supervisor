#ifndef PROCESS_H
#define PROCESS_H

struct process
{
    int pid;
    int arrival;
    int runtime;
    int burst;
    int priority;
    struct process *next;

    int quantum;
    float Ta; // Estimativa anterior.

    int first_clock;
    int waiting;
    int ready;
};

enum state { STATE_NEW, STATE_WAIT, STATE_READY, };

#endif
