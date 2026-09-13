// FUN_00417860 @ 00417860 size=1330 callers=1

undefined1 __fastcall FUN_00417860(void *param_1,void *param_2,char param_3,char param_4)

{
  char cVar1;
  BOOL BVar2;
  uint *puVar3;
  int *piVar4;
  int iVar5;
  undefined4 uVar6;
  char *this;
  LPWSTR pWVar7;
  undefined4 *puVar8;
  HGLOBAL hMem;
  uint ****ppppuVar9;
  void *pvVar10;
  HANDLE pvVar11;
  void *this_00;
  int iVar12;
  uint uVar13;
  undefined1 local_10c [8];
  int local_104;
  int local_100;
  uint *local_f8;
  uint local_f4 [15];
  int local_b8 [4];
  void *local_a8 [4];
  undefined4 local_98;
  uint local_94;
  void *local_90 [5];
  uint local_7c;
  void *local_78 [4];
  undefined4 local_68;
  uint local_64;
  uint ***local_60;
  undefined4 local_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  int iStack_50;
  uint uStack_4c;
  uint ***local_48 [4];
  int local_38;
  uint local_34;
  void *local_30;
  char *local_2c;
  int local_28;
  uint *local_24;
  int local_20;
  HWND local_1c;
  HANDLE local_18;
  char local_13;
  char local_12;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b194;
  local_10 = ExceptionList;
  iVar12 = 0;
  local_1c = *(HWND *)(&DAT_004a2470 + *(int *)(*(int *)ThreadLocalStoragePointer + 4) * 4);
  ExceptionList = &local_10;
  local_30 = param_2;
  local_18 = param_1;
  do {
    BVar2 = OpenClipboard(local_1c);
    local_12 = BVar2 != 0;
    if ((bool)local_12) break;
    Sleep(10);
    iVar12 = iVar12 + 1;
  } while (iVar12 < 5);
  pvVar10 = local_30;
  local_8 = 0;
  local_8._1_3_ = 0;
  switch(local_30) {
  case (void *)0x1:
    uStack_4c = 7;
    iStack_50 = 0;
    local_60 = (uint ***)((uint)local_60 & 0xffff0000);
    local_8._0_1_ = 1;
    if (param_4 != '\0') {
      FUN_00416c20(&local_12,&local_28,0xd);
      local_8._0_1_ = 2;
      if ((local_28 != 0) && (local_24 != (uint *)0x0)) {
        FUN_00435130(&local_60,local_24);
      }
      local_8._0_1_ = 1;
      FUN_00416a80(&local_28);
    }
    FUN_00440d90(local_18,local_90);
    local_8._0_1_ = 3;
    pWVar7 = FUN_00404640((LPWSTR)local_78,(LPCSTR)local_90);
    local_8 = CONCAT31(local_8._1_3_,4);
    FUN_0043dd10(&local_60,(undefined4 *)pWVar7,0,0xffffffff);
    FUN_00435170(local_78);
    FUN_004061c0(local_90);
    ppppuVar9 = &local_60;
    if (7 < uStack_4c) {
      ppppuVar9 = (uint ****)local_60;
    }
    local_11 = FUN_00416cc0(&local_12,0xd,(uint *)ppppuVar9,iStack_50 * 2 + 2,param_3);
    FUN_00435170(&local_60);
    break;
  default:
    local_11 = 0;
    break;
  case (void *)0x8:
    FUN_00440d90(local_18,local_90);
    local_8._0_1_ = 5;
    puVar3 = FUN_00404220((uint *)local_78,(char *)local_90);
    local_8 = CONCAT31(local_8._1_3_,6);
    piVar4 = FUN_0040a960((int *)&local_1c,puVar3);
    iVar12 = *piVar4;
    local_18 = (HANDLE)0x0;
    iVar5 = GdipCreateHBITMAPFromBitmap(*(undefined4 *)(iVar12 + 4),&local_18,0);
    if (iVar5 != 0) {
      *(int *)(iVar12 + 8) = iVar5;
    }
    if (local_1c != (HWND)0x0) {
      (**(code **)local_1c->unused)(1);
    }
    FUN_004061c0(local_78);
    FUN_004061c0(local_90);
    if ((local_18 == (HANDLE)0x0) || (iVar12 = GetObjectA(local_18,0x54,local_10c), iVar12 == 0)) {
      local_11 = 0;
    }
    else {
      iVar12 = FUN_0040a7f0((int)local_f4);
      uVar13 = iVar12 + local_f4[0];
      FUN_00416a50(&local_28,local_104 * local_100 + uVar13);
      FUN_00416ab0(&local_28,local_f4,uVar13,0);
      FUN_00416ab0(&local_28,local_f8,local_104 * local_100,uVar13);
      if (local_12 == '\0') {
        local_20 = CONCAT31(local_20._1_3_,1);
        local_11 = 0;
        FUN_00416a80(&local_28);
      }
      else {
        uVar6 = FUN_00416c70(local_30,&local_28,param_3);
        local_11 = (undefined1)uVar6;
        FUN_00416a80(&local_28);
      }
    }
    if (local_18 != (HGDIOBJ)0x0) {
      DeleteObject(local_18);
    }
    break;
  case (void *)0xf:
    local_5c = 0x14;
    local_34 = 7;
    local_38 = 0;
    uStack_58 = 0;
    uStack_54 = 0;
    iStack_50 = 0;
    uStack_4c = 0;
    local_48[0] = (uint ***)((uint)local_48[0] & 0xffff0000);
    local_8 = 7;
    FUN_00434120(local_18,&local_2c);
    FUN_004340a0(this_00,local_b8);
    uVar6 = FUN_004383a0(&local_2c,local_b8);
    cVar1 = (char)uVar6;
    iVar12 = 0;
    while (cVar1 == '\0') {
      this = FUN_00433bc0(&local_2c);
      FUN_00440d90(this,local_90);
      local_8._0_1_ = 8;
      pWVar7 = FUN_00404640((LPWSTR)local_78,(LPCSTR)local_90);
      local_8._0_1_ = 9;
      puVar8 = (undefined4 *)FUN_00441c30((undefined2 *)local_a8,pWVar7);
      local_8 = CONCAT31(local_8._1_3_,10);
      FUN_0043dd10(local_48,puVar8,0,0xffffffff);
      if (7 < local_94) {
        FUN_00402430(local_a8[0],local_94 + 1,2);
      }
      local_94 = 7;
      local_a8[0] = (void *)((uint)local_a8[0] & 0xffff0000);
      local_98 = 0;
      if (7 < local_64) {
        FUN_00402430(local_78[0],local_64 + 1,2);
      }
      local_8 = CONCAT31(local_8._1_3_,7);
      local_78[0] = (void *)((uint)local_78[0] & 0xffff0000);
      local_64 = 7;
      local_68 = 0;
      if (0xf < local_7c) {
        FUN_00402430(local_90[0],local_7c + 1,1);
      }
      if (*local_2c == '\x01') {
        local_1c = (HWND)((uint)local_1c & 0xffffff00);
        FUN_00447660(&local_28);
      }
      else if (*local_2c == '\x02') {
        local_24 = local_24 + 4;
      }
      else {
        local_20 = local_20 + 1;
      }
      uVar6 = FUN_004383a0(&local_2c,local_b8);
      iVar12 = local_38;
      cVar1 = (char)uVar6;
    }
    local_1c = (HWND)(iVar12 * 2 + 2);
    hMem = GlobalAlloc(2,iVar12 * 2 + 0x16);
    puVar8 = (undefined4 *)0x0;
    if (hMem != (HGLOBAL)0x0) {
      puVar8 = GlobalLock(hMem);
    }
    local_13 = '\0';
    if (puVar8 != (undefined4 *)0x0) {
      *puVar8 = local_5c;
      puVar8[1] = uStack_58;
      puVar8[2] = uStack_54;
      puVar8[3] = iStack_50;
      puVar8[4] = 1;
    }
    ppppuVar9 = local_48;
    if (7 < local_34) {
      ppppuVar9 = (uint ****)local_48[0];
    }
    if (puVar8 != (undefined4 *)0x0) {
      FUN_0045c870(puVar8 + 5,(uint *)ppppuVar9,(uint)local_1c);
    }
    if (((local_12 == '\0') || (hMem == (HGLOBAL)0x0)) || (puVar8 == (undefined4 *)0x0)) {
LAB_00417d2d:
      local_13 = '\x01';
      local_11 = 0;
    }
    else {
      if (param_3 == '\0') {
        EmptyClipboard();
      }
      pvVar10 = local_30;
      if (local_30 == (void *)0x5b) {
        pvVar10 = DAT_004a26f4;
      }
      pvVar11 = SetClipboardData((UINT)pvVar10,hMem);
      if (pvVar11 == (HANDLE)0x0) goto LAB_00417d2d;
      local_11 = 1;
    }
    if (puVar8 != (undefined4 *)0x0) {
      GlobalUnlock(puVar8);
    }
    if ((hMem != (HGLOBAL)0x0) && (local_13 != '\0')) {
      GlobalFree(hMem);
    }
    if (7 < local_34) {
      FUN_00402430(local_48[0],local_34 + 1,2);
    }
    break;
  case (void *)0x5b:
    FUN_00440d90(local_18,local_48);
    ppppuVar9 = local_48;
    if (0xf < local_34) {
      ppppuVar9 = (uint ****)local_48[0];
    }
    local_11 = FUN_00416cc0(&local_12,(UINT)pvVar10,(uint *)ppppuVar9,local_38 + 1,param_3);
    FUN_004061c0(local_48);
  }
  if (local_12 != '\0') {
    CloseClipboard();
  }
  ExceptionList = local_10;
  return local_11;
}


