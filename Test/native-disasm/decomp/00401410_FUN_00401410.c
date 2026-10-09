// FUN_00401410 @ 00401410 size=220 callers=1

void FUN_00401410(void)

{
  uint *puVar1;
  void *this;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_0047956a;
  local_10 = ExceptionList;
  local_14 = 0;
  ExceptionList = &local_10;
  FUN_00442b40(&DAT_004a28b0);
  DAT_004a28b0 = (uint *)0x0;
  DAT_004a28b4 = (uint *)0x0;
  DAT_004a28b8 = 0;
  FUN_0043ef20(this,0x20,&local_14);
  DAT_004a28bc = 0;
  if (0x20 < (uint)((int)DAT_004a28b4 - (int)DAT_004a28b0 >> 2)) {
    puVar1 = DAT_004a28b0 + 0x20;
    if (puVar1 == DAT_004a28b0) {
      guard_check_icall();
      FUN_00435da0();
      DAT_004a28b4 = DAT_004a28b0;
    }
    else if (puVar1 != DAT_004a28b4) {
      FUN_0045b0e0(puVar1,DAT_004a28b4,0);
      FUN_00435da0();
      DAT_004a28b4 = puVar1;
    }
  }
  DAT_004a28bc = 0x400;
  _atexit(FUN_0047f0f0);
  ExceptionList = local_10;
  return;
}


