// caseD_2b @ 00423bcb size=57 callers=2

undefined4 switchD_0042396b::caseD_2b(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  
  if (**(int **)(unaff_EBP + 0x14) == 1) {
    uVar1 = FUN_0041e910((int)*(int **)(unaff_EBP + 0x14));
    ExceptionList = *(void **)(unaff_EBP + -0xc);
    return uVar1;
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return 0;
}


