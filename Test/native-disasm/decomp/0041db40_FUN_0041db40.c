// FUN_0041db40 @ 0041db40 size=733 callers=2

void __fastcall FUN_0041db40(HMENU param_1,void *param_2)

{
  byte bVar1;
  int *piVar2;
  int *piVar3;
  char cVar4;
  char *pcVar5;
  undefined4 uVar6;
  HMENU pHVar7;
  HMENU pHVar8;
  void *this;
  int iVar9;
  void *this_00;
  int *piVar10;
  uint uVar11;
  MENUITEMINFOW local_74;
  int local_44 [4];
  char *local_34;
  int *local_30;
  int local_2c;
  int local_28;
  int local_24;
  char *local_20;
  HMENU local_1c;
  HMENU local_18;
  HMENU local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b871;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_18 = param_1;
  local_14 = param_1;
  FUN_00441da0(&local_24,&local_18,param_2);
  pcVar5 = (char *)FUN_00440dd0(param_2,(uint *)"items");
  local_20 = pcVar5;
  FUN_00434120(pcVar5,&local_34);
  FUN_004340a0(this,local_44);
  uVar6 = FUN_004383a0(&local_34,local_44);
  cVar4 = (char)uVar6;
  piVar10 = local_30;
  while (cVar4 == '\0') {
    pcVar5 = FUN_00433bc0(&local_34);
    if (DAT_004a2904 == DAT_004a2908) {
      FUN_004364b0(&DAT_004a2900,1);
    }
    local_1c = DAT_004a2904;
    local_18 = DAT_004a2904;
    local_8 = 0;
    if (DAT_004a2904 != (HMENU)0x0) {
      FUN_00410fb0(DAT_004a2904,pcVar5,param_1);
    }
    DAT_004a2904 = DAT_004a2904 + 10;
    local_8 = 0xffffffff;
    this_00 = (void *)(((int)DAT_004a2904 - DAT_004a2900) / 0x28 + -1);
    local_1c = this_00;
    pHVar7 = (HMENU)FUN_00419890((uint)this_00);
    local_18 = pHVar7;
    if ((pHVar7[9].unused & 0x20000) == 0) {
      pHVar8 = (HMENU)0x0;
    }
    else {
      pHVar8 = FUN_0041dab0(this_00,0xf0000000);
    }
    bVar1 = *(byte *)((int)&pHVar7[9].unused + 2);
    if ((bVar1 & 8) == 0) {
      uVar11 = 0;
    }
    else {
      uVar11 = 0x40;
      if ((bVar1 & 4) != 0) {
        uVar11 = 0x20;
      }
    }
    if (((bVar1 & 8) == 0) && ((bVar1 & 4) != 0)) {
      local_74.cbSize = 0x30;
      _memset(&local_74.fMask,0,0x2c);
      local_74.fMask = 0x127;
      local_74.fType = 0x900;
      local_74.fState = 3;
      local_74.wID = 0xffffffff;
      local_74.hSubMenu = (HMENU)0x0;
      local_74.dwItemData = (ULONG_PTR)local_14;
      InsertMenuItemW(local_14,0xffffffff,1,&local_74);
    }
    local_74.cbSize = 0x30;
    _memset(&local_74.fMask,0,0x2c);
    param_1 = local_14;
    local_74.fType = uVar11 | 0x100;
    local_74.fMask = 0x127;
    local_74.dwItemData = (ULONG_PTR)local_14;
    local_74.fState = -(uint)((local_18[9].unused & 0x10000) != 0) & 3;
    local_74.wID = (UINT)local_1c;
    local_74.hSubMenu = pHVar8;
    InsertMenuItemW(local_14,0xffffffff,1,&local_74);
    if (*local_34 == '\x01') {
      if (*(char *)((int)piVar10 + 0xd) == '\0') {
        piVar2 = (int *)piVar10[2];
        if (*(char *)((int)piVar2 + 0xd) == '\0') {
          cVar4 = *(char *)(*piVar2 + 0xd);
          piVar10 = piVar2;
          piVar2 = (int *)*piVar2;
          while (local_30 = piVar10, cVar4 == '\0') {
            cVar4 = *(char *)(*piVar2 + 0xd);
            piVar10 = piVar2;
            piVar2 = (int *)*piVar2;
          }
        }
        else {
          cVar4 = *(char *)(piVar10[1] + 0xd);
          piVar3 = (int *)piVar10[1];
          piVar2 = piVar10;
          while ((piVar10 = piVar3, local_30 = piVar10, cVar4 == '\0' &&
                 (piVar2 == (int *)piVar10[2]))) {
            cVar4 = *(char *)(piVar10[1] + 0xd);
            piVar3 = (int *)piVar10[1];
            piVar2 = piVar10;
          }
        }
      }
    }
    else if (*local_34 == '\x02') {
      local_2c = local_2c + 0x10;
    }
    else {
      local_28 = local_28 + 1;
    }
    uVar6 = FUN_004383a0(&local_34,local_44);
    pcVar5 = local_20;
    cVar4 = (char)uVar6;
  }
  cVar4 = *pcVar5;
  if (cVar4 != '\0') {
    if (cVar4 == '\x01') {
      iVar9 = *(int *)(*(int *)(pcVar5 + 8) + 4);
    }
    else {
      if (cVar4 != '\x02') {
        ExceptionList = local_10;
        return;
      }
      iVar9 = (*(int **)(pcVar5 + 8))[1] - **(int **)(pcVar5 + 8) >> 4;
    }
    if (iVar9 != 0) {
      ExceptionList = local_10;
      return;
    }
  }
  local_74.cbSize = 0x30;
  _memset(&local_74.fMask,0,0x2c);
  local_74.fMask = 0x127;
  local_74.fType = 0x100;
  local_74.fState = 3;
  local_74.wID = 0xfffffffe;
  local_74.hSubMenu = (HMENU)0x0;
  local_74.dwItemData = (ULONG_PTR)param_1;
  InsertMenuItemW(param_1,0xffffffff,1,&local_74);
  ExceptionList = local_10;
  return;
}


