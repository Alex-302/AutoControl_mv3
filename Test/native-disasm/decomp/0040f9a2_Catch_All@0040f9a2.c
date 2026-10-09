// Catch_All@0040f9a2 @ 0040f9a2 size=190 callers=1

undefined * Catch_All_0040f9a2(void)

{
  int unaff_EBP;
  void *in_stack_ffffffe8;
  
  *(undefined1 *)(unaff_EBP + -0x60) = 0;
  *(undefined8 *)(unaff_EBP + -0x58) = 0;
  FUN_00451110((undefined1 *)(unaff_EBP + -0x60),(uint *)"exception");
  *(undefined1 *)(unaff_EBP + -4) = 2;
  *(undefined1 *)(unaff_EBP + -0x50) = 0;
  *(undefined8 *)(unaff_EBP + -0x48) = 0;
  FUN_00451110((undefined1 *)(unaff_EBP + -0x50),(uint *)"Exception in lambda function");
  *(undefined1 *)(unaff_EBP + -4) = 3;
  FUN_00434b50((void *)(unaff_EBP + -0x30),(char *)(unaff_EBP + -0x60),(char *)(unaff_EBP + -0x40),
               '\x01','\x02');
  *(undefined1 *)(unaff_EBP + -4) = 5;
  _eh_vector_destructor_iterator_((void *)(unaff_EBP + -0x60),0x10,2,FUN_00434820);
  *(undefined1 *)(unaff_EBP + -4) = 6;
  FUN_00434b50((void *)(unaff_EBP + -0x40),(char *)(unaff_EBP + -0x30),(char *)(unaff_EBP + -0x20),
               '\x01','\x02');
  *(undefined1 *)(unaff_EBP + -4) = 7;
  FUN_004355e0(&stack0xffffffe8,(uint *)"NH-except");
  FUN_00408c90((void *)(unaff_EBP + -0x40),in_stack_ffffffe8);
  FUN_00434820((char *)(unaff_EBP + -0x40));
  *(undefined1 *)(unaff_EBP + -4) = 1;
  _eh_vector_destructor_iterator_((void *)(unaff_EBP + -0x30),0x10,1,FUN_00434820);
  return &DAT_0040fa60;
}


