// FUN_004070b0 @ 004070b0 size=154 callers=2

uint __fastcall FUN_004070b0(undefined4 param_1)

{
  uint uVar1;
  HMODULE hModule;
  short unaff_SI;
  undefined1 *puVar2;
  char *lpProcName;
  undefined1 local_28 [40];
  
  if (*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a336c) {
    FUN_0045a219(&DAT_004a336c);
    if (DAT_004a336c == -1) {
      lpProcName = "IsWow64Process";
      hModule = GetModuleHandleA("kernel32.dll");
      DAT_004a2fb0 = GetProcAddress(hModule,lpProcName);
      FUN_0045a1da(&DAT_004a336c);
    }
  }
  uVar1 = 0;
  if (DAT_004a2fb0 != (FARPROC)0x0) {
    puVar2 = local_28;
    uVar1 = (*DAT_004a2fb0)(param_1);
    if ((uVar1 != 0) && (puVar2 == (undefined1 *)0x0)) {
      GetNativeSystemInfo((LPSYSTEM_INFO)&stack0xffffffd4);
      return (uint)(unaff_SI == 9);
    }
  }
  return uVar1 & 0xffffff00;
}


