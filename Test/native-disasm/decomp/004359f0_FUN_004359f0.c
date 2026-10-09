// FUN_004359f0 @ 004359f0 size=160 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_004359f0(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d8d6;
  local_10 = ExceptionList;
  _DAT_004a2770 = *param_1;
  DAT_004a2774 = 0;
  _DAT_004a2778 = 0;
  ExceptionList = &local_10;
  DAT_004a2774 = FUN_00448ac0((undefined4 *)0x0,(undefined4 *)0x0);
  DAT_004a277c = 0;
  _DAT_004a2780 = 0;
  DAT_004a2784 = 0;
  local_8 = 1;
  _DAT_004a2770 = 0x3f800000;
  FUN_00435e50(&DAT_004a2770,8);
  ExceptionList = local_10;
  return &DAT_004a2770;
}


