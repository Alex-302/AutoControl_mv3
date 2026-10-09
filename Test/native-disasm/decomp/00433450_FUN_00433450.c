// FUN_00433450 @ 00433450 size=135 callers=1

undefined4 * __fastcall FUN_00433450(undefined4 *param_1)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d976;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  uVar1 = FUN_00448f80((undefined4 *)0x0,(undefined4 *)0x0);
  param_1[1] = uVar1;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  local_8 = 1;
  *param_1 = 0x3f800000;
  FUN_00435e50(param_1,8);
  ExceptionList = local_10;
  return param_1;
}


