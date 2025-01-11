ENTRY(_start)

SECTIONS
{
  /DISCARD/ : {
    *(.note.gnu.property)
  }

  .text :
  {
    *(.text*)
    *(.rodata*)
  }

  .data :
  {
    *(.data*)
  }

  .bss :
  {
    *(.bss*)
  }
}
