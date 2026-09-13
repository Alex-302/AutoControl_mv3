// FUN_004014f0 @ 004014f0 size=217 callers=1

void FUN_004014f0(void)

{
  uint *puVar1;
  void *this;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_0047958a;
  local_10 = ExceptionList;
  local_14 = 0;
  ExceptionList = &local_10;
  FUN_00442b40(&DAT_004a2598);
  DAT_004a2598 = (uint *)0x0;
  DAT_004a259c = (uint *)0x0;
  DAT_004a25a0 = 0;
  FUN_0043ef20(this,0x10,&local_14);
  DAT_004a25a4 = 0;
  if (0x10 < (uint)((int)DAT_004a259c - (int)DAT_004a2598 >> 2)) {
    puVar1 = DAT_004a2598 + 0x10;
    if (puVar1 == DAT_004a2598) {
      guard_check_icall();
      FUN_00435da0();
      DAT_004a259c = DAT_004a2598;
    }
    else if (puVar1 != DAT_004a259c) {
      FUN_0045b0e0(puVar1,DAT_004a259c,0);
      FUN_00435da0();
      DAT_004a259c = puVar1;
    }
  }
  DAT_004a25a4 = 0x200;
  _atexit(FUN_0047f090);
  ExceptionList = local_10;
  return;
}


