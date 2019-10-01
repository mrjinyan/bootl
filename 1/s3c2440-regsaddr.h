/* UART */
#define UART_CTL_BASE  0x50000000
#define UART0_CTL_BASE  UART_CTL_BASE
#define UART1_CTL_BASE  UART_CTL_BASE + 0x4000
#define UART2_CTL_BASE  UART_CTL_BASE + 0x8000
#define bUART(x, Nb)  (UART_CTL_BASE + (x)*0x4000 + (Nb))
#define bUARTb(x, Nb) (UART_CTL_BASE + (x)*0x4000 + (Nb))/* Offset */
#define oULCON   0x00 /* R/W, UART line control register */
#define oUCON    0x04 /* R/W, UART control register */
#define oUFCON   0x08 /* R/W, UART FIFO control register */
#define oUMCON   0x0C /* R/W, UART modem control register */
#define oUTRSTAT 0x10 /* R  , UART Tx/Rx status register */
#define oUERSTAT 0x14 /* R  , UART Rx error status register */
#define oUFSTAT  0x18 /* R  , UART FIFO status register */
#define oUMSTAT  0x1C /* R  , UART Modem status register */
#define oUTXHL   0x20 /* W, UART transmit(little-end) buffer */
#define oUTXHB   0x23 /* W, UART transmit(big-end) buffer */
#define oURXHL   0x24 /* R  , UART receive(little-end) buffer */
#define oURXHB   0x27 
#define oUBRDIV  0x28 /* R/W, Baud rate divisor register *//* Registers */
#define ULCON0   bUART(0, oULCON)
#define UCON0    bUART(0, oUCON)
#define UFCON0   bUART(0, oUFCON)
#define UMCON0   bUART(0, oUMCON)
#define UTRSTAT0 bUART(0, oUTRSTAT)
#define UERSTAT0 bUART(0, oUERSTAT)
#define UFSTAT0  bUART(0, oUFSTAT)
#define UMSTAT0  bUART(0, oUMSTAT)
#define UTXH0    bUARTb(0, oUTXHL)
#define URXH0    bUARTb(0, oURXHL)
#define UBRDIV0  bUART(0, oUBRDIV)

#define UART_PCLK 50625000
#define BRD 115200
#define UBRDIVVAL ((UART_PCLK/(BRD*16))-1)
//UART operations
#define TX (volatile char*)(UTXH0)
#define IsReady (volatile char*)(UTRSTAT0)
//void Print(char *str);  靠靠靠靠靠靠
/////////////////////////////////////////////////////////
#define GPIO_CTL_BASE 0X56000000
#define GP_CON_OFFSET 0X0
#define GP_DAT_OFFSET 0X4
#define GP_UP_OFFSET 0X8
#define __REGL(x) (*(volatile unsigned long*)(x))

#define OGPA 0x00
#define OGPB 0x10
#define OGPC 0x20
#define OGPD 0x30
#define OGPE 0x40
#define OGPF 0x50
#define OGPG 0x60
#define OGPH 0x70
#define OEXTINT0 0x88
#define OEXTINT1 0x8c
#define OEXTINT2 0x90
#define bGPIO(p,o)  __REGL(GPIO_CTL_BASE + (p)+(o)) 
#define GPACON  bGPIO(OGPA,GP_CON_OFFSET)
#define GPAUP   bGPIO(OGPA,GP_UP_OFFSET)
#define GPADAT  bGPIO(OGPA,GP_DAT_OFFSET)
#define GPBCON  bGPIO(OGPB,GP_CON_OFFSET)
#define GPBUP   bGPIO(OGPB,GP_UP_OFFSET)
#define GPBDAT  bGPIO(OGPB,GP_DAT_OFFSET)
#define GPCCON bGPIO(OGPC,GP_CON_OFFSET)
#define GPCUP  bGPIO(OGPC,GP_UP_OFFSET)
#define GPCDAT bGPIO(OGPC,GP_DAT_OFFSET)
#define GPDCON  bGPIO(OGPD,GP_CON_OFFSET)
#define GPDUP   bGPIO(OGPD,GP_UP_OFFSET)
#define GPDDAT  bGPIO(OGPD,GP_DAT_OFFSET)
#define GPECON  bGPIO(OGPE,GP_CON_OFFSET)
#define GPEUP   bGPIO(OGPE,GP_UP_OFFSET)
#define GPEDAT  bGPIO(OGPE,GP_DAT_OFFSET)
#define GPFCON  bGPIO(OGPF,GP_CON_OFFSET)
#define GPFUP   bGPIO(OGPF,GP_UP_OFFSET)
#define GPFDAT  bGPIO(OGPF,GP_DAT_OFFSET)
#define GPGCON  bGPIO(OGPG,GP_CON_OFFSET)
#define GPGUP   bGPIO(OGPG,GP_UP_OFFSET)
#define GPGDAT  bGPIO(OGPG,GP_DAT_OFFSET)
#define EXTINT0 bGPIO(OEXTINT0,0)
#define EXTINT1 bGPIO(OEXTINT1,0)
#define EXTINT2 bGPIO(OEXTINT2,0)

#define __REGLADDR(x) (x)//为了汇编中使用
#define sbGPIO(p,o)  __REGLADDR(GPIO_CTL_BASE + (p)+(o)) 
#define sGPACON  sbGPIO(OGPA,GP_CON_OFFSET)
#define sGPAUP   sbGPIO(OGPA,GP_UP_OFFSET)
#define sGPADAT  sbGPIO(OGPA,GP_DAT_OFFSET)
#define sGPBCON  sbGPIO(OGPB,GP_CON_OFFSET)
#define sGPBUP   sbGPIO(OGPB,GP_UP_OFFSET)
#define sGPBDAT  sbGPIO(OGPB,GP_DAT_OFFSET)
#define sGPCCON sbGPIO(OGPC,GP_CON_OFFSET)
#define sGPCUP  sbGPIO(OGPC,GP_UP_OFFSET)
#define sGPCDAT sbGPIO(OGPC,GP_DAT_OFFSET)
#define sGPDCON  sbGPIO(OGPD,GP_CON_OFFSET)
#define sGPDUP   sbGPIO(OGPD,GP_UP_OFFSET)
#define sGPDDAT  sbGPIO(OGPD,GP_DAT_OFFSET)
#define sGPECON  sbGPIO(OGPE,GP_CON_OFFSET)
#define sGPEUP   sbGPIO(OGPE,GP_UP_OFFSET)
#define sGPEDAT  sbGPIO(OGPE,GP_DAT_OFFSET)
#define sGPFCON  sbGPIO(OGPF,GP_CON_OFFSET)
#define sGPFUP   sbGPIO(OGPF,GP_UP_OFFSET)
#define sGPFDAT  sbGPIO(OGPF,GP_DAT_OFFSET)
#define sGPGCON  sbGPIO(OGPG,GP_CON_OFFSET)
#define sGPGUP   sbGPIO(OGPG,GP_UP_OFFSET)
#define sGPGDAT  sbGPIO(OGPG,GP_DAT_OFFSET)
#define sEXTINT0 sbGPIO(OEXTINT0,0)
#define sEXTINT1 sbGPIO(OEXTINT1,0)
#define sEXTINT2 sbGPIO(OEXTINT2,0)






#define GPH_CON (GPIO_CTL_BASE + 0X70)
#define GPH_UP (GPIO_CTL_BASE + 0X70 + GP_UP_OFFSET)


#define GPB_OFFSET 0X10
#define GPH_OFFSET 0X70
#define GPB_CON (GPIO_CTL_BASE+GPB_OFFSET)
#define GPB_DAT (GPIO_CTL_BASE+GPB_OFFSET+GP_DAT_OFFSET)
#define GPB_UP  (GPIO_CTL_BASE+GPB_OFFSET+GP_UP_OFFSET)
/////////////////////////////////////////////////////////

#define CLKCFG_BASEADDR 0X4C000000
#define LOCKTIME_OFFSET 0X0
#define MPLLCON_OFFSET 0X4
#define UPLLCON_OFFSET 0X8
#define CLKCON_OFFSET 0XC
#define CLKDIVN_OFFSET 0X14

#define MEMCFG_BASE 0X48000000
//直接给出配置值即可转化为相应的数值
#define M_MDIV 0x7f
#define M_PDIV 0x2
#define M_SDIV 0x1
//405兆
#define U_MDIV 0x38
#define U_PDIV 0x2
#define U_SDIV 0x2
//下面的内容根据寄存器的内容设置
#define MDIV_POS 12
#define PDIV_POS 4
#define SDIV_POS 0
#define CFG_PLL(MDIV,PDIV,SDIV) ((MDIV<<MDIV_POS)+(PDIV<<PDIV_POS)+(SDIV<<SDIV_POS))

#define LOCKTIME_CFGVALUE 0XFFFFFFFF 
#define MPLLCON_CFGVAL CFG_PLL(M_MDIV,M_PDIV,M_SDIV)
#define UPLLCON_CFGVAL CFG_PLL(U_MDIV,U_PDIV,U_SDIV)
//#define CLKCON_CFGVAL 不用配置了
#define CLKDIVN_CFGVAL 0x5 //1:4:8

#define RAM_BASEADDR 0X30000000
#define RAM_SIZE 0X4000000
#define SP (RAM_BASEADDR+RAM_SIZE-4)
#define vBWSCON   0x22111110//这几个寄存器用来控制BANK0~BANK5外界设备的访问时序，一般使用默认的0x700即可。
#define vBANKCON0  0x00000700
#define vBANKCON1  0x00000700
#define vBANKCON2  0x00000700
#define vBANKCON3  0x00000700
#define vBANKCON4  0x00000700
#define vBANKCON5  0x00000700//0000-0000-0000-0001-1000-0000-0000-1001
#define vBANKCON6  0x00018009
#define vBANKCON7  0x00018009
#define vBANKSIZE  0xB2//128MB/128MB(bank7和bank6存储空间分配)，使能突发操作，SDRAM power down模式有效，SCLK仅当访问周期才被激活
#define vMRSRB6   0x30
#define vMRSRB7   0x30    //第9位?
#define vREFRESH 0x008e04eb

///////////////////////////////////////////////////////
//NandFlash addr
#define NAND_CTL_BASE 0X4E000000
#define oNFCONF 0x00
#define oNFCONT 0x04 
#define oNFCMD 0x08
#define oNFADDR 0x0c
#define oNFDATA 0x10
#define oNFSTAT 0x20
#define oNFECC 0x2c
//operations
#define NFCONF  ((volatile unsigned long*)(NAND_CTL_BASE + oNFCONF))
#define NFCONT  ((volatile unsigned long*)(NAND_CTL_BASE + oNFCONT))
#define NFCMD   ((volatile unsigned long*)(NAND_CTL_BASE   + oNFCMD))
#define NFADDR ((volatile unsigned long*)(NAND_CTL_BASE + oNFADDR))
#define NFDATA  ((volatile unsigned char*)(NAND_CTL_BASE  + oNFDATA))
//only bit 0 is in use, other bits are reserved.
#define NFSTAT  ((volatile unsigned long*)(NAND_CTL_BASE  + oNFSTAT))
#define NFECC   ((volatile unsigned long*)(NAND_CTL_BASE   + oNFECC))
//configure parameters
////////
//bit mask: test if its zero
#define TACLS_M 0x3000
#define TWRPH0_M 0x0600
#define TWRPH1_M 0x0070
//bit offset: used to set corresponding value
#define oTACLS 12 
#define oTWRPH0 8
#define oTWRPH1 4
//notice that the value can not overflow the width of corresponding bit
//first, clear corresponding bits and then, set the new value
//fixed method to name the mask and offset of one register
//先将对应位清零，然后再将要写入的数值存放到相应位置
#define SET_BIT(reg,bit_name,val) ((*reg) = (  (*reg)&(~(bit_name##_M)))|(val<<(o##bit_name))  )
// (*NFCONF) = ( (*NFCONF) & (~(TACLS_M) ) )|(val<<(oTACLS))
/*
.macro SET_TACLS val
	ldr r0,=NAND_CTL_BASE
	ldr r1,[r0,#oNFCONF]
	bic r1,r1,0x3000
	ldr r2,\val
	orr r1,r1,r2,LSL#12       
	str r1,[r0,oNFCONF]
*/
#define SET_TACLS(val)  SET_BIT(NFCONF,TACLS,val)
/*
.macro SET_TWRPH0 val
	ldr r0,=NAND_CTL_BASE
	ldr r1,[r0,#oNFCONF]
	bic r1,r1,0x0600
	ldr r2,\val
	orr r1,r1,r2,LSL#8       
	str r1,[r0,oNFCONF]
*/
#define SET_TWRPH0(val) SET_BIT(NFCONF,TWRPH0,val)
/*
.macro SET_TWRPH1 val
	ldr r0,=NAND_CTL_BASE
	ldr r1,[r0,#oNFCONF]
	bic r1,r1,0x0070
	ldr r2,\val
	orr r1,r1,r2,LSL#4       
	str r1,[r0,oNFCONF]
*/
#define SET_TWRPH1(val) SET_BIT(NFCONF,TWRPH1,val)
