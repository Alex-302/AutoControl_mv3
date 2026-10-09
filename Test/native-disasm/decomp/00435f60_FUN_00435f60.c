// FUN_00435f60 @ 00435f60 size=160 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_00435f60(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d8d6;
  local_10 = ExceptionList;
  _DAT_004a24b0 = *param_1;
  DAT_004a24b4 = 0;
  DAT_004a24b8 = 0;
  ExceptionList = &local_10;
  DAT_004a24b4 = FUN_00448ac0((undefined4 *)0x0,(undefined4 *)0x0);
  DAT_004a24bc = 0;
  _DAT_004a24c0 = 0;
  DAT_004a24c4 = 0;
  local_8 = 1;
  _DAT_004a24b0 = 0x3f800000;
  FUN_00435e50(&DAT_004a24b0,8);
  ExceptionList = local_10;
  return &DAT_004a24b0;
}


