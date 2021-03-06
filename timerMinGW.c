#include <sys/time.h>
#include "timer.h"
/*
   Implementation as per:
   The Open Group Base Specifications, Issue 6
   IEEE Std 1003.1, 2004 Edition

   The timezone pointer arg is ignored.  Errors are ignored.
*/

#ifdef	__cplusplus

void  GetSystemTimeAsFileTime(FILETIME*);

inline int gettimeofday(struct timeval* p, void* tz /* IGNORED */)
{
	union {
	    long long ns100; /*time since 1 Jan 1601 in 100ns units */
		FILETIME ft;
	} now;

    GetSystemTimeAsFileTime( &(now.ft) );
    p->tv_usec=(long)((now.ns100 / 10LL) % 1000000LL );
    p->tv_sec= (long)((now.ns100-(116444736000000000LL))/10000000LL);
	return 0;
}

#else
    /* Must be defined somewhere else */
	int gettimeofday(struct timeval* p, void* tz /* IGNORED */);
#endif


#define FALSE 0
#define TRUE 1


static int  timer_set = FALSE;
static double   old_time;

struct timeval p;
void *tz;

/* Return the amount of time in seconds used by the current process since
   it began. */
#ifdef __STDC__
double  user_time (void) 
#else
double  user_time () 
#endif
{
    gettimeofday(&p, tz /* IGNORED */);

/* Return processes userr mode time in seconds. */
    return (p.tv_sec + (p.tv_usec / 1000000.0));
}


/* Starts timer. */
#ifdef __STDC__
void start_timer (void) 
#else
start_timer () 
#endif
{
    timer_set = TRUE;
    old_time = user_time ();
}


/* Returns elapsed time since last call to start_timer().  Returns ERROR_VALUE
/* if Start_Timer() has never been called. */
#ifdef __STDC__
double  elapsed_time (void) 
#else
double  elapsed_time () 
#endif
{
    if      (timer_set == FALSE) {
	        return (ERROR_VALUE);
    }
    else {
	return (user_time () - old_time);
    }
}


#ifdef DEBUG
#define MAX_ITERATIONS 100000

main (argc, argv)
int     argc;
char   *argv[];
{
    int     i = argc == 1 ? MAX_ITERATIONS : atoi (argv[1]);

    start_timer ();
    while (--i);
    printf ("time = %f\n", elapsed_time ());
}
#endif
