// FUN_00441c70 @ 00441c70 size=192 callers=1

undefined4 * __fastcall FUN_00441c70(undefined4 *param_1,undefined4 *param_2)

{
  uint uVar1;
  bool bVar2;
  uint uVar3;
  undefined4 *puVar4;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00479309;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[5] = 7;
  param_1[4] = 0;
  puVar4 = param_1;
  if (7 < (uint)param_1[5]) {
    puVar4 = (undefined4 *)*param_1;
  }
  *(undefined2 *)puVar4 = 0;
  local_8 = 0;
  uVar1 = param_1[4];
  uVar3 = param_2[4] + 1;
  if (((uVar1 <= uVar3) && (param_1[5] != uVar3)) &&
     (bVar2 = FUN_0043a080(param_1,uVar3,'\x01'), bVar2)) {
    param_1[4] = uVar1;
    puVar4 = param_1;
    if (7 < (uint)param_1[5]) {
      puVar4 = (undefined4 *)*param_1;
    }
    *(undefined2 *)((int)puVar4 + uVar1 * 2) = 0;
  }
  FUN_0043dd10(param_1,param_2,0,0xffffffff);
  FUN_0043a870(param_1,1,10);
  ExceptionList = local_10;
  return param_1;
}


