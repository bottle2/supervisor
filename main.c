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

#if 0
    for (struct process *em = pending; em != NULL; em = em->next)
        printf("%3d:%3d:%3d:%3d\n", em->pid, em->arrival, em->burst, em->priority);
#endif

#define HLINE  "=========+=================+=================+============\n"
#define ROWFMT " %8d"   "| %16d"          "| %16d"          "| %11d"     "\n"
    puts(
               HLINE
               "Processo | Tempo total     | Tempo total     | Tempo total\n"
               "         | em estado Ready | em estado Wait  | no sistema \n"
               HLINE
    );

    {
        struct process *waiting = NULL;
        struct process *current = NULL;
        int quantum = -1;

        for (int clock = 0; pending != NULL || waiting != NULL || !scheduler_empty(); clock++)
        {
            while (pending != NULL && clock == pending->arrival)
            {
                struct process *temp = pending;
                pending = pending->next;
                free(temp); // XXX push to escalonador
            }

            for (struct process *a = waiting; a != NULL; a = a->next)
            {
                // Checar se acabou a porra
                if (IOTerm())
                {
                    // XXX Do it porra
                }
            }

            if (NULL == current)
                current = scheduler_next(&quantum);

            if (current != NULL)
            {
                assert(current->burst > 0);

                current->burst--;

                if (0 == current->burst)
                {
                    // XXX Calcula "coisas" e printa antes de liberar
                    free(current);
                    current = NULL;
                }

                if (IOReq())
                {
                    current = NULL;
                    waiting; // XXX
                    // Botar na fila de Wait
                }
            }
        }
    }

    puts(HLINE "\n");
    #undef HLINE

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
#if 0
    /* inicializar clock */
    clock=0;

    /* adicionar novos processos ao estado Ready */
    /* (seu código aqui) */

    clock++;
    /* Loop principal do Supervisor */
    while( /* há processos no sistema */ ) {
        currentProcess = /* escolher processo a executar */;
        while( 1 ) { /* loop principal de gerência de processos */
            /* se houver, adicionar novos processos ao estado Ready */

            /* enquanto houver processo(s) em estado Wait (I/O) */
            /* verificar se o I/O completou para cada processo em espera (ordem FIFO) */
            status = IOTerm();
            if (status == 1){
                /* colocar o processo que completou em estado Ready */
            }

            /* se o processo terminou sua execução (tempo restante 1) */
            /* marcar o processo atual como swappedOut (termino de execução) */

            /* se for um escalonador preemptivo e há processo com */
            /* prioridade superior em estado Ready */
            /* marcar o processo atual como swappedOut (preempção) */

            /* verificar se o processo atual requisita I/O */
            if ( /* processo atual não está completo */)
                status = IOReq();
            if (status == 1){
                /* need to do I/O */
                /* marcar o processo atual como swappedOut (wait on I/O) */
            } else {
                /* marcar o processo atual como swappedOut (fim do quantum) */
            }

            /* atualizar estatísticas de execução */

            clock++;

            /* se o processo atual foi swappedOut */
            /* mover o processo para a fila adequada e sair deste laço */
        } /* fim do loop de gerência de processos */

    } /* fim do loop principal do Supervisor */
#endif
    return 0;
}
