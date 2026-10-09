// FUN_0047f5a0 @ 0047f5a0 size=97 callers=1

void FUN_0047f5a0(void)

{
  void *pvVar1;
  
  pvVar1 = DAT_004a25b4;
  if (0xf < DAT_004a25c8) {
    FUN_0043ba10();
    FUN_00402430(pvVar1,DAT_004a25c8 + 1,1);
  }
  DAT_004a25c8 = 0xf;
  DAT_004a25c4 = 0;
  DAT_004a25b4 = (void *)((uint)DAT_004a25b4 & 0xffffff00);
  guard_check_icall();
  FUN_00435c40(&DAT_004a25a8);
  return;
}


