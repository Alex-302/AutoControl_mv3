// FUN_00452f60 @ 00452f60 size=132 callers=1

void FUN_00452f60(undefined4 *param_1,undefined4 *param_2,undefined1 *param_3)

{
  undefined4 *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e989;
  local_10 = ExceptionList;
  local_8 = 0;
  if (param_1 != (undefined4 *)0x0) {
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
    FUN_0043ade0(param_1,param_2,0,0xffffffff);
    local_8 = CONCAT31(local_8._1_3_,1);
    FUN_00434940(param_1 + 6,param_3);
  }
  ExceptionList = local_10;
  return;
}


