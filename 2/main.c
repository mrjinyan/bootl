#include "s3c2440-regsaddr.h"
#include "nand.h"
#include "common.h"

void PortInit(void);
extern void Read2048Page(unsigned char* dst,volatile unsigned char* addr);
#define p_shift 11
#define b_shift_p 6 
//notice that the block size contain valid content
#define p_size (1<<p_shift)
#define b_size (p_size<<b_shift_p)
#define os_ram_start 0x30008000
#define os_nand_start 0x60000
#define os_length 0x500000

const char cmdline[] = "noinitrd root=/dev/mtdblock3p init=/linuxrc console=ttySAC0";

void callinux(void);
void CopyLinuxFromNand(void);
	
int main(void){
	Print("Cancel Portinit\n");
	//PortInit();
	//NandInit();	
	//ReadOneSector((unsigned char*)Buf,0x48000);	
	CopyLinuxFromNand();
	Print("before judege!");
	return 0;
}
void CopyLinuxFromNand(void){
 
         //get the address of os in nand
         unsigned int BlockNum,pos,Length;
         BlockNum = os_nand_start>>(p_shift+b_shift_p);
         Length = ((os_length+b_size-1)>>(p_shift+b_shift_p))<<(p_shift+b_shift_p);
         unsigned int ram_start = os_ram_start;
 
         for(pos=0;pos<Length;pos+=b_size){
                 unsigned int p_pos;
                 for(;;){
                         //if it is a good block, then break;
                         if(!IsBadBlock(BlockNum<<(p_shift+b_shift_p))){
                                 break;
                         }
                         BlockNum++;
                 }//for check if it is a block   
                 //
                 for(p_pos = 0;p_pos<b_size;p_pos+=p_size,ram_start+=p_size){
                         //source address: start address + offset
                         ReadOneSector((unsigned char*)ram_start,(BlockNum<<(p_shift+b_shift_p))+p_pos);
                 }//for copy sectors
                 BlockNum++;
         }//for copy loop
         //unsigned int*pp = (unsigned int*)(0x30008024);
         //if(pp[0]==0x016f2818) Print("\r\nSuo Long!!\r\n");
         //else Print("\r\nNot the right time!!\r\n");
         callinux();
 }

void callinux(void){
	
	struct param_struct {
                  union {
                          struct {
                                  unsigned long page_size;        /*  0 */
                                  unsigned long nr_pages; /*  4 */
                                  unsigned long ramdisk_size;     /*  8 */
                                  unsigned long flags;    /* 12 */
                                  unsigned long rootdev;  /* 16 */
                                  unsigned long video_num_cols;   /* 20 */
                                  unsigned long video_num_rows;   /* 24 */
                                  unsigned long video_x;  /* 28 */
                                  unsigned long video_y;  /* 32 */
                                  unsigned long memc_control_reg; /* 36 */
                                  unsigned char sounddefault;     /* 40 */
                                  unsigned char adfsdrives;       /* 41 */
                                  unsigned char bytes_per_char_h; /* 42 */
                                  unsigned char bytes_per_char_v; /* 43 */
                                  unsigned long pages_in_bank[4]; /* 44 */
                                  unsigned long pages_in_vram;    /* 60 */
                                  unsigned long initrd_start;     /* 64 */
                                  unsigned long initrd_size;      /* 68 */
                                  unsigned long rd_start; /* 72 */
                                  unsigned long system_rev;       /* 76 */
                                  unsigned long system_serial_low;        /* 8    0 */
                                  unsigned long system_serial_high;       /* 8    4 */
                                  unsigned long mem_fclk_21285;   /* 88 */
                          } s;
                          char unused[256];//Ö»ÓÃÀ´Õ¼ÓÃ¿Õ¼ä
                  } u1;
                  union {
                          char paths[8][128];
                          struct {
                                  unsigned long magic;
                                  char n[1024 - sizeof(unsigned long)];
                          } s;//1024¸ö×Ö½Ú
                  } u2;
                  char commandline[1024];
          };//struct paramter
	  struct param_struct *p = (struct param_struct*)(0x30000000);
	  memset(p,0,sizeof(struct param_struct));
	  p->u1.s.page_size = 4*1024;
	  p->u1.s.nr_pages = 64*1024*1024/(4*1024);
	  memcpy(p->commandline,cmdline,sizeof(cmdline)); 
	 asm(
	"mov r5,%2\n"	
	"mov r0,%0\n"
	"mov r1,%1\n"
	"mov r2,%3\n"
	"mov ip,#0\n"
	"mov pc,r5\n"
	"nop\n" "nop\n":
	:"r"(0),"r"(1999),"r"(os_ram_start),"r"(0x30000000)
	); 
}//end of calinux
void PortInit(void){
          GPACON = 0X7FFFFF;
          GPBCON = 0X044555;
          GPBUP = 0X7FF;
          GPCCON = 0XAAAAAAAA;
          GPCUP = 0XFFFF;
          GPDCON = 0x00151544;
          GPDUP = 0x877a;
          GPDDAT = 0x0430;
          GPECON = 0xaa2aaaaa;
          GPEUP  = 0xf7ff;
          GPFCON = 0x55aa;
          GPFUP= 0xff;
          GPGCON = 1<<8;
          GPGDAT = 0;
          EXTINT0 = 0x22222222;
          EXTINT1 = 0x22222222;
          EXTINT2 = 0x22222222;
  }

