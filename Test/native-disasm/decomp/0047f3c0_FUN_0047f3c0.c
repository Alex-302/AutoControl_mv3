// FUN_0047f3c0 @ 0047f3c0 size=81 callers=1

void FUN_0047f3c0(void)

{
  if (DAT_004a28c0 != (void *)0x0) {
    guard_check_icall();
    FUN_00435da0();
    FUN_00402430(DAT_004a28c0,DAT_004a28c8 - (int)DAT_004a28c0 >> 2,4);
    DAT_004a28c0 = (void *)0x0;
    DAT_004a28c4 = 0;
    DAT_004a28c8 = 0;
  }
  return;
}


