// FUN_0041f390 @ 0041f390 size=389 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_0041f390(int param_1)

{
  uint uVar1;
  undefined1 *puVar2;
  uint *puVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  undefined1 local_4c [20];
  tagRECT local_38;
  int *local_24;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  local_14 = 0xffffffff;
  puStack_18 = &LAB_0047ba08;
  local_1c = ExceptionList;
  ExceptionList = &local_1c;
  puVar2 = &stack0xfffffffc;
  if ((DAT_004a29d4 != 0) &&
     (ExceptionList = &local_1c, puVar2 = &stack0xfffffffc, DAT_004a29d4 != DAT_004a243c)) {
    ExceptionList = &local_1c;
    FUN_0041d510(DAT_004a29dc,(ushort)DAT_004a29e0);
    puVar2 = puStack_20;
  }
  puStack_20 = puVar2;
  uVar1 = DAT_004a29d8;
  puVar3 = FUN_0041d6a0(local_4c,*(HMENU *)(param_1 + 8),*(ushort *)(param_1 + 4));
  DAT_004a29d4 = *puVar3;
  DAT_004a29d8 = puVar3[1];
  DAT_004a29dc = (HMENU)puVar3[2];
  DAT_004a29e0 = puVar3[3];
  _DAT_004a29e4 = puVar3[4];
  if ((DAT_004a29d8 != 0) && (DAT_004a29d8 != uVar1)) {
    FUN_0041d5d0(DAT_004a29d8,(HMENU)0x0);
  }
  if ((DAT_004a29d4 == 0) || (DAT_004a29d4 == DAT_004a2520)) {
    DAT_004a29e0 = DAT_004a29e0 & 0xffffff;
  }
  else {
    FUN_00419890(DAT_004a29d4);
    if (DAT_004a29d4 != DAT_004a243c) {
      FUN_0041d510(*(HMENU *)(param_1 + 8),*(ushort *)(param_1 + 4));
    }
    uVar4 = FUN_0041e5a0(&DAT_004a2520,0x4a29d4);
    DAT_004a29e0 = CONCAT13((char)uVar4,(undefined3)DAT_004a29e0);
    piVar5 = operator_new(0x1c);
    local_38.left = 0;
    local_38.top = 0;
    local_38.right = 0;
    local_38.bottom = 0;
    local_24 = piVar5;
    GetMenuItemRect((HWND)0x0,*(HMENU *)(param_1 + 8),(uint)*(ushort *)(param_1 + 4),&local_38);
    piVar5[1] = 1;
    *piVar5 = (int)&PTR_FUN_0048e8a4;
    piVar5[2] = local_38.left;
    piVar5[3] = local_38.top;
    piVar5[4] = local_38.right;
    piVar5[5] = local_38.bottom;
    piVar5[6] = (int)&DAT_004a29d4;
    local_14 = 0;
    local_24 = piVar5;
    iVar6 = FUN_00431f10(piVar5,*(int **)(param_1 + 0xc),(undefined4 *)(param_1 + 0x10));
    if (iVar6 == 0) {
      FUN_00431d80(&local_24);
      ExceptionList = local_1c;
      return 1;
    }
    FUN_00431d80(&local_24);
  }
  ExceptionList = local_1c;
  return 0;
}


