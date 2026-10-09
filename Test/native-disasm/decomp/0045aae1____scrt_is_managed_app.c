// ___scrt_is_managed_app @ 0045aae1 size=68 callers=2

/* Library Function - Single Match
    ___scrt_is_managed_app
   
   Library: Visual Studio 2015 Release */

uint ___scrt_is_managed_app(void)

{
  HMODULE pHVar1;
  int *piVar2;
  
  pHVar1 = GetModuleHandleW((LPCWSTR)0x0);
  piVar2 = (int *)0x0;
  if ((((pHVar1 != (HMODULE)0x0) && (piVar2 = (int *)0x5a4d, (short)pHVar1->unused == 0x5a4d)) &&
      (piVar2 = (int *)((int)&pHVar1->unused + pHVar1[0xf].unused), *piVar2 == 0x4550)) &&
     (((short)piVar2[6] == 0x10b && (0xe < (uint)piVar2[0x1d])))) {
    return CONCAT31((int3)((uint)piVar2 >> 8),piVar2[0x3a] != 0);
  }
  return (uint)piVar2 & 0xffffff00;
}


