// FUN_00406610 @ 00406610 size=228 callers=33

void __fastcall FUN_00406610(undefined4 param_1)

{
  int iVar1;
  HDC hdc;
  HMODULE hModule;
  char *lpProcName;
  int local_c;
  undefined4 local_8;
  int local_4;
  
  local_8 = param_1;
  FUN_00436e20(&local_4,(byte *)&local_8);
  if (local_4 == DAT_004a2804) {
    if ((*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a2b08) &&
       (FUN_0045a219(&DAT_004a2b08), DAT_004a2b08 == -1)) {
      lpProcName = "GetDpiForMonitor";
      hModule = GetModuleHandleA("Shcore.dll");
      DAT_004a2fc4 = GetProcAddress(hModule,lpProcName);
      FUN_0045a1da(&DAT_004a2b08);
    }
    if ((DAT_004a2fc4 == (FARPROC)0x0) ||
       (iVar1 = (*DAT_004a2fc4)(param_1,0,&local_c,&local_c), iVar1 != 0)) {
      hdc = GetDC((HWND)0x0);
      local_c = GetDeviceCaps(hdc,0x58);
      ReleaseDC((HWND)0x0,hdc);
    }
  }
  return;
}


