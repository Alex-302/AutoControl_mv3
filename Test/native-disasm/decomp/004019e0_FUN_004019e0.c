// FUN_004019e0 @ 004019e0 size=237 callers=1

void FUN_004019e0(void)

{
  uint *puVar1;
  void *this;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_0047af1a;
  local_10 = ExceptionList;
  local_14 = 0;
  ExceptionList = &local_10;
  FUN_00442b40(&DAT_004a28c0);
  DAT_004a28c0 = (uint *)0x0;
  DAT_004a28c4 = (uint *)0x0;
  DAT_004a28c8 = 0;
  FUN_0043ef20(this,3,&local_14);
  DAT_004a28cc = 0;
  if (3 < (uint)((int)DAT_004a28c4 - (int)DAT_004a28c0 >> 2)) {
    puVar1 = DAT_004a28c0 + 3;
    if (puVar1 == DAT_004a28c0) {
      guard_check_icall();
      FUN_00435da0();
      DAT_004a28c4 = DAT_004a28c0;
    }
    else if (puVar1 != DAT_004a28c4) {
      FUN_0045b0e0(puVar1,DAT_004a28c4,0);
      FUN_00435da0();
      DAT_004a28c4 = puVar1;
    }
  }
  DAT_004a28cc = 0x50;
  DAT_004a28c0[2] = DAT_004a28c0[2] & 0xffff;
  _atexit(FUN_0047f3c0);
  ExceptionList = local_10;
  return;
}


