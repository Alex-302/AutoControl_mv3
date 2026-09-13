// FUN_0047f150 @ 0047f150 size=87 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0047f150(void)

{
  void *pvVar1;
  
  pvVar1 = DAT_004a2538;
  if (0xf < DAT_004a254c) {
    FUN_0043ba10();
    FUN_00402430(pvVar1,DAT_004a254c + 1,1);
  }
  DAT_004a254c = 0xf;
  _DAT_004a2548 = 0;
  DAT_004a2538 = (void *)((uint)DAT_004a2538 & 0xffffff00);
  guard_check_icall();
  return;
}


