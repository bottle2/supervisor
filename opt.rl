#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "opt.h"
#include "scheduler.h"

static void usage(char *prog_name)
{
    fprintf(stderr, "usage: %s [-vF] [-S [a]]\n", prog_name);
    exit(EXIT_FAILURE);
}

%%{
    machine cmd;

    action set_verbose { verbose = true; } 
    action set_mfp  { scheduler_mfp(); }
    action set_psjf { scheduler_psjf(); aging = 0.5; }
    action set_mark { mark = p; }
    action set_aging { aging = strtof(mark, NULL); }
    action error { usage(argv[0]); }

    action yield { fbreak; }
    nul = 0 @yield;

    uv_lit = [10] | ("1." '0'*) | ("0." digit*);

    verbosity = 'v' %set_verbose;
    mfp       = 'F' %set_mfp;
    psjf      = 'S' %set_psjf;

    aging = nul? uv_lit >set_mark %set_aging;

    flag = verbosity | mfp | psjf;
    option = flag+ | ((flag*) psjf aging);

    main := ('-' option nul)*;

    write data noerror nofinal noentry;
}%%

extern bool verbose;
extern float aging;

void opt(int argc, char *argv[])
{
    int cs;
    //char *eof = NULL;

    %% write init;

    for (int i = 1; i < argc; i++)
    {
        char *p = argv[i];
        char *mark = NULL;

        %% write exec noend;
    }

    if (cs < %%{ write first_final; }%% )
        usage(argv[0]);
}
