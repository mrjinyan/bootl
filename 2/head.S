#include "s3c2440-regsaddr.h"
.macro sSET_TACLS val
	ldr r0,=NAND_CTL_BASE
	ldr r1,[r0,#oNFCONF]
	bic r1,r1,#0x3000
	ldr r2,=\val
	orr r1,r1,r2,LSL #12       
	str r1,[r0,#oNFCONF]
.endm
.macro sSET_TWRPH0 val
	ldr r0,=NAND_CTL_BASE
	ldr r1,[r0,#oNFCONF]
	bic r1,r1,#0x0600
	ldr r2,=\val
	orr r1,r1,r2,LSL #8       
	str r1,[r0,#oNFCONF]
.endm
.macro sSET_TWRPH1 val
	ldr r0,=NAND_CTL_BASE
	ldr r1,[r0,#oNFCONF]
	bic r1,r1,#0x0070
	ldr r2,=\val
	orr r1,r1,r2,LSL #4       
	str r1,[r0,#oNFCONF]
.endm
.macro sNF_nFCE_L
	ldr r0,=NAND_CTL_BASE
	ldr r1,[r0,#oNFCONT]
	bic r1,r1,#0x0002
    str r1,[r0,#oNFCONT]
.endm
.macro sNF_nFCE_H
	ldr r0,=NAND_CTL_BASE
	ldr r1,[r0,#oNFCONT]
	orr r1,r1,#0x0002
       str r1,[r0,#oNFCONT]
.endm
.macro sRDDATAB
	ldr r0,=NAND_CTL_BASE
	ldrb r1,[r0,#oNFDATA]
.endm
.macro sNFCMDf cmd_in_reg
	ldr r0,=NAND_CTL_BASE
	str \cmd_in_reg,[r0,#oNFCMD]
.endm
.macro sNFADDRf addr_in_reg
	ldr r0,=NAND_CTL_BASE
	str \addr_in_reg,[r0,#oNFADDR]
.endm
.macro sNF_CLEAR_RB
	ldr r0,=NAND_CTL_BASE
	ldr r1,[r0,#oNFSTAT]
	orr r1,r1,#0x0004
    str r1,[r0,#oNFSTAT]
.endm
.macro sWAITRB
	ldr r0,=NAND_CTL_BASE
1:	ldr r1,[r0,#oNFSTAT]@read the content of NFSTAT register preparing for bit 2 testing.
	tst r1,#0x0001
	beq 1b
.endm
.macro sDETECTRB
	ldr r0,=NAND_CTL_BASE
1:	ldr r1,[r0,#oNFSTAT]@read the content of NFSTAT register preparing for bit 2 testing.
	tst r1,#0x0004
	beq 1b  
.endm


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
	ldr r0,=0x4A000000// π”√µƒŒ±÷∏¡Ó£¨OK
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

    //following code functions as PortInit
        ldr r0,=sGPACON
		ldr r1,=0X7FFFFF
		str r1,[r0]
		ldr r0,=sGPBCON
		ldr r1,=0X044555
		str r1,[r0]
		ldr r0,=sGPBUP
		ldr r1,=0X7FF
		str r1,[r0]
		ldr r0,=sGPCCON
		ldr r1,=0XAAAAAAAA
		str r1,[r0]
		ldr r0,=sGPCUP
		ldr r1,=0XFFFF
		str r1,[r0]
		ldr r0,=sGPDCON
		ldr r1,=0x00151544
		str r1,[r0]
		ldr r0,=sGPDUP
		ldr r1,=0x877a
		str r1,[r0]
		ldr r0,=sGPDDAT
		ldr r1,=0x0430
		str r1,[r0]
		ldr r0,=sGPECON
		ldr r1,=0xaa2aaaaa
		str r1,[r0]
		ldr r0,=sGPEUP
		ldr r1,=0xf7ff
		str r1,[r0]
		ldr r0,=sGPFCON
		ldr r1,=0x55aa
		str r1,[r0]
		ldr r0,=sGPFUP
		ldr r1,=0xff
		str r1,[r0]
		ldr r0,=sGPGCON
		ldr r1,=0x100
		str r1,[r0]
		ldr r0,=sGPGDAT
		ldr r1,=0
		str r1,[r0]
		ldr r0,=sEXTINT0
		ldr r1,=0x22222222
		str r1,[r0]
		ldr r0,=sEXTINT1
		str r1,[r0]
		ldr r0,=sEXTINT2
		str r1,[r0]

        //following code function as NandInit
        sSET_TACLS 0x0
        sSET_TWRPH0 0x6
        sSET_TWRPH0 0x2
        ldr r0,=0
		ldr r1,=6
		orr r0,r0,r1,LSL #8 @possible ele: LSL
		ldr r1,=2
		orr r0,r0,r1,LSL #4
		ldr r1,=NAND_CTL_BASE
		str r0,[r1,#oNFCONF] 
        ldr r0,=0
		ldr r1,=1
		orr r0,r0,r1,LSL #4
		ldr r1,=1
		orr r0,r0,r1,LSL #1
		ldr r1,=1
		orr r0,r0,r1,LSL #0
		ldr r1,=NAND_CTL_BASE
		str r0,[r1,#oNFCONT] 
        bl sNandReset
        bl sNandCheckID
        bl copy
1:	b 1b
memsetup:
         mov     r1, #MEMCFG_BASE
         adrl    r2, MEMCFG_POOL
         add     r3, r1, #52
 1:      ldr     r4, [r2], #4
         str     r4, [r1], #4
         cmp     r1, r3
         bne     1b
         mov     pc,lr
.global ReadPage512
ReadPage512:
        stmfd   sp!, {r2-r7,r8}
        mov     r2,#0x200
        mov     r3,r0
        mov     r8,r1
1:
        ldr     r4, [r8]
        ldr     r5, [r8]
        ldr     r6, [r8]
        ldr     r7, [r8]
        stmia   r3!,{r4-r7}
        ldr     r4, [r8]
        ldr     r5, [r8]
        ldr     r6, [r8]
        ldr     r7, [r8]
        stmia   r3!,{r4-r7}
        ldr     r4, [r8]
        ldr     r5, [r8]
        ldr     r6, [r8]
        ldr     r7, [r8]
        stmia   r3!,{r4-r7}
        ldr     r4, [r8]
        ldr     r5, [r8]
        ldr     r6, [r8]
        ldr     r7, [r8]
        stmia   r3!,{r4-r7}
        subs    r2,r2,#64
        bne     1b;
        ldmfd   sp!,{r2-r7,r8}
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


/*
1 parameter: r0,the address of string that is going to be printed.
2 example of calling routine:
  ldr r0,=str_1
  bl sPrint
*/
.align 4 
1:	ldr r3,[r1,#oUTRSTAT]  
	tst r3,#0x0002
	beq 1b                 
	strb r2,[r1,#oUTXHL]   
	b 2f 
sPrint:
	ldr r1,=UART_CTL_BASE
    	push {r3}
2:  	ldrb r2,[r0],#1  
	cmp r2,#0     
	bne 1b         
    	pop {r3}
	mov pc,lr
.align 4
str_1:
.ascii "Keep going!\0"
.align 4
str_2:
.ascii "ID is right!\0"
.align 4
str_3:
.ascii "Here 1!\0"
.align 4
str_4:
.ascii "Here 2!\0"
.align 4
str_5:
.ascii "Here 3!\0"
.align 4
str_6:
.ascii "Here 4!\0"

.align 4
sNandReset:
		push {r3}
		sNF_nFCE_L		@although it looks a little weird, it is just the correct usage.
		sNF_CLEAR_RB
		ldr r3,=0xff
		sNFCMDf r3
		sDETECTRB
		sNF_nFCE_H
		pop {r3}
		mov pc,lr
.align 4
sNandCheckID:
	  push {r3,r4}
	  sNF_nFCE_L
	  ldr r3,=0x90
	  sNFCMDf r3
	  ldr r3,=0x0
	  sNFADDRf r3
	  sRDDATAB
	  mov r3,r1
	  sRDDATAB
	  mov r4,r1
	  sRDDATAB
	  mov r3,r1
	  sRDDATAB
	  mov r3,r1
	  sNF_nFCE_H
	  ldr r3,=0xda
	  cmp r3,#0xda
	  bne end
	  ldr r0,=str_2
	  push {lr}
	  bl sPrint
	  pop {lr}
end:      pop {r3,r4}
	  mov pc,lr
.align 4
sIsBadBlock:
       	push {r3,r4}
       	mov r3,r0,LSR #11
       	push {lr}
       	bl sNandReset
       	pop {lr}
       	sNF_nFCE_L
       	sNF_CLEAR_RB
	ldr r4,=0
	sNFCMDf r4
	ldr r4,=2048
	and r4,r4,#0xff
	sNFADDRf r4
	ldr r4,=2048
	mov r4,r4,LSR #8
	and r4,r4,#0x0f
	sNFADDRf r4
	mov r4,r3
	and r4,r4,#0xff
	sNFADDRf r4
	mov r4,r3,LSR #8
	and r4,r4,#0xff
	sNFADDRf r4
	mov r4,r3,LSR #16
	and r4,r4,#0x01
	sNFADDRf r4
	ldr r4,=0x30
	sNFCMDf r4
	sDETECTRB
	sRDDATAB
	mov r4,r1
	sNF_nFCE_H
	ldr r3,=0xff
	cmp r3,r4
	beq end1
	ldr r0,=1
	b 2f 
end1:
	ldr r0,=str_3
	push {lr}
	bl sPrint
	pop {lr}
	ldr r0,=0
2:
	pop {r3,r4}
       	mov pc,lr
.align 4
sReadOneSector:
	push {r3-r7}
	mov r5,r0 @dst addr
	mov r3,r1 @contain src addr
	mov r4,r1 @same as above
	ldr r0,=0x0fff
	and r3,r3,r0 @get col
	mov r4,r4,LSR #11 @get row
	push {lr}
	bl sNandReset
	pop {lr}
	sNF_nFCE_L
	sNF_CLEAR_RB
	ldr r1,=0x00
	sNFCMDf r1
	sNFADDRf r1
	sNFADDRf r1
	and r6,r4,#0xff
	sNFADDRf r6
	mov r6,r4,LSR #8
	and r6,r6,#0xff
	sNFADDRf r6
	mov r6,r4,LSR #16
	and r6,r6,#0xff
	sNFADDRf r6
	ldr r6,=0x30
	sNFCMDf r6
	sDETECTRB
@ the following loop requires that both r0,r1 not be used in ReadPage512.
	ldr r7,=0
	mov r0,r5
	sub r0,r0,#512
	ldr r1,=NAND_CTL_BASE
    	add r1,r1,#oNFDATA
1:	cmp r7,#4
	beq next
	add r0,#512    @increase by 512 each time
	push {lr}
	bl ReadPage512
	pop {lr}
	push {r0,r1,r2,lr}
	ldr r0,=str_5
	bl sPrint
	pop {r0,r1,r2,lr}
	add r7,r7,#1
	b 1b
next:
	sNF_nFCE_H
	pop {r3-r7}
	mov pc,lr

@#define p_size (1<<p_shift)//0x0800
@#define b_size (p_size<<b_shift_p)//0x20000
@r3: øøøø
@r4: øøøø
@r5: posøø
@r6:formal parameter;p_pos
@r7:ram_start

.align 4
@no need to return for "copy process"
copy:
	ldr r0,=str_1
	bl sPrint @keep going
	ldr r3,=0  @blocknum
	ldr r4,__start
	ldr r5,__end
	sub r4,r5,r4
	add r4,r4,#0x0800
	sub r4,r4,#1
	mov r4,r4,LSR #17
	mov r4,r4,LSL #17
	ldr r7,=0x30000000
	ldr r5,=0 	   @equal to variable pos

copy_loop:
	cmp r5,r4
	bne copy_loop_end  @if r5 is equal or greater to r4, then jump out the loop,else execute related code

checkbadblock_loop:
	ldr r0,=str_2   @ID is right
	bl sPrint
	mov r6,r3       @r6 used for calculating and passing the parameters 
	mov r6,r6,LSL #17
	mov r0,r6
	bl sIsBadBlock  @Here 1
	cmp r0,#0       @it indicates that the return value is in r0~
	beq doing_copy  @if equal, jump out the loop of checking bad blocks
	add r3,r3,#1
@@@@@@@@@
	ldr r0,=str_1
	bl sPrint  	@if it is a bad block
@@@@@@@@@
	b checkbadblock_loop
doing_copy:

	//ldr r0,=str_2
	//bl sPrint

	ldr r6,=0 @equal to p_pos
1:	cmp r6,#0x20000
	beq end_copy_oneblk 	   @if equal,one block has been copied. 
	@prepare the parameters
	ldr r8,=0
	mov r8,r3,LSL #11
	add r8,r8,r6
	@pass the parameters
	mov r0,r7
	mov r1,r8
	bl sReadOneSector
	add r6,r6,#0x0800
	add r7,r7,#0x0800
	b 1b
end_copy_oneblk:
	ldr r0,=str_6
	bl sPrint
	add r3,r3,#1
	add r5,r5,#0x20000
	b copy_loop
copy_loop_end:
	ldr r0,=str_5
	bl sPrint
	ldr pc,=main
__start:
.word _start_prog
__end:
.word _end_prog
