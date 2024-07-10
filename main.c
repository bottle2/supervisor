#include <assert.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "opt.h"
#include "process.h"
#include "scheduler.h"

bool verbose = false;
int ready_or_waiting = 0;

char *state = "running";

int main(int argc, char *argv[])
{
    scheduler_mfp();
    opt(argc, argv);

    char *category = setlocale(LC_ALL, "pt-BR.UTF8");
    assert(category != NULL);

    struct process *pending = NULL;

    int n_process = 0;
    int min_burst = INT_MAX;
    int max_burst = 0;
    int mean_burst = 0;

    // Lê lista de processos, lista encadeada ordenada por arrival. Linear.
    {
        struct process c = {0};

        while (4 == scanf("%d:%d:%d:%d\n", &c.pid, &c.arrival, &c.burst, &c.priority))
        {
            struct process **place = &pending;

            // Verifica PID e descobre onde posicionar processo, mas NÃO adiciona ainda.
            for (; *place != NULL && (*place)->arrival < c.arrival; place = &(*place)->next)
            {
                if (c.pid == (*place)->pid)
                {
                    fprintf(stderr, "PID %d ocorre mais de uma vez, quando devem ser únicos.\n", c.pid);
                    return EXIT_FAILURE;
                }
            }

            // Verifica resto dos PIDs.
            for (struct process *rest = *place; rest != NULL; rest = rest->next)
                if (c.pid == rest->pid)
                {
                    fprintf(stderr, "PID %d ocorre mais de uma vez, quando devem ser únicos.\n", c.pid);
                    return EXIT_FAILURE;
                }

            if (c.arrival < 0)
            {
                fprintf(stderr, "Tempo de chegada deve ser igual ou maior que zero. Leu %d para processo com PID %d\n", c.arrival, c.pid);
                return EXIT_FAILURE;
            }

            if (c.burst <= 0)
            {
                fprintf(stderr, "Tempo de execução deve maior que zero. Leu %d para processo com PID %d\n", c.arrival, c.pid);
                return EXIT_FAILURE;
            }

            if (c.priority < 0 || c.priority > 7)
            {
                fprintf(stderr, "Prioridade deve ser de zero a sete. Leu %d para processo com PID %d\n", c.priority, c.pid);
                return EXIT_FAILURE;
            }

            struct process *new = malloc(sizeof (*new));

            if (!new)
            {
                fprintf(stderr, "Faltou memória para criar processo com PID %d\n", c.pid);
                return EXIT_FAILURE;
            }

            c.runtime = c.burst;
            if (*place != NULL)
                c.next = *place;
            *new = c;
            *place = new;

            n_process++;
	    if (c.burst < min_burst)
		    min_burst = c.burst;
	    if (c.burst > max_burst)
		    max_burst = c.burst;
	    mean_burst += c.burst;
        }

        if (0 == n_process)
            return EXIT_FAILURE;

	mean_burst /= n_process;
    }

    int *completeds = malloc(sizeof (int) * n_process);
    if (!completeds)
    {
        perror(NULL);
        exit(EXIT_FAILURE);
    }
    int n_completed = 0;

#if 0
    for (struct process *em = pending; em != NULL; em = em->next)
        printf("%3d:%3d:%3d:%3d\n", em->pid, em->arrival, em->burst, em->priority);
#endif

#define HLINE  "=========+=================+=================+============"
#define ROWFMT " %-8d"  "| %-16d"         "| %-16d"         "| %-11d"    "\n"
    puts(
               HLINE "\n"
               "Processo | Tempo total     | Tempo total     | Tempo total\n"
               "         | em estado Ready | em estado Wait  | no sistema \n"
               HLINE
    );

    int clock = 0;

    {
        struct process *waiting = NULL;
        struct process *current = NULL;

        for (; current != NULL || pending != NULL || waiting != NULL || !scheduler_is_empty; clock++)
        {

            while (pending != NULL && clock == pending->arrival)
            {
                struct process *arrived = pending;
                pending = pending->next;
                arrived->next = NULL;
                arrived->first_clock = clock;
                scheduler_push(arrived, STATE_READY);
            }

            struct process **waiting_follow = &waiting;

            for (; *waiting_follow != NULL; waiting_follow = &(*waiting_follow)->next)
                if (IOTerm())
                {
                    completeds[n_completed++] = (*waiting_follow)->pid;
                    struct process *completed = *waiting_follow;
                    *waiting_follow = completed->next;
                    completed->next = NULL;
                    scheduler_push(completed, STATE_WAIT);
                    if (NULL == *waiting_follow)
                        break; // Very feio.
                }
                else
		{
                    ready_or_waiting++;
		    (*waiting_follow)->waiting++;
		}

            scheduler_next(&current);

            bool req_io = false;
            int pid = -1;
            int burst = -1;
            bool ended = false;

            if (current != NULL)
            {
                assert(current->burst > 0);
                assert(NULL == current->next);

                pid = current->pid;

                burst = --current->burst;

                if (0 == current->burst)
                {
                    assert(current->ready + current->waiting < clock - current->first_clock + 1);
                    printf(ROWFMT, current->pid, current->ready, current->waiting, clock - current->first_clock + 1);
                    free(current);
                    current = NULL;
                    state = "end";
                    ended = true;
                }
                else if (IOReq())
                {
                    *waiting_follow = current;
                    current = NULL;
                    req_io = state = "wait";
                }
            }
            else
                state = "idle";

            if (verbose)
            {
                fprintf(stderr, "%d:", clock);

                if (NULL == current && !req_io && !ended)
                    fprintf(stderr, "null:null");
                else
                    fprintf(stderr, "%d:%d", pid, burst);

                fprintf(stderr, ":%s", req_io ? "true" : "false");

                if (!n_completed)
                    fprintf(stderr, ":null");
                else for (int i = 0; i < n_completed; i++)
                    fprintf(stderr, "%c%d", ":,"[!!i], completeds[i]);

                fprintf(stderr, ":%s\n", state);
            }

            state = "running";

            n_completed = 0;
        }
    }

    free(completeds);

    printf(
        HLINE "\n\n"
        "Tempo total de simulação.: %d\n"
        "Número de processos......: %d\n"
        "Menor tempo de execução..: %d\n"
        "Maior tempo de execução..: %d\n"
        "Tempo médio de execução..: %d\n"
        "Tempo médio em Ready/Wait: %d\n"
        ,
        clock, n_process, min_burst, max_burst, mean_burst, ready_or_waiting / n_process
    );

    return 0;
}
