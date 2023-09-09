/* KallistiOS ##version##
   benchmark 
   (c)2022 Ian micheal Memcpy benchmark
*/
/* This simple example shows how to benchmark memcpy */

/* KallistiOS ##version##
   memcpy benchmark 
   (c)2023 Ian Micheal
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

#define MEM_ALLOC (1024 * 100) // 100KB
#define TEST_COUNT 10

double total_memcpy = 0;
double total_memcpyasm = 0;

#define START_BENCHMARK(LABEL) do {                         \
    total = min = max = 0;                                  \
    for (int i = 0; i < TEST_COUNT; i++) {                 \
        src = (char *)malloc(MEM_ALLOC);                    \
        dst = (char *)malloc(MEM_ALLOC);                    \
        printf("Initializing source data for %s %d...\n", #LABEL, i + 1); \
        fflush(stdout);                                      \
        memset(src, 'a', MEM_ALLOC);                         \
        start_time = timer_ms_gettime64();

#define END_BENCHMARK(LABEL)                                \
        end_time = timer_ms_gettime64();                      \
        double secs = (end_time - start_time) / 1000.0;       \
        printf("%s %d: %0.10lf seconds\n", #LABEL, i + 1, secs); \
        printf("Verifying copied data for %s %d...\n", #LABEL, i + 1); \
        assert(!memcmp(dst, src, MEM_ALLOC));                 \
        fflush(stdout);                                       \
        total += secs;                                        \
        min = i ? (min > secs ? secs : min) : secs;           \
        max = i ? (max < secs ? secs : max) : secs;           \
        free(dst); free(src);                                 \
    }                                                        \
    if (strcmp(#LABEL, "memcpy") == 0) {                     \
        total_memcpy = total / TEST_COUNT;                   \
    } else if (strcmp(#LABEL, "memcpyasm") == 0) {           \
        total_memcpyasm = total / TEST_COUNT;                \
    }                                                        \
    printf("Max\t: %0.10lf\n", max);                        \
    printf("Min\t: %0.10lf\n", min);                        \
    printf("Avg\t: %0.10lf\n", total / TEST_COUNT);         \
    printf("Total\t: %0.10lf\n", total);                    \
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
  
    // Calculate and display the comparison
  if (total_memcpy < total_memcpyasm) {
      printf("memcpy is faster by %.2f times\n", total_memcpyasm / total_memcpy);
  } else if (total_memcpy > total_memcpyasm) {
      printf("memcpyasm is faster by %.2f times\n", total_memcpy / total_memcpyasm);
  } else {
      printf("memcpy and memcpyasm have the same performance\n");
  }


  printf("OK!\n");
  fflush(stdout); // Flush the output buffer to ensure immediate display
  pvr_shutdown(); // Clean up PVR resources
  vid_shutdown(); // This function reinitializes the video system to what dcload and friends expect it to be.
  malloc_stats();
  spu_disable(); // Disable the Sound Processing Unit (SPU).
  arch_exit(); // Perform system-specific exit operations.


  return 0;
}

