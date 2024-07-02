#include "io.h"
#include "osPRNG.h"

#define PROB_OF_IO_REQ 10
#define PROB_OF_IO_TERM 4

int IOReq(void)
{
    return !(osPRNG() % PROB_OF_IO_REQ);
}

int IOTerm(void)
{
    return !(osPRNG() % PROB_OF_IO_TERM);
}
