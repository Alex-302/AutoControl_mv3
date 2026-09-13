// FUN_004580e0 @ 004580e0 size=160 callers=1

undefined4 * __fastcall FUN_004580e0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined1 local_8;
  undefined3 uStack_7;
  
  puStack_c = &LAB_0047ecb1;
  local_10 = ExceptionList;
  uStack_7 = 0;
  ExceptionList = &local_10;
  for (; param_1 != param_2; param_1 = param_1 + 7) {
    local_8 = 1;
    if (param_3 != (undefined4 *)0x0) {
      param_3[4] = 0;
      param_3[5] = 0;
      param_3[5] = 0xf;
      param_3[4] = 0;
      puVar1 = param_3;
      if (0xf < (uint)param_3[5]) {
        puVar1 = (undefined4 *)*param_3;
      }
      *(undefined1 *)puVar1 = 0;
      FUN_0043ade0(param_3,param_1,0,0xffffffff);
      param_3[6] = param_1[6];
    }
    param_3 = param_3 + 7;
  }
  ExceptionList = local_10;
  return param_3;
}


