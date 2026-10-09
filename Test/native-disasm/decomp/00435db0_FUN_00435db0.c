// FUN_00435db0 @ 00435db0 size=160 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_00435db0(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d8d6;
  local_10 = ExceptionList;
  _DAT_004a3320 = *param_1;
  DAT_004a3324 = 0;
  DAT_004a3328 = 0;
  ExceptionList = &local_10;
  DAT_004a3324 = FUN_00448b20((undefined4 *)0x0,(undefined4 *)0x0);
  DAT_004a332c = 0;
  _DAT_004a3330 = 0;
  DAT_004a3334 = 0;
  local_8 = 1;
  _DAT_004a3320 = 0x3f800000;
  FUN_00435e50(&DAT_004a3320,8);
  ExceptionList = local_10;
  return &DAT_004a3320;
}


