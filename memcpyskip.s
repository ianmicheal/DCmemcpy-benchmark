	.globl _memcpyskip

	.text

	! r4 = dest
	! r5 = src
	! r6 = size

_memcpyskip:
	mov.w	@r5, r7
	add	#-8, r6
	mov.w	r7, @r4	
	add	#8, r5
	cmp/pl	r6
	bt/s	_memcpyskip
	add	#2, r4	
	rts	
	nop

	.end

