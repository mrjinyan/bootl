SECTIONS{
. =000000;
.myhead ALIGN(0): {*(.text.vector)}
.text ALIGN(4):{*(.text)}
.bss ALIGN(4) :{*(.bss*) *(COMMON)}
.data ALIGN(4) : {*(.data*) *(.rodata*)}
}
