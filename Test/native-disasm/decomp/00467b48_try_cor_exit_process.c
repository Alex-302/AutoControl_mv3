// try_cor_exit_process @ 00467b48 size=106 callers=2

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    void __cdecl try_cor_exit_process(unsigned int)
   
   Library: Visual Studio 2015 Release */

void __cdecl try_cor_exit_process(uint param_1)

{
  BOOL BVar1;
  FARPROC pFVar2;
  HMODULE local_c;
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  local_c = (HMODULE)0x0;
  BVar1 = GetModuleHandleExW(0,L"mscoree.dll",&local_c);
  if ((BVar1 != 0) && (pFVar2 = GetProcAddress(local_c,"CorExitProcess"), pFVar2 != (FARPROC)0x0)) {
    (*(code *)PTR_guard_check_icall_004805b0)(param_1);
    (*pFVar2)();
  }
  if (local_c != (HMODULE)0x0) {
    FreeLibrary(local_c);
  }
  return;
}


