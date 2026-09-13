// FUN_0040ef60 @ 0040ef60 size=136 callers=1

uint FUN_0040ef60(void)

{
  FILE *_File;
  int iVar1;
  intptr_t iVar2;
  uint uVar3;
  HMODULE hModule;
  char *lpProcName;
  
  uVar3 = DAT_004a33d0;
  if (*(int *)(*(int *)ThreadLocalStoragePointer + 8) < (int)DAT_004a33d0) {
    uVar3 = FUN_0045a219((int *)&DAT_004a33d0);
    if (DAT_004a33d0 == 0xffffffff) {
      lpProcName = "CancelIoEx";
      hModule = GetModuleHandleA("Kernel32.dll");
      DAT_004a3340 = GetProcAddress(hModule,lpProcName);
      uVar3 = FUN_0045a1da((int *)&DAT_004a33d0);
    }
  }
  if (DAT_004a3340 != (FARPROC)0x0) {
    _File = (FILE *)___acrt_iob_func(0);
    iVar1 = __fileno(_File);
    iVar2 = __get_osfhandle(iVar1);
    iVar1 = (*DAT_004a3340)(iVar2,0);
    return (uint)(iVar1 != 0);
  }
  return uVar3 & 0xffffff00;
}


