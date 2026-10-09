// FUN_004073a0 @ 004073a0 size=73 callers=1

undefined4 __fastcall FUN_004073a0(HWND param_1)

{
  HWND pHVar1;
  HANDLE hObject;
  HWND local_4;
  
  local_4 = param_1;
  pHVar1 = (HWND)IsUserAnAdmin();
  if (pHVar1 == (HWND)0x0) {
    GetWindowThreadProcessId(param_1,(LPDWORD)&local_4);
    pHVar1 = local_4;
    if (local_4 != DAT_004a2454) {
      hObject = OpenProcess(0x400,0,(DWORD)local_4);
      if (hObject == (HANDLE)0x0) {
        return 1;
      }
      pHVar1 = (HWND)CloseHandle(hObject);
    }
  }
  return (uint)pHVar1 & 0xffffff00;
}


