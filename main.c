#include <stdbool.h>
#include <stdio.h>

#include "opt.h"
#include "scheduler.h"

enum scheduler scheduler = SCHEDULER_MFP;

bool  verbose = false;
float aging   = 0.5; // Valor default.

int main(int argc, char *argv[])
{
    opt(argc, argv);

    puts(verbose ? "verboso" : "nao verboso");
    if (SCHEDULER_MFP == scheduler)
        puts("multiple file");
    else
        printf("shortest with aging %f\n", (double)aging);

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