/*###ICF### Section handled by ICF editor, don't touch! ****/
/*-Editor annotation file-*/
/* IcfEditorFile="$TOOLKIT_DIR$\config\ide\IcfEditor\a_v1_0.xml" */
/*-Specials-*/
define symbol __ICFEDIT_intvec_start__ = 0x0;
/*-Memory Regions-*/
define symbol __ICFEDIT_region_ROM_start__ = 0x80;
define symbol __ICFEDIT_region_ROM_end__   = 0x1FFFF;
define symbol __ICFEDIT_region_RAM_start__ = 0x100000;
define symbol __ICFEDIT_region_RAM_end__   = 0x1FFFFF;
/*-Sizes-*/
define symbol __ICFEDIT_size_cstack__   = 0x2000;
define symbol __ICFEDIT_size_svcstack__ = 0x100;
define symbol __ICFEDIT_size_irqstack__ = 0x100;
define symbol __ICFEDIT_size_fiqstack__ = 0x100;
define symbol __ICFEDIT_size_undstack__ = 0x100;
define symbol __ICFEDIT_size_abtstack__ = 0x100;
define symbol __ICFEDIT_size_heap__     = 0x8000;
/**** End of ICF editor section. ###ICF###*/


define memory mem with size = 4G;
define region ROM_region   = mem:[from __ICFEDIT_region_ROM_start__   to __ICFEDIT_region_ROM_end__];
define region RAM_region   = mem:[from __ICFEDIT_region_RAM_start__   to __ICFEDIT_region_RAM_end__];

define block CSTACK    with alignment = 8, size = __ICFEDIT_size_cstack__   { };
define block SVC_STACK with alignment = 8, size = __ICFEDIT_size_svcstack__ { };
define block IRQ_STACK with alignment = 8, size = __ICFEDIT_size_irqstack__ { };
define block FIQ_STACK with alignment = 8, size = __ICFEDIT_size_fiqstack__ { };
define block UND_STACK with alignment = 8, size = __ICFEDIT_size_undstack__ { };
define block ABT_STACK with alignment = 8, size = __ICFEDIT_size_abtstack__ { };
define block HEAP      with alignment = 8, size = __ICFEDIT_size_heap__     { };

initialize by copy { readwrite };
do not initialize  { section .noinit };

place at address mem:__ICFEDIT_intvec_start__ { readonly section .intvec };

place in ROM_region   { readonly };
place in RAM_region   { readwrite,
                        block CSTACK, block SVC_STACK, block IRQ_STACK, block FIQ_STACK,
                        block UND_STACK, block ABT_STACK, block HEAP };