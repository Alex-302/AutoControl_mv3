// FUN_00415e80 @ 00415e80 size=1002 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 __fastcall FUN_00415e80(int *param_1,HWND param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  HMONITOR pHVar5;
  uint uVar6;
  float10 fVar7;
  float fVar8;
  float fVar9;
  tagRECT local_60;
  int local_50;
  int iStack_4c;
  int iStack_48;
  int iStack_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  int *local_30;
  int *local_2c;
  int *local_28;
  undefined1 local_21;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  local_14 = 0xffffffff;
  puStack_18 = &LAB_0047af8c;
  local_1c = ExceptionList;
  ExceptionList = &local_1c;
  piVar1 = FUN_0040b9e0(&local_2c,param_1);
  local_14 = 0;
  FUN_0040b9e0(&local_28,piVar1);
  local_14._0_1_ = 3;
  if (local_2c != (int *)0x0) {
    (**(code **)(*local_2c + 8))(local_2c);
  }
  local_14._0_1_ = 2;
  if (0x73 < DAT_004a23a4) {
    puVar2 = FUN_0040b9e0(&local_30,(int *)&local_28);
    local_14._0_1_ = 4;
    if (local_28 != (int *)0x0) {
      (**(code **)(*local_28 + 8))(local_28);
    }
    local_28 = (int *)*puVar2;
    *puVar2 = 0;
    local_14._0_1_ = 5;
    if (local_30 != (int *)0x0) {
      (**(code **)(*local_30 + 8))(local_30);
    }
  }
  local_14._0_1_ = 2;
  local_60.left = 0;
  local_60.top = 0;
  local_60.right = 0;
  local_60.bottom = 0;
  if (local_28 != (int *)0x0) {
    (**(code **)(*local_28 + 0x34))
              (local_28,_DAT_0048e618,_UNK_0048e61c,_UNK_0048e620,_UNK_0048e624,&local_60);
  }
  if ((local_60.right == 0x16) || (local_60.right == 0x10)) {
    FUN_0040b9e0(&local_30,(int *)&local_28);
    local_14 = CONCAT31(local_14._1_3_,6);
    if (local_30 != (int *)0x0) {
      local_50 = 0;
      iStack_4c = 0;
      iStack_48 = 0;
      iStack_44 = 0;
      (**(code **)(*local_30 + 0x58))
                (local_30,&local_50,&iStack_4c,&iStack_48,&iStack_44,_DAT_0048e618,_UNK_0048e61c,
                 _UNK_0048e620,_UNK_0048e624);
      fVar8 = 0.0;
      local_60.left = 0;
      local_60.top = 0;
      local_60.right = 0;
      local_60.bottom = 0;
      GetWindowRect(param_2,&local_60);
      iVar3 = GetSystemMetrics(0x20);
      local_2c = (int *)(local_60.top + iVar3);
      local_3c = (float)((local_60.right - iVar3) - (local_60.left + iVar3));
      local_40 = (float)((local_60.bottom - iVar3) - (int)local_2c);
      uVar4 = local_50 - (local_60.left + iVar3);
      uVar6 = (int)uVar4 >> 0x1f;
      local_38 = (float)((uVar4 ^ uVar6) - uVar6);
      if (param_2 != DAT_004a2430) {
        DAT_004a2430 = param_2;
        pHVar5 = MonitorFromWindow(param_2,2);
        FUN_00406610(pHVar5);
        DAT_0049d9e0 = fVar8;
      }
      fVar8 = DAT_0049d9e0 * _DAT_0048f268;
      fVar7 = roundf(fVar8);
      local_34 = (float)fVar7;
      if ((int)local_38 < (int)fVar7) {
        uVar4 = iStack_4c - (int)local_2c >> 0x1f;
        local_34 = (float)((iStack_4c - (int)local_2c ^ uVar4) - uVar4);
        if (param_2 != DAT_004a2430) {
          DAT_004a2430 = param_2;
          pHVar5 = MonitorFromWindow(param_2,2);
          FUN_00406610(pHVar5);
          DAT_0049d9e0 = fVar8;
        }
        fVar8 = DAT_0049d9e0 * _DAT_0048f268;
        fVar7 = roundf(fVar8);
        local_38 = (float)fVar7;
        if ((int)fVar7 <= (int)local_34) goto LAB_00416208;
        uVar4 = iStack_48 - (int)local_3c >> 0x1f;
        local_38 = (float)((iStack_48 - (int)local_3c ^ uVar4) - uVar4);
        if (param_2 != DAT_004a2430) {
          DAT_004a2430 = param_2;
          pHVar5 = MonitorFromWindow(param_2,2);
          FUN_00406610(pHVar5);
          DAT_0049d9e0 = fVar8;
        }
        fVar8 = DAT_0049d9e0 * _DAT_0048f280;
        fVar7 = roundf(fVar8);
        local_3c = (float)fVar7;
        if ((int)fVar7 <= (int)local_38) goto LAB_00416208;
        if (param_2 != DAT_004a2430) {
          DAT_004a2430 = param_2;
          pHVar5 = MonitorFromWindow(param_2,2);
          FUN_00406610(pHVar5);
          DAT_0049d9e0 = fVar8;
        }
        fVar8 = DAT_0049d9e0 * _DAT_0048f28c;
        fVar7 = roundf(fVar8);
        local_3c = (float)fVar7;
        if (iStack_44 <= (int)fVar7) goto LAB_00416208;
        if (param_2 != DAT_004a2430) {
          DAT_004a2430 = param_2;
          pHVar5 = MonitorFromWindow(param_2,2);
          FUN_00406610(pHVar5);
          DAT_0049d9e0 = fVar8;
        }
        fVar9 = DAT_0049d9e0 * _DAT_0048f29c;
        fVar7 = roundf(fVar9);
        local_3c = (float)fVar7;
        fVar8 = local_40;
        if ((int)fVar7 < (int)local_40) {
          if (param_2 != DAT_004a2430) {
            DAT_004a2430 = param_2;
            pHVar5 = MonitorFromWindow(param_2,2);
            FUN_00406610(pHVar5);
            DAT_0049d9e0 = fVar9;
          }
          fVar7 = roundf(DAT_0049d9e0 * _DAT_0048f29c);
          local_40 = (float)fVar7;
          fVar8 = (float)(int)fVar7;
        }
        if ((int)fVar8 <= iStack_44) goto LAB_00416208;
        local_21 = 1;
      }
      else {
LAB_00416208:
        local_21 = 0;
      }
      local_14 = CONCAT31(local_14._1_3_,7);
      if (local_30 != (int *)0x0) {
        (**(code **)(*local_30 + 8))(local_30);
      }
      goto LAB_0041622e;
    }
  }
  local_21 = 0;
LAB_0041622e:
  local_14 = 10;
  if (local_28 == (int *)0x0) {
    ExceptionList = local_1c;
    return local_21;
  }
  (**(code **)(*local_28 + 8))(local_28);
  ExceptionList = local_1c;
  return local_21;
}


