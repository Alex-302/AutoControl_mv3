// Unwind@0047a807 @ 0047a807 size=40 callers=1

void Unwind_0047a807(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + 0x74) & 0x80) != 0) {
    *(uint *)(unaff_EBP + 0x74) = *(uint *)(unaff_EBP + 0x74) & 0xffffff7f;
    _eh_vector_destructor_iterator_((void *)(unaff_EBP + -0x2c),0x10,1,FUN_00434820);
  }
  return;
}


