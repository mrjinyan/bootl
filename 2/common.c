#include "s3c2440-regsaddr.h"



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

