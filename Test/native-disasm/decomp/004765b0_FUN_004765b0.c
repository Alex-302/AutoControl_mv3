// FUN_004765b0 @ 004765b0 size=79 callers=1

void FUN_004765b0(void)

{
  ushort in_FPUControlWord;
  float10 in_ST0;
  double dVar1;
  
  if ((DAT_004a33e4 != 0) && ((MXCSR & 0x7f80) == 0x1f80 && (in_FPUControlWord & 0x7f) == 0x7f)) {
    FUN_00476bf0();
    return;
  }
  dVar1 = (double)in_ST0;
  FUN_0046faa8(SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
  FUN_00476608(SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
  return;
}


