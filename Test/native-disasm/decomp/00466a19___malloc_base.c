// __malloc_base @ 00466a19 size=78 callers=25

/* Library Function - Single Match
    __malloc_base
   
   Library: Visual Studio 2015 Release */

LPVOID __cdecl __malloc_base(size_t param_1)

{
  int iVar1;
  LPVOID pvVar2;
  int *piVar3;
  
  if (param_1 < 0xffffffe1) {
    if (param_1 == 0) {
      param_1 = 1;
    }
    do {
      pvVar2 = HeapAlloc(DAT_0049fb20,0,param_1);
      if (pvVar2 != (LPVOID)0x0) {
        return pvVar2;
      }
      iVar1 = FUN_00468ddd();
    } while ((iVar1 != 0) && (iVar1 = __callnewh(param_1), iVar1 != 0));
  }
  piVar3 = __errno();
  *piVar3 = 0xc;
  return (LPVOID)0x0;
}


