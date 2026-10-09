// FUN_0041e910 @ 0041e910 size=502 callers=1

undefined4 __fastcall FUN_0041e910(int param_1)

{
  RECT *lprc;
  int iVar1;
  POINT pt;
  byte bVar2;
  uint uVar3;
  HWND *ppHVar4;
  BOOL BVar5;
  void *this;
  HWND pHVar6;
  byte bVar7;
  undefined **local_54 [9];
  undefined ***local_30;
  HWND *local_2c [2];
  tagPOINT local_24;
  tagPOINT local_1c;
  HWND local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b308;
  local_10 = ExceptionList;
  local_1c.y = *(int *)(param_1 + 0x14);
  DAT_004a243c = *(undefined4 *)(param_1 + 8);
  pHVar6 = (HWND)local_1c.y;
  ExceptionList = &local_10;
  if ((HWND)local_1c.y != DAT_0049fc68) {
    ExceptionList = &local_10;
    local_14 = WindowFromDC(*(HDC *)(param_1 + 0x18));
    if (local_14 != (HWND)0x0) {
      uVar3 = GetWindowLongA(local_14,-0x14);
      SetWindowLongA(local_14,-0x14,uVar3 | 0x2000000);
      pHVar6 = (HWND)local_1c.y;
      DAT_0049fc68 = (HWND)local_1c.y;
      FUN_00435ec0(&local_24.y,(byte *)&local_14);
      ppHVar4 = (HWND *)local_24.y;
      if ((HWND *)local_24.y == DAT_004a24b4) {
        local_24.y = (LONG)&local_14;
        FUN_0044a4d0(this,(int *)local_2c,this,&local_24.y);
        ppHVar4 = local_2c[0];
        pHVar6 = DAT_0049fc68;
      }
      ppHVar4[3] = pHVar6;
    }
    pHVar6 = (HWND)local_1c.y;
  }
  if (DAT_004a2444 == '\0') {
    bVar7 = *(byte *)(param_1 + 0x10) & 1;
  }
  else {
    iVar1 = *(int *)(param_1 + 8);
    if ((iVar1 == DAT_004a2520) ||
       ((iVar1 == DAT_004a29d8 && ((*(byte *)(param_1 + 0x10) & 1) != 0)))) {
      bVar7 = 1;
    }
    else {
      bVar7 = 0;
      if ((iVar1 == DAT_004a29d4) && (DAT_004a29e0._3_1_ != '\0')) {
        local_1c.y._0_1_ = DAT_004a29e4;
        goto LAB_0041ea01;
      }
    }
  }
  local_1c.y._0_1_ = 0;
LAB_0041ea01:
  lprc = (RECT *)(param_1 + 0x1c);
  uVar3 = 0;
  if (bVar7 != 0) {
    uVar3 = 0x80;
  }
  bVar2 = FUN_0041e780(*(uint *)(param_1 + 8),uVar3,pHVar6,*(undefined4 *)(param_1 + 0x18),
                       (int *)lprc,(char)((uint5)local_1c._0_5_ >> 0x20));
  if (((bVar2 != 0) || (DAT_004a2444 != '\0')) &&
     (ExcludeClipRect(*(HDC *)(param_1 + 0x18),lprc->left,*(int *)(param_1 + 0x20),
                      *(int *)(param_1 + 0x24),*(int *)(param_1 + 0x28)), bVar2 != 0)) {
    ExceptionList = local_10;
    return 1;
  }
  iVar1 = *(int *)(param_1 + 8);
  if (bVar7 == 0) {
    if (iVar1 == DAT_004a29c0) {
      DAT_004a29c0 = 0;
      FUN_0041e810();
    }
  }
  else if (DAT_004a29c0 != iVar1) {
    local_1c.x = 0;
    local_1c.y = 0;
    DAT_004a29c0 = iVar1;
    BVar5 = GetDCOrgEx(*(HDC *)(param_1 + 0x18),&local_1c);
    if (BVar5 != 0) {
      GetCursorPos(&local_24);
      pt.y = local_24.y - local_1c.y;
      pt.x = local_24.x - local_1c.x;
      BVar5 = PtInRect(lprc,pt);
      if (BVar5 != 0) {
        FUN_0041e810();
        local_30 = local_54;
        local_54[0] = &PTR_LAB_0048e440;
        local_8 = 0;
        DAT_004a2440 = FUN_0040fd50(500,(int *)local_30);
        FUN_0040fe40((int *)local_54);
      }
    }
  }
  ExceptionList = local_10;
  return 1;
}


