// FUN_004043e0 @ 004043e0 size=267 callers=3

int * __fastcall FUN_004043e0(int *param_1,undefined4 *param_2)

{
  uint *puVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004792d9;
  local_10 = ExceptionList;
  local_8 = 0;
  iVar2 = param_2[4];
  ExceptionList = &local_10;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[5] = 0xf;
  param_1[4] = 0;
  piVar3 = param_1;
  if (0xf < (uint)param_1[5]) {
    piVar3 = (int *)*param_1;
  }
  *(undefined1 *)piVar3 = 0;
  FUN_0043ac10(param_1,((iVar2 + 2U) / 3) * 4 + 1,'\0');
  local_8 = 0;
  puVar1 = param_2 + 4;
  if (0xf < (uint)param_2[5]) {
    param_2 = (undefined4 *)*param_2;
  }
  piVar3 = param_1;
  if (0xf < (uint)param_1[5]) {
    piVar3 = (int *)*param_1;
  }
  uVar4 = FUN_00403640((char *)piVar3,(int)param_2,*puVar1);
  if ((uint)param_1[4] < uVar4) {
    FUN_0043aef0(param_1,uVar4 - param_1[4],'\0');
    ExceptionList = local_10;
    return param_1;
  }
  param_1[4] = uVar4;
  if ((uint)param_1[5] < 0x10) {
    *(undefined1 *)((int)param_1 + uVar4) = 0;
    ExceptionList = local_10;
    return param_1;
  }
  *(undefined1 *)(*param_1 + uVar4) = 0;
  ExceptionList = local_10;
  return param_1;
}


