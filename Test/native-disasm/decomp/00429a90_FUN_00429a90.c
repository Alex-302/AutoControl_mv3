// FUN_00429a90 @ 00429a90 size=166 callers=1

void __fastcall FUN_00429a90(int *param_1)

{
  bool bVar1;
  int *piVar2;
  HWND hWnd;
  BOOL BVar3;
  
  piVar2 = DAT_004a2514;
  do {
    if (piVar2 == DAT_004a2518) {
LAB_00429aca:
      FUN_00432e80(&DAT_004a2514,param_1);
      FUN_0040ea50((HWND)*param_1,(char)param_1[1]);
      hWnd = GetForegroundWindow();
      BVar3 = IsWindowVisible(hWnd);
      if ((BVar3 == 0) || (BVar3 = IsIconic(hWnd), BVar3 != 0)) {
        hWnd = (HWND)0x0;
      }
      else {
        bVar1 = FUN_00404e90(hWnd);
        if (!bVar1) {
          hWnd = GetAncestor(hWnd,3);
        }
      }
      if ((HWND)*param_1 == hWnd) {
        DAT_004a26c5 = 1;
        FUN_00423250(*param_1,'\0');
      }
      FUN_0040f560();
      return;
    }
    if (*piVar2 == *param_1) {
      if ((piVar2 != DAT_004a2518) && (-1 < (int)piVar2 - (int)DAT_004a2514 >> 2)) {
        return;
      }
      goto LAB_00429aca;
    }
    piVar2 = piVar2 + 1;
  } while( true );
}


