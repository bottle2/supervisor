
#line 1 "opt.rl"
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


#line 18 "opt.c"
static const int cmd_start = 9;


#line 41 "opt.rl"


extern bool verbose;
extern float aging;

void opt(int argc, char *argv[])
{
    int cs;
    //char *eof = NULL;

    
#line 34 "opt.c"
	{
	cs = cmd_start;
	}

#line 52 "opt.rl"

    for (int i = 1; i < argc; i++)
    {
        char *p = argv[i];
        char *mark = NULL;

        
#line 47 "opt.c"
	{
	switch ( cs )
	{
tr4:
#line 18 "opt.rl"
	{ scheduler_mfp(); }
#line 24 "opt.rl"
	{ {p++; cs = 9; goto _out;} }
	goto st9;
tr14:
#line 21 "opt.rl"
	{ aging = strtof(mark, NULL); }
#line 24 "opt.rl"
	{ {p++; cs = 9; goto _out;} }
	goto st9;
tr17:
#line 17 "opt.rl"
	{ verbose = true; }
#line 24 "opt.rl"
	{ {p++; cs = 9; goto _out;} }
	goto st9;
st9:
	p += 1;
case 9:
#line 72 "opt.c"
	if ( (*p) == 45 )
		goto st1;
	goto st0;
st0:
cs = 0;
	goto _out;
st1:
	p += 1;
case 1:
	switch( (*p) ) {
		case 70: goto st2;
		case 83: goto st3;
		case 118: goto st8;
	}
	goto st0;
tr5:
#line 18 "opt.rl"
	{ scheduler_mfp(); }
	goto st2;
tr11:
#line 19 "opt.rl"
	{ scheduler_psjf(); aging = 0.5; }
	goto st2;
tr18:
#line 17 "opt.rl"
	{ verbose = true; }
	goto st2;
st2:
	p += 1;
case 2:
#line 103 "opt.c"
	switch( (*p) ) {
		case 0: goto tr4;
		case 70: goto tr5;
		case 83: goto tr6;
		case 118: goto tr7;
	}
	goto st0;
tr6:
#line 18 "opt.rl"
	{ scheduler_mfp(); }
	goto st3;
tr12:
#line 19 "opt.rl"
	{ scheduler_psjf(); aging = 0.5; }
	goto st3;
tr19:
#line 17 "opt.rl"
	{ verbose = true; }
	goto st3;
st3:
	p += 1;
case 3:
#line 126 "opt.c"
	switch( (*p) ) {
		case 0: goto tr8;
		case 48: goto tr9;
		case 49: goto tr10;
		case 70: goto tr11;
		case 83: goto tr12;
		case 118: goto tr13;
	}
	goto st0;
tr8:
#line 19 "opt.rl"
	{ scheduler_psjf(); aging = 0.5; }
#line 24 "opt.rl"
	{ {p++; cs = 10; goto _out;} }
	goto st10;
st10:
	p += 1;
case 10:
#line 145 "opt.c"
	switch( (*p) ) {
		case 45: goto st1;
		case 48: goto tr22;
		case 49: goto tr23;
	}
	goto st0;
tr9:
#line 19 "opt.rl"
	{ scheduler_psjf(); aging = 0.5; }
#line 20 "opt.rl"
	{ mark = p; }
	goto st4;
tr22:
#line 20 "opt.rl"
	{ mark = p; }
	goto st4;
st4:
	p += 1;
case 4:
#line 165 "opt.c"
	switch( (*p) ) {
		case 0: goto tr14;
		case 46: goto st5;
	}
	goto st0;
st5:
	p += 1;
case 5:
	if ( (*p) == 0 )
		goto tr14;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st5;
	goto st0;
tr10:
#line 19 "opt.rl"
	{ scheduler_psjf(); aging = 0.5; }
#line 20 "opt.rl"
	{ mark = p; }
	goto st6;
tr23:
#line 20 "opt.rl"
	{ mark = p; }
	goto st6;
st6:
	p += 1;
case 6:
#line 192 "opt.c"
	switch( (*p) ) {
		case 0: goto tr14;
		case 46: goto st7;
	}
	goto st0;
st7:
	p += 1;
case 7:
	switch( (*p) ) {
		case 0: goto tr14;
		case 48: goto st7;
	}
	goto st0;
tr7:
#line 18 "opt.rl"
	{ scheduler_mfp(); }
	goto st8;
tr13:
#line 19 "opt.rl"
	{ scheduler_psjf(); aging = 0.5; }
	goto st8;
tr20:
#line 17 "opt.rl"
	{ verbose = true; }
	goto st8;
st8:
	p += 1;
case 8:
#line 221 "opt.c"
	switch( (*p) ) {
		case 0: goto tr17;
		case 70: goto tr18;
		case 83: goto tr19;
		case 118: goto tr20;
	}
	goto st0;
	}

	_out: {}
	}

#line 59 "opt.rl"
    }

    if (cs < 9 )
        usage(argv[0]);
}
