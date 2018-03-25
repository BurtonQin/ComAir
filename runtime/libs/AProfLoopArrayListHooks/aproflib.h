#ifndef APROFHOOKS_LIBRARY_H
#define APROFHOOKS_LIBRARY_H

#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>


/* ---- page table ---- */
#define STACK_SIZE 2000
/*---- end ----*/

/*---- share memory ---- */
#define BUFFERSIZE (unsigned long) 1UL << 34
#define APROF_MEM_LOG "/aprof_loop_arry_list_log.log"

/*---- end ----*/

/*---- run time lib api ----*/

struct log_address {
    unsigned long  numCost;
    int  length;
};

void aprof_init();

void aprof_dump(void *memory_addr, int length);

void aprof_return(unsigned long numCost);

int aprof_geo(int iRate);            // Returns a geometric random variable

//=========================================================================
//= Multiplicative LCG for generating uniform(0.0, 1.0) random numbers    =
//=   - x_n = 7^5*x_(n-1)mod(2^31 - 1)                                    =
//=   - With x seeded to 1 the 10000th x value should be 1043618065       =
//=   - From R. Jain, "The Art of Computer Systems Performance Analysis," =
//=     John Wiley & Sons, 1991. (Page 443, Figure 26.2)                  =
//=========================================================================
static double aprof_rand_val(int seed);    // Jain's RNG

/*---- end ----*/

#endif
