// FUN_0040fa66 @ 0040fa66 size=73 callers=2

void FUN_0040fa66(void)

{
  int *piVar1;
  int unaff_EBP;
  int *unaff_ESI;
  HANDLE unaff_EDI;
  
  if ((unaff_EDI != (HANDLE)0x0) && ((char)unaff_ESI[10] != '\0')) {
    SetEvent(unaff_EDI);
  }
  piVar1 = (int *)unaff_ESI[9];
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x10))(piVar1 != unaff_ESI);
    unaff_ESI[9] = 0;
  }
  FUN_0045a6a4(unaff_ESI);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}


