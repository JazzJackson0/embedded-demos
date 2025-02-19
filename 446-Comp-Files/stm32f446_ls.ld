ENTRY(Reset_Handler)

MEMORY 
{ 
	FLASH (RX) : ORIGIN = 0x08000000, LENGTH = 512K
	SRAM (RWX) : ORIGIN = 0x20000000, LENGTH = 128K
}



SECTIONS 
{

	.text :

	{
		*( .isr_vector ) /* Merge all .isr_vector sections from all input files */
		*( .text ) /* Merge all .text sections from all input files */
		*( .text.* ) /* Merges any other .text.<something> sections. */
		*( .rodata ) /* Merge all .rodata sections from all input files */
		*( .rodata.* ) /* Merges any other .rodata.<something> sections. */
		. = ALIGN(4); /* Ensures the section starts at an address that is a multiple of 4 bytes for proper alignment. */
		_etext = .; /* Defines a SYMBOL marking [END] of .text section */
	}> FLASH
	/* FLASH (Code Storage): Holds the executable code (.text) and constants (.rodata).*/

	_la_data = LOADADDR(.data); /* Get the load address of .data section in FLASH */

	

	.data :
	{
		_sdata = .; /* Defines a SYMBOL marking [START] of .data section */
		*( .data ) /* Merge all .data sections from all input files */
		*( .data.* ) /* Merges any other .data.<something> sections. */
		. = ALIGN(4);
		_edata = .; /* Defines a SYMBOL marking [END] of .data section */

	}> SRAM AT> FLASH /* Startup code copies .data section from FLASH to SRAM */


	
	.bss :
	{
		_sbss = .; /* Defines a SYMBOL marking [START] of .bss section */
		__bss_start__ = _sbss; /* Defines a SYMBOL marking [START] of .bss section */
		*( .bss )
		*( .bss.* )
		. = ALIGN(4);
		_ebss = .; /* Defines a SYMBOL marking [END] of .bss section */
		__bss_end__ = _ebss; /* Defines a SYMBOL marking [END] of .bss section */
		. = ALIGN(4);
		end = .; /* Defines a SYMBOL marking [END] of Entire Memory Layout */
	}> SRAM
		/* SRAM (Runtime Data): Holds initialized data (.data), uninitialized data (.bss), 
			and dynamically allocated variables (heap and stack)*/
}



