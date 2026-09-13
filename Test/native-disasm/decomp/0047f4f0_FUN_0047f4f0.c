// FUN_0047f4f0 @ 0047f4f0 size=87 callers=1

void FUN_0047f4f0(void)

{
  void *pvVar1;
  
  pvVar1 = DAT_004a26d8;
  if (0xf < DAT_004a26ec) {
    FUN_0043ba10();
    FUN_00402430(pvVar1,DAT_004a26ec + 1,1);
  }
  DAT_004a26ec = 0xf;
  DAT_004a26e8 = 0;
  DAT_004a26d8 = (void *)((uint)DAT_004a26d8 & 0xffffff00);
  guard_check_icall();
  return;
}


