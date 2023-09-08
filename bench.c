/* KallistiOS ##version##

   benchmark 
   (c)2022 Ian micheal Memcpy benchmark
*/

/* This simple example shows how to benchmark memcpy */

/* KallistiOS ##version##

   memcpy benchmark 
   (c)2002 Ian Micheal

   This simple example shows how to benchmark memcpy
*/

#include <kos.h>
#include <kos/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "memfuncs.h"
extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);
#include <assert.h>

#define MEM_ALLOC (1024 * 500) // 500 KB

#define START_BENCHMARK(LABEL) do {                         \
    total = min = max = 0;                                  \
    src = (char *)malloc(MEM_ALLOC);                        \
    dst = (char *)malloc(MEM_ALLOC);                        \
    printf("Initializing source data for %s...\n", #LABEL); \
    fflush(stdout);                                         \
    memset(src, 'a', MEM_ALLOC);                            \
    start_time = timer_ms_gettime64();

#define END_BENCHMARK(LABEL)                                \
    end_time = timer_ms_gettime64();                        \
    double secs = (end_time - start_time) / 1000.0;         \
    printf("%s: %0.10lf seconds\n", #LABEL, secs);          \
    printf("Verifying copied data for %s...\n", #LABEL);    \
    assert(!memcmp(dst, src, MEM_ALLOC));                   \
    fflush(stdout);                                         \
    total += secs;                                          \
    min = total;                                            \
    max = total;                                            \
    free(dst); free(src);                                   \
  } while (0)

typedef unsigned long long timestamp_t;

int main() {
  double total, min, max;
  char *dst = NULL, *src = NULL;
  timestamp_t start_time, end_time;

  /* Do basic setup */
  pvr_init_defaults();

  // Benchmark memcpy
  printf("Benchmarking memcpy...\n");
  START_BENCHMARK(memcpy);
  memcpy(dst, src, MEM_ALLOC);
  END_BENCHMARK(memcpy);

  // Benchmark memcpyasm
  printf("Benchmarking memcpyasm...\n");
  START_BENCHMARK(memcpyasm);
  memcpyasm(dst, src, MEM_ALLOC);
  END_BENCHMARK(memcpyasm);

  printf("OK!\n");
  fflush(stdout); // Flush the output buffer to ensure immediate display
  pvr_shutdown(); // Clean up PVR resources
  vid_shutdown(); // This function reinitializes the video system to what dcload and friends expect it to be.
  malloc_stats();
  spu_disable(); // Disable the Sound Processing Unit (SPU).
  arch_exit(); // Perform system-specific exit operations.

  return 0;
}


