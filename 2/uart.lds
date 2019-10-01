SECTIONS{
. = 0x30000000;
.myhead ALIGN(0):
{
	_start_prog = .;
	*(.text.vector);
}
.text ALIGN(4):
{
	*(.text);
}
.bss ALIGN(4) :
{
	*(.bss*) *(COMMON);
}
.data ALIGN(4) : 
{
	*(.data*) *(.rodata*);
	_end_prog = .;
}
}
