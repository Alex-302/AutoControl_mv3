// FUN_00414360 @ 00414360 size=1016 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float * __fastcall FUN_00414360(HWND param_1,char param_2,float *param_3,int param_4)

{
  HRESULT HVar1;
  int **ppiVar2;
  HMONITOR pHVar3;
  BOOL BVar4;
  float fVar5;
  int iVar6;
  float10 fVar7;
  float fVar8;
  tagRECT local_70;
  float local_60;
  float fStack_5c;
  float fStack_58;
  float afStack_54 [2];
  HRESULT local_4c;
  int *local_48;
  int *local_44;
  int *local_40;
  int *local_3c;
  int *local_38;
  int *local_34;
  int *local_30;
  uint local_2c;
  uint local_28;
  char local_21;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  local_14 = 0xffffffff;
  puStack_18 = &LAB_0047ada2;
  local_1c = ExceptionList;
  local_2c = 0;
  ExceptionList = &local_1c;
  local_21 = param_2;
  HVar1 = CoInitializeEx((LPVOID)0x0,2);
  local_14 = 0;
  local_4c = HVar1;
  if (param_4 == 4) {
    if (local_21 == '\x02') {
      ppiVar2 = (int **)FUN_004141d0((int *)&local_48,param_1);
      local_2c = 1;
      goto LAB_0041443f;
    }
LAB_00414418:
    ppiVar2 = (int **)FUN_0040dec0((int *)&local_40,param_1);
    local_2c = 0x10;
  }
  else {
    if (param_4 == 10) goto LAB_00414418;
    if (param_4 == 0x14) {
      ppiVar2 = (int **)FUN_0040dfc0((int *)&local_44,param_1);
      local_2c = 2;
    }
    else {
      local_3c = (int *)0x0;
      ppiVar2 = &local_3c;
      local_2c = 4;
    }
    local_34 = (int *)0x0;
    local_34 = *ppiVar2;
    *ppiVar2 = (int *)0x0;
    ppiVar2 = &local_34;
    local_2c = local_2c | 8;
  }
  local_30 = (int *)0x0;
  local_30 = *ppiVar2;
  *ppiVar2 = (int *)0x0;
  ppiVar2 = &local_30;
  local_2c = local_2c | 0x20;
LAB_0041443f:
  local_28 = local_2c;
  local_38 = (int *)0x0;
  local_14 = 8;
  local_38 = *ppiVar2;
  if (local_38 != (int *)0x0) {
    (**(code **)(*local_38 + 4))(local_38);
  }
  local_14._1_3_ = 0;
  if ((local_28 & 0x20) != 0) {
    local_2c = local_28 & 0xffffffdf;
    local_14._0_1_ = 0xc;
    local_14._1_3_ = 0;
    local_28 = local_2c;
    if (local_30 != (int *)0x0) {
      (**(code **)(*local_30 + 8))(local_30);
    }
  }
  if ((local_28 & 0x10) != 0) {
    local_2c = local_28 & 0xffffffef;
    local_14._0_1_ = 0xe;
    local_28 = local_2c;
    if (local_40 != (int *)0x0) {
      (**(code **)(*local_40 + 8))(local_40);
    }
  }
  if ((local_28 & 8) != 0) {
    local_2c = local_28 & 0xfffffff7;
    local_14._0_1_ = 0x10;
    local_28 = local_2c;
    if (local_34 != (int *)0x0) {
      (**(code **)(*local_34 + 8))(local_34);
    }
  }
  if ((local_28 & 4) != 0) {
    local_2c = local_28 & 0xfffffffb;
    local_14._0_1_ = 0x12;
    local_28 = local_2c;
    if (local_3c != (int *)0x0) {
      (**(code **)(*local_3c + 8))(local_3c);
    }
  }
  if ((local_28 & 2) != 0) {
    local_2c = local_28 & 0xfffffffd;
    local_14._0_1_ = 0x14;
    local_28 = local_2c;
    if (local_44 != (int *)0x0) {
      (**(code **)(*local_44 + 8))(local_44);
    }
  }
  if (((local_28 & 1) != 0) && (local_14._0_1_ = 0x16, local_48 != (int *)0x0)) {
    (**(code **)(*local_48 + 8))(local_48);
  }
  local_14 = CONCAT31(local_14._1_3_,0x15);
  local_60 = 0.0;
  fStack_5c = 0.0;
  fStack_58 = 0.0;
  afStack_54[0] = 0.0;
  if (local_38 != (int *)0x0) {
    (**(code **)(*local_38 + 0x58))
              (local_38,&local_60,&fStack_5c,&fStack_58,afStack_54,_DAT_0048e618,_UNK_0048e61c,
               _UNK_0048e620,_UNK_0048e624);
  }
  local_70.left = (LONG)local_60;
  local_70.top = (LONG)fStack_5c;
  local_70.right = (LONG)fStack_58;
  local_70.bottom = (LONG)afStack_54[0];
  if (param_4 == 10) {
    if (param_1 != DAT_004a2430) {
      fVar8 = local_60;
      DAT_004a2430 = param_1;
      pHVar3 = MonitorFromWindow(param_1,2);
      FUN_00406610(pHVar3);
      DAT_0049d9e0 = fVar8;
    }
    fVar8 = DAT_0049d9e0 + DAT_0049d9e0;
    fVar7 = roundf(fVar8);
    local_3c = (int *)(float)fVar7;
    local_70.left = (int)fVar7 + (int)local_60;
    BVar4 = IsZoomed(param_1);
    if (BVar4 == 0) {
      if (param_1 != DAT_004a2430) {
        DAT_004a2430 = param_1;
        pHVar3 = MonitorFromWindow(param_1,2);
        FUN_00406610(pHVar3);
        DAT_0049d9e0 = fVar8;
      }
      fVar8 = DAT_0049d9e0 + DAT_0049d9e0;
      fVar7 = roundf(fVar8);
      local_3c = (int *)(float)fVar7;
      local_70.top = local_70.top + (int)fVar7;
    }
    if (param_1 != DAT_004a2430) {
      DAT_004a2430 = param_1;
      pHVar3 = MonitorFromWindow(param_1,2);
      FUN_00406610(pHVar3);
      DAT_0049d9e0 = fVar8;
    }
    fVar8 = DAT_0049d9e0 * _DAT_0048f260;
    fVar7 = roundf(fVar8);
    local_3c = (int *)(float)fVar7;
    local_70.right = local_70.right - (int)fVar7;
    if (param_1 != DAT_004a2430) {
      DAT_004a2430 = param_1;
      pHVar3 = MonitorFromWindow(param_1,2);
      FUN_00406610(pHVar3);
      DAT_0049d9e0 = fVar8;
    }
    fVar7 = roundf(DAT_0049d9e0 * _DAT_0048f260);
    local_48 = (int *)(float)fVar7;
    local_70.bottom = local_70.bottom - (int)fVar7;
    fVar8 = (float)local_70.right;
    fVar5 = (float)local_70.bottom;
  }
  else {
    fVar8 = fStack_58;
    fVar5 = afStack_54[0];
    if (param_4 == 4) {
      local_70.left = 0;
      local_70.top = 0;
      local_70.right = 0;
      local_70.bottom = 0;
      GetWindowRect(param_1,&local_70);
      fVar8 = (float)(local_70.right - local_70.left);
      if (local_21 == '\x02') {
        iVar6 = -local_70.top;
      }
      else {
        iVar6 = (int)afStack_54[0] - local_70.top;
      }
      fVar5 = (float)((int)fStack_5c + iVar6);
    }
  }
  *param_3 = (float)local_70.left;
  param_3[1] = (float)local_70.top;
  param_3[2] = fVar8;
  param_3[3] = fVar5;
  local_14 = CONCAT31(local_14._1_3_,0x17);
  if (local_38 != (int *)0x0) {
    (**(code **)(*local_38 + 8))(local_38);
  }
  if (-1 < HVar1) {
    CoUninitialize();
  }
  ExceptionList = local_1c;
  return param_3;
}


