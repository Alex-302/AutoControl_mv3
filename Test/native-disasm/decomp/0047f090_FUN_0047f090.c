// FUN_0047f090 @ 0047f090 size=81 callers=1

void FUN_0047f090(void)

{
  if (DAT_004a2598 != (void *)0x0) {
    guard_check_icall();
    FUN_00435da0();
    FUN_00402430(DAT_004a2598,DAT_004a25a0 - (int)DAT_004a2598 >> 2,4);
    DAT_004a2598 = (void *)0x0;
    DAT_004a259c = 0;
    DAT_004a25a0 = 0;
  }
  return;
}


