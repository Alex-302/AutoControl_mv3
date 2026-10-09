// Catch_All@00409426 @ 00409426 size=330 callers=1

undefined4 Catch_All_00409426(void)

{
  undefined4 *puVar1;
  int unaff_EBP;
  void *in_stack_ffffffe8;
  char cVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  
  *(undefined1 *)(unaff_EBP + -0x6c) = 0;
  *(undefined8 *)(unaff_EBP + -100) = 0;
  FUN_00451110((undefined1 *)(unaff_EBP + -0x6c),(uint *)"stdinMsg");
  *(undefined1 *)(unaff_EBP + -4) = 7;
  puVar1 = FUN_00440e70((void *)(unaff_EBP + 0x3c),(uint *)&DAT_0048cf60);
  FUN_00434940((void *)(unaff_EBP + -0x5c),(undefined1 *)puVar1);
  *(undefined1 *)(unaff_EBP + -4) = 8;
  FUN_00434b50((void *)(unaff_EBP + -0x8c),(char *)(unaff_EBP + -0x6c),(char *)(unaff_EBP + -0x4c),
               '\x01','\x02');
  *(undefined1 *)(unaff_EBP + -4) = 10;
  _eh_vector_destructor_iterator_((void *)(unaff_EBP + -0x6c),0x10,2,FUN_00434820);
  *(undefined1 *)(unaff_EBP + 0xc) = 0;
  *(undefined8 *)(unaff_EBP + 0x14) = 0;
  FUN_00451110((undefined1 *)(unaff_EBP + 0xc),(uint *)"exception");
  *(undefined1 *)(unaff_EBP + -4) = 0xb;
  *(undefined1 *)(unaff_EBP + 0x1c) = 0;
  *(undefined8 *)(unaff_EBP + 0x24) = 0;
  FUN_00451110((undefined1 *)(unaff_EBP + 0x1c),(uint *)"error processing stdin msg");
  *(undefined1 *)(unaff_EBP + -4) = 0xc;
  FUN_00434b50((void *)(unaff_EBP + -0x7c),(char *)(unaff_EBP + 0xc),(char *)(unaff_EBP + 0x2c),
               '\x01','\x02');
  *(undefined1 *)(unaff_EBP + -4) = 0xe;
  _eh_vector_destructor_iterator_((void *)(unaff_EBP + 0xc),0x10,2,FUN_00434820);
  *(undefined1 *)(unaff_EBP + -4) = 0xf;
  FUN_00434b50((void *)(unaff_EBP + -0x40),(char *)(unaff_EBP + -0x8c),(char *)(unaff_EBP + -0x6c),
               '\x01','\x02');
  *(undefined1 *)(unaff_EBP + -4) = 0x10;
  FUN_004355e0(&stack0xffffffe8,(uint *)"NH-except");
  FUN_00408c90((void *)(unaff_EBP + -0x40),in_stack_ffffffe8);
  FUN_00434820((char *)(unaff_EBP + -0x40));
  uVar3 = 0x10;
  *(undefined1 *)(unaff_EBP + -4) = 6;
  _eh_vector_destructor_iterator_((void *)(unaff_EBP + -0x8c),0x10,2,FUN_00434820);
  cVar2 = '\0';
  uVar4 = 0;
  FUN_00451110(&stack0xfffffff0,(uint *)"exception");
  FUN_004348c0((void *)(unaff_EBP + 0x2c),cVar2,uVar3,(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
  return 0x4093aa;
}


