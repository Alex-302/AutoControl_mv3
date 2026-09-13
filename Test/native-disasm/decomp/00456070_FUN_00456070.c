// FUN_00456070 @ 00456070 size=140 callers=1

void FUN_00456070(undefined4 *param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047eb17;
  local_10 = ExceptionList;
  local_8 = 0;
  if (param_1 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*param_3;
    ExceptionList = &local_10;
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[5] = 0xf;
    param_1[4] = 0;
    puVar2 = param_1;
    if (0xf < (uint)param_1[5]) {
      puVar2 = (undefined4 *)*param_1;
    }
    *(undefined1 *)puVar2 = 0;
    FUN_0043ade0(param_1,puVar1,0,0xffffffff);
    local_8 = CONCAT31(local_8._1_3_,1);
    *(undefined1 *)(param_1 + 6) = 0;
    FUN_004381d0(param_1 + 8,'\0');
  }
  ExceptionList = local_10;
  return;
}


