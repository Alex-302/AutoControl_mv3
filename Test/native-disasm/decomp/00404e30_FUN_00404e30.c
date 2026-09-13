// FUN_00404e30 @ 00404e30 size=69 callers=8

HWND __fastcall FUN_00404e30(POINT *param_1,char param_2)

{
  HWND hwnd;
  HWND hwnd_00;
  
  hwnd = GetDesktopWindow();
  hwnd_00 = ChildWindowFromPointEx(hwnd,*param_1,5);
  if (hwnd_00 == hwnd) {
    return (HWND)0x0;
  }
  if (param_2 != '\0') {
    hwnd_00 = GetAncestor(hwnd_00,3);
  }
  return hwnd_00;
}


