#include "s3c2440-regsaddr.h"
.section .text.vector
	b Reset
UndefEntryPoint:
	b UndefEntryPoint
SWIEntryPoint:
	b SWIEntryPoint
PrefetchAbortEntryPoint:
	b PrefetchAbortEntryPoint
DataAbortEntryPoint:
	b DataAbortEntryPoint
NotUsedEntryPoint:
	b NotUsedEntryPoint
IRQEntryPoint:
	b IRQEntryPoint
@0x1c size space
FIQEntryPoint:
	b FIQEntryPoint
.section .text
Reset:
////////////////////////////////////////////////////////////////////////////////////////////////

	ldr r0,=0x53000000
	ldr r1,=0x0000
	str r1,[r0]
	ldr r0,=0x4A000000//使用的伪指令，OK
	ldr r1,=0xffffffff
	str r1,[r0]
	ldr r0,=0x4A000008
	ldr r1,=0xffffffff
	str r1,[r0]
	ldr r0,=0x4A00001c
	ldr r1,=0xffffffff
	str r1,[r0]
////////////////////////////////////////////////////////////////////////////////////////////////
	ldr r0,=CLKCFG_BASEADDR
	ldr r1,=LOCKTIME_CFGVALUE
	str r1,[r0,#LOCKTIME_OFFSET]
	ldr r1,=UPLLCON_CFGVAL
	str r1,[r0,#UPLLCON_OFFSET]
	ldr r1,=CLKDIVN_CFGVAL
	str r1,[r0,#CLKDIVN_OFFSET]
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0xc0000000
	mcr p15,0,r0,c1,c0,0
	ldr r0,=CLKCFG_BASEADDR
	ldr r1,=MPLLCON_CFGVAL
	str r1,[r0,#MPLLCON_OFFSET]
////////////////////////////////////////////////////////////////////////////////////////////////
	ldr sp,=SP
//////////////////////////////////////////////////////////////////////////////////////////////////
 	bl memsetup
////////////////////////////////////////////////////////////////////////////////////////////////
	ldr r0,=0x0016faaa
	ldr r1,=GPH_CON
	str r0,[r1]
	ldr r0,=0x000007ff
	ldr r1,=GPH_UP
	str r0,[r1]
//
//	ldr r0,=0x55555555
//	ldr r1,=GPB_CON
//	str r0,[r1]
//	ldr r0,=0xffffffff
//	ldr r1,=GPB_UP
//	str r0,[r1]
//	ldr r0,=0x0
//	ldr r1,=GPB_DAT
//	str r0,[r1]
////////////////////////////////////////////////////////////////////////////////////////////////
	ldr r0,=ULCON0
	ldr r1,=0x03
	str r1,[r0]
	//UCON 0b0000_00_0_1_0_1_0_0_01_01
	ldr r0,=UCON0
	ldr r1,=0x245
	str r1,[r0]
	//UFCON 0b00_00_0_0_0_0
	ldr r0,=UFCON0
	ldr r1,=0x0
	str r1,[r0]
	//UMCON 0b00000000
	ldr r0,=UMCON0
	ldr r1,=0x0
	str r1,[r0]
	//UBRDIV UBRDIV
	ldr r0,=UBRDIV0
	ldr r1,=UBRDIVVAL
	str r1,[r0]
	mov r3,#100
	mov r2,#0
	1:sub r3,r3,#0x1
	tst r2,r3
	bne 1b
	
	bl main
1:	b 1b
memsetup:
         mov     r1, #MEMCFG_BASE
         adrl    r2, MEMCFG_POOL
         add     r3, r1, #52
 1:      ldr     r4, [r2], #4
         str     r4, [r1], #4
         cmp     r1, r3
         bne     1b
         mov     pc, lr

.global ReadPage512
ReadPage512:
        stmfd   sp!, {r2-r7,r8}
        mov     r2, #0x200
	 mov r3,r0
	 mov r8,r1
1:
        ldr     r4, [r8]
        ldr     r5, [r8]
        ldr     r6, [r8]
        ldr     r7, [r8]
        stmia   r3!, {r4-r7}
        ldr     r4, [r8]
        ldr     r5, [r8]
        ldr     r6, [r8]
        ldr     r7, [r8]
        stmia   r3!, {r4-r7}
        ldr     r4, [r8]
        ldr     r5, [r8]
        ldr     r6, [r8]
        ldr     r7, [r8]
        stmia   r3!, {r4-r7}
        ldr     r4, [r8]
        ldr     r5, [r8]
        ldr     r6, [r8]
        ldr     r7, [r8]
        stmia   r3!, {r4-r7}
        subs    r2, r2, #64
        bne     1b;
        ldmfd   sp!, {r2-r7,r8}
        mov     pc,lr

.align 4
MEMCFG_POOL:
.long 	vBWSCON
.long	vBANKCON0
.long	vBANKCON1 
.long	vBANKCON2 
.long	vBANKCON3
.long	vBANKCON4
.long	vBANKCON5
.long	vBANKCON6
.long	vBANKCON7
.long	vREFRESH
.long	vBANKSIZE
.long	vMRSRB6
.long	vMRSRB7



	
