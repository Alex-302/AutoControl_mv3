// FUN_00436c80 @ 00436c80 size=160 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_00436c80(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d8d6;
  local_10 = ExceptionList;
  _DAT_004a27b0 = *param_1;
  DAT_004a27b4 = 0;
  DAT_004a27b8 = 0;
  ExceptionList = &local_10;
  DAT_004a27b4 = FUN_00448e80((undefined4 *)0x0,(undefined4 *)0x0);
  DAT_004a27bc = 0;
  _DAT_004a27c0 = 0;
  DAT_004a27c4 = 0;
  local_8 = 1;
  _DAT_004a27b0 = 0x3f800000;
  FUN_00435e50(&DAT_004a27b0,8);
  ExceptionList = local_10;
  return &DAT_004a27b0;
}


