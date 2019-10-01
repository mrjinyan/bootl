#include "s3c2440-regsaddr.h"
#include "common.h"
#define NF_nFCE_L() {(*NFCONT) &= ~(1<<1);}
#define NF_nFCE_H() {(*NFCONT) |= (1<<1);}
#define RDDATAB() (*NFDATA)  
#define NFCMDf(cmd) {(*NFCMD) = cmd;}
#define NFADDRf(addr) {*NFADDR = addr;}
#define WAITRB() {while(!((*NFSTAT)&(1<<0)));}
#define NF_CLEAR_RB() {(*NFSTAT) |= (1<<2);}
#define DETECTRB() {while(!((*NFSTAT)&(1<<2)));}

//This function is defined in head.S
extern void ReadPage512(unsigned char* buf,volatile unsigned char* nf_data_ptr);

 void static inline NandReset(void){
  
	  //select the chip and enable it
          NF_nFCE_L();
	  //clean the RB bit
          NF_CLEAR_RB();
          NFCMDf(0xff);
          DETECTRB();
          NF_nFCE_H();
  }
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
          *NFCONF = (0X0<<12)|(0X6<<8)|(0X2<<4);
	  // 9: 0, disable RnB interrupt
	  // 8: 0, detect the rising edge
	  // 6: 0, open ECC for backup zone
	  // 5: 0, open ECC for main zone
	  // 4: 1, intialize ECC coder/decoder
	  // 1: 1, make nFCE high, disable chip
	  // 0: 1, enable Nand controller
          *NFCONT = (0<<13)|(0<<12)|(0<<10)|(0<<9)|(0<<8)|(0<<6)|(0<<5)|(1<<4)|(1<<1)|(1<<0);
          *NFSTAT = 0;
          NandReset();
          NandCheckID();
  }


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
         //Read2048Page(dst_addr,NFDATA);        
         ReadPage512(dst_addr+0*512,NFDATA);
         ReadPage512(dst_addr+1*512,NFDATA);
         ReadPage512(dst_addr+2*512,NFDATA);
         ReadPage512(dst_addr+3*512,NFDATA);
         NF_nFCE_H();
 }

