// DloadGetSRWLockFunctionPointers @ 00476fd4 size=123 callers=2

/* Library Function - Single Match
    unsigned char __stdcall DloadGetSRWLockFunctionPointers(void)
   
   Library: Visual Studio 2015 Release */

uchar DloadGetSRWLockFunctionPointers(void)

{
  HMODULE pHVar1;
  uchar uVar2;
  HMODULE hModule;
  FARPROC pFVar3;
  HMODULE pHVar4;
  
  if (DAT_0049fc10 == (HMODULE)0x1) {
    return '\0';
  }
  if (DAT_0049fc10 == (HMODULE)0x0) {
    hModule = GetModuleHandleW(L"KERNEL32.DLL");
    if (((hModule == (HMODULE)0x0) ||
        (pFVar3 = GetProcAddress(hModule,"AcquireSRWLockExclusive"), pFVar3 == (FARPROC)0x0)) ||
       (DAT_0049fc14 = pFVar3, pFVar3 = GetProcAddress(hModule,"ReleaseSRWLockExclusive"),
       pFVar3 == (FARPROC)0x0)) {
      hModule = (HMODULE)0x1;
      pFVar3 = DAT_0049fc18;
    }
    DAT_0049fc18 = pFVar3;
    pHVar4 = (HMODULE)0x0;
    LOCK();
    pHVar1 = hModule;
    if (DAT_0049fc10 != (HMODULE)0x0) {
      pHVar4 = DAT_0049fc10;
      pHVar1 = DAT_0049fc10;
    }
    DAT_0049fc10 = pHVar1;
    UNLOCK();
    if (((pHVar4 == (HMODULE)0x0) && (hModule == (HMODULE)0x1)) || (pHVar4 == (HMODULE)0x1)) {
      uVar2 = '\0';
    }
    else {
      uVar2 = '\x01';
    }
    return uVar2;
  }
  return '\x01';
}


