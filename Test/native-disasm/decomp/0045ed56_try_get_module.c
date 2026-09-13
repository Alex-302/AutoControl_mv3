// try_get_module @ 0045ed56 size=129 callers=1

/* Library Function - Single Match
    struct HINSTANCE__ * __cdecl try_get_module(enum `anonymous namespace'::module_id)
   
   Library: Visual Studio 2015 Release */

HINSTANCE__ * __cdecl try_get_module(module_id param_1)

{
  uint *puVar1;
  LPCWSTR lpLibFileName;
  uint uVar2;
  HINSTANCE__ *hLibModule;
  DWORD DVar3;
  
  puVar1 = &DAT_0049f4a0 + param_1;
  LOCK();
  uVar2 = *puVar1;
  if (uVar2 == 0) {
    *puVar1 = 0;
    uVar2 = 0;
  }
  UNLOCK();
  if (uVar2 == 0) {
    lpLibFileName = (LPCWSTR)(&PTR_u_advapi32_00483e00)[param_1];
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
        return (HINSTANCE__ *)0x0;
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
    hLibModule = (HINSTANCE__ *)(-(uint)(uVar2 != 0xffffffff) & uVar2);
  }
  return hLibModule;
}


