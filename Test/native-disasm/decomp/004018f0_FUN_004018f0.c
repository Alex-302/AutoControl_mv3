// FUN_004018f0 @ 004018f0 size=237 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004018f0(void)

{
  uint *puVar1;
  void *this;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_0047aefa;
  local_10 = ExceptionList;
  local_14 = 0;
  ExceptionList = &local_10;
  FUN_00442b40(&DAT_004a27f0);
  DAT_004a27f0 = (uint *)0x0;
  DAT_004a27f4 = (uint *)0x0;
  DAT_004a27f8 = 0;
  FUN_0043ef20(this,3,&local_14);
  _DAT_004a27fc = 0;
  if (3 < (uint)((int)DAT_004a27f4 - (int)DAT_004a27f0 >> 2)) {
    puVar1 = DAT_004a27f0 + 3;
    if (puVar1 == DAT_004a27f0) {
      guard_check_icall();
      FUN_00435da0();
      DAT_004a27f4 = DAT_004a27f0;
    }
    else if (puVar1 != DAT_004a27f4) {
      FUN_0045b0e0(puVar1,DAT_004a27f4,0);
      FUN_00435da0();
      DAT_004a27f4 = puVar1;
    }
  }
  _DAT_004a27fc = 0x50;
  DAT_004a27f0[2] = DAT_004a27f0[2] & 0xffff;
  _atexit(FUN_0047f420);
  ExceptionList = local_10;
  return;
}


