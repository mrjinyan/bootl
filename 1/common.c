#include "s3c2440-regsaddr.h"


/*

.align 4 
1:	ldr r3,[r1,#oUTRSTAT]@从串口的状态寄存器中读取数值
	tst r3,#0x0002
	beq 1b @判断串口寄存器是否处于忙的状态
	#向寄存器发送数据
	strb r2,[r1,#oUTXHL] @不忙的时候就将内容写入
	@需要跳转到标号2处
	b 2f @写完之后继续读
Pget:
	#函数入口点，这里只执行了一次
	ldr r1,=UART_CTL_BASE
2:    ldrb r2,[r0],#1@从r0的起始地址中获取字节
	cmp r2,#0  @将获取的字节与0比对，判断是否为结束符
	bne 1b @如果不相等，说明不是，则跳转到1处
	@从子函数中返回的函数代码
	mov pc,lr
*/
void Print(char *str){
         while(*str!='\0'){
                 while(!((*IsReady)&0x2));
                 (*TX) = *str;
                 str++;
         }//while
 }
void* memset(void* dst,int src,unsigned int len){
         char *p = dst;
         while(len--)
                 *p++ = src;
         return dst;
 
 }
void memcpy(void* dst,const void* src,unsigned int size){
 
         const char* s = src;
         char * d = dst;
         while(size--)
                 *d++ = *s++;
 
 }

