/* KallistiOS ##version##

   benchmark 
   (c)20022 Ian micheal Memcpy benchmark
*/

/* This simple example shows how to benchmark memcpy */

#include <kos.h>
#include <kos/string.h>
extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "memfuncs.h"

static inline void*
memcpy_forward(void* dst, void* src, size_t n)
{
	size_t i;
	for(i = 0; i < n; i++)
		((char*)dst)[i] = ((char*)src)[i];
	return dst;
}

static inline void*
memcpy_backwards(char* dst, char* src, size_t n)
{
	size_t i;
	for(i = 0; i < n; i++)
		dst[n - i - 1] = src[n - i - 1];
	return dst;
}

/*
 * To show that copying backwards is no slower then copying forwards.
 */
static inline void*
memcpy_backwards_optimized(char* dst, char* src, size_t n)
{
	if(n != 0){
		do{
			n--;
			dst[n] = src[n];
		}while(n != 0);
	}
	return dst;
}

void*
my_memcpy(void* dst, void* src, size_t n)
{
	return memcpy_forward(dst,src,n);
}

void*
my_memmove(void* dst, void* src, size_t n)
{		
	if(dst > src)
		return memcpy_backwards(dst,src,n);
	else
		return memcpy_forward(dst,src,n);
}

int main(int argc, char **argv)
{
	const int N = 10000;
	const int SIZE = 4;
	void *src = malloc(SIZE);
	void *dst = malloc(SIZE);
	int i;
	
	long double memcpy_total = 0;
	for(i = 0; i < N; ++i)
	{
		clock_t	start = clock();
		memcpy(dst,src,SIZE);
		memcpy_total += (clock() - start);
	}

	long double memmove_total = 0;
	for(i = 0; i < N; ++i)
	{
		clock_t	start = clock();
		memmove(dst,src,SIZE);
		memmove_total += (clock() - start);
	}
	printf("memcpy is time: %.2f ms\n", memcpy_total);
	printf("memmove is time: %.2f ms\n", memmove_total);
	if(memmove_total > memcpy_total)
		printf("memcpy is time: %.2f ms\n times faster\n", memmove_total / memcpy_total);
	else
		printf("Surprise!\memmove is time: %.2f ms\n times faster then memcpy\n", memcpy_total / memmove_total);
	
	
	return 0;
}
