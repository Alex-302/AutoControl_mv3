// FUN_0041d3c0 @ 0041d3c0 size=200 callers=6

UINT __thiscall FUN_0041d3c0(char param_1,LONG param_2,LONG param_3)

{
  HMENU hMenu;
  POINT Point;
  POINT ptScreen;
  POINT Point_00;
  void *this;
  ushort uVar1;
  int iVar2;
  UINT UVar3;
  HWND hWnd;
  HWND local_10;
  int local_c [2];
  
  if (DAT_004a2998 == 0) {
    if ((DAT_004a299c != (void *)0x0) &&
       (Point_00.y = param_3, Point_00.x = param_2, hWnd = WindowFromPoint(Point_00),
       this = DAT_004a299c, hWnd == *(HWND *)((int)DAT_004a299c + 0x28))) {
      ScreenToClient(hWnd,(LPPOINT)&param_2);
      uVar1 = FUN_0041c900(this,param_2,param_3);
      if (uVar1 != 0xffff) {
        return *(UINT *)(*(int *)((int)this + 0xc) + (uint)uVar1 * 0x14);
      }
    }
  }
  else {
    Point.y = param_3;
    Point.x = param_2;
    local_10 = WindowFromPoint(Point);
    FUN_00435ec0(local_c,(byte *)&local_10);
    if (((local_c[0] != DAT_004a24b4) && (hMenu = *(HMENU *)(local_c[0] + 0xc), hMenu != (HMENU)0x0)
        ) && (ptScreen.y = param_3, ptScreen.x = param_2,
             iVar2 = MenuItemFromPoint((HWND)0x0,hMenu,ptScreen), -1 < iVar2)) {
      UVar3 = FUN_0041d300(hMenu,(ushort)iVar2);
      if (param_1 != '\0') {
        return UVar3;
      }
      if (-1 < (int)UVar3) {
        return UVar3;
      }
    }
  }
  return 0;
}


