// FUN_0040fe70 @ 0040fe70 size=682 callers=1

bool __fastcall
FUN_0040fe70(void **param_1,undefined4 *param_2,undefined4 *param_3,HWND param_4,char param_5)

{
  uint uVar1;
  HRESULT HVar2;
  BOOL BVar3;
  code *pcVar4;
  int iVar5;
  DWORD DVar6;
  void **ppvVar7;
  void *pvVar8;
  bool bVar9;
  LPITEMIDLIST local_84;
  _browseinfoW local_80;
  undefined4 local_60;
  HWND local_5c;
  undefined4 local_58;
  undefined4 *local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  void **local_44;
  void *local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  wchar_t *local_30;
  uint local_2c;
  undefined4 local_28;
  undefined4 *local_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined8 local_10;
  
  DAT_0049d9f5 = 0;
  if (param_1[4] < (void *)0x7d0) {
    FUN_0043a870(param_1,2000 - (int)param_1[4],0);
  }
  else {
    param_1[4] = (void *)0x7d0;
    if (param_1[5] < (void *)0x8) {
      *(undefined2 *)(param_1 + 1000) = 0;
    }
    else {
      *(undefined2 *)((int)*param_1 + 4000) = 0;
    }
  }
  uVar1 = FUN_00444360(param_2,(ushort *)&DAT_0048d358);
  if (uVar1 == 0) {
    HVar2 = CoInitializeEx((LPVOID)0x0,2);
    local_80.hwndOwner = param_4;
    local_80.pidlRoot = (LPCITEMIDLIST)0x0;
    local_80.pszDisplayName = (LPWSTR)0x0;
    local_80.lpszTitle = L"Select a folder...";
    local_80.ulFlags = 0x51;
    local_80.iImage = 0;
    local_80.lParam = (LPARAM)param_1;
    if ((void *)0x7 < param_1[5]) {
      local_80.lParam = (LPARAM)*param_1;
    }
    local_80.lpfn = (BFFCALLBACK)&LAB_00410120;
    local_84 = SHBrowseForFolderW(&local_80);
    if (local_84 == (LPITEMIDLIST)0x0) {
      bVar9 = true;
      ppvVar7 = param_1;
      if ((void *)0x7 < param_1[5]) {
        ppvVar7 = *param_1;
      }
      *(undefined2 *)ppvVar7 = 0;
    }
    else {
      ppvVar7 = param_1;
      if ((void *)0x7 < param_1[5]) {
        ppvVar7 = *param_1;
      }
      BVar3 = SHGetPathFromIDListW(local_84,(LPWSTR)ppvVar7);
      bVar9 = BVar3 != 0;
      CoTaskMemFree(local_84);
    }
    if (-1 < HVar2) {
      CoUninitialize();
    }
  }
  else {
    local_60 = 0x58;
    local_5c = param_4;
    local_58 = 0;
    if (param_2[4] == 0) {
      param_2 = (undefined4 *)0x0;
    }
    else if (7 < (uint)param_2[5]) {
      param_2 = (undefined4 *)*param_2;
    }
    local_50 = 0;
    local_4c = 0;
    local_48 = 0;
    local_44 = param_1;
    if ((void *)0x7 < param_1[5]) {
      local_44 = *param_1;
    }
    local_40 = param_1[4];
    local_30 = L"Select a file...";
    if (param_5 != '\0') {
      local_30 = (wchar_t *)0x0;
    }
    local_3c = 0;
    local_2c = 0x1000;
    local_38 = 0;
    if (param_5 != '\0') {
      local_2c = 2;
    }
    local_34 = 0;
    local_2c = local_2c | 0x210000c;
    local_28 = 0;
    if (param_3[4] == 0) {
      param_3 = (undefined4 *)0x0;
    }
    else if (7 < (uint)param_3[5]) {
      param_3 = (undefined4 *)*param_3;
    }
    pcVar4 = GetOpenFileNameW_exref;
    if (param_5 != '\0') {
      pcVar4 = GetSaveFileNameW_exref;
    }
    local_20 = 0;
    uStack_1c = 0;
    uStack_18 = 0;
    uStack_14 = 0;
    local_10 = 0;
    local_54 = param_2;
    local_24 = param_3;
    iVar5 = (*pcVar4)(&local_60);
    bVar9 = iVar5 != 0;
    if (!bVar9) {
      DVar6 = CommDlgExtendedError();
      bVar9 = DVar6 == 0;
      if (bVar9) {
        ppvVar7 = param_1;
        if ((void *)0x7 < param_1[5]) {
          ppvVar7 = *param_1;
        }
        *(undefined2 *)ppvVar7 = 0;
      }
    }
  }
  DAT_0049d9f5 = 1;
  local_84 = (LPITEMIDLIST)0x0;
  pvVar8 = (void *)FUN_0043a360(param_1,(ushort *)&local_84);
  if (param_1[4] < pvVar8) {
    FUN_0043a870(param_1,(int)pvVar8 - (int)param_1[4],0);
    FUN_00434ee0(param_1);
    return bVar9;
  }
  param_1[4] = pvVar8;
  if (param_1[5] < (void *)0x8) {
    *(undefined2 *)((int)param_1 + (int)pvVar8 * 2) = 0;
    FUN_00434ee0(param_1);
    return bVar9;
  }
  *(undefined2 *)((int)*param_1 + (int)pvVar8 * 2) = 0;
  FUN_00434ee0(param_1);
  return bVar9;
}


