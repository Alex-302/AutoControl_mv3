// FUN_0041e220 @ 0041e220 size=387 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_0041e220(char param_1,uint param_2,char param_3)

{
  LONG LVar1;
  LONG LVar2;
  DWORD DVar3;
  HWND pHVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  UINT gaFlags;
  tagPOINT local_90 [2];
  LONG local_80;
  LONG LStack_7c;
  int local_50;
  DWORD local_38 [13];
  
  if (param_3 == '\0') {
    DVar3 = GetTickCount();
    LVar1 = DAT_0049fc38;
    LVar2 = DAT_0049fc3c;
    if (0xf9 < DVar3 - _DAT_0049fc50) {
      GetCursorPos(local_90);
      LVar1 = local_90[0].x;
      LVar2 = local_90[0].y;
    }
  }
  else {
    local_90[0].x = DAT_004a23e0;
    local_90[0].y = DAT_004a23e4;
    LVar1 = local_90[0].x;
    LVar2 = local_90[0].y;
  }
  local_90[0].y = LVar2;
  local_90[0].x = LVar1;
  local_80 = local_90[0].x;
  LStack_7c = local_90[0].y;
  DAT_004a23e0 = local_90[0].x;
  DAT_004a23e4 = local_90[0].y;
  if (param_1 != 'M') {
    if (param_1 == 'W') {
      gaFlags = 3;
      pHVar4 = GetForegroundWindow();
      pHVar4 = GetAncestor(pHVar4,gaFlags);
      piVar5 = (int *)FUN_0040e9b0(pHVar4,'\0',&local_90[0].x);
      iVar8 = *piVar5;
      iVar9 = piVar5[1];
      iVar7 = piVar5[2];
      local_50 = piVar5[3];
    }
    else {
      iVar6 = FUN_00404ba0(&local_80,local_38);
      iVar8 = *(int *)(iVar6 + 0x14);
      iVar9 = *(int *)(iVar6 + 0x18);
      iVar7 = *(int *)(iVar6 + 0x1c);
      local_50 = (int)*(undefined8 *)(iVar6 + 0x20);
    }
    if ((param_2 & 4) == 0) {
      iVar6 = 0;
      if ((param_2 & 8) != 0) {
        iVar6 = iVar7 - iVar8;
      }
    }
    else {
      iVar6 = (iVar7 - iVar8) / 2;
    }
    if ((param_2 & 0x10) == 0) {
      iVar7 = 0;
      if ((param_2 & 0x20) != 0) {
        iVar7 = local_50 - iVar9;
      }
      return CONCAT44(iVar9 + iVar7,iVar8 + iVar6);
    }
    return CONCAT44(iVar9 + (local_50 - iVar9) / 2,iVar8 + iVar6);
  }
  return CONCAT44(local_90[0].y,local_90[0].x);
}


