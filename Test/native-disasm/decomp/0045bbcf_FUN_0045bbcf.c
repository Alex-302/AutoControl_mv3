// FUN_0045bbcf @ 0045bbcf size=129 callers=1

void FUN_0045bbcf(void)

{
  int iVar1;
  int unaff_EBX;
  int unaff_EBP;
  int *unaff_EDI;
  
  *(undefined4 *)(unaff_EBX + -4) = *(undefined4 *)(unaff_EBP + -0x2c);
  FUN_0045d075(*(int *)(unaff_EBP + -0x30));
  iVar1 = ___vcrt_getptd();
  *(undefined4 *)(iVar1 + 0x10) = *(undefined4 *)(unaff_EBP + -0x34);
  iVar1 = ___vcrt_getptd();
  *(undefined4 *)(iVar1 + 0x14) = *(undefined4 *)(unaff_EBP + -0x38);
  if (((((*unaff_EDI == -0x1f928c9d) && (unaff_EDI[4] == 3)) &&
       ((unaff_EDI[5] == 0x19930520 ||
        ((unaff_EDI[5] == 0x19930521 || (unaff_EDI[5] == 0x19930522)))))) &&
      (*(int *)(unaff_EBP + -0x3c) == 0)) &&
     ((*(int *)(unaff_EBP + -0x1c) != 0 &&
      (iVar1 = __IsExceptionObjectToBeDestroyed(unaff_EDI[6]), iVar1 != 0)))) {
    ___DestructExceptionObject(unaff_EDI);
  }
  return;
}


