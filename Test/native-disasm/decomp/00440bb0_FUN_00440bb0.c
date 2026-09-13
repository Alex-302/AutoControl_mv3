// FUN_00440bb0 @ 00440bb0 size=119 callers=7

undefined4 * __thiscall FUN_00440bb0(void *this,undefined4 *param_1)

{
  undefined4 *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047df29;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[5] = 0xf;
  param_1[4] = 0;
  puVar1 = param_1;
  if (0xf < (uint)param_1[5]) {
    puVar1 = (undefined4 *)*param_1;
  }
  *(undefined1 *)puVar1 = 0;
  local_8 = 0;
  FUN_00451060(this,param_1);
  ExceptionList = local_10;
  return param_1;
}


