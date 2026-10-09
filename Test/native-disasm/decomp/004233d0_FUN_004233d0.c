// FUN_004233d0 @ 004233d0 size=346 callers=1

void FUN_004233d0(void)

{
  bool bVar1;
  char cVar2;
  HWND hWnd;
  BOOL BVar3;
  uint uVar4;
  DWORD DVar5;
  int iVar6;
  undefined4 uVar7;
  HWND extraout_ECX;
  HWND pHVar8;
  undefined **local_38 [9];
  undefined ***local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047aba8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  hWnd = GetForegroundWindow();
  BVar3 = IsWindowVisible(hWnd);
  if ((BVar3 != 0) && (BVar3 = IsIconic(hWnd), BVar3 == 0)) {
    bVar1 = FUN_00404e90(hWnd);
    if (!bVar1) {
      hWnd = GetAncestor(hWnd,3);
    }
    if (hWnd != (HWND)0x0) {
      if (hWnd == DAT_004a239c) {
        ExceptionList = local_10;
        return;
      }
      DAT_004a239c = hWnd;
      uVar4 = FUN_0040f470((int)hWnd);
      DAT_004a26c5 = (undefined1)uVar4;
      cVar2 = FUN_00409750(extraout_ECX);
      if ((cVar2 == '\0') ||
         ((DAT_004a2460 != 0 &&
          (DVar5 = GetWindowThreadProcessId(hWnd,(LPDWORD)0x0), DAT_004a2460 != DVar5)))) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
      pHVar8 = (HWND)0x0;
      if (bVar1) {
        pHVar8 = hWnd;
      }
      FUN_00423250((int)pHVar8,'\x01');
      if (bVar1) {
        FUN_0040f560();
        ExceptionList = local_10;
        return;
      }
      iVar6 = 0;
      while ((&DAT_004a26b8)[iVar6] == '\0') {
        iVar6 = iVar6 + 1;
        if (9 < iVar6) {
          ExceptionList = local_10;
          return;
        }
      }
      uVar7 = FUN_004073a0(hWnd);
      if ((char)uVar7 == '\0') {
        ExceptionList = local_10;
        return;
      }
      FUN_00412ad0();
      ExceptionList = local_10;
      return;
    }
  }
  local_14 = local_38;
  local_38[0] = &PTR_LAB_0048e858;
  local_8 = 0;
  DAT_004a23f4 = FUN_0040fd50(200,(int *)local_14);
  if (local_14 != (undefined ***)0x0) {
    (*(code *)(*local_14)[4])(local_14 != local_38);
  }
  ExceptionList = local_10;
  return;
}


