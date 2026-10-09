// FUN_0040b2d0 @ 0040b2d0 size=328 callers=1

int * __fastcall FUN_0040b2d0(int *param_1)

{
  undefined4 *puVar1;
  BOOL BVar2;
  int *piVar3;
  int iVar4;
  bool bVar5;
  undefined1 *local_170;
  HDC local_16c;
  int local_168;
  undefined4 *local_164;
  undefined4 *local_160;
  UINT local_15c;
  undefined1 local_158 [156];
  undefined1 local_bc [188];
  
  local_168 = *(int *)ThreadLocalStoragePointer;
  iVar4 = *(int *)(local_168 + 4);
  *param_1 = 0;
  local_16c = GetWindowDC(*(HWND *)(&DAT_004a2470 + iVar4 * 4));
  if (local_16c != (HDC)0x0) {
    iVar4 = 4;
    if (DAT_004a24ae != '\0') {
      iVar4 = 0;
    }
    local_15c = 0x158 - iVar4;
    _memset(local_158,0,0x154);
    BVar2 = SystemParametersInfoA(0x29,local_15c,&local_15c,0);
    bVar5 = BVar2 == 0;
    if (bVar5) {
      local_170 = (undefined1 *)0x41000000;
      piVar3 = FUN_00441510(&local_164);
    }
    else {
      local_170 = local_bc;
      piVar3 = FUN_00441490((int *)&local_160,&local_16c,(int *)&local_170);
    }
    if (param_1 != piVar3) {
      iVar4 = *piVar3;
      *piVar3 = 0;
      puVar1 = (undefined4 *)*param_1;
      *param_1 = iVar4;
      if (puVar1 != (undefined4 *)0x0) {
        GdipDeleteFont(*puVar1);
        GdipFree(puVar1);
      }
    }
    if (bVar5) {
      if (local_164 != (undefined4 *)0x0) {
        GdipDeleteFont(*local_164);
        GdipFree(local_164);
      }
    }
    if ((!bVar5) && (local_160 != (undefined4 *)0x0)) {
      GdipDeleteFont(*local_160);
      GdipFree(local_160);
    }
    ReleaseDC(*(HWND *)(&DAT_004a2470 + *(int *)(local_168 + 4) * 4),local_16c);
  }
  return param_1;
}


