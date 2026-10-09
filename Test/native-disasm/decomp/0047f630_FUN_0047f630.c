// FUN_0047f630 @ 0047f630 size=81 callers=1

void FUN_0047f630(void)

{
  if (DAT_004a2508 != (void *)0x0) {
    guard_check_icall();
    FUN_00435da0();
    FUN_00402430(DAT_004a2508,DAT_004a2510 - (int)DAT_004a2508 >> 2,4);
    DAT_004a2508 = (void *)0x0;
    DAT_004a250c = 0;
    DAT_004a2510 = 0;
  }
  return;
}


