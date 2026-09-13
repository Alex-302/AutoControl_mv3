// __calloc_base @ 004667b0 size=93 callers=33

/* Library Function - Single Match
    __calloc_base
   
   Library: Visual Studio 2015 Release */

LPVOID __cdecl __calloc_base(uint param_1,uint param_2)

{
  int iVar1;
  LPVOID pvVar2;
  int *piVar3;
  size_t dwBytes;
  
  if ((param_1 == 0) || (param_2 <= 0xffffffe0 / param_1)) {
    dwBytes = param_1 * param_2;
    if (dwBytes == 0) {
      dwBytes = 1;
    }
    do {
      pvVar2 = HeapAlloc(DAT_0049fb20,8,dwBytes);
      if (pvVar2 != (LPVOID)0x0) {
        return pvVar2;
      }
      iVar1 = FUN_00468ddd();
    } while ((iVar1 != 0) && (iVar1 = __callnewh(dwBytes), iVar1 != 0));
  }
  piVar3 = __errno();
  *piVar3 = 0xc;
  return (LPVOID)0x0;
}


