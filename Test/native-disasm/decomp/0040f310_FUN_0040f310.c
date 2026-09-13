// FUN_0040f310 @ 0040f310 size=343 callers=2

void FUN_0040f310(void)

{
  HWND pHVar1;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  RAWINPUTDEVICE local_c;
  
  local_c.usUsagePage = 1;
  local_c.usUsage = 0;
  local_c.dwFlags = 0x21;
  local_c.hwndTarget = (HWND)0x0;
  RegisterRawInputDevices(&local_c,1,0xc);
  UnhookWindowsHookEx(DAT_004a23d0);
  UnhookWindowsHookEx(DAT_004a23e8);
  PostThreadMessageA(DAT_004a2450,0x12,0,0);
  WaitForSingleObject(DAT_004a23f8,5000);
  pHVar1 = *(HWND *)(&DAT_004a2470 + DAT_004a2458 * 4);
  DeregisterShellHookWindow(pHVar1);
  UnhookWinEvent(DAT_004a23cc);
  UnhookWinEvent(DAT_004a244c);
  DAT_004a2a38 = 0;
  if (DAT_0049fc58 != (HWINEVENTHOOK)0x0) {
    UnhookWinEvent(DAT_0049fc58);
  }
  DestroyWindow(pHVar1);
  lParam = 0;
  wParam = 0;
  Msg = 0x8f3f;
  pHVar1 = FindWindowExA((HWND)0xfffffffd,(HWND)0x0,"ACNH_mainMsgWin",(LPCSTR)0x0);
  PostMessageA(pHVar1,Msg,wParam,lParam);
  FUN_0040ef60();
  if (*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a3380) {
    FUN_0045a219(&DAT_004a3380);
    if (DAT_004a3380 == -1) {
      DAT_004a3358 = CreateFileMappingA((HANDLE)0xffffffff,(LPSECURITY_ATTRIBUTES)0x0,4,0,0xc,
                                        "ACNH_interProcData");
      DAT_004a2e88 = MapViewOfFile(DAT_004a3358,0xf001f,0,0,0);
      FUN_0045a1da(&DAT_004a3380);
    }
  }
  UnmapViewOfFile(DAT_004a2e88);
  CloseHandle(DAT_004a3358);
  return;
}


