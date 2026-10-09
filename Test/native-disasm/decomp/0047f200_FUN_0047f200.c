// FUN_0047f200 @ 0047f200 size=80 callers=1

void FUN_0047f200(void)

{
  if (DAT_004a3370 != (void *)0x0) {
    guard_check_icall();
    FUN_00435da0();
    FUN_00402430(DAT_004a3370,DAT_004a3378 - (int)DAT_004a3370 >> 1,2);
    DAT_004a3370 = (void *)0x0;
    DAT_004a3374 = 0;
    DAT_004a3378 = 0;
  }
  return;
}


