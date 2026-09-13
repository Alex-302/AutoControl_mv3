// FUN_00430a70 @ 00430a70 size=442 callers=1

undefined4 FUN_00430a70(void)

{
  int iVar1;
  HANDLE hThread;
  HWND hWndNewViewer;
  HMODULE pHVar2;
  FARPROC pFVar3;
  int iVar4;
  int nPriority;
  char *pcVar5;
  tagMSG local_54;
  WNDCLASSEXA local_38;
  
  LOCK();
  UNLOCK();
  nPriority = -2;
  DAT_004a23dc = DAT_004a2464;
  iVar4 = *(int *)ThreadLocalStoragePointer;
  iVar1 = DAT_004a2464 + 1;
  *(int *)(iVar4 + 4) = DAT_004a2464;
  DAT_004a2464 = iVar1;
  hThread = GetCurrentThread();
  SetThreadPriority(hThread,nPriority);
  iVar4 = *(int *)(iVar4 + 4);
  local_38.cbSize = 0x30;
  local_38.style = 0;
  local_38.lpfnWndProc = FUN_00423920;
  local_38.cbClsExtra = 0;
  local_38.cbWndExtra = 0;
  local_38.hInstance = GetModuleHandleA((LPCSTR)0x0);
  local_38.hIcon = (HICON)0x0;
  local_38.hCursor = LoadCursorA((HINSTANCE)0x0,&DAT_00007f00);
  local_38.hbrBackground = (HBRUSH)0x10;
  local_38.lpszMenuName = (LPCSTR)0x0;
  local_38.lpszClassName = "ACtl.msgWin";
  local_38.hIconSm = (HICON)0x0;
  RegisterClassExA(&local_38);
  hWndNewViewer =
       CreateWindowExA(0,"ACtl.msgWin","",0,-32000,-32000,10,10,(HWND)0xfffffffd,(HMENU)0x0,
                       (HINSTANCE)0x0,(LPVOID)0x0);
  *(HWND *)(&DAT_004a2470 + iVar4 * 4) = hWndNewViewer;
  FUN_00422240('\x01');
  pcVar5 = "AddClipboardFormatListener";
  pHVar2 = GetModuleHandleA("User32.dll");
  pFVar3 = GetProcAddress(pHVar2,pcVar5);
  if (pFVar3 == (FARPROC)0x0) {
    DAT_004a23ec = SetClipboardViewer(hWndNewViewer);
  }
  else {
    (*pFVar3)();
  }
  iVar4 = GetMessageA(&local_54,(HWND)0x0,0,0);
  while (iVar4 != 0) {
    DispatchMessageA(&local_54);
    iVar4 = GetMessageA(&local_54,(HWND)0x0,0,0);
  }
  pcVar5 = "RemoveClipboardFormatListener";
  pHVar2 = GetModuleHandleA("User32.dll");
  pFVar3 = GetProcAddress(pHVar2,pcVar5);
  if (pFVar3 == (FARPROC)0x0) {
    ChangeClipboardChain(hWndNewViewer,DAT_004a23ec);
  }
  else {
    (*pFVar3)(hWndNewViewer);
  }
  FUN_00422ff0();
  if (DAT_004a2398 != '\0') {
    FUN_00411ed0(&DAT_004a28e0);
    FUN_00432210();
    GdiplusShutdown(DAT_004a330c);
    DAT_004a2398 = '\0';
  }
  FUN_004167f0(0);
  return 0;
}


