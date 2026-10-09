// FUN_004011f0 @ 004011f0 size=182 callers=1

void FUN_004011f0(void)

{
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00479514;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00442b40(&DAT_004a2a14);
  DAT_004a2a14 = 0;
  DAT_004a2a18 = 0;
  DAT_004a2a14 = FUN_00448fb0((undefined4 *)0x0,(undefined4 *)0x0);
  local_8 = 0;
  FUN_00442b40(&local_11);
  FUN_00442b40(&DAT_004a2a1c);
  DAT_004a2a1c = 0;
  DAT_004a2a20 = 0;
  DAT_004a2a24 = 0;
  local_8 = CONCAT31(local_8._1_3_,1);
  DAT_004a2a10 = 0x3f800000;
  FUN_00435e50(&DAT_004a2a10,8);
  _atexit(FUN_0047ef60);
  ExceptionList = local_10;
  return;
}


