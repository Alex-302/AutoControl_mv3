// FUN_0047ee00 @ 0047ee00 size=87 callers=1

void FUN_0047ee00(void)

{
  void *pvVar1;
  
  pvVar1 = DAT_004a2580;
  if (0xf < DAT_004a2594) {
    FUN_0043ba10();
    FUN_00402430(pvVar1,DAT_004a2594 + 1,1);
  }
  DAT_004a2594 = 0xf;
  DAT_004a2590 = 0;
  DAT_004a2580 = (void *)((uint)DAT_004a2580 & 0xffffff00);
  guard_check_icall();
  return;
}


