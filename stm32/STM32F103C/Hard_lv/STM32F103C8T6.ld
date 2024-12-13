/* Memory layout */
MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
  RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 20K
}

/* Sections */
SECTIONS
{
  .isr_vector : {
    KEEP(*(.isr_vector)) /* Vector table */
  } > FLASH

  .text : {
    *(.text*)           /* Code */
    *(.rodata*)         /* Read-only data */
    KEEP(*(.init))      /* Startup */
  } > FLASH

  .data : {
    _sdata = .;         /* Start of data section */
    *(.data*)           /* Initialized data */
    _edata = .;         /* End of data section */
  } > RAM AT > FLASH

  .bss : {
    _sbss = .;          /* Start of BSS section */
    *(.bss*)            /* Uninitialized data */
    *(COMMON)
    _ebss = .;          /* End of BSS section */
  } > RAM

  /* Stack configuration */
  _estack = ORIGIN(RAM) + LENGTH(RAM);
  PROVIDE(_stack = _estack);
}
