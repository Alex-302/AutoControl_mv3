// FUN_00437290 @ 00437290 size=160 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_00437290(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d8d6;
  local_10 = ExceptionList;
  _DAT_004a27d0 = *param_1;
  DAT_004a27d4 = 0;
  DAT_004a27d8 = 0;
  ExceptionList = &local_10;
  DAT_004a27d4 = FUN_00448ac0((undefined4 *)0x0,(undefined4 *)0x0);
  DAT_004a27dc = 0;
  _DAT_004a27e0 = 0;
  DAT_004a27e4 = 0;
  local_8 = 1;
  _DAT_004a27d0 = 0x3f800000;
  FUN_00435e50(&DAT_004a27d0,8);
  ExceptionList = local_10;
  return &DAT_004a27d0;
}


