// FUN_00415b40 @ 00415b40 size=171 callers=1

uint __fastcall FUN_00415b40(POINT *param_1,uint param_2)

{
  HWND pHVar1;
  char cVar2;
  HWND hWnd;
  HWND pHVar3;
  undefined3 extraout_var;
  int iVar4;
  uint uVar5;
  byte *in_stack_ffffffd4;
  UINT gaFlags;
  CHAR local_8 [8];
  
  hWnd = FUN_00404e30(param_1,param_2 == 1);
  pHVar3 = (HWND)GetWindowTextA(hWnd,local_8,2);
  if (pHVar3 == (HWND)0x0) {
    FUN_00404670((int *)&stack0xffffffd4,hWnd);
    cVar2 = FUN_004096c0(in_stack_ffffffd4);
    pHVar3 = (HWND)CONCAT31(extraout_var,cVar2);
    if (cVar2 != '\0') {
      gaFlags = 3;
      pHVar3 = GetForegroundWindow();
      pHVar3 = GetAncestor(pHVar3,gaFlags);
      hWnd = pHVar3;
    }
  }
  pHVar1 = DAT_004a2514;
  if (hWnd != (HWND)0x0) {
    while (pHVar3 = pHVar1, pHVar3 != DAT_004a2518) {
      if ((HWND)pHVar3->unused == hWnd) {
        if (pHVar3 != DAT_004a2518) {
          iVar4 = (int)pHVar3 - (int)DAT_004a2514;
          pHVar3 = (HWND)(iVar4 >> 2);
          if (-1 < (int)pHVar3) {
            if (param_2 == 1) {
              return CONCAT31((int3)(iVar4 >> 10),1);
            }
            uVar5 = FUN_004156f0(param_1,param_2,hWnd);
            return uVar5;
          }
        }
        break;
      }
      pHVar1 = pHVar3 + 1;
    }
  }
  return (uint)pHVar3 & 0xffffff00;
}


