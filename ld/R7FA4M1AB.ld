MEMORY
{
   FIXED_VECTOR_TABLE (rx)          : ORIGIN = 0x00000000, LENGTH = 0x400
   OFS_ROM (r)                      : ORIGIN = 0x00000400, LENGTH = 0x100
   ROM (rx)                         : ORIGIN = 0x00000500, LENGTH = 0x00040000 - ORIGIN(ROM)
   RAM (rwx)                        : ORIGIN = 0x20000000, LENGTH = 32K
   ID_CODE_ROM (rx)                 : ORIGIN = 0x01010018, LENGTH = 0x20
   DATA_FLASH (rx)                  : ORIGIN = 0x40100000, LENGTH = 8K
}

ENTRY(start)

SECTIONS
{
   .vectors :
   {
      _vectors_start = .;
      _dtc_vectors_start = .;
      KEEP(*(.vectors*))
      _mappable_vectors_start = .;
      KEEP(*(.mappable_vectors*))
      KEEP(*(.dtc_vectors*))
   } > FIXED_VECTOR_TABLE

   .ofs :
   {
      KEEP(*(.ofs*))
   } > OFS_ROM

   .text :
   {
      *(.text*)

      KEEP(*(.version))
      KEEP(*(.init))
      KEEP(*(.fini))

      *(.rodata*)

      KEEP(*(.eh_frame*))
   } > ROM

   .ARM.extab :
   {
      *(.ARM.extab* .gnu.linkonce.armextab.*)
   } > ROM

   __exidx_start = .;
   .ARM.exidx :
   {
      *(.ARM.exidx* .gnu.linkonce.armexidx.*)
   } > ROM
   __exidx_end = .;

   .etext :
   {
      . = ALIGN(4);
      _etext = .;
   } > ROM

   .data :
   {
      . = ALIGN(4);
      _data = .;

      *(vtable)
      *(.data.*)

      . = ALIGN(4);
      PROVIDE_HIDDEN (__preinit_array_start = .);
      KEEP(*(.preinit_array))
      PROVIDE_HIDDEN (__preinit_array_end = .);

      . = ALIGN(4);
      PROVIDE_HIDDEN (__init_array_start = .);
      KEEP(*(SORT(.init_array.*)))
      KEEP(*(.init_array))
      PROVIDE_HIDDEN (__init_array_end = .);

      . = ALIGN(4);
      PROVIDE_HIDDEN (__fini_array_start = .);
      KEEP(*(SORT(.fini_array.*)))
      KEEP(*(.fini_array))
      PROVIDE_HIDDEN (__fini_array_end = .);

      KEEP(*(.jcr*))

      . = ALIGN(4);
      _edata = .;
   } > RAM AT > ROM

   .bss :
   {
      . = ALIGN(4);
      _bss = .;
      *(.bss*)
      *(COMMON)
      . = ALIGN(4);
      _ebss = .;
   } > RAM

   .id_code :
   {
      KEEP(*(.id_code*))
   } > ID_CODE_ROM

   .data_flash :
   {
      KEEP(*(.data_flash*))
   } > DATA_FLASH

   _stack_start = ORIGIN(RAM) + LENGTH(RAM) - 4;
}
