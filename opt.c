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


#line 17 "opt.c"
static const int cmd_start = 9;

static const int cmd_en_main = 9;


#line 41 "opt.rl"


extern enum scheduler scheduler;
extern bool verbose;
extern float aging;

void opt(int argc, char *argv[])
{
	int cs;
	//char *eof = NULL;
	
	
#line 36 "opt.c"
	{
		cs = (int)cmd_start;
	}
	
#line 52 "opt.rl"
	
	
	for (int i = 1; i < argc; i++)
	{
		char *p = argv[i];
		char *mark = NULL;
		
		
#line 50 "opt.c"
		{
			switch ( cs ) {
				case 9:
				goto st_case_9;
				case 0:
				goto st_case_0;
				case 1:
				goto st_case_1;
				case 2:
				goto st_case_2;
				case 3:
				goto st_case_3;
				case 10:
				goto st_case_10;
				case 4:
				goto st_case_4;
				case 5:
				goto st_case_5;
				case 6:
				goto st_case_6;
				case 7:
				goto st_case_7;
				case 8:
				goto st_case_8;
			}
			_ctr5:
			{
#line 18 "opt.rl"
				scheduler = SCHEDULER_MFP; }
			
#line 81 "opt.c"
			
			{
#line 24 "opt.rl"
				{p+= 1; cs = 9; goto _out;} }
			
#line 87 "opt.c"
			
			goto _st9;
			_ctr16:
			{
#line 21 "opt.rl"
				aging = strtof(mark, NULL); }
			
#line 95 "opt.c"
			
			{
#line 24 "opt.rl"
				{p+= 1; cs = 9; goto _out;} }
			
#line 101 "opt.c"
			
			goto _st9;
			_ctr20:
			{
#line 17 "opt.rl"
				verbose = true; }
			
#line 109 "opt.c"
			
			{
#line 24 "opt.rl"
				{p+= 1; cs = 9; goto _out;} }
			
#line 115 "opt.c"
			
			goto _st9;
			_st9:
			p+= 1;
			st_case_9:
			if ( ( (*( p))) == 45 ) {
				goto _st1;
			}
			goto _st0;
			_st0:
			st_case_0:
			goto _out0;
			_st1:
			p+= 1;
			st_case_1:
			switch( ( (*( p))) ) {
				case 70: {
					goto _st2;
				}
				case 83: {
					goto _st3;
				}
				case 118: {
					goto _st8;
				}
			}
			goto _st0;
			_ctr6:
			{
#line 18 "opt.rl"
				scheduler = SCHEDULER_MFP; }
			
#line 148 "opt.c"
			
			goto _st2;
			_ctr12:
			{
#line 19 "opt.rl"
				scheduler = SCHEDULER_PSJF; aging = 0.5; }
			
#line 156 "opt.c"
			
			goto _st2;
			_ctr21:
			{
#line 17 "opt.rl"
				verbose = true; }
			
#line 164 "opt.c"
			
			goto _st2;
			_st2:
			p+= 1;
			st_case_2:
			switch( ( (*( p))) ) {
				case 0: {
					goto _ctr5;
				}
				case 70: {
					goto _ctr6;
				}
				case 83: {
					goto _ctr7;
				}
				case 118: {
					goto _ctr8;
				}
			}
			goto _st0;
			_ctr7:
			{
#line 18 "opt.rl"
				scheduler = SCHEDULER_MFP; }
			
#line 190 "opt.c"
			
			goto _st3;
			_ctr13:
			{
#line 19 "opt.rl"
				scheduler = SCHEDULER_PSJF; aging = 0.5; }
			
#line 198 "opt.c"
			
			goto _st3;
			_ctr22:
			{
#line 17 "opt.rl"
				verbose = true; }
			
#line 206 "opt.c"
			
			goto _st3;
			_st3:
			p+= 1;
			st_case_3:
			switch( ( (*( p))) ) {
				case 0: {
					goto _ctr9;
				}
				case 48: {
					goto _ctr10;
				}
				case 49: {
					goto _ctr11;
				}
				case 70: {
					goto _ctr12;
				}
				case 83: {
					goto _ctr13;
				}
				case 118: {
					goto _ctr14;
				}
			}
			goto _st0;
			_ctr9:
			{
#line 19 "opt.rl"
				scheduler = SCHEDULER_PSJF; aging = 0.5; }
			
#line 238 "opt.c"
			
			{
#line 24 "opt.rl"
				{p+= 1; cs = 10; goto _out;} }
			
#line 244 "opt.c"
			
			goto _st10;
			_st10:
			p+= 1;
			st_case_10:
			switch( ( (*( p))) ) {
				case 45: {
					goto _st1;
				}
				case 48: {
					goto _ctr26;
				}
				case 49: {
					goto _ctr27;
				}
			}
			goto _st0;
			_ctr10:
			{
#line 19 "opt.rl"
				scheduler = SCHEDULER_PSJF; aging = 0.5; }
			
#line 267 "opt.c"
			
			{
#line 20 "opt.rl"
				mark = p; }
			
#line 273 "opt.c"
			
			goto _st4;
			_ctr26:
			{
#line 20 "opt.rl"
				mark = p; }
			
#line 281 "opt.c"
			
			goto _st4;
			_st4:
			p+= 1;
			st_case_4:
			switch( ( (*( p))) ) {
				case 0: {
					goto _ctr16;
				}
				case 46: {
					goto _st5;
				}
			}
			goto _st0;
			_st5:
			p+= 1;
			st_case_5:
			if ( ( (*( p))) == 0 ) {
				goto _ctr16;
			}
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st5;
			}
			goto _st0;
			_ctr11:
			{
#line 19 "opt.rl"
				scheduler = SCHEDULER_PSJF; aging = 0.5; }
			
#line 311 "opt.c"
			
			{
#line 20 "opt.rl"
				mark = p; }
			
#line 317 "opt.c"
			
			goto _st6;
			_ctr27:
			{
#line 20 "opt.rl"
				mark = p; }
			
#line 325 "opt.c"
			
			goto _st6;
			_st6:
			p+= 1;
			st_case_6:
			switch( ( (*( p))) ) {
				case 0: {
					goto _ctr16;
				}
				case 46: {
					goto _st7;
				}
			}
			goto _st0;
			_st7:
			p+= 1;
			st_case_7:
			switch( ( (*( p))) ) {
				case 0: {
					goto _ctr16;
				}
				case 48: {
					goto _st7;
				}
			}
			goto _st0;
			_ctr8:
			{
#line 18 "opt.rl"
				scheduler = SCHEDULER_MFP; }
			
#line 357 "opt.c"
			
			goto _st8;
			_ctr14:
			{
#line 19 "opt.rl"
				scheduler = SCHEDULER_PSJF; aging = 0.5; }
			
#line 365 "opt.c"
			
			goto _st8;
			_ctr23:
			{
#line 17 "opt.rl"
				verbose = true; }
			
#line 373 "opt.c"
			
			goto _st8;
			_st8:
			p+= 1;
			st_case_8:
			switch( ( (*( p))) ) {
				case 0: {
					goto _ctr20;
				}
				case 70: {
					goto _ctr21;
				}
				case 83: {
					goto _ctr22;
				}
				case 118: {
					goto _ctr23;
				}
			}
			goto _st0;
			_out9: cs = 9; goto _out; 
			_out0: cs = 0; goto _out; 
			_out1: cs = 1; goto _out; 
			_out2: cs = 2; goto _out; 
			_out3: cs = 3; goto _out; 
			_out10: cs = 10; goto _out; 
			_out4: cs = 4; goto _out; 
			_out5: cs = 5; goto _out; 
			_out6: cs = 6; goto _out; 
			_out7: cs = 7; goto _out; 
			_out8: cs = 8; goto _out; 
			_out: {}
		}
		
#line 59 "opt.rl"
		
	}
	
	if (cs < 
#line 413 "opt.c"
	9
#line 62 "opt.rl"
	)
	usage(argv[0]);
}
