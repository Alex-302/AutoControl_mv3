// FUN_0047f420 @ 0047f420 size=81 callers=1

void FUN_0047f420(void)

{
  if (DAT_004a27f0 != (void *)0x0) {
    guard_check_icall();
    FUN_00435da0();
    FUN_00402430(DAT_004a27f0,DAT_004a27f8 - (int)DAT_004a27f0 >> 2,4);
    DAT_004a27f0 = (void *)0x0;
    DAT_004a27f4 = 0;
    DAT_004a27f8 = 0;
  }
  return;
}


