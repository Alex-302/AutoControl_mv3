// FUN_00436aa0 @ 00436aa0 size=160 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_00436aa0(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047dbb6;
  local_10 = ExceptionList;
  _DAT_004a2f90 = *param_1;
  DAT_004a2f94 = 0;
  DAT_004a2f98 = 0;
  ExceptionList = &local_10;
  DAT_004a2f94 = FUN_00448c30((undefined4 *)0x0,(undefined4 *)0x0);
  DAT_004a2f9c = 0;
  _DAT_004a2fa0 = 0;
  DAT_004a2fa4 = 0;
  local_8 = 1;
  _DAT_004a2f90 = 0x3f800000;
  FUN_00435e50(&DAT_004a2f90,8);
  ExceptionList = local_10;
  return &DAT_004a2f90;
}


