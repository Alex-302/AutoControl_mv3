// FUN_0040ad80 @ 0040ad80 size=173 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_0040ad80(HWND param_1,HDC param_2,uint param_3,int param_4)

{
  ulonglong uVar1;
  BOOL BVar2;
  COLORREF CVar3;
  UINT nFlags;
  int iVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  
  iVar4 = 0;
  nFlags = 0;
  dVar7 = (double)(int)(param_3 * param_4) / _DAT_0048f250;
  if (DAT_004a24ac != '\0') {
    nFlags = 2;
  }
  iVar6 = 0;
  do {
    BVar2 = PrintWindow(param_1,param_2,nFlags);
    if (BVar2 != 0) {
      iVar5 = 0;
      do {
        uVar1 = (ulonglong)(uint)((int)dVar7 + iVar4) % (ulonglong)(param_3 * param_4);
        iVar4 = (int)uVar1;
        CVar3 = GetPixel(param_2,(int)(uVar1 % (ulonglong)param_3),(int)(uVar1 / param_3));
        if (CVar3 != 0) {
          return CONCAT31((int3)(CVar3 >> 8),1);
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < 3);
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 0x1e);
  return 0;
}


