

all:
	arm-linux-gcc -nostdlib -mabi=aapcs-linux -mno-thumb-interwork -Os -Wall  -c head.S main.c common.c nand.c
	arm-linux-ld -T uart.lds -Bstatic head.o main.o common.o nand.o
	arm-linux-objcopy -O binary -S a.out head.bin -R .comment -R .stab -R .stabstr
#	rm *.o a.out
clean:
	rm head.bin 
