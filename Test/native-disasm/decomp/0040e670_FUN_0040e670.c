// FUN_0040e670 @ 0040e670 size=386 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_0040e670(void)

{
  HWND hwnd;
  undefined4 *puVar1;
  BOOL BVar2;
  int iVar3;
  HMONITOR pHVar4;
  int *piVar5;
  float10 fVar6;
  float fVar7;
  byte local_3c [4];
  int local_38;
  tagRECT local_34;
  int local_24;
  int iStack_20;
  int iStack_1c;
  int iStack_18;
  int local_14 [5];
  
  puVar1 = FUN_00437190(&local_38,local_3c);
  if (local_38 == DAT_004a27d4) {
    return puVar1;
  }
  BVar2 = IsIconic(*(HWND *)(local_38 + 0xc));
  if (BVar2 != 0) {
    iVar3 = FUN_00404c40(*(void **)(local_38 + 0xc),&local_24);
    fVar7 = *(float *)(iVar3 + 0xc);
    hwnd = *(HWND *)(local_38 + 0xc);
    if (hwnd != DAT_004a2430) {
      DAT_004a2430 = hwnd;
      pHVar4 = MonitorFromWindow(hwnd,2);
      FUN_00406610(pHVar4);
      DAT_0049d9e0 = fVar7;
    }
    fVar6 = roundf(DAT_0049d9e0 * _DAT_0048f290);
    return (undefined4 *)(int)fVar6;
  }
  local_34.left = 0;
  local_34.top = 0;
  local_34.right = 0;
  local_34.bottom = 0;
  GetWindowRect(*(HWND *)(local_38 + 0xc),&local_34);
  iStack_1c = local_34.right - local_34.left;
  iStack_18 = local_34.bottom - local_34.top;
  local_24 = local_34.left;
  iStack_20 = local_34.top;
  piVar5 = FUN_0040e3a0(*(HWND *)(local_38 + 0xc),&local_24,local_14,'\0');
  return (undefined4 *)piVar5[3];
}


