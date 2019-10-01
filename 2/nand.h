
#ifndef NAND_H_
#define NAND_H_
void NandInit(void);
unsigned int IsBadBlock(unsigned int addr);
void ReadOneSector(unsigned char* dst_addr,unsigned int src_addr);
#endif






