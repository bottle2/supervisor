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

int main(int argc, char *argv[])
{
    char *category = setlocale(LC_ALL, "pt-BR.UTF8");
    assert(category != NULL);

    scheduler_mfp();
    opt(argc, argv);

    puts(verbose ? "verboso" : "nao verboso");

    struct process *pending = NULL;

    // Lê lista de processos, lista encadeada ordenada por arrival. Linear.
    // XXX Vários com mesmo, arrival, ordenar pelo PID?
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

            if (*place != NULL)
                c.next = *place;
            *new = c;
            *place = new;
        }
    }

#if 1
    for (struct process *em = pending; em != NULL; em = em->next)
    {
        printf("%3d:%3d:%3d:%3d\n", em->pid, em->arrival, em->burst, em->priority);

        float Ta = em->burst;
        for (int ta = 1; ta < 10; ta++)
        {
            extern float aging;
            Ta = aging * ta + (1 - aging) * Ta;
            printf("Tn = %f\n", (double)Ta);
        }
    }
#endif

#define HLINE  "=========+=================+=================+============"
#define ROWFMT " %8d"   "| %16d"          "| %16d"          "| %11d"     "\n"
    puts(
               HLINE "\n"
               "Processo | Tempo total     | Tempo total     | Tempo total\n"
               "         | em estado Ready | em estado Wait  | no sistema \n"
               HLINE
    );

    {
        struct process *waiting = NULL;
        struct process *current = NULL;

        for (int clock = 0; pending != NULL || waiting != NULL || !scheduler_is_empty; clock++)
        {
            while (pending != NULL && clock == pending->arrival)
            {
                struct process *arrived = pending;
                pending = pending->next;
                arrived->next = NULL;
                scheduler_push(arrived, STATE_READY);
            }

            struct process **waiting_follow = &waiting;

            for (; *waiting_follow != NULL; waiting_follow = &(*waiting_follow)->next)
                if (IOTerm())
                {
                    struct process *completed = *waiting_follow;
                    *waiting_follow = completed->next;
                    completed->next = NULL;
                    scheduler_push(completed, STATE_WAIT);
		    if (NULL == *waiting_follow)
                        break; // Very feio.
                }

            scheduler_next(&current);

            if (current != NULL)
            {
                assert(current->burst > 0);
                assert(NULL == current->next);

                current->burst--;

                if (0 == current->burst)
                {
                    // XXX Calcula "coisas" e printa antes de liberar
                    free(current);
                    current = NULL;
                }
                else if (IOReq())
                {
                    *waiting_follow = current;
                    current = NULL;
                }
            }
        }
    }

    puts(HLINE "\n");

    int dummy = 0;
    printf(
        "Tempo total de simulação.: %d\n"
        "Número de processos......: %d\n"
        "Menor tempo de execução..: %d\n"
        "Maior tempo de execução..: %d\n"
        "Tempo médio de execução..: %d\n"
        "Tempo médio em Ready/Wait: %d\n"
        ,
        dummy, dummy, dummy, dummy, dummy, dummy
    );

    return 0;
}
