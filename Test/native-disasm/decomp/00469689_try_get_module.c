// try_get_module @ 00469689 size=123 callers=1

/* Library Function - Multiple Matches With Same Base Name
    struct HINSTANCE__ * __cdecl try_get_module(enum `anonymous namespace'::module_id)
    struct HINSTANCE__ * __cdecl try_get_module(enum `anonymous namespace'::module_id)
   
   Library: Visual Studio 2015 Release */

HMODULE __cdecl try_get_module(int param_1)

{
  uint *puVar1;
  uint uVar2;
  LPCWSTR lpLibFileName;
  HMODULE hLibModule;
  DWORD DVar3;
  
  puVar1 = &DAT_0049f820 + param_1;
  uVar2 = *puVar1;
  if (uVar2 == 0) {
    lpLibFileName = (LPCWSTR)(&PTR_u_api_ms_win_appmodel_runtime_l1_1_00485e58)[param_1];
    hLibModule = LoadLibraryExW(lpLibFileName,(HANDLE)0x0,0x800);
    if (hLibModule == (HMODULE)0x0) {
      DVar3 = GetLastError();
      if (DVar3 == 0x57) {
        hLibModule = LoadLibraryExW(lpLibFileName,(HANDLE)0x0,0);
      }
      else {
        hLibModule = (HMODULE)0x0;
      }
      if (hLibModule == (HMODULE)0x0) {
        LOCK();
        *puVar1 = 0xffffffff;
        UNLOCK();
        return (HMODULE)0x0;
      }
    }
    LOCK();
    uVar2 = *puVar1;
    *puVar1 = (uint)hLibModule;
    UNLOCK();
    if (uVar2 != 0) {
      FreeLibrary(hLibModule);
    }
  }
  else {
    hLibModule = (HMODULE)(-(uint)(uVar2 != 0xffffffff) & uVar2);
  }
  return hLibModule;
}


