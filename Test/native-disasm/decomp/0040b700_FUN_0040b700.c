// FUN_0040b700 @ 0040b700 size=373 callers=2

/* WARNING: Removing unreachable block (ram,0x0040b833) */

undefined4 * __fastcall
FUN_0040b700(undefined4 *param_1,HWND param_2,int param_3,int param_4,char param_5)

{
  HWND pHVar1;
  int iVar2;
  HWND pHVar3;
  int iVar4;
  undefined4 *puVar5;
  int *piVar6;
  tagRECT local_50;
  undefined4 local_3c;
  int local_38;
  HWND local_34;
  undefined4 *local_30;
  int local_2c;
  int *local_28;
  int *local_24;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  int local_14;
  
  puStack_20 = &stack0xfffffffc;
  local_14 = 0xffffffff;
  puStack_18 = &LAB_00479e66;
  local_1c = ExceptionList;
  local_3c = 0;
  local_50.left = 0;
  local_50.top = 0;
  local_50.right = 0;
  local_50.bottom = 0;
  ExceptionList = &local_1c;
  local_34 = param_2;
  local_30 = param_1;
  GetWindowRect(param_2,&local_50);
  if (param_5 == '\0') {
    local_30 = (undefined4 *)local_50.bottom;
    local_28 = (int *)local_50.right;
    local_2c = local_50.top;
    piVar6 = (int *)local_50.left;
  }
  else {
    iVar4 = GetSystemMetrics(0x20);
    local_2c = local_50.top + iVar4;
    local_28 = (int *)(local_50.right - iVar4);
    local_30 = (undefined4 *)(local_50.bottom - iVar4);
    piVar6 = (int *)(local_50.left + iVar4);
  }
  FUN_0040b5f0(&local_24,local_34);
  local_14 = 0;
  if (param_3 < 0) {
    piVar6 = local_28;
  }
  puVar5 = (undefined4 *)local_2c;
  if (param_4 < 0) {
    puVar5 = local_30;
  }
  local_38 = param_3 + (int)piVar6;
  local_34 = (HWND)(param_4 + (int)puVar5);
  FUN_0040b650(&local_28,(int *)&local_24,&local_38);
  iVar2 = param_3 + (int)piVar6;
  pHVar3 = (HWND)(param_4 + (int)puVar5);
  iVar4 = local_38;
  pHVar1 = local_34;
  while (local_34 = pHVar3, local_38 = iVar2, local_14._1_3_ = (uint3)((uint)local_14 >> 8),
        local_28 != (int *)0x0) {
    local_14._0_1_ = 2;
    piVar6 = local_28;
    if (local_24 != (int *)0x0) {
      (**(code **)(*local_24 + 8))(local_24);
      piVar6 = local_28;
    }
    local_28 = (int *)0x0;
    local_14 = (uint)local_14._1_3_ << 8;
    local_24 = piVar6;
    FUN_0040b650(&local_28,(int *)&local_24,&local_38);
    iVar2 = local_38;
    pHVar3 = local_34;
    iVar4 = local_38;
    pHVar1 = local_34;
  }
  local_14 = (uint)local_14._1_3_ << 8;
  *param_1 = local_24;
  local_38 = iVar4;
  local_34 = pHVar1;
  if (local_24 != (int *)0x0) {
    (**(code **)(*local_24 + 4))(local_24);
  }
  local_14 = 5;
  if (local_24 != (int *)0x0) {
    (**(code **)(*local_24 + 8))(local_24);
  }
  ExceptionList = local_1c;
  return param_1;
}


