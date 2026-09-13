// FUN_00431110 @ 00431110 size=361 callers=2

HWND FUN_00431110(void)

{
  int iVar1;
  HANDLE hHandle;
  HWND hWnd;
  HMODULE pHVar2;
  HWND hWnd_00;
  UINT Msg;
  WPARAM wParam;
  DWORD DVar3;
  LPARAM lParam;
  WNDCLASSEXA local_30;
  
  hHandle = CreateMutexA((LPSECURITY_ATTRIBUTES)0x0,0,"ACNH-mutex1");
  WaitForSingleObject(hHandle,3000);
  iVar1 = *(int *)(*(int *)ThreadLocalStoragePointer + 4);
  hWnd = *(HWND *)(&DAT_004a2470 + iVar1 * 4);
  if (hWnd == (HWND)0x0) {
    local_30.cbSize = 0x30;
    local_30.style = 0;
    local_30.lpfnWndProc = (WNDPROC)&LAB_00423610;
    local_30.cbClsExtra = 0;
    local_30.cbWndExtra = 0;
    local_30.hInstance = GetModuleHandleA((LPCSTR)0x0);
    local_30.hIcon = (HICON)0x0;
    local_30.hCursor = LoadCursorA((HINSTANCE)0x0,&DAT_00007f00);
    local_30.hbrBackground = (HBRUSH)0x10;
    local_30.lpszMenuName = (LPCSTR)0x0;
    local_30.lpszClassName = "ACNH_mainMsgWin";
    local_30.hIconSm = (HICON)0x0;
    RegisterClassExA(&local_30);
    hWnd = CreateWindowExA(0,"ACNH_mainMsgWin","",0,-32000,-32000,10,10,(HWND)0xfffffffd,(HMENU)0x0,
                           (HINSTANCE)0x0,(LPVOID)0x0);
    *(HWND *)(&DAT_004a2470 + iVar1 * 4) = hWnd;
  }
  else {
    SetWindowPos(hWnd,(HWND)0x0,0,0,0,0,0x1b);
  }
  DVar3 = 0;
  pHVar2 = GetModuleHandleA((LPCSTR)0x0);
  DAT_004a23d0 = SetWindowsHookExA(0xd,FUN_004310d0,pHVar2,DVar3);
  DVar3 = 0;
  pHVar2 = GetModuleHandleA((LPCSTR)0x0);
  DAT_004a23e8 = SetWindowsHookExA(0xe,FUN_004310f0,pHVar2,DVar3);
  lParam = 0;
  wParam = 0;
  Msg = 0x8f3f;
  hWnd_00 = FindWindowExA((HWND)0xfffffffd,(HWND)0x0,"ACNH_mainMsgWin",(LPCSTR)0x0);
  PostMessageA(hWnd_00,Msg,wParam,lParam);
  ReleaseMutex(hHandle);
  CloseHandle(hHandle);
  return hWnd;
}


