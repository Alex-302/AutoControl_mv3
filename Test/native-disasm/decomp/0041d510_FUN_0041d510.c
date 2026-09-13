// FUN_0041d510 @ 0041d510 size=185 callers=8

void __fastcall FUN_0041d510(HMENU param_1,ushort param_2)

{
  POINT Point;
  char cVar1;
  HWND pHVar2;
  BOOL BVar3;
  tagRECT local_30;
  RECT local_20;
  
  local_30.left = 0;
  local_30.top = 0;
  local_30.right = 0;
  local_30.bottom = 0;
  GetMenuItemRect((HWND)0x0,param_1,(uint)param_2,&local_30);
  local_20.left = local_30.left;
  local_20.top = local_30.top;
  local_20.right = local_30.right;
  local_20.bottom = local_30.bottom;
  Point.y = local_30.top;
  Point.x = local_30.left;
  pHVar2 = WindowFromPoint(Point);
  cVar1 = FUN_0041d490(pHVar2);
  if (cVar1 != '\0') {
    DAT_0049fc74 = pHVar2;
  }
  BVar3 = IsWindow(DAT_0049fc74);
  if (BVar3 != 0) {
    local_30.left = 0;
    local_30.top = 0;
    ClientToScreen(DAT_0049fc74,(LPPOINT)&local_30);
    local_20.left = local_20.left - local_30.left;
    local_20.right = local_20.right - local_30.left;
    local_20.top = local_20.top - local_30.top;
    local_20.bottom = local_20.bottom - local_30.top;
    InvalidateRect(DAT_0049fc74,&local_20,0);
  }
  return;
}


