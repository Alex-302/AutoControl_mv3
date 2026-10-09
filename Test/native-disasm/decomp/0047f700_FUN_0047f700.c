// FUN_0047f700 @ 0047f700 size=81 callers=1

void FUN_0047f700(void)

{
  if (DAT_004a3360 != (void *)0x0) {
    guard_check_icall();
    FUN_00435da0();
    FUN_00402430(DAT_004a3360,DAT_004a3368 - (int)DAT_004a3360 >> 2,4);
    DAT_004a3360 = (void *)0x0;
    DAT_004a3364 = 0;
    DAT_004a3368 = 0;
  }
  return;
}


