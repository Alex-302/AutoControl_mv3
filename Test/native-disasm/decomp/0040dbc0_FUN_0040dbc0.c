// FUN_0040dbc0 @ 0040dbc0 size=766 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __fastcall FUN_0040dbc0(undefined4 *param_1,HWND param_2)

{
  undefined4 *puVar1;
  undefined1 *puVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  HMONITOR pHVar6;
  code *pcVar7;
  float10 fVar8;
  float in_XMM0_Da;
  float fVar9;
  void *local_60 [5];
  uint local_4c;
  tagRECT local_48;
  undefined4 local_34;
  undefined4 *local_30;
  float local_2c;
  float local_28;
  int *local_24;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  uint local_14;
  
  puStack_20 = &stack0xfffffffc;
  local_14 = 0xffffffff;
  puStack_18 = &LAB_0047a27a;
  local_1c = ExceptionList;
  local_34 = 0;
  pcVar7 = MonitorFromWindow_exref;
  ExceptionList = &local_1c;
  local_30 = param_1;
  puVar2 = &stack0xfffffffc;
  if (DAT_004a23d7 != '\0') goto LAB_0040dc70;
  ExceptionList = &local_1c;
  FUN_00404790((LPWSTR)local_60,param_2,1,'\0');
  uVar3 = FUN_00444360(local_60,(ushort *)&DAT_0048d264);
  if (uVar3 == 0) {
LAB_0040dc3e:
    DAT_004a23d7 = 'Y';
  }
  else {
    uVar3 = FUN_00444360(local_60,(ushort *)&DAT_0048d268);
    DAT_004a23d7 = 'N';
    if (uVar3 == 0) goto LAB_0040dc3e;
  }
  pcVar7 = MonitorFromWindow_exref;
  puVar2 = puStack_20;
  if (7 < local_4c) {
    FUN_00402430(local_60[0],local_4c + 1,2);
    pcVar7 = MonitorFromWindow_exref;
    puVar2 = puStack_20;
  }
LAB_0040dc70:
  while( true ) {
    puStack_20 = puVar2;
    iVar5 = 0x14;
    if (DAT_0049fc60 != 0) {
      iVar5 = DAT_0049fc60;
    }
    local_28 = (float)iVar5;
    if (param_2 != DAT_004a2430) {
      DAT_004a2430 = param_2;
      uVar4 = (*pcVar7)(param_2,2);
      FUN_00406610(uVar4);
      DAT_0049d9e0 = in_XMM0_Da;
    }
    fVar9 = DAT_0049d9e0;
    fVar8 = roundf(local_28 * DAT_0049d9e0);
    local_2c = (float)fVar8;
    local_28 = (float)(int)(((uint)(DAT_004a23d7 == 'Y') * 2 + -1) * 0x19);
    if (param_2 != DAT_004a2430) {
      DAT_004a2430 = param_2;
      uVar4 = (*pcVar7)(param_2,2);
      FUN_00406610(uVar4);
      DAT_0049d9e0 = fVar9;
    }
    fVar8 = roundf(local_28 * DAT_0049d9e0);
    local_28 = (float)fVar8;
    FUN_0040b700(&local_24,param_2,(int)fVar8,(int)local_2c,'\x01');
    local_14 = 0;
    if (DAT_0049fc60 != 0) break;
    local_48.left = 0;
    local_48.top = 0;
    local_48.right = 0;
    local_48.bottom = 0;
    if (local_24 != (int *)0x0) {
      (**(code **)(*local_24 + 0x34))
                (local_24,_DAT_0048e618,_UNK_0048e61c,_UNK_0048e620,_UNK_0048e624,&local_48);
    }
    if (local_48.right != 0x2b) break;
    local_48.left = 0;
    local_48.top = 0;
    local_48.right = 0;
    local_48.bottom = 0;
    GetWindowRect(param_2,&local_48);
    iVar5 = GetSystemMetrics(0x20);
    fVar9 = 0.0;
    iVar5 = local_48.top + iVar5;
    local_48.left = 0;
    local_48.top = 0;
    local_48.right = 0;
    local_48.bottom = 0;
    if (local_24 != (int *)0x0) {
      fVar9 = _DAT_0048e618;
      (**(code **)(*local_24 + 0x58))
                (local_24,&local_48,&local_48.top,&local_48.right,&local_48.bottom,_DAT_0048e618,
                 _UNK_0048e61c,_UNK_0048e620,_UNK_0048e624);
    }
    pcVar7 = MonitorFromWindow_exref;
    local_2c = (float)((local_48.top - iVar5) + local_48.bottom);
    if (param_2 != DAT_004a2430) {
      DAT_004a2430 = param_2;
      pHVar6 = MonitorFromWindow(param_2,2);
      FUN_00406610(pHVar6);
      DAT_0049d9e0 = fVar9;
    }
    in_XMM0_Da = DAT_0049d9e0;
    fVar8 = roundf(local_2c / DAT_0049d9e0);
    local_2c = (float)fVar8;
    DAT_0049fc60 = (int)fVar8 + 2;
    local_14 = 1;
    if (local_24 != (int *)0x0) {
      (**(code **)(*local_24 + 8))(local_24);
    }
    local_14 = 0xffffffff;
    puVar2 = puStack_20;
  }
  puVar1 = local_30;
  local_14 = local_14 & 0xffffff00;
  *local_30 = local_24;
  if (local_24 != (int *)0x0) {
    (**(code **)(*local_24 + 4))(local_24);
  }
  local_14 = 3;
  if (local_24 != (int *)0x0) {
    (**(code **)(*local_24 + 8))(local_24);
  }
  ExceptionList = local_1c;
  return puVar1;
}


