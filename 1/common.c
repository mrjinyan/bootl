#include "s3c2440-regsaddr.h"


/*

.align 4 
1:	ldr r3,[r1,#oUTRSTAT]@�Ӵ��ڵ�״̬�Ĵ����ж�ȡ��ֵ
	tst r3,#0x0002
	beq 1b @�жϴ��ڼĴ����Ƿ���æ��״̬
	#��Ĵ�����������
	strb r2,[r1,#oUTXHL] @��æ��ʱ��ͽ�����д��
	@��Ҫ��ת�����2��
	b 2f @д��֮�������
Pget:
	#������ڵ㣬����ִֻ����һ��
	ldr r1,=UART_CTL_BASE
2:    ldrb r2,[r0],#1@��r0����ʼ��ַ�л�ȡ�ֽ�
	cmp r2,#0  @����ȡ���ֽ���0�ȶԣ��ж��Ƿ�Ϊ������
	bne 1b @�������ȣ�˵�����ǣ�����ת��1��
	@���Ӻ����з��صĺ�������
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

