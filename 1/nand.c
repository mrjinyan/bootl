#include "s3c2440-regsaddr.h"
#include "common.h"
//读取该地址值，并将该第二个bit置0，再放回去。
/*
.macro sNF_nFCE_L
	ldr r0,=NAND_CTL_BASE
	ldr r1,[r0,#oNFCONT]
	bic r1,r1,#0x0002
       str r1,[r0,#oNFCONT]
*/
#define NF_nFCE_L() {(*NFCONT) &= ~(1<<1);}
/*
.macro sNF_nFCE_H
	ldr r0,=NAND_CTL_BASE
	ldr r1,[r0,#oNFCONT]
	orr r1,r1,#0x0002
       str r1,[r0,#oNFCONT]
*/
#define NF_nFCE_H() {(*NFCONT) |= (1<<1);}
/*
.macro sRDDATAB
	ldr r0,=NAND_CTL_BASE
	ldrb r1,[r0,#oNFDATA]
*/
#define RDDATAB() (*NFDATA)  
/*
.macro sNFCMDf cmd_in_reg
	ldr r0,=NAND_CTL_BASE
	str \cmd_in_reg,[r0,#oNFCMD]
	
*/
#define NFCMDf(cmd) {(*NFCMD) = cmd;}
/*
.macro sNFADDRf addr_in_reg
	ldr r0,=NAND_CTL_BASE
	str \addr_in_reg,[r0,#oNFADDR]
*/
#define NFADDRf(addr) {*NFADDR = addr;}
/*
.macro sNF_CLEAR_RB
	ldr r0,=NAND_CTL_BASE
	ldr r1,[r0,#oNFSTAT]
	orr r1,r1,#0x0004
       str r1,[r0,#oNFSTAT]
*/
#define NF_CLEAR_RB() {(*NFSTAT) |= (1<<2);}
/*
.macro sWAITRB
	ldr r0,=NAND_CTL_BASE
1:	ldr r1,[r0,#oNFSTAT]@read the content of NFSTAT register preparing for bit 2 testing.
	tst r1,#0x0001
	beq 1b
*/
#define WAITRB() {while(!((*NFSTAT)&(1<<0)));}
//当该位为1的时候，跳出循环。
/*
.macro sDETECTRB
	ldr r0,=NAND_CTL_BASE
1:	ldr r1,[r0,#oNFSTAT]@read the content of NFSTAT register preparing for bit 2 testing.
	tst r1,#0x0004
	beq 1b  
*/
#define DETECTRB() {while(!((*NFSTAT)&(1<<2)));}

extern void ReadPage512(unsigned char* buf,volatile unsigned char* nf_data_ptr);
/*
	NandReset:
		push r3
		NF_nFCE_L		@although it looks a little weird, it is just the correct usage.
		NF_CLEAR_RB
		ldr r3,=0xff
		NFCMDf r3
		DETECTRB
		NF_nFCE_H
		pop r3
		mov pc lr
*/
 void static inline NandReset(void){
  
	  //select the chip and enable it
	  
          NF_nFCE_L();
	  //clean the RB bit
          NF_CLEAR_RB();
          NFCMDf(0xff);
          DETECTRB();
          NF_nFCE_H();
  }
/*
NandCheckID:
	  push {r3,r4}
	  NF_nFCE_L
	  ldr r3,=0x90
	  NFCMDf r3
	  ldr r3,=0x0
	  NFADDRf r3
	  RDDATAB
	  mov r3,r1
	  RDDATAB
	  mov r4,r1
	  RDDATAB
	  mov r3,r1
	  RDDATAB
	  mov r3,r1
	  NF_nFCE_H
	  ldr r3,=0xda
	  cmp r3,#0xda
	  bne end
	  ldr r0,=DEBUG_CHECKID@存储字符串的地址
	  push lr
	  bl Pget
	  pop lr
end:	  pop{r3,r4}
	  mov pc,lr

*/
  void static inline NandCheckID(void){

          unsigned char mid,did,concare,id4th;
          NF_nFCE_L();
          NFCMDf(0x90);
          NFADDRf(0X0);
          mid = RDDATAB();
          did = RDDATAB();
          concare = RDDATAB();
          id4th = RDDATAB();
          NF_nFCE_H();
          if(did==0xda) Print("IT IS DA!\n\r");

  }
  void NandInit(void){
  
          SET_TACLS(0x0);
          SET_TWRPH0(0X6);
          SET_TWRPH1(0X2);
	  /*
		ldr r0,=0
		ldr r1,=6
		orr r0,r0,r1,LSL#8 @possible ele: LSL
		ldr r1,=2
		orr r0,r0,r1,LSL#4
		ldr r1,=NAND_CTL_BASE
		str r0,[r1,oNFCONF] 
	  */
          *NFCONF = (0X0<<12)|(0X6<<8)|(0X2<<4);
	  // 9: 0, disable RnB interrupt
	  // 8: 0, detect the rising edge
	  // 6: 0, open ECC for backup zone
	  // 5: 0, open ECC for main zone
	  // 4: 1, intialize ECC coder/decoder
	  // 1: 1, make nFCE high, disable chip
	  // 0: 1, enable Nand controller
	  
	    /*
		ldr r0,=0
		ldr r1,=1
		orr r0,r0,r1,LSL#4
		ldr r1,=1
		orr r0,r0,r1,LSL#1
		ldr r1,=1
		orr r0,r0,r1,LSL#0
		ldr r1,=NAND_CTL_BASE
		str r0,[r1,oNFCONT] 
	  */
          *NFCONT = (0<<13)|(0<<12)|(0<<10)|(0<<9)|(0<<8)|(0<<6)|(0<<5)|(1<<4)|(1<<1)|(1<<0);
          *NFSTAT = 0;
          NandReset();
          NandCheckID();
  }
  
  /*
	@r3: row
       IsBadBlock:
       	push {r3,r4}
       	mov r3,r0,LSR#11
       	push lr
       	bl NandReset
       	pop lr
       	NF_nFCE_L
       	NF_CLEAR_RB
		ldr r4,=0
		NFCMDf r4
		ldr r4,=2048
		and r4,r4,0xff
		NFADDRf r4
		ldr r4,=2048
		mov r4,r4,LSR#8
		and r4,r4,#0x0f
		NFADDRf r4
		mov r4,r3
		and r4,r4,#0xff
		NFADDRf r4
		mov r4,r3,LSR#8 @row>>8
		and r4,r4,0xff
		NFADDRf r4
		mov r4,r3,LSR#16@row>>16
		and r4,r4,0x01
		NFADDRf r4
		ldr r4,=0x30
		NFCMDf r4
		DETECTRB
		RDDATAB
		mov r4,r1
		NF_nFCE_H
		ldr r3,=0xff
		cmp r3,r4
		beq end1
		ldr r0,=1
		b end
     end1:
		ldr r0,=0
	end:
		pop {r3,r4}
       	mov pc,lr
  */
  
unsigned int IsBadBlock(unsigned int addr){
 
         unsigned int row = addr>>11;
         unsigned char bad_value;
         NandReset();
         NF_nFCE_L();
         NF_CLEAR_RB();
         NFCMDf(0x0);
         //big or little endian is a problem
         NFADDRf(2048&0xff);
         NFADDRf((2048>>8)&0x0f);
         NFADDRf(row&0xff);
         NFADDRf((row>>8)&0xff);
         NFADDRf((row>>16)&0x01);
         NFCMDf(0x30);
         DETECTRB();
         bad_value = RDDATAB();
         NF_nFCE_H();
         if(bad_value == 0xff) return 0;
         else return 1;//it is a bad block
 }


/*
ReadOneSector:
	push {r3-r7}
	mov r5,r0 @dst_addr
	mov r3,r1@col
	mov r4,r1@row
	and r3,r3,#0x0fff
	mov r4,r4,LSR#11
	push lr
	bl NandReset
	pop lr
	NF_nFCE_L
	NF_CLEAR_RB
	ldr r1,=0x00
	NFCMDf r1
	NFADDRf r1
	NFADDRf r1
	and r6,r4,0xff
	NFADDRf r6
	mov r6,r4,LSR#8
	and r6,r6,oxff
	NFADDRf r6
	mov r6,r4,LSR#16
	and r6,r6,oxff
	NFADDRf r6
	ldr r6,=0x30
	NFCMDf r6
	DETECTRB
@ the following loop requires that both r0,r1 not be used in ReadPage512.
	ldr r7,=0
	mov r0,r5
	sub r0,r0,#512
	ldr r1,=NAND_CTL_BASE
       add r1,r1,#oNFDATA
1:	cmp r7,#4
	beq next
	add r0,#512    @increase by 512 each time
	push lr
	bl ReadPage
	pop lr
	add r7,r7,#1
	b 1b
next:
	NF_nFCE_H
	pop {r3-r7}
	mov pc,lr
*/
void ReadOneSector(unsigned char* dst_addr,unsigned int src_addr){
 
         unsigned int row,col;
         col = src_addr&0x0fff;
         //row = (src_addr>>16)&0x1ffff;//>>16 is wrong, mislead by Page 9.the content of different a    ddress cycle.
         row = src_addr>>11;
         NandReset();
         NF_nFCE_L();
         NF_CLEAR_RB();
         NFCMDf(0x00);
         NFADDRf(0x00);
         NFADDRf(0x00);
         NFADDRf((row)&0xff);
         NFADDRf((row>>8)&0xff);
         NFADDRf((row>>16)&0xff);
         NFCMDf(0x30);
         DETECTRB();
         //notice that read from NFDATA register
         //Read2048Page(dst_addr,NFDATA);        
         ReadPage512(dst_addr+0*512,NFDATA);
         ReadPage512(dst_addr+1*512,NFDATA);
         ReadPage512(dst_addr+2*512,NFDATA);
         ReadPage512(dst_addr+3*512,NFDATA);
         NF_nFCE_H();
 }

