// FUN_004365f0 @ 004365f0 size=160 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_004365f0(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047db96;
  local_10 = ExceptionList;
  _DAT_004a28e0 = *param_1;
  DAT_004a28e4 = 0;
  DAT_004a28e8 = 0;
  ExceptionList = &local_10;
  DAT_004a28e4 = FUN_00448c30((undefined4 *)0x0,(undefined4 *)0x0);
  DAT_004a28ec = 0;
  _DAT_004a28f0 = 0;
  DAT_004a28f4 = 0;
  local_8 = 1;
  _DAT_004a28e0 = 0x3f800000;
  FUN_00435e50(&DAT_004a28e0,8);
  ExceptionList = local_10;
  return &DAT_004a28e0;
}


