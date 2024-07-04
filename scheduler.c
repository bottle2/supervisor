#include "scheduler.h"

#define X void scheduler_##X(void) \
{ \
    SCHEDULER_API_XS(Y)\
}
#define Y 
SCHEDULER_XS
#undef X

void scheduler_choose(enum scheduler which)
{
    // XXX
}
