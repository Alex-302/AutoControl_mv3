// FUN_0042aae0 @ 0042aae0 size=90 callers=1

HWND __fastcall FUN_0042aae0(POINT *param_1)

{
  HWND hWnd;
  DWORD DVar1;
  uint dwNewLong;
  HWND pHVar2;
  
  hWnd = FUN_00404e30(param_1,'\0');
  DVar1 = GetWindowThreadProcessId(hWnd,(LPDWORD)0x0);
  if (DVar1 == DAT_004a2450) {
    dwNewLong = GetWindowLongA(hWnd,-0x14);
    SetWindowLongA(hWnd,-0x14,dwNewLong | 0x20);
    pHVar2 = FUN_00404e30(param_1,'\0');
    SetWindowLongA(hWnd,-0x14,dwNewLong);
    return pHVar2;
  }
  return hWnd;
}


