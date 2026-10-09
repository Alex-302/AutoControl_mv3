// FUN_00404da0 @ 00404da0 size=140 callers=3

bool FUN_00404da0(void)

{
  HMODULE hModule;
  undefined4 *puVar1;
  char *lpProcName;
  undefined4 local_4;
  
  if (DAT_004a284c != '\0') {
    return true;
  }
  if (DAT_004a24ae != '\0') {
    if (*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a32fc) {
      FUN_0045a219(&DAT_004a32fc);
      if (DAT_004a32fc == -1) {
        lpProcName = "DwmIsCompositionEnabled";
        hModule = LoadLibraryA("Dwmapi.dll");
        DAT_004a2fb4 = GetProcAddress(hModule,lpProcName);
        FUN_0045a1da(&DAT_004a32fc);
      }
    }
    puVar1 = &local_4;
    local_4 = 0;
    (*DAT_004a2fb4)();
    return puVar1 != (undefined4 *)0x0;
  }
  return false;
}


