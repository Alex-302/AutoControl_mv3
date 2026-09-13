// FUN_0040bdf0 @ 0040bdf0 size=231 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __fastcall FUN_0040bdf0(undefined4 *param_1,int *param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  UINT UVar4;
  undefined4 local_38;
  undefined4 local_28;
  uint local_24;
  undefined4 *local_20;
  undefined4 local_1c;
  BSTR local_18 [2];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00479f19;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[5] = 7;
  param_1[4] = 0;
  puVar2 = param_1;
  if (7 < (uint)param_1[5]) {
    puVar2 = (undefined4 *)*param_1;
  }
  *(undefined2 *)puVar2 = 0;
  local_8 = 0;
  piVar1 = (int *)*param_2;
  local_1c = 1;
  if ((piVar1 != (int *)0x0) &&
     (local_20 = param_1,
     iVar3 = (**(code **)(*piVar1 + 0x28))
                       (piVar1,_DAT_0048e618,_UNK_0048e61c,_UNK_0048e620,_UNK_0048e624,local_18),
     iVar3 == 0)) {
    UVar4 = SysStringLen(local_18[0]);
    local_24 = 7;
    local_38 = (void *)((uint)local_38._2_2_ << 0x10);
    local_28 = 0;
    FUN_0043a650(&local_38,(uint *)local_18[0],UVar4);
    FUN_004351b0(param_1,&local_38);
    if (7 < local_24) {
      FUN_00402430(local_38,local_24 + 1,2);
    }
    SysFreeString(local_18[0]);
  }
  ExceptionList = local_10;
  return param_1;
}


