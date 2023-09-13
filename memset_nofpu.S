//TODO finish and test this

.globl _memset
.globl _memset_nofpu

#define len	r6
#define pattern	r5
#define dst	r4

_memset:
_memset_nofpu:
		tst	len, len
//		mov	#32, r3
		bt	.Lmemset_nofpu_rts
//		cmp/hi	len, r3
//		bt .Lmemset_nofpu_long
		add	len, dst
	.Lmemset_short:
		dt	len
	.align 2
	1:	mov.b	pattern, @-dst
		bf/s	1b
		 dt	len
	.Lmemset_nofpu_rts:
		rts
		 mov	dst, r0
#if 0
	.Lmemset_nofpu_long:
		tst	pattern, pattern
		extu.b	pattern, pattern
		bt	.Lmemset_zero_pattern
		swap.b	pattern, r3
		or	r3, pattern
		swap.w	pattern, r3
		or	r3, pattern
	.Lmemset_zero_pattern:
		
		//Get to cacheline alignment
	.align 2
		mov	dst, r0
		tst	#1, r0
		bt/s	.Lmemset_word_aligned
		 tst	#2, r0
		mov.b	pattern, @-r0
		add	#-1, len
	.Lmemset_word_aligned:
		bt	.Lmemset_long_aligned
		mov.w	pattern, @-r0
		add	#-2, len
	.Lmemset_long_aligned:
		mov.l	pattern, @-r0
		tst	#CPU_CACHELINE_MASK, r0
		bf/s	.Lmemset_long_aligned
		 add	#-4, len
	.Lmemset_cacheline_aligned:
		mov	#CPU_CACHELINE_SIZE, r1
		mov	r0, dst
		
		cmp/hs	len, r1		//Do we have more than a cacheline to go?
		mov	pattern, r0
		
		bt	.Lmemset_short
		add	#-4, dst
	1:
		movca.l	r0, @dst
		mov.l	r0, @-dst
		mov.l	r0, @-dst
		mov.l	r0, @-dst
		mov.l	r0, @-dst
		mov.l	r0, @-dst
		add	#-CPU_CACHELINE_SIZE, len
		mov.l	r0, @-dst
		cmp/hi	len, r1
		mov.l	r0, @-dst
		ocbwb	@dst
		bt/s	1b
		 add	#-4, dst
		add	#4, dst
		tst	len, len
		bf/s	.Lmemset_short
		 mov	r0, len
		rts
		 mov	dst, r0
		
#endif
